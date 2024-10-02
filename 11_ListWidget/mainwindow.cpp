#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include<QMessageBox>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // ui->listWidget->addItem("open");
    // ui->listWidget->addItem("Close");
    // ui->listWidget->addItem("New");
    QListWidgetItem *item1=new QListWidgetItem(QIcon(":/images/images/open.png"),"Open");
    QListWidgetItem *item2=new QListWidgetItem(QIcon(":/images/images/close.png"),"Close");
    QListWidgetItem *item3=new QListWidgetItem(QIcon(":/images/images/new.png"),"New");
    ui->listWidget->addItem(item1);
    ui->listWidget->addItem(item2);
    ui->listWidget->addItem(item3);

    // ui->listWidget->addItem();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    //QMessageBox::information(this,"information",ui->listWidget->currentItem()->text());
    ui->listWidget->currentItem()->setBackground(Qt::yellow);
    ui->listWidget->currentItem()->setForeground(Qt::black);
}
