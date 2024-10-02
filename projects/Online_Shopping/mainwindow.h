#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableView>
#include "DataBase.h"
#include "cart.h"
#include "user.h"
#include "order.h"
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow,public DataBase
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void getUserInput(void);
    ~MainWindow();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_comboBox_currentTextChanged(const QString &arg1);

    void on_lineEdit_search_textChanged(const QString &arg1);

    void on_comboBox_price_currentTextChanged(const QString &arg1);

    void on_pushButton_clicked();

    void on_pushButton_calc_clicked();

private:
    Ui::MainWindow *ui;
    Cart *cart;
    User *user;
    Order * order;
    QString Table_Name;
    QString Price_Filter;
    QString Category_Filter;
    float Total_Price_to_Pay{};
    float Total_Price_Paid{};
    float price_without_Discount{};
    float price_with_Discount{};
    QString Discount_Code{};

};
#endif // MAINWINDOW_H
