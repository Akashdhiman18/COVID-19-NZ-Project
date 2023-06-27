#ifndef USERSIGNIN_H
#define USERSIGNIN_H

#include <QDialog>

namespace Ui {
class usersignin;
}

class usersignin : public QDialog
{
    Q_OBJECT

public:
    explicit usersignin(QWidget *parent = nullptr);
    ~usersignin();

private slots:
    void on_signin_login_clicked();
    void on_signinbutton_clicked();


    void on_backbutton_2_clicked();

private:
    Ui::usersignin *ui; // Add the ui member variable
};

#endif // USERSIGNIN_H
