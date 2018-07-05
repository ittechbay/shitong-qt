#ifndef DIALOG_CLOCKCFG_H
#define DIALOG_CLOCKCFG_H

#include <QDialog>

namespace Ui {
class Dialog_clockcfg;
}

class Dialog_clockcfg : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_clockcfg(QWidget *parent = 0);
    ~Dialog_clockcfg();

private:
    Ui::Dialog_clockcfg *ui;
};

#endif // DIALOG_CLOCKCFG_H
