#ifndef EDIT_ACCOUNT_H
#define EDIT_ACCOUNT_H

#include <QDialog>
#include "account.h"
namespace Ui {
class Edit_Account;
}
/**
 * @brief The Edit_Account class provides a dialog for editing account information.
 *
 * This class inherits from QDialog and BankAccount, and allows users to
 * modify account details such as account type and personal information.
 */
class Edit_Account : public QDialog,public BankAccount
{
    Q_OBJECT
private:
private:
    Ui::Edit_Account *ui; ///< Pointer to the UI elements for the dialog.

    /// @brief Enum representing the types of bank accounts.
    enum class Account_Type : unsigned char
    {
        LOAN_ACCOUNT,    ///< Represents a loan account.
        SAVING_ACCOUNT,  ///< Represents a savings account.
        CHECKING_ACCOUNT ///< Represents a checking account.
    };
    Account_Type account_type{Account_Type::LOAN_ACCOUNT}; ///< Current account type.
    QString language;                                      ///< Selected language for the user interface.
public:
    explicit Edit_Account(QWidget *parent = nullptr);
    int Check_Authorization();

    ~Edit_Account();

private slots:
    void on_pushButton_Home_clicked();

    void on_pushButton_Back_clicked();


    void on_comboBox_2_currentTextChanged(const QString &arg1);
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_comboBox_currentTextChanged(const QString &arg1);
    void on_pushButton_3_clicked();
    void on_checkBox_clicked();
};

#endif // EDIT_ACCOUNT_H
