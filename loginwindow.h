#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class LoginWindow; }
QT_END_NAMESPACE

class LoginWindow : public QWidget {
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = nullptr);
    ~LoginWindow();

signals:
    void loginSuccessful(const QString &username);

private slots:
    void on_loginButton_clicked();

private:
    Ui::LoginWindow *ui;
    void authenticateUser(const QString &username, const QString &password);
};

#endif // LOGINWINDOW_H
