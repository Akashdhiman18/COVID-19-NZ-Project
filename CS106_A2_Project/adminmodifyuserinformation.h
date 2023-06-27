#ifndef ADMINMODIFYUSERINFORMATION_H
#define ADMINMODIFYUSERINFORMATION_H

#include <QDialog>

namespace Ui {
class adminmodifyuserinformation;
}

class adminmodifyuserinformation : public QDialog
{
    Q_OBJECT

public:
    explicit adminmodifyuserinformation(QWidget *parent = nullptr);
    ~adminmodifyuserinformation();

private slots:
    void on_searchbutton_clicked();

    void on_save_clicked();

    void on_GenQRcode_clicked();

    void on_backbutton_clicked();

private:
    Ui::adminmodifyuserinformation *ui;

};

#endif // ADMINMODIFYUSERINFORMATION_H
