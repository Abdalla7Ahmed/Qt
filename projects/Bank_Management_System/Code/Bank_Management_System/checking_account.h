#ifndef CHECKING_ACCOUNT_H
#define CHECKING_ACCOUNT_H

#include <QDialog>
#include "customer.h"
namespace Ui
{
class Checking_Account;
}
/**
 * @brief The Checking_Account class provides a dialog for checking account management.
 *
 * This class inherits from QDialog and allows the user to manage their checking account.
 */
class Checking_Account : public QDialog
{
    Q_OBJECT

public:
    explicit Checking_Account(QWidget *parent = nullptr);
    ~Checking_Account();

private slots:
    void on_pushButton_Home_clicked();

    void on_pushButton_Back_clicked();

    void on_pushButton_Next_clicked();

    void on_comboBox_currentTextChanged(const QString &arg1);

    void on_checkBox_clicked();

private:
    Ui::Checking_Account *ui; ///< Pointer to the UI for the checking account dialog.
};
/**
 * @brief The Bank_Checking class represents a checking account for a bank customer.
 *
 * This class inherits from BankCustomer and provides methods to manage checking account specifics.
 */
class Bank_Checking : public BankCustomer
{
private:
    int m_Credit_Limit{50000}; ///< The credit limit for the checking account.

public:
    Bank_Checking() = default;
    Bank_Checking(QString Customer_Name, QString Customer_Pass, QString Customer_NN);
    int Get_Interset_Rate(void);
    ~Bank_Checking() = default;
};

#endif // CHECKING_ACCOUNT_H
