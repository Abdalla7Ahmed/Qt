#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMessageBox>
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

void MainWindow::on_actionOpen_triggered()
{
    QMessageBox::information(this,"information","the Open icon is clicked");
}


void MainWindow::on_actionClose_triggered()
{
    QMessageBox::information(this,"information","the close icon is clicked");

}


void MainWindow::on_actionNew_triggered()
{
    QMessageBox::information(this,"information","the new icon is clicked");

}

