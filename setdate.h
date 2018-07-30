#ifndef SETDATE_H
#define SETDATE_H

#include <QWidget>

namespace Ui {
class setDate;
}

class setDate : public QWidget
{
    Q_OBJECT

public:
    explicit setDate(QWidget *parent = 0);
    ~setDate();

private slots:
    void on_pushButton_5_clicked();

private:
    Ui::setDate *ui;
};

#endif // SETDATE_H
