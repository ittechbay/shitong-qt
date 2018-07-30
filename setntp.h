#ifndef SETNTP_H
#define SETNTP_H

#include <QDialog>

namespace Ui {
class setNTP;
}

class setNTP : public QDialog
{
    Q_OBJECT

public:
    explicit setNTP(QWidget *parent = 0);
    ~setNTP();

private:
    Ui::setNTP *ui;
};

#endif // SETNTP_H
