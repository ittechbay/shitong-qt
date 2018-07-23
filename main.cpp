#include "mainpanel.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    mainPanel w;
    w.show();

    return a.exec();
}
