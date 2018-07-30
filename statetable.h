#ifndef STATETABLE_H
#define STATETABLE_H

#include <QTableWidget>

class StateTable : public QTableWidget
{
public:
    StateTable(QWidget *parent = 0);

protected:
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);

};

#endif // STATETABLE_H
