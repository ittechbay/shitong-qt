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

private:
    Ui::BoardButton *ui;
};

#endif // BOARDBUTTON_H
