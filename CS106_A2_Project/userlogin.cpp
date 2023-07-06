#include "userlogin.h"
#include "ui_userlogin.h"
#include "adminlogin.h"
#include "userdashboard.h"
#include <QPixmap>
#include <QFile>
#include <QDateTime>
#include <QTextStream>
#include <QMessageBox>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlDatabase>
#include "databaseheader.h"
#include "welcomescreenuser.h"

userlogin::userlogin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::userlogin)
{
    ui->setupUi(this);

    QPixmap pix(":/image/userlogin.png");
    ui->label_3->setPixmap(pix);

    QPixmap arrow(":/image/arrowleft.png");
    QIcon icon(arrow);
    ui->welcomeScreen->setIcon(icon);
    ui->welcomeScreen->setIconSize(arrow.rect().size());

}

userlogin::~userlogin()
{
    delete ui;
}


void userlogin::on_admin_login_clicked()
{
    // Create an instance of the next screen
    adminlogin* nextScreen = new adminlogin(this);

    // Hide the current screen
    hide();

    // Show the next screen
    nextScreen->show();
}


void userlogin::on_userLogin_clicked()
{
    QString phoneNumber = ui->lineEdit_userUsername->text();
    QString password = ui->lineEdit_userUsername_2->text();

    QSqlDatabase database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName("C:/CS106_A2_Project/mycovidnz.sqlite");

    if (!database.open())
    {
        qDebug() << "Error: Unable to open database";
        return;
    }

    QSqlQuery query;
    query.prepare("SELECT userid, password FROM UserRegister WHERE phonenumber = :phonenumber");
    query.bindValue(":phonenumber", phoneNumber);

    if (!query.exec())
    {
        qDebug() << "Error executing query: " << query.lastError().text();
        return;
    }

    if (query.next())
    {
        QString storedPassword = query.value("password").toString();
        int userId = query.value("userid").toInt();

        if (password == storedPassword)
        {
            // Show a loading message
            QMessageBox loadingMessageBox;
            loadingMessageBox.setIcon(QMessageBox::Information);
            loadingMessageBox.setText("Logging in...");
            loadingMessageBox.setWindowModality(Qt::WindowModal);
            loadingMessageBox.show();

            // Create an instance of the userdashboard screen and pass the user ID
            userdashboard* dashboard = new userdashboard(userId, this);

            // Hide the current screen
            hide();

            // Show the userdashboard screen
            dashboard->show();
        }
        else
        {
            QMessageBox::warning(this, "Login Failed", "Incorrect password. Please try again.");
        }
    }
    else
    {
        QMessageBox::warning(this, "Login Failed", "Phone number not found. Please try again or sign up.");
    }

    database.close();

    // Clear the input fields
    ui->lineEdit_userUsername->clear();
    ui->lineEdit_userUsername_2->clear();
}


void userlogin::on_welcomeScreen_clicked()
{
    welcomescreenuser *dashboard = new welcomescreenuser();
    dashboard->show();
    this->close();  // Close the current window
}

