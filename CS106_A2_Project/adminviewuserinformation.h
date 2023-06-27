#ifndef ADMINVIEWUSERINFORMATION_H
#define ADMINVIEWUSERINFORMATION_H

#include <QDialog>

namespace Ui {
class adminviewuserinformation;
}

class adminviewuserinformation : public QDialog
{
    Q_OBJECT

public:
    explicit adminviewuserinformation(QWidget *parent = nullptr);
    ~adminviewuserinformation();

private:
    Ui::adminviewuserinformation *ui;
};

#endif // ADMINVIEWUSERINFORMATION_H
