#ifndef CUSTOMER_EDIT_H
#define CUSTOMER_EDIT_H

#include <QDialog>
#include "account.h"
namespace Ui
{
class Customer_Edit;
}

/**
 * @brief The Customer_Edit class provides a dialog for editing customer details.
 *
 * This class inherits from QDialog and BankAccount, allowing users to
 * load customer data, modify it, and submit the changes.
 */
class Customer_Edit : public QDialog, public BankAccount
{
    Q_OBJECT

public:
    explicit Customer_Edit(QWidget *parent = nullptr);
    ~Customer_Edit();

private slots:
    void on_pushButton_Load_clicked();

    void on_pushButton_CN_clicked();

    void on_pushButton_Submit_clicked();

    void on_pushButton_Home_clicked();

    void on_pushButton_clicked();

    void on_comboBox_currentTextChanged(const QString &arg1);

    void on_checkBox_clicked();

    void on_checkBox_2_clicked();

private:
    Ui::Customer_Edit *ui;     ///< User interface object for the dialog.
    int Check_Authorization(); ///< Checks the authorization level of the user.

protected:
    bool eventFilter(QObject *watched, QEvent *event) override;
};

#endif // CUSTOMER_EDIT_H
