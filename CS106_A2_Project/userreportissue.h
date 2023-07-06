#ifndef USERREPORTISSUE_H
#define USERREPORTISSUE_H

#include <QDialog>

namespace Ui {
class userreportissue;
}

class userreportissue : public QDialog
{
    Q_OBJECT
    // Add the following member variable declaration
private:
    int m_userId;

public:
    // Update the constructor definition
    explicit userreportissue(int userId, QWidget *parent = nullptr);
    ~userreportissue();


private slots:

    void on_reportissueSubmit_clicked();

private:
    Ui::userreportissue *ui;
    void logIssueReport(const QString& message);
};

#endif // USERREPORTISSUE_H
