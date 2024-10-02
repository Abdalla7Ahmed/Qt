#include "mainwindow.h"
#include "./ui_mainwindow.h"

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




void MainWindow::on_pushButton1_clicked()
{

}


void MainWindow::on_pushButton2_clicked()
{
    static int flag{};
    if(!flag)
    {
        ui->label->setText("pushButton2 is clicked");
        flag = 1;
    }
    else
    {
        ui->label->setText("status");
        flag =0;
    }
}

