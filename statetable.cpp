#include "statetable.h"
#include <QDebug>

StateTable::StateTable(QWidget *parent):
QTableWidget(parent)
{

}

void StateTable::mousePressEvent(QMouseEvent *e)
{
    qDebug() << "##test StateTable::mousePressEvent" << endl;
}

void StateTable::mouseReleaseEvent(QMouseEvent *e)
{
    qDebug() << "##test StateTable::mouseReleaseEvent" << endl;
}


