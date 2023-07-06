#include "userreportissue.h"
#include "ui_userreportissue.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QFile>
#include <QDateTime>
#include <QMessageLogger>

userreportissue::userreportissue(int userId, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::userreportissue),
    m_userId(userId)
{
    ui->setupUi(this);
}

userreportissue::~userreportissue()
{
    delete ui;
}

void userreportissue::logIssueReport(const QString& message)
{
    QString logFilePath = "issue_report.log";
    QFile file(logFilePath);
    if (file.open(QIODevice::Append | QIODevice::Text))
    {
        QTextStream stream(&file);
        QString timestamp = QDateTime::currentDateTime().toString(Qt::ISODate);
        stream << timestamp << " - User ID: " << m_userId << " - Issue: " << message << "\n";
        file.close();
    }
    else
    {
        QMessageLogger().warning("Failed to open issue report log file.");
    }
}

void userreportissue::on_reportissueSubmit_clicked()
{
    QString issue = ui->lineEdit_userUsername->text();


    QSqlDatabase database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName("C:/CS106_A2_Project/mycovidnz.sqlite");

    if (!database.open())
    {
        QMessageLogger().critical("Error: Unable to open database");
        return;
    }

    QSqlQuery query;
    query.prepare("INSERT INTO ReportIssue (userid, issue) VALUES (:userid, :issue)");
    query.bindValue(":userid", m_userId);
    query.bindValue(":issue", issue);

    if (!query.exec())
    {
        QMessageLogger().warning() << "Error executing query: " << query.lastError().text();
        return;
    }

    QMessageLogger().info() << "Issue reported successfully";

    logIssueReport(issue);

    database.close();


    close();
}

