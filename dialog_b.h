#ifndef DIALOG_B_H
#define DIALOG_B_H

#include <QDialog>

namespace Ui {
class Dialog_b;
}

class Dialog_b : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_b(QWidget *parent = 0);
    ~Dialog_b();

private:
    Ui::Dialog_b *ui;
};

#endif // DIALOG_B_H
