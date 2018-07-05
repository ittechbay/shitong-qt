#ifndef DIALOG_PTPCFG_H
#define DIALOG_PTPCFG_H

#include <QDialog>

namespace Ui {
class Dialog_ptpcfg;
}

class Dialog_ptpcfg : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_ptpcfg(QWidget *parent = 0);
    ~Dialog_ptpcfg();

private:
    Ui::Dialog_ptpcfg *ui;
};

#endif // DIALOG_PTPCFG_H
