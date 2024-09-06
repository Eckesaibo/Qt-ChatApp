#include "chatwindow.h"
#include "ui_chatwindow.h"
#include <QFileDialog>
#include <QPixmap>
#include <QTextBrowser>
#include <QFile>
#include <QDataStream>
#include <QTcpSocket>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QTextStream>
#include <QListWidgetItem>
#include <QLabel>
#include <QVBoxLayout>
#include <QTextCursor>
#include <QTextDocument>
#include <QTextCharFormat>
#include <QTextImageFormat>
#include "SocketThread.h"

chatwindow::chatwindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::chatwindow)
{
    ui->setupUi(this);

    // 禁用按钮
    ui->btn1->setEnabled(false);
    ui->sendPhotoButton->setEnabled(false);
    ui->sendFileButton->setEnabled(false);
    ui->receiveFileButton->setEnabled(false);
    ui->voiceInputButton->setEnabled(false);

    QString ip = "127.0.0.1";
    quint16 port = 8888;
    QThread * sub = new QThread;
    SocketThread * worker = new SocketThread;
    worker->moveToThread(sub);
    //连接服务器
    connect(this, &chatwindow::startConnect, worker, &SocketThread::connectServer);
    connect(this, &chatwindow::sendMsgSignal, worker, &SocketThread::sendMsgToServer);
    emit startConnect(port, ip);
    connect(worker, &SocketThread::connectOK, this, [=](){
        qDebug()<<"connection";
    });
    connect(worker, &SocketThread::gameOver, this, [=](){
        sub->quit();
        sub->wait();
        worker->deleteLater();
        sub->deleteLater();  // 线程对象析构
    });
    sub->start();   // 启动子线程
    // 选择联系人
    connect(ui->chatList, &QListWidget::itemClicked, this, &chatwindow::onContactClicked);
    // 发送图片
    connect(ui->sendPhotoButton, &QPushButton::clicked, this, &chatwindow::sendPhotoButton_clicked);
    // 发送文件
    connect(ui->sendFileButton, &QPushButton::clicked, this, &chatwindow::sendFileButton_clicked);
    // 接收文件
    connect(ui->receiveFileButton, &QPushButton::clicked, this, &chatwindow::receiveFileButton_clicked);
    // 语音识别
    connect(ui->voiceInputButton, &QPushButton::pressed, this, &chatwindow::startRecording);
    connect(ui->voiceInputButton, &QPushButton::released, this, &chatwindow::stopRecording);
    connect(worker, &SocketThread::messageReceived, this, &chatwindow::readyRead_slot);

}

chatwindow::~chatwindow() {
    delete ui;
}

void chatwindow::setCurrentUsername(const QString &username) {
    currentusername = username;
    //qDebug() << currentUsername;
}

// 初始化联系人列表
void chatwindow::initializeContactList() {
    QSqlQuery query("SELECT username, avatar_path FROM usernames");

    while (query.next()) {
        QString username = query.value(0).toString();
        QString avatarPath = ":/" + query.value(1).toString();
        if (username == currentusername) {
            continue;
        }

        // 创建一个新的 QWidget 作为项
        QWidget *widget = new QWidget();
        QHBoxLayout *layout = new QHBoxLayout(widget);
        layout->setContentsMargins(10, 10, 10, 10);
        layout->setSpacing(10);

        // 创建 QLabel 显示头像
        QLabel *avatarLabel = new QLabel();
        avatarLabel->setFixedSize(30, 30);
        avatarLabel->setStyleSheet(QString("border-image: url(%1); border-radius: 3px;").arg(avatarPath));
        layout->addWidget(avatarLabel);

        // 创建 QLabel 显示用户名，并设置对象名称
        QLabel *usernameLabel = new QLabel(username);
        usernameLabel->setObjectName("usernameLabel");  // 设置对象名称
        QFont font = usernameLabel->font();
        font.setPointSize(18);
        usernameLabel->setFont(font);
        usernameLabel->setStyleSheet("color: black; background-color: rgba(0,0,0,0)");
        layout->addWidget(usernameLabel);

        // 将 QWidget 设置为 QListWidgetItem 的项
        QListWidgetItem *item = new QListWidgetItem();
        item->setSizeHint(widget->sizeHint());
        ui->chatList->addItem(item);
        ui->chatList->setItemWidget(item, widget);

        widget->setStyleSheet(
            "QWidget::hover { background-color: #c4c4c4; }"   // 鼠标悬停时的背景色
            "QWidget::selected { background-color: #c4c4c4; }" // 项目被选中时的背景色
            );
    }

    if (query.lastError().isValid()) {
        qDebug() << "Error loading contact list: " << query.lastError().text();
    } else {
        qDebug() << "Contact list initialized successfully for user:" << currentusername;
    }
}


//点击联系人
void chatwindow::onContactClicked(QListWidgetItem *item) {
    // 获取与 QListWidgetItem 关联的 QWidget
    QWidget *widget = ui->chatList->itemWidget(item);

    // 从 QWidget 中通过对象名称获取显示用户名的 QLabel
    QLabel *usernameLabel = widget->findChild<QLabel *>("usernameLabel");

    // 确保 QLabel 存在并获取用户名
    QString username;
    if (usernameLabel) {
        username = usernameLabel->text();
    } else {
        qDebug() << "Error: Username label not found!";
        return;
    }

    // 启用发送、发送文件、发送图片、接收文件按钮
    ui->btn1->setEnabled(true);
    ui->sendPhotoButton->setEnabled(true);
    ui->sendFileButton->setEnabled(true);
    ui->receiveFileButton->setEnabled(true);
    ui->voiceInputButton->setEnabled(true);

    // 将聊天窗口的标题设置为当前聊天用户的名字
    ui->chatWindowTitleLabel->setText(username);

    // 清空当前聊天记录
    ui->ui_mag->clear();
    loadChatHistory(currentusername, username);

    // 若有未接收文件则显示
    QSqlQuery query;
    QString received;
    QString sender;

    query.prepare("SELECT received, username FROM files WHERE received = '0' AND username = :username");
    query.bindValue(":username", username);

    if (query.exec() && query.next()) {
        received = query.value(0).toString();
        sender = query.value(1).toString();

        if (received == "0") {
            QListWidgetItem *item = new QListWidgetItem();
            QWidget *fileBubble = createFileBubble(sender + "向你发来了新文件");
            item->setSizeHint(fileBubble->sizeHint());
            ui->ui_mag->addItem(item);
            ui->ui_mag->setItemWidget(item, fileBubble);
        }
    } else {
        qDebug() << "Error retrieving file data from database:" << query.lastError().text();
    }
}

//存储聊天记录
void chatwindow::saveMessageToHistory(const QString &sender, const QString &receiver, const QString &content, const QString &contentType) {
    QSqlQuery query;
    query.prepare("INSERT INTO chat_history (sender, receiver, content, contentType) VALUES (?, ?, ?, ?)");
    query.addBindValue(sender);
    query.addBindValue(receiver);
    query.addBindValue(content);
    query.addBindValue(contentType);
    query.exec();
}

//加载聊天记录
void chatwindow::loadChatHistory(const QString &username1, const QString &username2) {
    QSqlQuery query;
    query.prepare("SELECT sender, receiver, content, contentType FROM chat_history "
                  "WHERE (sender = ? AND receiver = ?) OR (sender = ? AND receiver = ?)");
    query.addBindValue(username1);
    query.addBindValue(username2);
    query.addBindValue(username2);
    query.addBindValue(username1);
    query.exec();
    QString username = ui->chatWindowTitleLabel->text();
    while (query.next()) {
        QString sender = query.value(0).toString();
        QString receiver = query.value(1).toString();
        QString content = query.value(2).toString();
        QString contentType = query.value(3).toString();
        bool isSelf = (currentusername == sender);
        // 使用createMessageBubble或createImageBubble函数来显示消息
        if (contentType == "0") {
            if ((currentusername == sender && username == receiver) || (username == sender && currentusername == receiver)) {
                QListWidgetItem *item = new QListWidgetItem();
                QWidget *messageBubble = createMessageBubble(sender, content, isSelf);
                item->setSizeHint(messageBubble->sizeHint());
                ui->ui_mag->addItem(item);
                ui->ui_mag->setItemWidget(item, messageBubble);
            }
        } else if (contentType == "1") {
            if ((username == sender && currentusername == receiver) || (currentusername == sender && username == receiver)) {
                QListWidgetItem *item = new QListWidgetItem();
                QWidget *imageBubble = createImageBubble(sender, content, isSelf);
                item->setSizeHint(imageBubble->sizeHint());
                ui->ui_mag->addItem(item);
                ui->ui_mag->setItemWidget(item, imageBubble);
            }
        }
    }
}

//有关readyRead槽函数实现
void chatwindow::readyRead_slot(QByteArray msg) {
    QString message = QString::fromLocal8Bit(msg);
    QString username = ui->chatWindowTitleLabel->text();

    QString sender = message.section('#', 1, 1);
    QString receiver = message.section('#', 3, 3);
    QString content = message.section('#', 2, 2);
    QString contentType = message.section('#', 0, 0);
    bool isSelf = (currentusername == sender);
    if(currentusername =="")return;
    if(sender==currentusername)saveMessageToHistory(sender,receiver,content,contentType);
    //0是消息，1是图片，2是文件提示
    if (contentType == "0") {
        if ((currentusername == sender && username == receiver) || (username == sender && currentusername == receiver)) {
            QListWidgetItem *item = new QListWidgetItem();
            QWidget *messageBubble = createMessageBubble(sender, content, isSelf);
            item->setSizeHint(messageBubble->sizeHint());
            ui->ui_mag->addItem(item);
            ui->ui_mag->setItemWidget(item, messageBubble);
        }
    } else if (contentType == "1") {
        if ((username == sender && currentusername == receiver) || (currentusername == sender && username == receiver)) {
            QListWidgetItem *item = new QListWidgetItem();
            QWidget *imageBubble = createImageBubble(sender, content, isSelf);
            item->setSizeHint(imageBubble->sizeHint());
            ui->ui_mag->addItem(item);
            ui->ui_mag->setItemWidget(item, imageBubble);
        }
    } else if (contentType == "2") {
        if(receiver == currentusername)
        {
            QListWidgetItem *item = new QListWidgetItem();
            QWidget *fileBubble = createFileBubble(sender + content);
            item->setSizeHint(fileBubble->sizeHint());
            ui->ui_mag->addItem(item);
            ui->ui_mag->setItemWidget(item, fileBubble);
        }
    }
}

//创建文字气泡
QWidget* chatwindow::createMessageBubble(const QString &username, const QString &message, bool isSelf)
{
    QString avatarPath = getAvatarPathFromUsername(username);

    QWidget *widget = new QWidget();
    QHBoxLayout *layout = new QHBoxLayout(widget);
    layout->setContentsMargins(10, 10, 10, 10);
    layout->setSpacing(10);

    // 设置头像
    QLabel *avatarLabel = new QLabel();
    avatarLabel->setFixedSize(40, 40); // 头像尺寸
    avatarLabel->setStyleSheet(QString("border-image: url(%1); border-radius: 4px;").arg(avatarPath));
    avatarLabel->setObjectName("avatarLabel");

    // 设置消息区域
    QWidget *messageWidget = new QWidget();
    QVBoxLayout *messageLayout = new QVBoxLayout(messageWidget);
    messageLayout->setContentsMargins(0, 0, 0, 0);
    messageLayout->setSpacing(5);

    //设置用户名
    QLabel *usernameLabel = new QLabel(username);
    usernameLabel->setObjectName("usernameLabel");
    QFont font = usernameLabel->font();
    font.setPointSize(8);
    usernameLabel->setFont(font);
    usernameLabel->setStyleSheet("color: black");
    messageLayout->addWidget(usernameLabel);

    //设置消息气泡
    QLabel *messageLabel = new QLabel(message);
    font.setPointSize(12);
    messageLabel->setFont(font);
    messageLabel->setWordWrap(true);
    messageLabel->setStyleSheet(QString("background-color: %1; color: black; border-radius: 10px; padding: 10px;").arg(isSelf ? "#95ec69" : "white"));
    messageLabel->setObjectName("messageLabel");
    messageLayout->addWidget(messageLabel);

    if (isSelf) {
        // 如果是自己发的消息，头像显示在最右边
        QHBoxLayout *rightLayout = new QHBoxLayout();
        rightLayout->addStretch();
        rightLayout->addWidget(messageWidget);
        layout->addLayout(rightLayout);
        layout->addWidget(avatarLabel);
    } else {
        // 如果是别人发的消息，头像显示在最左边
        layout->addWidget(avatarLabel);
        layout->addWidget(messageWidget);
        layout->addStretch();
    }

    widget->setLayout(layout);
    return widget;
}

// 创建图像气泡
QWidget* chatwindow::createImageBubble(const QString &username, const QString &imagePath, bool isSelf)
{
    QString avatarPath = getAvatarPathFromUsername(username);

    QWidget *widget = new QWidget();
    QHBoxLayout *layout = new QHBoxLayout(widget);
    layout->setContentsMargins(10, 10, 10, 10);
    layout->setSpacing(10);

    // 设置头像
    QLabel *avatarLabel = new QLabel();
    avatarLabel->setFixedSize(40, 40); // 头像尺寸
    avatarLabel->setStyleSheet(QString("border-image: url(%1); border-radius: 4px;").arg(avatarPath));
    avatarLabel->setObjectName("avatarLabel");

    // 设置用户名标签
    QLabel *usernameLabel = new QLabel(username);
    QFont font = usernameLabel->font();
    font.setPointSize(8);
    usernameLabel->setFont(font);
    usernameLabel->setStyleSheet("color: black");

    // 设置图片区域
    QLabel *imageLabel = new QLabel();
    QPixmap pixmap(imagePath);
    imageLabel->setPixmap(pixmap.scaled(150, 150, Qt::KeepAspectRatio));
    imageLabel->setStyleSheet("border-radius: 10px;");
    imageLabel->setObjectName("imageLabel");

    // 创建一个垂直布局，用于包含用户名和图片
    QVBoxLayout *imageLayout = new QVBoxLayout();
    imageLayout->setContentsMargins(0, 0, 0, 0);
    imageLayout->setSpacing(5);
    imageLayout->addWidget(usernameLabel);
    imageLayout->addWidget(imageLabel);

    // 将用户名和图片的垂直布局添加到主布局中
    if (isSelf) {
        // 如果是自己发的图片，头像显示在最右边
        layout->addStretch();
        layout->addLayout(imageLayout);
        layout->addWidget(avatarLabel);
    } else {
        // 如果是别人发的图片，头像显示在最左边
        layout->addWidget(avatarLabel);
        layout->addLayout(imageLayout);
    }

    widget->setLayout(layout);
    return widget;
}

//创建文件提示气泡
QWidget* chatwindow::createFileBubble(const QString &content)
{
    QWidget *widget = new QWidget();
    QHBoxLayout *layout = new QHBoxLayout(widget);
    layout->setContentsMargins(10, 10, 10, 10);
    layout->setAlignment(Qt::AlignCenter);  // 居中对齐

    QLabel *fileLabel = new QLabel(content);
    fileLabel->setStyleSheet("background-color: #dadada; color: #fdfdfd; border-radius: 10px; padding: 10px;");

    layout->addWidget(fileLabel);
    widget->setLayout(layout);

    return widget;
}

// 获取头像路径的示例函数
QString chatwindow::getAvatarPathFromUsername(const QString &username)
{
    // 根据用户名从数据库或其他数据源获取头像路径
    QSqlQuery query;
    query.prepare("SELECT avatar_path FROM usernames WHERE username = :username");
    query.bindValue(":username", username);
    if (query.exec() && query.next()) {
        return ":/" + query.value(0).toString();  // 这里假设头像路径是相对路径
    }
    return ":/default_avatar.png";  // 默认头像路径
}

//发送按钮对应的槽函数
void chatwindow::on_btn1_clicked()
{
    //获取ui界面中要发送的文本内容
    QString sendMsg = ui->idt->toPlainText();
    QString username = ui->chatWindowTitleLabel->text();
    //将数据整改
    sendMsg = "0#" + currentusername + "#" + sendMsg + "#" +username;
    //将消息发送给服务器
    //socket->write(sendMsg.toLocal8Bit());
    emit sendMsgSignal(sendMsg);
    //将编辑文本内容清空
    ui->idt->clear();
}

//发送图片按钮
void chatwindow::sendPhotoButton_clicked()
{
    // 打开文件对话框
    QString filePath = QFileDialog::getOpenFileName(this,"选择文件", "", "Images (*.png *.xpm *.jpg *.jpeg *.bmp)");
    qDebug() << "Sending file:" << filePath;
    // 检查是否选择了文件
    if (!filePath.isEmpty()) {
        // 显示文件预览
        QString username = ui->chatWindowTitleLabel->text();
        QString sendMsg = "1#" + currentusername + "#" + filePath + "#" +username;
        //socket->write(sendMsg.toLocal8Bit());
        emit sendMsgSignal(sendMsg);
    }
}

//发送文件按钮
void chatwindow::sendFileButton_clicked()
{
    QString username = ui->chatWindowTitleLabel->text();
    QString filePath = QFileDialog::getOpenFileName(this, "选择文件", "", "Files (*.*)");
    qDebug() << "Sending file:" << filePath;
    // 检查是否选择了文件
    if (!filePath.isEmpty()) {
        // 显示文件预览
        QSqlQuery query;
        // 删除表中的所有数据
        if (!query.exec("DELETE FROM files")) {
            qDebug() << "Error clearing table:" << query.lastError().text();
        } else {
            qDebug() << "Table data cleared successfully.";
        }
        //插入数据
        query.prepare("INSERT INTO files (filepath, received, username) VALUES (:filepath, :received, :username)");
        query.bindValue(":filepath", filePath);
        query.bindValue(":received", "0");
        query.bindValue(":username", currentusername);
        if (!query.exec()) {
            qDebug() << "Error inserting data:" << query.lastError().text();
        } else {
            qDebug() << "Inserted data for filepath:" << filePath;
        }
        QString sendMsg = "2#" + currentusername + "#向你发来了新文件#" +username;
        //socket->write(sendMsg.toLocal8Bit());
        emit sendMsgSignal(sendMsg);
    }
}

//接收文件按钮
void chatwindow::receiveFileButton_clicked() {
    QSqlQuery query;
    QString filePath;
    // 查询文件路径
    query.prepare("SELECT filepath FROM files");
    if (query.exec() && query.next()) {
        filePath = query.value(0).toString();
    } else {
        qDebug() << "Error retrieving file path from database:" << query.lastError().text();
    }

    if (filePath.isEmpty()) {
        qDebug() << "File path is empty. Cannot receive file.";
        return;
    }
    //改为已接收
    query.prepare("UPDATE files SET received = '1' WHERE filepath = :filepath");
    query.bindValue(":filepath", filePath);
    if (!query.exec()) {
        qDebug() << "Error updating file status:" << query.lastError().text();
    } else {
        qDebug() << "File status updated successfully.";
    }
    qDebug()<<filePath;
    QString savePath = QFileDialog::getSaveFileName(this, "Save File As", filePath, "All Files (*.*)");
    if (!savePath.isEmpty()) {
        QFile sourceFile(filePath); // 源文件路径
        QFile destFile(savePath);   // 目标文件路径

        // 打开源文件和目标文件
        if (sourceFile.open(QIODevice::ReadOnly) && destFile.open(QIODevice::WriteOnly)) {
            // 读取数据到缓冲区并写入目标文件
            while (!sourceFile.atEnd()) {
                QByteArray buf = sourceFile.read(1024); // 从源文件读取数据
                qint64 bytesWritten = destFile.write(buf); // 写入数据到目标文件
                if (bytesWritten == -1) {
                    qDebug() << "Error writing to file:" << destFile.errorString();
                    break;
                }
            }
            sourceFile.close(); // 关闭源文件
            destFile.close();   // 关闭目标文件
            qDebug() << "File saved successfully to" << savePath;
        } else {
            qDebug() << "Error opening files:" << sourceFile.errorString() << destFile.errorString();
        }
    } else {
        qDebug() << "Save file operation was canceled.";
    }
}

//开始录音
void chatwindow::startRecording() {
    // 配置音频格式
    QAudioFormat format;
    format.setSampleRate(16000);  // 设置采样率
    format.setChannelCount(1);    // 设置声道数
    format.setSampleFormat(QAudioFormat::Int16); // 设置样本格式

    // 创建音频输入源对象
    audioSource = new QAudioSource(format, this);

    // 打开文件保存录音
    outputFile = new QFile("output.wav");
    if (!outputFile->open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        qDebug() << "Unable to open file for recording";
        return;
    }

    // 开始录音
    audioIODevice = audioSource->start();
    connect(audioIODevice, &QIODevice::readyRead, this, &chatwindow::writeAudioData);
    ui->idt->setText("录音中...");
}

void chatwindow::writeAudioData() {
    if (audioIODevice && outputFile) {
        QByteArray data = audioIODevice->readAll();
        outputFile->write(data);
    }
}

//结束录音
void chatwindow::stopRecording() {
    if (audioSource) {
        // 停止录音
        audioSource->stop();
        outputFile->close();

        delete audioSource;
        delete outputFile;

        audioSource = nullptr;
        outputFile = nullptr;

        ui->idt->setText("录音结束，正在识别...");

        recognizeSpeech();  // 调用语音识别函数
    }
}

//发送录音数据到百度api处理
void chatwindow::recognizeSpeech() {
    QString apiKey = "";//这里删掉了，可以自己去百度智能云平台申请
    QString secretKey = "";

    // 获取百度云的Access Token
    QString tokenUrl = QString("https://aip.baidubce.com/oauth/2.0/token?grant_type=client_credentials&client_id=%1&client_secret=%2")
                           .arg(apiKey).arg(secretKey);

    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    QNetworkRequest request(tokenUrl);
    QNetworkReply *reply = manager->get(request);

    connect(reply, &QNetworkReply::finished, [=]() {
        if (reply->error() == QNetworkReply::NoError) {
            QByteArray response = reply->readAll();
            QJsonDocument jsonDoc = QJsonDocument::fromJson(response);
            QString accessToken = jsonDoc.object().value("access_token").toString();

            // 准备语音识别请求
            QFile audioFile("output.wav");
            if (!audioFile.open(QIODevice::ReadOnly)) {
                qDebug() << "无法打开音频文件";
                return;
            }
            QByteArray audioData = audioFile.readAll();
            audioFile.close();

            QString speechUrl = QString("https://vop.baidu.com/server_api?dev_pid=1537&cuid=baidu_speech_demo&token=%1").arg(accessToken);
            QNetworkRequest speechRequest(speechUrl);
            speechRequest.setHeader(QNetworkRequest::ContentTypeHeader, "audio/pcm;rate=16000");

            QNetworkReply *speechReply = manager->post(speechRequest, audioData);

            connect(speechReply, &QNetworkReply::finished, [=]() {
                if (speechReply->error() == QNetworkReply::NoError) {
                    QByteArray speechResponse = speechReply->readAll();
                    QJsonDocument speechJsonDoc = QJsonDocument::fromJson(speechResponse);
                    QString result = speechJsonDoc.object().value("result").toArray().at(0).toString();
                    ui->idt->setText(result);  // 将识别结果显示在输入框中
                } else {
                    qDebug() << "语音识别请求失败:" << speechReply->errorString();
                }
                speechReply->deleteLater();
            });
        } else {
            qDebug() << "获取Access Token失败:" << reply->errorString();
        }
        reply->deleteLater();
    });
}

void chatwindow::on_backButton_clicked()
{
    this->close();
}

