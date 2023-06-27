#include "userdashboard.h"
#include "ui_userdashboard.h"
#include<QSqlDatabase>
#include<QSqlQuery>
#include<QDebug>
#include<QSqlError>
#include "userreportissue.h"
#include "covidpositiveresult.h"
#include "usercovidlist.h"
#include "uservaccinationrecord.h"
#include "welcomescreenuser.h"

userdashboard::userdashboard(int userId, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::userdashboard),
    m_userId(userId) // Initialize the m_userId member variable
{

    ui->setupUi(this);
    QPixmap pix(":/image/dashboard.png");
    ui->pick->setPixmap(pix);


    QPixmap log(":/image/logout.png");
    ui->label_9->setPixmap(log);

    QPixmap home(":/image/home.png");
    ui->label_4->setPixmap(home);

    QPixmap bg(":/image/cspng.png");
    ui->background->setPixmap(bg);

    QPixmap bg1(":/image/cspng.png");
    ui->background_2->setPixmap(bg1);

    QPixmap bg2(":/image/cspng.png");
    ui->background_3->setPixmap(bg2);

    //arrow
    QPixmap arrow(":/image/arrow.png");
    QIcon icon(arrow);
    ui->pushButton_3->setIcon(icon);
    ui->pushButton_3->setIconSize(arrow.rect().size());

    QPixmap arrow1(":/image/arrow.png");
    QIcon icon1(arrow1);
    ui->pushButton_4->setIcon(icon1);
    ui->pushButton_4->setIconSize(arrow1.rect().size());

    QPixmap arrow2(":/image/arrow.png");
    QIcon icon2(arrow2);
    ui->pushButton_5->setIcon(icon2);
    ui->pushButton_5->setIconSize(arrow2.rect().size());

    QPixmap img(":/image/file.png");
    ui->label_12->setPixmap(img);

    QPixmap img2(":/image/report.png");
    ui->label_13->setPixmap(img2);

    QPixmap img3(":/image/file.png");
    ui->label_14->setPixmap(img3);

    // Retrieve user information from the database
    QSqlDatabase database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName("D:/CS106_A2_Project/mycovidnz.sqlite");

    if (!database.open())
    {
        qDebug() << "Error: Unable to open database";
        return;
    }

    QSqlQuery query;
    query.prepare("SELECT name, email, phonenumber FROM UserRegister WHERE userid = :userId");
    query.bindValue(":userId", m_userId);

    if (!query.exec())
    {
        qDebug() << "Error executing query: " << query.lastError().text();
        return;
    }

    if (query.next())
    {
        QString name = query.value("name").toString();
        QString email = query.value("email").toString();
        QString phoneNumber = query.value("phonenumber").toString();

        // Set the labels' text with the retrieved information
        ui->name->setText(name);
        ui->email->setText(email);
        ui->phone->setText(phoneNumber);

        query.prepare("SELECT vaccinationStatus FROM VaccinationRecords WHERE userid = :userId");
        query.bindValue(":userId", m_userId);

        if (!query.exec())
        {
            qDebug() << "Error executing query: " << query.lastError().text();
            return;
        }

        if (query.next())
        {
            QString status = query.value("vaccinationStatus").toString();

            // Set the label's text with the retrieved status
            ui->vacciance->setText("Status: " + status);
        }

    }

    database.close();
}
userdashboard::~userdashboard()
{
    delete ui;
}


void userdashboard::on_pushButton_3_clicked()
{
    usercovidlist* nextScreen = new usercovidlist(m_userId, this);
    hide();
    nextScreen->show();
}


void userdashboard::on_pushButton_5_clicked()
{

    userreportissue* nextScreen = new userreportissue(m_userId,this);
    nextScreen->show();
}


void userdashboard::on_pushButton_4_clicked()
{
    uservaccinationrecord* nextScreen = new uservaccinationrecord(m_userId,this);
    hide();
    nextScreen->show();
}


void userdashboard::on_pushButton_2_clicked()
{
    welcomescreenuser *screen = new welcomescreenuser();
    screen->show();
    this->close();
}

