#include "second_window.h"
#include "ui_second_window.h"

Second_Window::Second_Window(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Second_Window)
{
    ui->setupUi(this);
}

Second_Window::~Second_Window()
{
    delete ui;
}

void Second_Window::on_pushButton_clicked()
{
 QApplication::quit(); // Exit the application
}

