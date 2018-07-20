#ifndef CLOCK_H
#define CLOCK_H

#include <QWidget>

class FTSClock : public QWidget
{
    Q_OBJECT
public:
    explicit FTSClock(QWidget *parent = 0);
    void paintEvent(QPaintEvent *ev);
    int hourArrawPos;
    int minuteArrawPos;
    void setHourArrawPos(int n);
    void setMinuteArrawPos(int n);

signals:

public slots:
};

#endif // CLOCK_H
