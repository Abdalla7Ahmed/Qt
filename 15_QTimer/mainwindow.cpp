#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QDebug>
#include <QDateTime>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(TimeOutCallBack()));
    timer->start(1000);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::TimeOutCallBack(void)
{
    // QTime time=QTime::currentTime();
    // QString time_in_string = time.toString("hh : mm : ss");
    // if((time.second()) %2 ==0)
    // {
    //     time_in_string[3] = ' ';
    //     time_in_string[8] = ' ';
    // }
    // ui->label->setText(time_in_string);


    QTime time=QTime::currentTime();
    ui->lcdNumber_Hours->display(time.hour());
    ui->lcdNumber_Minutes->display(time.minute());
    ui->lcdNumber_Seconds->display(time.second());

}
