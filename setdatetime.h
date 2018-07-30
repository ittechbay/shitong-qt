#ifndef SETDATETIME_H
#define SETDATETIME_H

#include <QDialog>

namespace Ui {
class setDateTime;
}

class setDateTime : public QDialog
{
    Q_OBJECT

public:
    explicit setDateTime(QWidget *parent = 0);
    ~setDateTime();

private slots:
    void on_timeEdit_dateTimeChanged(const QDateTime &dateTime);

private:
    Ui::setDateTime *ui;
};

#endif // SETDATETIME_H
