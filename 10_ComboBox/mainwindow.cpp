#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMessageBox>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->comboBox->addItem("Open");
    ui->comboBox->addItem("Close");
    ui->comboBox->addItem("New");

    // we can use overload method
    ui->comboBox->addItem(QIcon(":/images/images/open.png"),"Open");
    ui->comboBox->addItem(QIcon(":/images/images/close.png"),"Close");
    ui->comboBox->addItem(QIcon(":/images/images/new.png"),"New");

    for(int i=0;i<10;i++)
    {
        ui->comboBox_2->addItem(QString::number(i) + "-index");

    }

    //change an index
    ui->comboBox_2->insertItem(0,"New index");

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_comboBox_currentTextChanged(const QString &arg1)
{
    // if(arg1=="Open")
    // {
    //     QMessageBox::information(this,"information","Open");
    // }
    // if(arg1=="Close")
    // {
    //     QMessageBox::information(this,"information","Close");
    // }
    // if(arg1=="New")
    // {
    //     QMessageBox::information(this,"information","New");
    // }

    QMessageBox::information(this,"nformation",
                             "index "+QString::number(ui->comboBox->currentIndex()) +"-"+ui->comboBox->currentText() );
}


void MainWindow::on_comboBox_textActivated(const QString &arg1)
{

}

