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


    void on_viewUserinformation_clicked();

    void on_modifyUserinformation_clicked();

    void on_UploadCovidReport_clicked();

    void on_logoutButton_clicked();

private:
    Ui::admindashboard *ui;
};

#endif // ADMINDASHBOARD_H
