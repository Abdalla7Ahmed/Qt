#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <QDialog>
#include "database.h"
#include <QMessageBox>
#include <QCryptographicHash>
#include <QInputDialog>
class Saving_Acount ;
class Checking_Account;
class Loan_Acount;
// class Customer_operations;
namespace Ui {
class Account;
}
/**
 * @class Account
 * @brief Represents a dialog for managing bank accounts.
 *
 * This class provides an interface for users to perform operations related to
 * different types of bank accounts, including saving accounts, checking accounts,
 * and loan accounts. It allows users to create new accounts and edit existing ones.
 *
 * The class inherits from QDialog and includes slots for handling button clicks
 * and changes in the user interface, enabling a responsive and interactive experience.
 */
class Account :public QDialog
{
    Q_OBJECT
private:
    Ui::Account *ui;
    Saving_Acount *saving_account;
    Checking_Account *checking_account;
    Loan_Acount *loan_account;
public:
    explicit Account(QWidget *parent = nullptr);
    ~Account();

private slots:


    void on_pushButton_loan_clicked();

    void on_pushButton_saving_clicked();

    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_Edit_clicked();


    void on_comboBox_currentTextChanged(const QString &arg1);

    void on_pushButton_3_clicked();

protected:
    bool eventFilter(QObject *watched, QEvent *event) override;
};

/**
 * @class BankAccount
 * @brief This class represents a bank account with various operations such as
 * depositing, withdrawing, and managing different account types.
 *
 * It allows the user to perform normal banking operations, create loan accounts,
 * saving accounts, and checking accounts, and handles balance inquiries.
 */
class BankAccount :public BankDataBase
{
private:

    QString Customer_Name;       ///< Name of the customer
    QString Customer_NN;         ///< National Number of the customer
    QString Customer_Pass;       ///< Password for account access
    QString m_Customer_phone;    ///< Phone number of the customer
    QString m_Customer_Email;    ///< Email address of the customer
    int Customer_id;             ///< Unique identifier for the customer
    float m_Balance;             ///< Current balance of the account
    QString Customer_Address;    ///< Address of the customer
    int Customer_Age;            ///< Age of the customer
    float m_Credit_Limit{50000}; ///< Credit limit for the account
public:
    BankAccount(QString Customer_Name,QString Customer_NN,QString Customer_Pass,QString Customer_Address = " ",int Customer_Age = 0 ,QString m_Customer_phone = " ",QString m_Customer_Email = " ");
    BankAccount()=default;
    void Set_Customer_Name(QString Customer_Name);
    void Set_Customer_NN(QString Customer_NN);
    void Set_Customer_Pass(QString Customer_Pass);
    void Set_Customer_Address(QString Customer_Address);
    void Set_Customer_Age(int Customer_Age);
    void Set_Customer_Phone(QString m_Customer_phone);
    void Set_Customer_Email(QString m_Customer_Email);
    void Set_Credit_Limit(float m_Credit_Limit);
    int Check_Account_Info(void);
    void deposit(int Customer_id , float m_Amount);
    void withdraw(int Customer_id ,float m_Amount);
    void balance_Enquiry(void);
    int QMessageBox_Display(QString text,int type);

    void Add_New_Customer(void);


    void Create_Saving_Account(float Saving_Amount);
    void Create_Loan_Account(float Loan_Amount,int Loan_Duration,float Interest_Rate);
    void Create_Checking_Account(float Cheking_Amount);

    QString generateOTP();
    void sendEmail(const QString& otp, const QString& recipientEmail);

    ~BankAccount();
};

#endif // ACCOUNT_H
