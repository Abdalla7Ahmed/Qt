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

void MainWindow::on_pushButton_clicked()
{
    // Second_Window second_window;
    // second_window.setModal(true);
    // second_window.exec();
    second_window = new Second_Window(this);
    second_window->show();
}


void MainWindow::on_pushButton_2_clicked()
{
    hide();
    second_window = new Second_Window(this);
    second_window->show();
}


