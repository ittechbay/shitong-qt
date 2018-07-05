#ifndef DIALOG_SWICH_H
#define DIALOG_SWICH_H

#include <QDialog>

namespace Ui {
class Dialog_swich;
}

class Dialog_swich : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_swich(QWidget *parent = 0);
    ~Dialog_swich();

private:
    Ui::Dialog_swich *ui;
};

#endif // DIALOG_SWICH_H
