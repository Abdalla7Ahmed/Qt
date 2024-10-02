#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <QDialog>
#include "account.h"
class BankAccount;
namespace Ui {
class Customer;
}

/**
 * @class Customer
 * @brief Represents a dialog for customer interactions.
 *
 * This class is responsible for managing customer-related operations
 * in a dialog interface, including navigating through the interface
 * and handling customer data inputs.
 */
class Customer :  public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Constructs a Customer dialog.
     * @param parent Pointer to the parent widget (default is nullptr).
     */
    explicit Customer(QWidget *parent = nullptr);

    /**
     * @brief Destroys the Customer dialog and releases resources.
     */
    ~Customer();
private slots:
    void on_pushButton_Home_clicked();

    void on_pushButton_Next_clicked();

    void on_comboBox_currentTextChanged(const QString &arg1);

    void on_pushButton_clicked();

    void on_checkBox_clicked();

private:
    Ui::Customer *ui;
};

/**
 * @class BankCustomer
 * @brief Represents a bank customer inheriting from BankAccount.
 *
 * This class extends the BankAccount class to include customer-specific
 * attributes and behaviors for bank operations.
 */
class BankCustomer :public BankAccount{
private:
public :
    BankCustomer()=default;
    BankCustomer(QString m_Customer_Name,QString m_Customer_NN,QString m_Customer_Address,
int m_Customer_Age,QString m_Customer_Password,QString m_Customer_phone,QString m_Customer_Email);
    ~BankCustomer();
};

#endif // CUSTOMER_H
