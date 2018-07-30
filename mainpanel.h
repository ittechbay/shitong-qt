#ifndef MAINPANEL_H
#define MAINPANEL_H

#include <QWidget>

namespace Ui {
class mainPanel;
}

class mainPanel : public QWidget
{
    Q_OBJECT

public:
    explicit mainPanel(QWidget *parent = 0);
    ~mainPanel();

private slots:
    void on_pushButton_clicked();



    void on_frame_3_clicked();

    void on_frame_4_clicked();




    void on_pushButton_2_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::mainPanel *ui;
};

#endif // MAINPANEL_H
