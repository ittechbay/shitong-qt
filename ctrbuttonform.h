#ifndef CTRBUTTONFORM_H
#define CTRBUTTONFORM_H

#include <QWidget>
#include <QColor>

namespace Ui {
class ctrButtonForm;
}

class ctrButtonForm : public QWidget
{
    Q_OBJECT

public:
    explicit ctrButtonForm(const QString &title, QWidget *parent = 0);
    //explicit ctrButtonForm(QWidget *parent = 0, QString s1, QString s2,QString s3,QString s4);
    void addSubTitle(const  QString &s);
    void addSubLed( QString &s);
    void addSubLed(QPixmap *pixmap);
    void replaceSubLed(int index, QPixmap *pixmap);
    void changeSubLed(int index, QColor &s);
    void replaceMainLed(QPixmap *pixmap);
    void replaceMainLed(QString &s);

    void paintEvent(QPaintEvent *ev);
    ~ctrButtonForm();



    QString title;
    QVector<QString> subTitle;
    QVector<QString> ledState;
    QPixmap *ledMain;
    QVector<QPixmap *> led;
    QVector<QPixmap *> ledGreen;
    QVector<QPixmap *> ledRed;
    QVector<QPixmap *> ledGray;

private:

};

#endif // CTRBUTTONFORM_H
