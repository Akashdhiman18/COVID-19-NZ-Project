#include "adminviewuserinformation.h"
#include "ui_adminviewuserinformation.h"

adminviewuserinformation::adminviewuserinformation(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::adminviewuserinformation)
{
    ui->setupUi(this);
}

adminviewuserinformation::~adminviewuserinformation()
{
    delete ui;
}
