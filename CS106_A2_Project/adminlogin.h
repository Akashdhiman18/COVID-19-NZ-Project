#ifndef ADMINLOGIN_H
#define ADMINLOGIN_H

#include <QDialog>

namespace Ui {
class adminlogin;
}

class adminlogin : public QDialog
{
    Q_OBJECT

public:
    explicit adminlogin(QWidget *parent = nullptr);
    ~adminlogin();

private slots:

    void on_backbutton_2_clicked();

    void on_adminloginbutton_clicked();

private:
    Ui::adminlogin *ui;
};

#endif // ADMINLOGIN_H
