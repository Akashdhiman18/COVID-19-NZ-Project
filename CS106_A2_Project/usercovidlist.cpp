#include "usercovidlist.h"
#include "ui_usercovidlist.h"
#include "covidpositiveresult.h" // Include the header file for the positiveuser screen
#include "covidnegativeresult.h"
#include "userdashboard.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QListWidgetItem>
#include <QVBoxLayout>
#include <QLabel>
#include <QPixmap>
#include <QDate>
#include <QFrame>
#include <QPalette>
#include<QMessageBox>
#include <QDebug>

usercovidlist::usercovidlist(int userId, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::usercovidlist),
    m_userId(userId)
{
    ui->setupUi(this);

    // Connect to the database
    QSqlDatabase database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName("D:/CS106_A2_Project/mycovidnz.sqlite");

    if (!database.open())
    {
        qDebug() << "Error: Unable to open database";
        return;
    }

    QSqlQuery query;
    QString queryString = "SELECT * FROM COVIDTests WHERE UserID = :userId"; // Filter the query by UserID
    query.prepare(queryString);
    query.bindValue(":userId", m_userId);

    if (query.exec())
    {
        // Clear any existing data in the UI
        ui->listWidget->clear();

        // Initialize the incrementing number
        int testNumber = 1;

        // Iterate over the query results and display the reports in the UI
        while (query.next())
        {
            QString testDate = query.value("TestDate").toString();
            QString result = query.value("Result").toString();

            // Create a custom list item widget
            QWidget* listItemWidget = new QWidget(this);
            QVBoxLayout* listItemLayout = new QVBoxLayout(listItemWidget);
            QFrame* listItemFrame = new QFrame(listItemWidget); // Add a frame for the border
            listItemFrame->setFrameShape(QFrame::Box);
            listItemFrame->setLineWidth(1);
            listItemFrame->setMidLineWidth(0);
            listItemFrame->setContentsMargins(10, 10, 10, 10); // Adjust the margins
            listItemFrame->setStyleSheet("border-radius: 5px; border-color:black;");

            // Add the icon
            QIcon icon(":/image/list.png");
            QLabel* iconLabel = new QLabel(listItemFrame);
            iconLabel->setPixmap(icon.pixmap(30, 30));

            // Add the heading label
            QLabel* headingLabel = new QLabel(listItemFrame);
            headingLabel->setText("<h4>COVID-19 Test " + QString::number(testNumber) + "</h4>");

            // Add the report details
            QLabel* reportLabel = new QLabel(listItemFrame);
            QString reportText = "Date: " + testDate;
            reportLabel->setText(reportText);

            // Add the widgets to the list item layout
            listItemLayout->addWidget(iconLabel);
            listItemLayout->addWidget(headingLabel);
            listItemLayout->addWidget(reportLabel);
            listItemLayout->addStretch();
            listItemLayout->setContentsMargins(0, 0, 0, 0);
            listItemLayout->setSpacing(10);

            listItemFrame->setLayout(listItemLayout);

            // Create a list widget item and set the custom widget as its item widget
            QListWidgetItem* listItem = new QListWidgetItem(ui->listWidget);
            listItem->setSizeHint(listItemFrame->sizeHint());
            listItem->setData(Qt::UserRole, m_userId); // Store the userId in the item's data
            listItem->setData(Qt::UserRole + 1, result); // Store the result in the item's data
            ui->listWidget->setItemWidget(listItem, listItemFrame);

            qDebug() << "Result: " << result;

            // Increment the test number
            testNumber++;
        }

        // Connect the itemClicked signal to the slot function that handles the click event
        connect(ui->listWidget, &QListWidget::itemClicked, this, &usercovidlist::handleItemClick);
    }
    else
    {
        // Handle any error that occurred during the query execution
        qDebug() << "Error executing query: " << query.lastError().text();
    }
}
void usercovidlist::handleItemClick(QListWidgetItem* item)
{
    QString result = item->data(Qt::UserRole + 1).toString();

    qDebug() << "Result: " << result;

    if (result == "Positive")
    {
        // Open the positiveuser screen with the corresponding userId
        covidpositiveresult* positiveUserScreen = new covidpositiveresult(m_userId, this);
        hide();
        positiveUserScreen->show();
    }
    else if (result == "Negative")
    {
        // Open the positiveuser screen with the corresponding userId
        covidnegativeresult* UserScreen = new covidnegativeresult(m_userId, this);
        hide();
        UserScreen->show();
    }
}
usercovidlist::~usercovidlist()
{
    delete ui;
}

void usercovidlist::on_backbutton_2_clicked()
{
//    userdashboard *dashboard = new userdashboard();
//    dashboard->show();
//    this->close();
}

