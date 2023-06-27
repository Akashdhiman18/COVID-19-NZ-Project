#ifndef ADMINDASHBOARD_H
#define ADMINDASHBOARD_H

#include <QDialog>

namespace Ui {
class admindashboard;
}

class admindashboard : public QDialog
{
    Q_OBJECT

public:
    explicit admindashboard(QWidget *parent = nullptr);
    ~admindashboard();

private slots:



    void on_covidreport_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::admindashboard *ui;
};

#endif // ADMINDASHBOARD_H
