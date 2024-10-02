#include "mainwindow.h"
#include <QApplication>
#include <QLabel>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // MainWindow w;
    // w.show();
    QLabel *label = new QLabel ("Hello world");
    label->resize(400,400);
    label->setWindowTitle("this is hello world label");
    label->show();
    return a.exec();
}
