#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "dialog_ptpcfg.h"
#include "dialog_clockcfg.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_pressed();

    void on_pushButton_2_clicked();

    void on_Widget_destroyed();

    void on_pushButton_3_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_11_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_20_clicked();

    void on_pushButton_19_clicked();

    void on_pushButton_24_clicked();

private:
    Ui::Widget *ui;
    //Dialog di;
    Dialog_clockcfg di_clk;
    Dialog_ptpcfg di_ptp;
};

#endif // WIDGET_H
