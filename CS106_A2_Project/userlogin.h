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

    void on_pushButton_clicked();



    void on_admin_login_clicked();

    void on_backbutton_2_clicked();

private:
    Ui::userlogin *ui;
};

#endif // USERLOGIN_H
