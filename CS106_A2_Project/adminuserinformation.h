#ifndef ADMINUSERINFORMATION_H
#define ADMINUSERINFORMATION_H

#include <QDialog>

namespace Ui {
class adminuserinformation;
}

class adminuserinformation : public QDialog
{
    Q_OBJECT

public:
     explicit adminuserinformation(QWidget *parent = nullptr);
    ~adminuserinformation();
private slots:
    void handleItemClicked(const QModelIndex &index);


    void on_backbutton_2_clicked();

private:
    Ui::adminuserinformation *ui;
};

#endif // ADMINUSERINFORMATION_H
