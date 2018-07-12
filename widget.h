#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
//#include "dialog_ptpcfg.h"
//#include "dialog_clockcfg.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    void paintEvent(QPaintEvent *ev);

private slots:






};

#endif // WIDGET_H
