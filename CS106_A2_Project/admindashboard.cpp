#include "admindashboard.h"
#include "ui_admindashboard.h"
#include "admincovidtestreport.h"
#include "adminuserinformation.h"
#include "adminmodifyuserinformation.h"
#include "welcomescreenuser.h"
#include <QPixmap>

admindashboard::admindashboard(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::admindashboard)
{
    ui->setupUi(this);
    QPixmap pix(":/image/admindashboard.png");
    ui->pick->setPixmap(pix);

    QPixmap log(":/image/logout.png");
    ui->label_9->setPixmap(log);

    QPixmap home(":/image/home.png");
    ui->label_4->setPixmap(home);





    QPixmap bg(":/image/cspng.png");
    ui->background_4->setPixmap(bg);

    QPixmap bg1(":/image/cspng.png");
    ui->background_3->setPixmap(bg1);

    QPixmap bg2(":/image/cspng.png");
    ui->background_5->setPixmap(bg2);


    QPixmap img(":/image/file.png");
    ui->label_12->setPixmap(img);

    QPixmap img2(":/image/report.png");
    ui->label_13->setPixmap(img2);

    QPixmap img3(":/image/file.png");
    ui->label_14->setPixmap(img3);



    //arrow
    QPixmap arrow(":/image/arrow.png");
    QIcon icon(arrow);
    ui->modifyUserinformation->setIcon(icon);
    ui->modifyUserinformation->setIconSize(arrow.rect().size());

    QPixmap arrow1(":/image/arrow.png");
    QIcon icon1(arrow1);
    ui->UploadCovidReport->setIcon(icon1);
    ui->UploadCovidReport->setIconSize(arrow1.rect().size());

    QPixmap arrow2(":/image/arrow.png");
    QIcon icon2(arrow2);
    ui->viewUserinformation->setIcon(icon2);
    ui->viewUserinformation->setIconSize(arrow2.rect().size());

}
admindashboard::~admindashboard()
{
    delete ui;
}


void admindashboard::on_viewUserinformation_clicked()
{
    adminuserinformation* nextScreen = new adminuserinformation(this);
    hide();
    nextScreen->show();
}


void admindashboard::on_modifyUserinformation_clicked()
{
    adminmodifyuserinformation* nextScreens = new adminmodifyuserinformation(this);
    hide();
    nextScreens->show();
}


void admindashboard::on_UploadCovidReport_clicked()
{

    admincovidtestreport* nextScreenes = new admincovidtestreport(this);
    hide();
    nextScreenes->show();
}


void admindashboard::on_logoutButton_clicked()
{
    welcomescreenuser *screen = new welcomescreenuser();
    screen->show();
    this->close();  // Close the current window
}

