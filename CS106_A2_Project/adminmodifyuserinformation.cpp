#include "adminmodifyuserinformation.h"
#include "ui_adminmodifyuserinformation.h"
#include "admindashboard.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QComboBox>
#include <QImage>
#include <QPixmap>
#include <QBuffer>
#include <QByteArray>
#include<QFile>



adminmodifyuserinformation::adminmodifyuserinformation(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::adminmodifyuserinformation)
{
    ui->setupUi(this);


    QPixmap arrow(":/image/arrowleft.png");
    QIcon icon(arrow);
    ui->backbutton->setIcon(icon);
    ui->backbutton->setIconSize(arrow.rect().size());


    ui->status->addItem("Partial");
    ui->status->addItem("Completed");
    ui->status->addItem("Unvaccinated");
}

adminmodifyuserinformation::~adminmodifyuserinformation()
{
    delete ui;
}

void adminmodifyuserinformation::on_searchbutton_clicked()
{
    QString userID = ui->textuserid->text();

    QSqlDatabase database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName("D:/CS106_A2_Project/mycovidnz.sqlite");

    if (!database.open())
    {
        qDebug() << "Error: Unable to open database";
        return;
    }

    QSqlQuery query;
    query.prepare("SELECT * FROM UserRegister WHERE UserID = ?");
    query.addBindValue(userID);

    if (query.exec() && query.next())
    {
        QString userName = query.value(1).toString();
        QString phoneNumber = query.value(2).toString();
        QString email = query.value(4).toString();

        ui->fullnameedit->setText(userName);
        ui->phonenumberedit->setText(phoneNumber);
        ui->emailedit->setText(email);
    }
    else
    {
        QMessageBox::warning(this, "User Not Found", "No user found with the given ID.");
    }
}

void adminmodifyuserinformation::on_save_clicked()
{
    QString userID = ui->textuserid->text();
    QString userName = ui->fullnameedit->text();
    QString phoneNumber = ui->phonenumberedit->text();
    QString email = ui->emailedit->text();
    QString vaccinationStatus = ui->status->currentText();

    if (userID.isEmpty() || userName.isEmpty() || phoneNumber.isEmpty() || email.isEmpty())
    {
        QMessageBox::warning(this, "Missing Information", "Please fill in all the required fields.");
        return;
    }

    QSqlDatabase database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName("D:/CS106_A2_Project/mycovidnz.sqlite");

    if (!database.open())
    {
        qDebug() << "Error: Unable to open database";
        return;
    }

    QSqlQuery query;
    query.prepare("UPDATE UserRegister SET Name = ?, PhoneNumber = ?, Email = ? WHERE UserID = ?");
    query.addBindValue(userName);
    query.addBindValue(phoneNumber);
    query.addBindValue(email);
    query.addBindValue(userID);

    if (query.exec())
    {
        QMessageBox::information(this, "Update Successful", "User information updated successfully.");
        QString qrCodeFilePath = ":/image/nzcp.png";
        QFile qrCodeFile(qrCodeFilePath);
        if (!qrCodeFile.exists())
        {
            QMessageBox::warning(this, "QR Code Image Not Found", "The QR code image file was not found.");
            return;
        }
        QSqlQuery insertQuery;
        insertQuery.prepare("INSERT INTO VaccinationRecords (userid, vaccinationStatus, qrCode) VALUES (?, ?, ?)");
        insertQuery.addBindValue(userID);
        insertQuery.addBindValue(vaccinationStatus);

        QByteArray qrCodeData;
        if (qrCodeFile.open(QIODevice::ReadOnly))
        {
            qrCodeData = qrCodeFile.readAll();
            qrCodeFile.close();
            insertQuery.addBindValue(qrCodeData);

            if (insertQuery.exec())
            {
                QMessageBox::information(this, "Vaccination Record Updated", "Vaccination record updated successfully.");
            }
            else
            {
                QMessageBox::warning(this, "Update Failed", "Failed to update vaccination record.");
            }
        }
        else
        {
            QMessageBox::warning(this, "QR Code Image Error", "Failed to read the QR code image file.");
        }
    }
}
void adminmodifyuserinformation::on_GenQRcode_clicked()
{
    QPixmap qr("D:/CS106_A2_Project/image/nzcp.png");
    ui->qrCodeLabel->setPixmap(qr);
}
void adminmodifyuserinformation::on_backbutton_clicked()
{
    admindashboard *dashboard = new admindashboard();
    dashboard->show();
    this->close();  // Close the current window
}



