#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QtSql/QtSql>
#include <QtDebug>
#include <QLoggingCategory>
#include <QMessageBox>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // QSqlDatabase mydb=QSqlDatabase::addDatabase ("QSQLITE");
    // mydb.setDatabaseName("/home/abdallah/Documents/ABDELGHAFOR'S_VIRTUAL_INTERNSHIPS/Tasks/4/code/Library_Management_Systsem.db");
    // if(!mydb.open())
    //     ui->label->setText("Failed to open the database");
    // else
    //     ui->label->setText("Connected....");zz


    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("memory.db");
    if (!db.open()) {
        QMessageBox::critical(nullptr, QObject::tr("Cannot open database"),
                              QObject::tr("Unable to establish a database connection.\n"
                                          "This example needs SQLite support. Please read "
                                          "the Qt SQL driver documentation for information how "
                                          "to build it.\n\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
        // return false;
    }
    else

    {
        // QMessageBox::information(this,"information","1-open");
    }

    QSqlQuery query;
    query.exec("create table person (id int primary key, "
               "firstname varchar(20), lastname varchar(20))");
    query.exec("insert into person values(101, 'Danny', 'Young')");
    query.exec("insert into person values(102, 'Christine', 'Holand')");
    query.exec("insert into person values(103, 'Lars', 'Gordon')");
    query.exec("insert into person values(104, 'Roberto', 'Robitaille')");
    query.exec("insert into person values(105, 'Maria', 'Papadopoulos')");

    query.exec("create table items (id int primary key,"
               "imagefile int,"
               "itemtype varchar(20),"
               "description varchar(100))");
    query.exec("insert into items "
               "values(0, 0, 'Qt',"
               "'Qt is a full development framework with tools designed to "
               "streamline the creation of stunning applications and  "
               "amazing user interfaces for desktop, embedded and mobile "
               "platforms.')");
    query.exec("insert into items "
               "values(1, 1, 'Qt Quick',"
               "'Qt Quick is a collection of techniques designed to help "
               "developers create intuitive, modern-looking, and fluid "
               "user interfaces using a CSS & JavaScript like language.')");
    query.exec("insert into items "
               "values(2, 2, 'Qt Creator',"
               "'Qt Creator is a powerful cross-platform integrated "
               "development environment (IDE), including UI design tools "
               "and on-device debugging.')");
    query.exec("insert into items "
               "values(3, 3, 'Qt Project',"
               "'The Qt Project governs the open source development of Qt, "
               "allowing anyone wanting to contribute to join the effort "
               "through a meritocratic structure of approvers and "
               "maintainers.')");

    QSqlQuery personQuery("select * from person");
    while (personQuery.next()) {
        int id = personQuery.value(0).toInt();
        QString firstname = personQuery.value(1).toString();
        QString lastname = personQuery.value(2).toString();
        qDebug() << "ID:" << id << ", First Name:" << firstname << ", Last Name:" << lastname;
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{

}

