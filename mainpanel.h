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

private:
    Ui::mainPanel *ui;
};

#endif // MAINPANEL_H
