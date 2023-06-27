#include "adminlogin.h"
#include "ui_adminlogin.h"
#include "welcomescreenuser.h"
#include <QMessageBox>
#include <QPixmap>
#include "admindashboard.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include<QSqlError>

adminlogin::adminlogin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::adminlogin)
{
    ui->setupUi(this);
    QPixmap pix(":/image/adminlogin.png");
    ui->label_3->setPixmap(pix);


    QPixmap arrow(":/image/arrowleft.png");
    QIcon icon(arrow);
    ui->backbutton_2->setIcon(icon);
    ui->backbutton_2->setIconSize(arrow.rect().size());
}

adminlogin::~adminlogin()
{
    delete ui;
}

void adminlogin::on_pushButton_clicked()
{
    QString username = ui->lineEdit_userUsername->text();
    QString password = ui->lineEdit_userUsername_2->text();
    QSqlDatabase database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName("D:/CS106_A2_Project/mycovidnz.sqlite");

    if (!database.open())
    {
        qDebug() << "Error: Unable to open database";
        return;
    }

    QSqlQuery query;
    query.prepare("SELECT username, password FROM Adminlogin WHERE username = :username AND password = :password");
    query.bindValue(":username", username);
    query.bindValue(":password", password);

    bool isAdminValid = false;  // Initialize the variable with a default value

    if (query.exec() && query.next()) {
        // Login successful
        qDebug() << "Admin login successful";
        isAdminValid = true;  // Set the variable to indicate successful login
    } else {
        // Login failed
        qDebug() << "Admin login failed: " << query.lastError().text();
        QMessageBox::warning(this, "Login Failed", "Invalid username or password. Please try again.");
    }

    // Check the value of isAdminValid
    if (isAdminValid) {
        // Create a new instance of the admin dashboard
        admindashboard* admin = new admindashboard(this);

        // Close the login window
        close();

        // Show the admin dashboard screen
        admin->show();
    }
}





void adminlogin::on_backbutton_2_clicked()
{
     welcomescreenuser *dashboard = new welcomescreenuser();
    dashboard->show();
    this->close();
}

