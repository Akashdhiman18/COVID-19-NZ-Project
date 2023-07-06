#ifndef ADMINCOVIDTESTREPORT_H
#define ADMINCOVIDTESTREPORT_H

#include <QDialog>

namespace Ui {
class admincovidtestreport;
}

class admincovidtestreport : public QDialog
{
    Q_OBJECT

public:
    explicit admincovidtestreport(QWidget *parent = nullptr);
    ~admincovidtestreport();

private slots:
    void on_signinbutton_clicked();


    void on_backbutton_clicked();
    void on_submitCovidreport_clicked();

private:
    Ui::admincovidtestreport *ui;
};

#endif // ADMINCOVIDTESTREPORT_H
