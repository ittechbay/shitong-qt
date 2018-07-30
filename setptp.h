#ifndef SETPTP_H
#define SETPTP_H

#include <QDialog>

namespace Ui {
class setPTP;
}

class setPTP : public QDialog
{
    Q_OBJECT

public:
    explicit setPTP(QWidget *parent = 0);
    ~setPTP();

private:
    Ui::setPTP *ui;
};

#endif // SETPTP_H
