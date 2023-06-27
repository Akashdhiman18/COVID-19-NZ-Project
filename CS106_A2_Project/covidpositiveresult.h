#ifndef COVIDPOSITIVERESULT_H
#define COVIDPOSITIVERESULT_H

#include <QDialog>

class usercovidlist;

namespace Ui {
class covidpositiveresult;
}

class covidpositiveresult : public QDialog
{
    Q_OBJECT
private:
    int m_userId;

public:
    explicit covidpositiveresult(int userId, QWidget* parent = nullptr);

    ~covidpositiveresult();

private slots:
    void on_pushButton_clicked();

private:
    Ui::covidpositiveresult *ui;
};

#endif // COVIDPOSITIVERESULT_H
