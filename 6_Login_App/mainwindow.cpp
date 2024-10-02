#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPixmap pic(":/images/images/login.jpg");
    int w=ui->label_pic->width();
    int h=ui->label_pic->height();
    ui->label_pic->setPixmap(pic.scaled(w,h,Qt::KeepAspectRatio));
    ui->statusbar->addPermanentWidget(ui->progressBar,1);
    ui->statusbar->addPermanentWidget(ui->label,1);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_login_clicked()
{
    QString uname=ui->lineEdit_username->text();
    QString password =ui->lineEdit_password->text();

    if(uname == "Abdallah" && password == "abdo")
    {
        //QMessageBox::information(this,"Login_status","the username and password are correct");
        //ui->statusbar->showMessage("the username and password are correct",5000);
        ui->label->setText("the username and password are correct");
    }
    else
    {
        // QMessageBox::warning(this,"Login_status","the username and password are not correct");
        //ui->statusbar->showMessage("the username and password are not correct",5000);
        ui->label->setText("the username and password are not correct");

    }

}

