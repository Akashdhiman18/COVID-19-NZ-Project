#ifndef USERVACCINATIONRECORD_H
#define USERVACCINATIONRECORD_H

#include <QDialog>

namespace Ui {
class uservaccinationrecord;
}

class uservaccinationrecord : public QDialog
{
    Q_OBJECT

private:
    int m_userId;
public:
    explicit uservaccinationrecord(int userId,QWidget *parent = nullptr);
    ~uservaccinationrecord();

private slots:
    void on_pushButton_clicked();

    void on_backbutton_clicked();

private:
    Ui::uservaccinationrecord *ui;
};

#endif // USERVACCINATIONRECORD_H
