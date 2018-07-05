#ifndef DIALOG_RB_H
#define DIALOG_RB_H

#include <QDialog>

namespace Ui {
class Dialog_rb;
}

class Dialog_rb : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_rb(QWidget *parent = 0);
    ~Dialog_rb();

private:
    Ui::Dialog_rb *ui;
};

#endif // DIALOG_RB_H
