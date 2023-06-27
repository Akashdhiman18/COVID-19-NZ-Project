#ifndef COVIDNEGATIVERESULT_H
#define COVIDNEGATIVERESULT_H

#include <QDialog>

namespace Ui {
class covidnegativeresult;
}

class covidnegativeresult : public QDialog
{
    Q_OBJECT

private:
    int m_userId;
public:
    explicit covidnegativeresult(int userId ,QWidget *parent = nullptr);
    ~covidnegativeresult();

private slots:
    void on_pushButton_1_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::covidnegativeresult *ui;
};

#endif // COVIDNEGATIVERESULT_H
