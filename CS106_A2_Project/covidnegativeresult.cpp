#include "covidnegativeresult.h"
#include "ui_covidnegativeresult.h"
#include "userdashboard.h"
#include "uservaccinationrecord.h"
#include<QSqlDatabase>
#include<QDebug>
#include<QSqlQuery>
#include<QSqlError>

covidnegativeresult::covidnegativeresult(int userId,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::covidnegativeresult),
  m_userId(userId)
{
    ui->setupUi(this);
    QPixmap pix(":/image/negative.png");
    ui->label_4->setPixmap(pix);



    QPixmap bg(":/image/cspng.png");
    ui->background->setPixmap(bg);


    QPixmap arrow(":/image/arrow.png");
    QIcon icon(arrow);
    ui->pushButton_3->setIcon(icon);
    ui->pushButton_3->setIconSize(arrow.rect().size());


    QPixmap bg1(":/image/file.png");
    ui->label_12->setPixmap(bg1);



QSqlDatabase database = QSqlDatabase::addDatabase("QSQLITE");
database.setDatabaseName("D:/CS106_A2_Project/mycovidnz.sqlite");

if (!database.open())
{
    qDebug() << "Error: Unable to open database";
    return;
}

QSqlQuery query;
query.prepare("SELECT testtime, testdate, location FROM COVIDTests WHERE userid = :userId ");
query.bindValue(":userId", m_userId);

if (!query.exec())
{
    qDebug() << "Error executing query: " << query.lastError().text();
    return;
}

if (query.next())
{
    QString timed = query.value("testtime").toString();
    QString dated = query.value("testdate").toString();
    QString locationd = query.value("location").toString();

    // Set the labels' text with the retrieved information
    ui->time->setText(timed);
    ui->date->setText("Date :"+dated);
    ui->location->setText("Location :" +locationd);


}


database.close();
}

covidnegativeresult::~covidnegativeresult()
{
    delete ui;
}



void covidnegativeresult::on_pushButton_1_clicked()
{

   userdashboard *dashboards = new userdashboard(m_userId, parentWidget());
   dashboards->show();
   this->close();
}


void covidnegativeresult::on_pushButton_3_clicked()
{
   uservaccinationrecord *user=new uservaccinationrecord(m_userId,parentWidget());
   user->show();
   this->close();
}

