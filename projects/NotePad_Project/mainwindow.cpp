#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QFontDialog>
#include <QFont>
#include <QColorDialog>
#include <QColor>
#include <QtSql/QSql>
// #include <QtPrintSupport/QPrintDialog>
// #include <QtPrintSupport/QPrinter>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->textEdit);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionNew_triggered()
{
    file_path = " ";
    ui->textEdit->setText(" ");
}
void MainWindow::on_actionOpen_triggered()
{
    QString file_name = QFileDialog::getOpenFileName(this,"Open file");
    QFile file(file_name);
    file_path = file_name;
    if(!file.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this,"warning","Can't open this file");
        return;
    }

    QTextStream in(&file);
    QString file_content = in.readAll();
    ui->textEdit->setText(file_content);

    file.close();


}
void MainWindow::on_actionSave_triggered()
{
    QFile file(file_path);

    if(!file.open(QFile::WriteOnly | QFile::Text))
    {
        QMessageBox::warning(this,"warning","Can't open this file");
        return;
    }

    QTextStream out(&file);

    QString file_content = ui->textEdit->toPlainText();
    out << file_content;
    file.flush();
    file.close();
}
void MainWindow::on_actionSave_as_triggered()
{
    QString file_name = QFileDialog::getOpenFileName(this,"Open file");
    file_path = file_name;
    QFile file(file_name);
    if(!file.open(QFile::WriteOnly | QFile::Text))
    {
        QMessageBox::warning(this,"warning","Can't open this file");
        return;
    }
    QTextStream out(&file);

    QString file_content = ui->textEdit->toPlainText();
    out << file_content;
    file.flush();
    file.close();

}

void MainWindow::on_actionCopy_triggered()
{
    ui->textEdit->copy();

}
void MainWindow::on_actionCut_triggered()
{
    ui->textEdit->cut();
}
void MainWindow::on_actionPast_triggered()
{
    ui->textEdit->paste();

}


void MainWindow::on_actionundo_triggered()
{

    ui->textEdit->undo();


}


void MainWindow::on_actionredo_triggered()
{
    ui->textEdit->redo();

}




void MainWindow::on_actionAbout_triggered()
{
    QString about="Author : Abdallah Ahmed Mohammed \n";
    about +="Date : 01-01-200 \n";
    about +="(C) Notpad (R) \n";

    QMessageBox::about(this,"about Notpad",about);
}

void MainWindow::on_actionFont_triggered()
{
    bool ok;
    QFont font = QFontDialog::getFont(&ok,this);
    if(ok)
    {
        ui->textEdit->setFont(font);
    }
    else
    {
        return ;
    }

}


void MainWindow::on_actionColor_triggered()
{
    QColor color = QColorDialog::getColor(Qt::white,this,"Color Dialog");
    if(color.isValid())
    {
        ui->textEdit->setTextColor(color);
    }
}


void MainWindow::on_actionBackground_text_triggered()
{
    QColor color = QColorDialog::getColor(Qt::white,this,"Color Dialog");
    if(color.isValid())
    {
        ui->textEdit->setTextBackgroundColor(color);
    }
}


void MainWindow::on_actionBackgrount_Edit_Text_triggered()
{
    QColor color = QColorDialog::getColor(Qt::white,this,"Color Dialog");
    if(color.isValid())
    {
        ui->textEdit->setPalette(QPalette(color));
    }
}


void MainWindow::on_actionPrint_triggered()
{
    // QPrinter printer ;
    // printer.setPrinterName("Printer name");
    // QPrintDialog dialog(&printer,this);
    // if(dialog.exec()== QDialog::Rejected)
    // {
    //     QMessageBox::warning(this,"warning","Faild to print");
    //     return;
    // }
    // ui->textEdit->print(&printer);
}

