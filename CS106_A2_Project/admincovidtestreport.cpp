#include "admincovidtestreport.h"
#include "ui_admincovidtestreport.h"
#include "admindashboard.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include<QSqlError>
#include<QMessageBox>

admincovidtestreport::admincovidtestreport(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::admincovidtestreport)
{
    ui->setupUi(this);


    QPixmap arrow(":/image/arrowleft.png");
    QIcon icon(arrow);
    ui->backbutton->setIcon(icon);
    ui->backbutton->setIconSize(arrow.rect().size());
}

admincovidtestreport::~admincovidtestreport()
{
    delete ui;
}

void admincovidtestreport::on_signinbutton_clicked()
{
    int userID = ui->userid->text().toInt();
    QString location = ui->location->text();
    QString testResult;

    if (ui->positive->isChecked()) {
        testResult = "Positive";
    } else if (ui->negative->isChecked()) {
        testResult = "Negative";
    }
    QSqlDatabase database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName("D:/CS106_A2_Project/mycovidnz.sqlite");

    if (!database.open())
    {
        qDebug() << "Error: Unable to open database";
        return;
    }

    // Insert the data into the COVIDTests table
    QSqlQuery query;
    query.prepare("INSERT INTO COVIDTests (userid, location, result) VALUES (:userid, :location, :result)");
    query.bindValue(":userid", userID);
    query.bindValue(":location", location);
    query.bindValue(":result", testResult);

    if (query.exec()) {
        qDebug() << "Data inserted into COVIDTests table successfully";

        // Clear input fields
        ui->userid->clear();
        ui->location->clear();
        ui->positive->setChecked(false);
        ui->negative->setChecked(false);

        // Show message box
        QMessageBox::information(this, "Data Inserted", "Data inserted into COVIDTests table successfully");
    } else {
        qDebug() << "Error inserting data into COVIDTests table: " << query.lastError().text();
        QMessageBox::warning(this, "Error", "Failed to insert data into COVIDTests table");
    }
}



void admincovidtestreport::on_backbutton_clicked()
{

        admindashboard *dashboard = new admindashboard();
        dashboard->show();
        this->close();  // Close the current window

}

