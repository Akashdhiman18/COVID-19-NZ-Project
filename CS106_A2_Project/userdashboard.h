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



    void on_pushButton_3_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::userdashboard *ui;
     int m_userId;
};

#endif // USERDASHBOARD_H
