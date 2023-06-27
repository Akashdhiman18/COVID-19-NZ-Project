#include "welcomescreenuser.h"

#include <QTimer>
#include <QApplication>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    welcomescreenuser welcomeScreen;
    welcomeScreen.show();

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("D:/CS106_A2_Project/mycovidnz.sqlite");

    if (!db.open()) {
        qDebug() << "Error: Unable to open database";
        return -1;
    }

    QSqlQuery query(db);

    // Create UserRegister table
    QString createUserRegisterTableQuery = "CREATE TABLE IF NOT EXISTS UserRegister ("
                                           "userid INTEGER PRIMARY KEY AUTOINCREMENT,"
                                           "name TEXT,"
                                           "phonenumber TEXT,"
                                           "password TEXT,"
                                           "email TEXT,"
                                           "registrationdate TEXT DEFAULT CURRENT_TIMESTAMP)";

    if (!query.exec(createUserRegisterTableQuery)) {
        qDebug() << "Error creating UserRegister table: " << query.lastError().text();
        return -1;
    }

    qDebug() << "UserRegister table created successfully";



    // Continue with the rest of the code

    // Create Admin table
    QString createAdminTableQuery = "CREATE TABLE IF NOT EXISTS Adminlogin ("
                                    "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                                    "username TEXT,"
                                    "password TEXT)";

    if (!query.exec(createAdminTableQuery)) {
        qDebug() << "Error creating Admin table: " << query.lastError().text();
        return -1; // Specify a return value to indicate an error
    }

    qDebug() << "Admin table created successfully";




    // Create ReportIssue table
    QString createReportIssueTableQuery = "CREATE TABLE IF NOT EXISTS ReportIssue ("
                                          "issueid INTEGER PRIMARY KEY AUTOINCREMENT,"
                                          "userid INTEGER,"
                                          "issue TEXT,"
                                          "date TEXT DEFAULT CURRENT_TIMESTAMP,"
                                          "FOREIGN KEY (userid) REFERENCES UserRegister(userid),"
                                          "FOREIGN KEY (userid) REFERENCES UserRegister(name),"
                                          "FOREIGN KEY (userid) REFERENCES UserRegister(phonenumber),"
                                          "FOREIGN KEY (userid) REFERENCES UserRegister(email))";


    if (!query.exec(createReportIssueTableQuery)) {
        qDebug() << "Error creating ReportIssue table: " << query.lastError().text();
        return -1;
    }

    qDebug() << "ReportIssue table created successfully";

    // Create the VaccinationRecords table
    QString createTableQuery = "CREATE TABLE VaccinationRecords ("
                               "vcid INTEGER PRIMARY KEY AUTOINCREMENT,"
                               "userid INTEGER,"
                               "vaccinationStatus TEXT,"
                               "vaccinationDate DATE DEFAULT CURRENT_TIMESTAMP,"
                               "vaccinationTime TIME DEFAULT CURRENT_TIMESTAMP,"
                               "qrCode BLOB,"
                               "FOREIGN KEY(userid) REFERENCES UserRegister(userid)"
                               ");";

    if (query.exec(createTableQuery))
    {
        qDebug() << "VaccinationRecords table created successfully.";
    }
    else
    {
        qDebug() << "Error creating VaccinationRecords table: " << query.lastError().text();
    }




    // Create COVIDTests table
    QString createCOVIDTestsTableQuery = "CREATE TABLE IF NOT EXISTS COVIDTests ("
                                         "test_id INTEGER PRIMARY KEY AUTOINCREMENT,"
                                         "userid INTEGER,"
                                         "result TEXT,"
                                         "location TEXT,"
                                         "testdate TEXT DEFAULT CURRENT_DATE,"
                                         "testtime TEXT DEFAULT CURRENT_TIME,"
                                         "FOREIGN KEY (userid) REFERENCES UserRegister(userid))";

    if (!query.exec(createCOVIDTestsTableQuery)) {
        qDebug() << "Error creating COVIDTests table: " << query.lastError().text();
        return -1; // Specify a return value to indicate an error
    }

    qDebug() << "COVIDTests table created successfully";


    db.close();


    return a.exec();
}
