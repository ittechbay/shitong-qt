#ifndef DIALOG_POWER_H
#define DIALOG_POWER_H

#include <QDialog>

namespace Ui {
class Dialog_power;
}

class Dialog_power : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_power(QWidget *parent = 0);
    ~Dialog_power();

private:
    Ui::Dialog_power *ui;
};

#endif // DIALOG_POWER_H
