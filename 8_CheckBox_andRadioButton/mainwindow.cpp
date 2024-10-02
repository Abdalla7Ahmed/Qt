#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMessageBox>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // to make it check when run the app
    // ui->checkBox->setChecked(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    if(ui->checkBox->isChecked())
    {
        QMessageBox::information(this,"status","you are not a root");
    }
    else
    {
        QMessageBox::warning(this,"status","you are a root");

    }

}


void MainWindow::on_checkBox_stateChanged(int arg1)
{
    if(arg1)
    {
        QMessageBox::information(this,"status","you are not a root");
    }
    else
    {
        QMessageBox::warning(this,"status","you are a root");

    }
}


void MainWindow::on_pushButton_2_clicked()
{
    if(ui->radioButton_1->isChecked())
    {
        QMessageBox::information(this,"status","you are in the first year");
    }
    else if(ui->radioButton_2->isChecked())
    {
        QMessageBox::information(this,"status","you are in the second year");
    }
    else if(ui->radioButton_3->isChecked())
    {
        QMessageBox::information(this,"status","you are in the third year");
    }
    else if(ui->radioButton_4->isChecked())
    {
        QMessageBox::information(this,"status","you are in the fourth year");
    }
}


void MainWindow::on_pushButton_3_clicked()
{
    if(ui->radioButton_5->isChecked())
    {
        QMessageBox::information(this,"status","your grade is good");
    }
    else if(ui->radioButton_6->isChecked())
    {
        QMessageBox::information(this,"status","your grade is very good");
    }
    else if(ui->radioButton_7->isChecked())
    {
        QMessageBox::information(this,"status","your grade is excellent");
    }


}

