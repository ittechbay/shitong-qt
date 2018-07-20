#include "boardbutton.h"
#include "ui_boardbutton.h"

BoardButton::BoardButton(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::BoardButton)
{
    ui->setupUi(this);
}

BoardButton::~BoardButton()
{
    delete ui;
}
