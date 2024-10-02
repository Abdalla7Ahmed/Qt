#ifndef SAVING_ACOUNT_H
#define SAVING_ACOUNT_H

#include <QDialog>
#include "customer.h"
// class BankCustomer;
namespace Ui {
class Saving_Acount;
}
/**
 * @brief The Saving_Acount class provides a dialog for managing savings accounts.
 *
 * This class allows users to interact with savings account functionalities
 * in a dialog window.
 */
class Saving_Acount : public QDialog
{
    Q_OBJECT

public:
    explicit Saving_Acount(QWidget *parent = nullptr);
    ~Saving_Acount();

private slots:
    void on_pushButton_Home_clicked();

    void on_pushButton_Back_clicked();

    void on_pushButton_Next_clicked();

    void on_comboBox_currentTextChanged(const QString &arg1);

    void on_checkBox_clicked();

private:
    Ui::Saving_Acount *ui; ///< Pointer to the UI elements for this dialog.

};

/**
 * @brief The Bank_Saving class represents a bank customer with a savings account.
 *
 * This class extends the BankCustomer class and includes functionalities specific
 * to savings accounts.
 */
class Bank_Saving :public BankCustomer{
private:
    int m_Interset_Rate; ///< Interest rate for the savings account.
public:
    Bank_Saving();
    Bank_Saving(QString Customer_Name,QString Customer_Pass,QString Customer_NN);
    int Get_Interset_Rate(void);
    ~Bank_Saving();
};

#endif // SAVING_ACOUNT_H
