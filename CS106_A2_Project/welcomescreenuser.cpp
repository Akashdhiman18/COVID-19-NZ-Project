#include "welcomescreenuser.h"
#include "ui_welcomescreenuser.h"
#include<QPixmap>
#include "usersignin.h"

welcomescreenuser::welcomescreenuser(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::welcomescreenuser)
{
    ui->setupUi(this);

    // Connect the button clicked signal to the slot function
    connect(ui->pushButton, &QPushButton::clicked, this, &welcomescreenuser::handlePushButtonClicked);

    QPixmap pix(":/image/welcomescreen.png");
    ui->label_pic->setPixmap(pix);
}


welcomescreenuser::~welcomescreenuser()
{
    delete ui;
}

void welcomescreenuser::handlePushButtonClicked()
{
    // Create an instance of the next screen
    usersignin* nextScreen = new usersignin(this);

    // Hide the current screen
    hide();

    // Show the next screen
    nextScreen->show();
}
