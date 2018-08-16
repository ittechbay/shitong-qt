#ifndef BOARDBUTTON_H
#define BOARDBUTTON_H

#include <QFrame>

namespace Ui {
class BoardButton;
}

class BoardButton : public QFrame
{
    Q_OBJECT

public:
    explicit BoardButton(QWidget *parent = 0);
    ~BoardButton();
    void setBoard();
    void setBoard(const QString &s1);
    void setBoard(const QString &s1, const QString &s2);
    void setBoard(const QString &s1, const QString &s2, const QString &s3);
    void setBoard(const QString &s1, const QString &s2, const QString &s3, const QString &s4);
    void setNullBoard();
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void setLedColor(const Qt::GlobalColor &color);
    void setLedColor_sub1(const Qt::GlobalColor &color);
    void setLedColor_sub2(const Qt::GlobalColor &color);
    void setLedColor_sub3(const Qt::GlobalColor &color);
    void setLedColor_sub4(const Qt::GlobalColor &color);

private:
    Ui::BoardButton *ui;
    bool enable;

signals:
    void clicked();

//private slots:
//    void click();


private slots:
    void on_BoardButton_clicked();
};

#endif // BOARDBUTTON_H
