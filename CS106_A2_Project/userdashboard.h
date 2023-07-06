#ifndef USERDASHBOARD_H
#define USERDASHBOARD_H

#include <QDialog>

namespace Ui {
class userdashboard;
}

class userdashboard : public QDialog
{
    Q_OBJECT

public:
    explicit userdashboard(int userId, QWidget *parent = nullptr);
    ~userdashboard();

private slots:
    void on_label_9_windowIconTextChanged(const QString &iconText);


    void on_COVID19Test_clicked();

    void on_viewVaccine_clicked();

    void on_reportissue_clicked();

    void on_logout_clicked();

private:
    Ui::userdashboard *ui;
     int m_userId;
};

#endif // USERDASHBOARD_H
