#ifndef USERLOGIN_H
#define USERLOGIN_H

#include <QDialog>

namespace Ui {
class userlogin;
}

class userlogin : public QDialog
{
    Q_OBJECT

public:
    explicit userlogin(QWidget *parent = nullptr);
    ~userlogin();

private slots:


    void on_admin_login_clicked();


    void on_userLogin_clicked();

    void on_welcomeScreen_clicked();

private:
    Ui::userlogin *ui;
};

#endif // USERLOGIN_H
