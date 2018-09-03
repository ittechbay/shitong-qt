#ifndef MAINPANEL_H
#define MAINPANEL_H

#include <QWidget>
#include <QLabel>
#include "boardbutton.h"

namespace Ui {
class mainPanel;
}

class mainPanel : public QWidget
{
    Q_OBJECT

public:
    explicit mainPanel(QWidget *parent = 0);

    ~mainPanel();
    BoardButton * toButtonFrame(int slot);
    QLabel * toButtonLabel(int slot);

private slots:
    void on_pushButton_clicked();

    void onTimerOutMain();
    void onTimerOut0();
    void onTimerOut1();
    void onTimerOut2();
    void onTimerOut3();
    void onTimerOut4();
    void onTimerOut5();
    void onTimerOut6();
    void onTimerOut7();
    void onTimerOut8();
    void onTimerOut9();
    void onTimerOut10();
    void onTimerOut11();

    void on_frame_3_clicked();

    void on_frame_4_clicked();




    void on_pushButton_2_clicked();

    void on_pushButton_4_clicked();
    void cmdProcessTask();

private:
    Ui::mainPanel *ui;
    QTimer *timer;
};

#endif // MAINPANEL_H
