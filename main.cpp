#include <QApplication>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QThread>
#include "chatwindow.h"
#include "loginwindow.h"
#include "server.h"

// 初始化数据库
void initializeDatabase() {
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("chatapp.db");
    if (!db.open()) {
        qDebug() << "Error: Unable to open database" << db.lastError().text();
        return;
    }
    QSqlQuery query;
    //文件接收部分
    // if (!query.exec("DROP TABLE IF EXISTS files")) {
    //     qDebug() << "Error deleting table 'files':" << query.lastError().text();
    // } else {
    //     qDebug() << "Table 'files' deleted successfully.";
    // }
    if (!query.exec("CREATE TABLE IF NOT EXISTS files ("
                    "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                    "filepath TEXT NOT NULL,"
                    "received TEXT NOT NULL,"
                    "username TEXT NOT NULL)")) {
        qDebug() << "Error creating table:" << query.lastError().text();
    } else {
        qDebug() << "Table 'files' created successfully.";
    }
    //用户表部分
    if (!query.exec("DROP TABLE IF EXISTS usernames")) {
        qDebug() << "Error deleting table 'usernames':" << query.lastError().text();
    } else {
        qDebug() << "Table 'usernames' deleted successfully.";
    }
    if (!query.exec("CREATE TABLE IF NOT EXISTS usernames ("
                    "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                    "username TEXT NOT NULL,"
                    "password TEXT NOT NULL,"
                    "avatar_path TEXT NOT NULL)")) {
        qDebug() << "Error creating table:" << query.lastError().text();
    } else {
        qDebug() << "Table 'usernames' created successfully.";
    }
    // 删除表中的所有数据
    if (!query.exec("DELETE FROM usernames")) {
        qDebug() << "Error clearing table:" << query.lastError().text();
    } else {
        qDebug() << "Table data cleared successfully.";
    }
    // 插入 username、密码和头像路径
    QStringList usernames = {"张三", "李四", "王五"};
    QStringList avatarPaths = {"1.jpeg", "2.jpeg", "3.jpeg"}; // 对应头像路径
    for (int i = 0; i < usernames.size(); ++i) {
        QString username = usernames[i];
        QString avatarPath = avatarPaths[i];
        QSqlQuery query;
        query.prepare("INSERT INTO usernames (username, password, avatar_path) VALUES (:username, :password, :avatar_path)");
        query.bindValue(":username", username);
        query.bindValue(":password", "123");
        query.bindValue(":avatar_path", avatarPath);
        if (!query.exec()) {
            qDebug() << "Error inserting data:" << query.lastError().text();
        } else {
            qDebug() << "Inserted data for username:" << username << "with avatar path:" << avatarPath;
        }
    }
    //历史记录表部分
    // if (!query.exec("DROP TABLE IF EXISTS chat_history")) {
    //     qDebug() << "Error deleting table 'chat_history':" << query.lastError().text();
    // } else {
    //     qDebug() << "Table 'chat_history' deleted successfully.";
    // }
    if (!query.exec("CREATE TABLE IF NOT EXISTS chat_history ("
            "id INTEGER PRIMARY KEY AUTOINCREMENT,"
            "sender TEXT,"
            "receiver TEXT,"
            "content TEXT,"
            "contentType TEXT)")) {
        qDebug() << "Error creating table:" << query.lastError().text();
    } else {
        qDebug() << "Table 'chat_history' created successfully.";
    }
}

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    // 初始化数据库
    initializeDatabase();

    // 创建对象并将其设置为指针对象
    Server server1;
    server1.start();

    LoginWindow *loginWindow = new LoginWindow();
    chatwindow *chatWindow = new chatwindow();

    // 连接登录成功信号与槽
    QObject::connect(loginWindow, &LoginWindow::loginSuccessful, chatWindow, [chatWindow](const QString &username){
        chatWindow->setCurrentUsername(username);  // 设置当前用户
        qDebug() << username;
        // 初始化联系人列表
        chatWindow->initializeContactList();
        chatWindow->show();
    });

    // 显示登录窗口
    loginWindow->show();

    return a.exec();
}
