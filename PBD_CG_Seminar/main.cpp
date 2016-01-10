#include "mainwindow.h"
#include <QApplication>
#include "canvas.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //Canvas canvas;
    //canvas.show();

    MainWindow w;
    w.show();

    return a.exec();
}
