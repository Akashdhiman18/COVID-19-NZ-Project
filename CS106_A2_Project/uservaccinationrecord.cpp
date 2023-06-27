#include "uservaccinationrecord.h"
#include "ui_uservaccinationrecord.h"
#include "userdashboard.h"
#include<QSqlDatabase>
#include<QSqlError>
#include<QDebug>
#include <QPdfWriter>
#include <QPainter>
#include<QSqlQuery>
#include<QFileDialog>
#include<QMessageBox>

uservaccinationrecord::uservaccinationrecord(int userId,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::uservaccinationrecord),
    m_userId(userId)
{
    ui->setupUi(this);



    QPixmap arrow(":/image/arrowleft.png");
    QIcon icon(arrow);
    ui->backbutton->setIcon(icon);
    ui->backbutton->setIconSize(arrow.rect().size());


    QSqlDatabase database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName("D:/CS106_A2_Project/mycovidnz.sqlite");

    if (!database.open())
    {
        qDebug() << "Error: Unable to open database";
        return;
    }

    QSqlQuery query;
    query.prepare("SELECT name, phoneNumber, email FROM UserRegister WHERE UserID = ?");
    query.addBindValue(m_userId);

    if (query.exec() && query.next())
    {
        QString userName = query.value(0).toString();
        QString phoneNumber = query.value(1).toString();


        ui->name->setText(userName);
        ui->phonenumber->setText(phoneNumber);

    }
    query.prepare("SELECT qrCode, vaccinationTime, vaccinationDate,vaccinationStatus FROM VaccinationRecords WHERE userid = ?");
    query.addBindValue(m_userId);

    if (query.exec() && query.next())
    {


        QString qrCodeFilePath = ":/image/nzcp.png";

        QPixmap qrCodeImage(qrCodeFilePath);
        QPixmap scaledQrCodeImage = qrCodeImage.scaled(ui->qrcode->size(), Qt::KeepAspectRatio);

        ui->qrcode->setPixmap(scaledQrCodeImage);
        ui->qrcode->setAlignment(Qt::AlignCenter);
        QString date = query.value(3).toString();
        QString vaccination=query.value(2).toString();


        ui->time->setText(date);
        ui->vaccinationstatus->setText(vaccination);
    }
}

uservaccinationrecord::~uservaccinationrecord()
{
    delete ui;
}

void uservaccinationrecord::on_pushButton_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save Certificate", QString(), "PDF Files (*.pdf)");

    if (!fileName.isEmpty())
    {
        // Create a PDF writer
        QPdfWriter pdfWriter(fileName);
        pdfWriter.setPageSize(QPageSize(QPageSize::A4));
        pdfWriter.setPageOrientation(QPageLayout::Portrait);

        QPainter painter(&pdfWriter);


        QFont titleFont("Arial", 18, QFont::Bold);
        QFont regularFont("Arial", 12);


        QString userName, phoneNumber, email;

        QString vaccinationStatus, qrCodeFilePath, vaccinationDate, vaccinationTime;

        QPixmap qrCodeImage(qrCodeFilePath);
        QPixmap scaledQrCodeImage = qrCodeImage.scaled(200, 200, Qt::KeepAspectRatio);


        painter.setFont(titleFont);
        painter.drawText(50, 50, "Vaccination Certificate");

        painter.setFont(regularFont);
        painter.drawText(50, 100, "Name: " + userName);
        painter.drawText(50, 120, "Phone Number: " + phoneNumber);
        painter.drawText(50, 140, "Email: " + email);
        painter.drawText(50, 160, "Vaccination Status: " + vaccinationStatus);
        painter.drawText(50, 180, "Vaccination Date: " + vaccinationDate);
        painter.drawText(50, 200, "Vaccination Time: " + vaccinationTime);
        painter.drawText(50, 220, "QR Code:");

        // Draw the scaled QR code image
        painter.drawPixmap(50, 240, scaledQrCodeImage);

        // Finish painting
        painter.end();

        QMessageBox::information(this, "Download Successful", "Certificate downloaded successfully.");
    }
}


void uservaccinationrecord::on_backbutton_clicked()
{
    userdashboard *user=new userdashboard(m_userId,parentWidget());
    user->show();
    this->close();

}

