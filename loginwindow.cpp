#include "loginwindow.h"
#include "ui_loginwindow.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QDebug>

LoginWindow::LoginWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
    ui->usernameLineEdit->setPlaceholderText(tr("用户名")); // 设置提示文字为“用户名”
    ui->usernameLineEdit->setStyleSheet("background-color: white; color:black;");
    ui->passwordLineEdit->setPlaceholderText(tr("密码")); // 设置提示文字为“密码”
    ui->passwordLineEdit->setStyleSheet("background-color: white; color:black;");
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::on_loginButton_clicked()
{
    QString username = ui->usernameLineEdit->text();
    QString password = ui->passwordLineEdit->text();
    authenticateUser(username, password);
}

void LoginWindow::authenticateUser(const QString &username, const QString &password)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM usernames WHERE username = :username AND password = :password");
    query.bindValue(":username", username);
    query.bindValue(":password", password);
    if (query.exec() && query.next()) {
        emit loginSuccessful(username);
        //qDebug()<<username;
        this->close(); // Close login window
    } else {
        QMessageBox::warning(this, "Login Failed", "username or password is incorrect.");
    }
}
