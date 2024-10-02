#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMessageBox>
#include <QDebug>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{

    QMessageBox::about(this,"about message","this is the test message ");
}


void MainWindow::on_pushButton_2_clicked()
{
    QMessageBox::aboutQt(this,"about message");
}


void MainWindow::on_pushButton_6_clicked()
{
    // the fourth argument is optional
    // by default is ok
    // QMessageBox::critical(this,"about message","this is the test message ","Abdallah");
    // QMessageBox::critical(this,"about message","this is the test message ");
    QMessageBox::StandardButton replay = QMessageBox::critical(this,"about message","this is the test message ",QMessageBox::Yes);
    if(replay == QMessageBox::Yes)
    {
        qDebug()<<"Yes is pressed ";
    }


}




void MainWindow::on_pushButton_4_clicked()
{
    QMessageBox::StandardButton replay = QMessageBox::question(
        this,
        "about message",
        "this is the test message ",
        QMessageBox::Yes|QMessageBox::No);


    if(replay == QMessageBox::Yes)
    {
        qDebug()<<"Yes is pressed ";
    }
    else if(replay == QMessageBox::No)
    {
        qDebug()<<"No is pressed ";
    }
}


void MainWindow::on_pushButton_3_clicked()
{

    QMessageBox::StandardButton replay = QMessageBox::warning(this,"about message","this is the test message ",QMessageBox::Ok);

    if(replay == QMessageBox::Ok)
    {
        qDebug()<<"Ok is pressed ";
    }
}


void MainWindow::on_pushButton_7_clicked()
{
    QMessageBox::StandardButton replay = QMessageBox::information(this,"about message","this is the test message ");

    if(replay == QMessageBox::Ok)
    {
        qDebug()<<"Ok is pressed ";
    }
}

