#ifndef SETTIME_H
#define SETTIME_H

#include <QDialog>
#include <QTimer>

namespace Ui {
class SetTime;
}

class SetTime : public QDialog
{
    Q_OBJECT
private:
    QTimer *timer;
public:
    explicit SetTime(QWidget *parent = 0);
    ~SetTime();

private slots:
    void on_timeEdit_dateTimeChanged(const QDateTime &dateTime);

    void on_timeEdit_timeChanged(const QTime &time);
    void onTimerOut();

    void on_comboBox_currentIndexChanged(const QString &arg1);

private:
    Ui::SetTime *ui;
    QDateTime *dt;

};

#endif // SETTIME_H
