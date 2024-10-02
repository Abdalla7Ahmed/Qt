#ifndef LOAN_ACOUNT_H
#define LOAN_ACOUNT_H

#include <QDialog>
// #include "account.h"
#include "customer.h"
namespace Ui {
class Loan_Acount;
}

/**
 * @brief The Loan_Acount class provides a dialog for managing loan accounts.
 *
 * This class allows users to interact with loan-related functionalities
 * through a graphical user interface (GUI).
 */
class Loan_Acount : public QDialog
{
    Q_OBJECT

public:
    explicit Loan_Acount(QWidget *parent = nullptr);
    ~Loan_Acount();

private slots:
    void on_pushButton_Home_clicked();

    void on_pushButton_Back_clicked();

    void on_pushButton_Next_clicked();

    void on_comboBox_currentTextChanged(const QString &arg1);

    void on_checkBox_clicked();

private:
    Ui::Loan_Acount *ui;
};

/**
 * @brief The BankLoan class represents a loan account for a bank customer.
 *
 * This class manages the loan details such as amount, duration, and interest ratio.
 */
class BankLoan : public BankCustomer{
private:
    float m_Loan_Amount;    ///< The amount of the loan.
    int m_Loan_Duration;    ///< The duration of the loan in months.
    float m_Interest_Ratio; ///< The interest ratio for the loan.
public:
    BankLoan();
    BankLoan(QString Customer_Name,QString Customer_Pass,QString Customer_NN);

    void Set_Loan_Amount(float m_Loan_Amount);
    void Set_Loan_Duration(int m_Loan_Duration);
    float Get_Loan_Amount(void);
    int Get_Loan_Duration(void);
    float Get_Interest_Ratio(void);

    ~BankLoan();
};

#endif // LOAN_ACOUNT_H
