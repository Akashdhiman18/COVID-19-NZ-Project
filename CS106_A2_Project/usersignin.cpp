#include "usersignin.h"
#include "ui_usersignin.h"
#include "userlogin.h"
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

usersignin::usersignin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::usersignin)
{
    ui->setupUi(this);

    QPixmap pix(":/image/signinimg.png");
    ui->label_pick->setPixmap(pix);

    QPixmap arrow(":/image/arrowleft.png");
    QIcon icon(arrow);
    ui->backbutton_2->setIcon(icon);
    ui->backbutton_2->setIconSize(arrow.rect().size());

    connect(ui->signinbutton, &QPushButton::clicked, this, &usersignin::on_signinbutton_clicked);
}

usersignin::~usersignin()
{
    qDebug() << "~ usersignin()";
    delete ui;
}

void usersignin::on_signin_login_clicked()
{
    userlogin* nextScreen = new userlogin(this);
    hide();
    nextScreen->show();
}

void usersignin::on_signinbutton_clicked()
{
    QString fullname = ui->textfullname->text();
    QString email = ui->textemailaddress->text();
    QString phonenumber = ui->textphonenumber->text();
    QString password = ui->textpassword->text();
    if (fullname.isEmpty() || email.isEmpty() || phonenumber.isEmpty() || password.isEmpty())
    {
        QMessageBox::warning(this, "Incomplete Information", "Please fill in all the fields.");
        return;
    }

    if (phonenumber.length() != 12)
    {
        QMessageBox::warning(this, "Invalid Phone Number", "Phone number must be 12 digits long.");
        return;
    }

    if (password.length() < 8)
    {
        QMessageBox::warning(this, "Invalid Password", "Password must be at least 8 characters long.");
        return;
    }
    QSqlDatabase database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName("C:/CS106_A2_Project/mycovidnz.sqlite");

    if (!database.open())
    {
        qDebug() << "Error: Unable to open database";
        return;
    }
    QSqlQuery query;
    query.prepare("SELECT phonenumber, email FROM UserRegister WHERE phonenumber = :phonenumber OR email = :email");
    query.bindValue(":phonenumber", phonenumber);
    query.bindValue(":email", email);
    if (!query.exec())
    {
        qDebug() << "Error executing query: " << query.lastError().text();
        return;
    }
    if (query.next())
    {
        QMessageBox::warning(this, "Duplicate Entry", "Phone number or email already exists. Please choose a different one.");
        return;
    }
    query.prepare("INSERT INTO UserRegister (name, phonenumber, password, email) VALUES (:name, :phonenumber, :password, :email)");
    query.bindValue(":name", fullname);
    query.bindValue(":phonenumber", phonenumber);
    query.bindValue(":password", password);
    query.bindValue(":email", email);

    if (!query.exec()) {
        qDebug() << "Error executing query: " << query.lastError().text();
        return;
    }

    database.close();

    QMessageBox::information(this, "Sign In Successful", "User signed in successfully!");

    ui->textfullname->clear();
    ui->textemailaddress->clear();
    ui->textphonenumber->clear();
    ui->textpassword->clear();
}

void usersignin::on_backbutton_2_clicked()
{
    welcomescreenuser *dashboard = new welcomescreenuser();
    dashboard->show();
    this->close();  // Close the current window
}

