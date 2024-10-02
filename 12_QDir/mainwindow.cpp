#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QDir>
#include <QMessageBox>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QDir dir("/home/abdallah/Documents/Github/Embedded_Linux_Diploma/qt/1_Widget_applications/12_QDir");
    if(dir.exists())
    {
        // QMessageBox::information(this,"info","Dir is exist");
    }
    else
    {
        QMessageBox::information(this,"info","Dir is not exist");
    }


    QDir dir2("/home/abdallah/Documents/Github/Embedded_Linux_Diploma/qt/1_Widget_applications/12_QDir");
    // QDir dir2("/");
    foreach (QFileInfo var, dir2.entryInfoList()) {
        if(var.isFile())
        {
            ui->listWidget->addItem("File "+var.absoluteFilePath());

        }
        else if(var.isDir())
        {
            ui->listWidget->addItem("Dir " +var.absoluteFilePath());

        }
    }


    QDir dir3;
    foreach (QFileInfo var, dir3.drives()) {
        ui->comboBox->addItem(var.absoluteFilePath());
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString path {"/home/abdallah/Documents/Github/Embedded_Linux_Diploma/qt/1_Widget_applications/12_QDir/TmpDir"};
    QDir dir(path);
    if(dir.exists())
    {
        QMessageBox::information(this,"info","Dir is exist");
    }
    else
    {
        dir.mkdir(path);
    }

}

