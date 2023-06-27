#ifndef WELCOMESCREENUSER_H
#define WELCOMESCREENUSER_H

#include <QDialog>

namespace Ui {
class welcomescreenuser;
}

class welcomescreenuser : public QDialog
{
    Q_OBJECT

public:
    explicit welcomescreenuser(QWidget *parent = nullptr);
    ~welcomescreenuser();

private slots:
      void handlePushButtonClicked();

private:
    Ui::welcomescreenuser *ui;
};

#endif // WELCOMESCREENUSER_H
