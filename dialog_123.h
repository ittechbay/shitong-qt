#ifndef DIALOG_123_H
#define DIALOG_123_H

#include <QDialog>

namespace Ui {
class Dialog_123;
}

class Dialog_123 : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_123(QWidget *parent = 0);
    ~Dialog_123();

private:
    Ui::Dialog_123 *ui;
};

#endif // DIALOG_123_H
