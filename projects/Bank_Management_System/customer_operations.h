#ifndef CUSTOMER_OPERATIONS_H
#define CUSTOMER_OPERATIONS_H

#include <QDialog>
#include "customer.h"
namespace Ui
{
class Customer_operations;
}
/**
 * @class Customer_operations
 * @brief Dialog for customer operations such as deposit, withdraw, and balance inquiry.
 *
 * This class handles the UI and operations related to customer transactions,
 * including depositing funds, withdrawing funds, and checking account balance.
 */
class Customer_operations : public QDialog
{
    Q_OBJECT

private:
    Ui::Customer_operations *ui; ///< Pointer to the UI components.
    enum class Operation_Type : unsigned char
    {
        DEPOSIT,
        WITHDRAW,
        BALANCE_ENQUIRY,
    };
    Operation_Type current_type;

public:
    explicit Customer_operations(QWidget *parent = nullptr);
    void make_action(Operation_Type current_type);
    // int QMessageBox_Display(QString text,int type);
    ~Customer_operations();

private slots:

    void on_pushButton_Home_clicked();

    void on_pushButton_Back_clicked();

    void on_comboBox_currentTextChanged(const QString &arg1);
    void on_pushButton_Deposit_clicked();
    void on_pushButton_Withdraw_clicked();
    void on_pushButton_Balance_clicked();
    void on_checkBox_clicked();
};
/**
 * @class Make_Operation
 * @brief Class to handle operations for a bank customer.
 *
 * This class represents a bank customer and encapsulates the necessary
 * details for performing operations on the customer's account.
 */
class Make_Operation : public BankCustomer
{
private:
public:
    Make_Operation(QString Customer_Name, QString Customer_NN, QString Customer_Pass);
    Make_Operation() = default;
    ~Make_Operation();
};

#endif // CUSTOMER_OPERATIONS_H
