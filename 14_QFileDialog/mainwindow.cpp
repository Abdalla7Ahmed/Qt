#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QFileDialog>
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
    //write
    QFile file("/home/abdallah/Documents/Github/Embedded_Linux_Diploma/qt/1_Widget_applications/13_QFile/test_file.txt");
    if(!file.open(QFile::WriteOnly | QFile::Text))
    {
        QMessageBox::warning(this,"warning","can't open this file");
    }
    QTextStream out(&file);
    QString text = ui->plainTextEdit->toPlainText();
    out<<text;

    file.flush();
    file.close();

}


void MainWindow::on_pushButton_2_clicked()
{
    //Read
    // QString filename = QFileDialog::getOpenFileName(this,"Open File","/home/abdallah");
    QString filter = "All files (*.*);; text files (*.txt)";
    QString filename = QFileDialog::getOpenFileName(this,"Open File","/home/abdallah",filter);


    QFile file(filename);
    if(!file.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this,"warning","can't open this file");
    }
    QTextStream in(&file);

    QString text = in.readAll();
    ui->plainTextEdit->setPlainText(text);

    file.close();

}
