#include "covidpositiveresult.h"
#include "ui_covidpositiveresult.h"
#include "userdashboard.h"
#include<QSqlDatabase>
#include<QSqlQuery>
#include<QDebug>
#include<QSqlError>
#include<QMessageBox>

covidpositiveresult::covidpositiveresult(int userId, QWidget* parent) :
    QDialog(parent),
    ui(new Ui::covidpositiveresult),
    m_userId(userId)
{

     ui->setupUi(this);

     QPixmap pix(":/image/positive.png");
     ui->label_4->setPixmap(pix);


    // Retrieve user information from the database
    QSqlDatabase database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName("C:/CS106_A2_Project/mycovidnz.sqlite");

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


        ui->time->setText(timed);
        ui->date->setText("Date :"+dated);
        ui->location->setText("Location :" +locationd);
    }
    database.close();
}

covidpositiveresult::~covidpositiveresult()
{
    delete ui;
}

void covidpositiveresult::on_pushButton_clicked()
{
     userdashboard *dashboard = new userdashboard(m_userId ,parentWidget());
     dashboard->show();
     this->close();
}

