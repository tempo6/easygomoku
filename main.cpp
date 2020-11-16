#include "mainwindow.h"
#include "gomoku.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    mywin w;

    return a.exec();
}
