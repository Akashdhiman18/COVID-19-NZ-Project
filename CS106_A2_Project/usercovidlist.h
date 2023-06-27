#ifndef USERCOVIDLIST_H
#define USERCOVIDLIST_H

#include <QDialog>
#include <QListWidgetItem>

namespace Ui {
class usercovidlist;
}

class usercovidlist : public QDialog
{
    Q_OBJECT

private:
    int m_userId;
public:
    explicit usercovidlist(int userId, QWidget *parent = nullptr);
    ~usercovidlist();

private slots:
    void handleItemClick(QListWidgetItem* item);


    void on_backbutton_2_clicked();

private:
    Ui::usercovidlist *ui;
};

#endif // USERCOVIDLIST_H
