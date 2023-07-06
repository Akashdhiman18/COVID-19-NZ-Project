#include "adminuserinformation.h"
#include "ui_adminuserinformation.h"
#include "admindashboard.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QTextBrowser>

adminuserinformation::adminuserinformation(QWidget* parent) :
    QDialog(parent),
    ui(new Ui::adminuserinformation)
{
    ui->setupUi(this);


    QPixmap arrow(":/image/arrowleft.png");
    QIcon icon(arrow);
    ui->backbutton_2->setIcon(icon);
    ui->backbutton_2->setIconSize(arrow.rect().size());

    QSqlDatabase database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName("C:/CS106_A2_Project/mycovidnz.sqlite");
    if (!database.open())
    {
        qDebug() << "Error: Unable to open database";
        return;
    }

    QSqlQuery query;
    QString queryString = "SELECT * FROM UserRegister";
    if (query.exec(queryString))
    {
        QString data;
        // Iterate over the query results and append the data
        while (query.next())
        {
            QString name = query.value(1).toString();
            QString number = query.value(2).toString();
            QString email = query.value(4).toString();
            QString userid = query.value(0).toString();

            // Format the text with HTML tags
            data += "<b>Name:</b> " + name + "<br>";
            data += "<b>Number:</b> " + number + "<br>";
            data += "<b>Email:</b> " + email + "<br>";
            data += "<b>User ID:</b> " + userid + "<br>";
            data += "---------------------------------<br>";
        }

        ui->textBrowser->setHtml(data);
    }
    else
    {
        // Handle any error that occurred during the query execution
        qDebug() << "Error executing query: " << query.lastError().text();
    }
}

adminuserinformation::~adminuserinformation()
{
    delete ui;
}


void adminuserinformation::on_backbutton_2_clicked()
{
    admindashboard *dashboard = new admindashboard();
    dashboard->show();
    this->close();  // Close the current window
}

