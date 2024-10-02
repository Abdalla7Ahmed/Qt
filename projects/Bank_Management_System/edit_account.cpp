#include "edit_account.h"
#include "ui_edit_account.h"
#include "mainwindow.h"



/**
 * @brief Constructs an Edit_Account dialog.
 *
 * This constructor initializes the UI components and sets up the available
 * languages and account types for selection.
 *
 * @param parent Pointer to the parent widget. This is passed to the QDialog
 * constructor to ensure proper parent-child relationships in the widget hierarchy.
 */
Edit_Account::Edit_Account(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Edit_Account)
{
    ui->setupUi(this);
    ui->comboBox->addItem("English");
    ui->comboBox->addItem("Arabic");
    ui->comboBox->addItem("German");
    ui->comboBox->addItem("French");


    ui->comboBox_2->addItem("Loan Account");
    ui->comboBox_2->addItem("Saving Account");
    ui->comboBox_2->addItem("Checking Account");



    Initialize_Data_Base(Get_Data_Base_Name());


}
/**
 * @brief Destructor for the Edit_Account class.
 *
 * Cleans up the allocated UI resources.
 */
Edit_Account::~Edit_Account()
{
    delete ui;
}



/**
 * @brief Navigates to the main window.
 *
 * This slot is triggered when the home button is clicked. It creates a new
 * instance of the MainWindow, hides the current Edit_Account dialog,
 * and shows the main window maximized.
 */
void Edit_Account::on_pushButton_Home_clicked()
{
    MainWindow *mainwindow;
    mainwindow = new MainWindow;
    hide();
    mainwindow->showMaximized();
}

/**
 * @brief Navigates back to the account window.
 *
 * This slot is triggered when the back button is clicked. It hides the current
 * Edit_Account dialog and creates a new instance of the Account window, which
 * is then displayed maximized.
 */
void Edit_Account::on_pushButton_Back_clicked()
{
    hide();
    Account *account;
    account = new Account;
    account->showMaximized();
}
/**
 * @brief Updates the input fields based on the selected account type.
 *
 * This slot is triggered when the user selects a different account type from
 * the combo box. It adjusts the labels for the loan amount and loan duration
 * according to the selected account type and the current language. The
 * following account types are handled: Loan Account, Saving Account, and
 * Checking Account. The corresponding labels are updated, and debug messages
 * are logged to indicate the selected account type.
 *
 * @param arg1 The selected account type from the combo box.
 */
void Edit_Account::on_comboBox_2_currentTextChanged(const QString &arg1)
{
    ui->lineEdit_LA->setText(" ");
    ui->lineEdit_LD->setText(" ");

    if (arg1 == "Loan Account") {
        account_type = Account_Type::LOAN_ACCOUNT;

        if (language == "English") {
            ui->label_LA->setText("Loan Amount");
            ui->label_LD->setText("Loan Duration (in months)");
        } else if (language == "Arabic") {
            ui->label_LA->setText("مبلغ القرض");
            ui->label_LD->setText("مدة القرض (بالشهور)");
        } else if (language == "French") {
            ui->label_LA->setText("Montant du prêt");
            ui->label_LD->setText("Durée du prêt (en mois)");
        } else if (language == "German") {
            ui->label_LA->setText("Darlehensbetrag");
            ui->label_LD->setText("Darlehensdauer (in Monaten)");
        }

    } else if (arg1 == "Saving Account") {
        account_type = Account_Type::SAVING_ACCOUNT;

        if (language == "English") {
            ui->label_LA->setText("Saving Amount");
            ui->label_LD->setText(" ");
        } else if (language == "Arabic") {
            ui->label_LA->setText("مبلغ الادخار");
            ui->label_LD->setText(" ");
        } else if (language == "French") {
            ui->label_LA->setText("Montant de l'épargne");
            ui->label_LD->setText(" ");
        } else if (language == "German") {
            ui->label_LA->setText("Einsparungsbetrag");
            ui->label_LD->setText(" ");
        }

    } else if (arg1 == "Checking Account") {
        account_type = Account_Type::CHECKING_ACCOUNT;

        if (language == "English") {
            ui->label_LA->setText("Checking Amount");
            ui->label_LD->setText(" ");
        } else if (language == "Arabic") {
            ui->label_LA->setText("مبلغ الحساب الجاري");
            ui->label_LD->setText(" ");
        } else if (language == "French") {
            ui->label_LA->setText("Montant du compte courant");
            ui->label_LD->setText(" ");
        } else if (language == "German") {
            ui->label_LA->setText("Scheckbetrag");
            ui->label_LD->setText(" ");
        }
    }
}
/**
 * @brief Checks the authorization of the customer based on their credentials.
 *
 * This function verifies whether the provided name, national number, and password
 * match the stored information in the database. If the credentials are valid,
 * it returns the customer ID. If any field is empty or incorrect, appropriate
 * messages are displayed, and the function returns -1.
 *
 * @return int The customer ID if authorization is successful, otherwise -1.
 *
 * The function performs the following checks:
 * - Validates that the name, password, and national number fields are not empty.
 * - Retrieves the customer's information from the database.
 * - Compares the entered credentials with the retrieved information.
 *
 * If the entered information matches, the customer ID is returned. If not,
 * specific warning messages are displayed for incorrect fields.
 */
int Edit_Account::Check_Authorization()
{
    int result {-1};

    QString Customer__Name;
    QString Customer__NN;
    QString Customer__Pass;

    Customer__Name = ui->lineEdit_Name->text();
    Customer__NN = ui->lineEdit_NN->text();
    Customer__Pass = ui->lineEdit_Password->text();

    Customer__Pass = hashPassword(Customer__Pass);
    bool flag{false};
    if(Customer__Name.isEmpty())
    {
        ui->lineEdit_Name->setText("*");
        flag =true;
    }
    if(Customer__Pass.isEmpty())
    {
        ui->lineEdit_Password->setText("*");
        flag =true;
    }
    if(Customer__NN.isEmpty())
    {
        ui->lineEdit_NN->setText("*");
        flag =true;
    }

    if(!flag)
    {
        QString Customer_Name;
        QString Customer_NN;
        QString Customer_Password;
        int Customer_ID;


        Customer_Name = Return_Item("Person","Name",QString("WHERE National_Number = %1").arg(Customer__NN));
        Customer_Password = Return_Item("Person","Password",QString("WHERE National_Number = %1").arg(Customer__NN));
        Customer_NN = Return_Item("Person","National_Number",QString("WHERE National_Number = %1").arg(Customer__NN));
        Customer_ID = Return_Item("Person","Customer_ID",QString("WHERE National_Number = %1").arg(Customer__NN)).toInt();

        if((Customer_Name == Customer__Name) && (Customer_Password == Customer__Pass) && (Customer__NN == Customer_NN))
        {
            result = Customer_ID;
        }
        else if ((Customer_Name == Customer__Name) && (Customer_Password != Customer__Pass) && (Customer__NN == Customer_NN))
        {
            QMessageBox_Display("Passowrd incorrect",QMessageBox::Warning);
        }
        else if ((Customer_Name != Customer__Name) && (Customer__NN == Customer_NN))
        {
            QMessageBox_Display("Name incorrect",QMessageBox::Warning);
        }
        else if (Customer__NN != Customer_NN)
        {
            QMessageBox_Display("National Number not found",QMessageBox::Warning);
        }

    }

    return result;
}

/**
 * @brief Handles the click event for loading account information based on the account type.
 *
 * This function is triggered when the user clicks a button in the UI. It checks the authorization
 * for a customer, retrieves the account information based on the account type, and populates
 * the appropriate fields in the user interface with the account details.
 *
 * @details
 * The function performs the following steps:
 * 1. Calls `Check_Authorization()` to verify if the customer has a valid ID.
 * 2. Based on the account type (`LOAN_ACCOUNT`, `SAVING_ACCOUNT`, `CHECKING_ACCOUNT`), it retrieves
 *    the corresponding balance and, if applicable, additional details like loan duration.
 * 3. If no account is found for the given customer ID, a warning is displayed using `QMessageBox`.
 * 4. The retrieved information is populated into the respective UI fields such as `lineEdit_LA` for the balance amount and `lineEdit_LD` for loan duration.
 *
 * @note
 * - The function assumes that balance amounts retrieved for loan and checking accounts might be negative and converts them to positive before displaying.
 * - Account types are handled using the `Account_Type` enum.
 *
 * @warning If no account of the selected type is found for the customer, an error message will be displayed, and the UI fields will not be updated.
 *
 * @see Return_Item(), Check_Authorization(), QMessageBox_Display()
 */

void Edit_Account::on_pushButton_clicked()
{
    // load information pushButton
    int Customer_ID = Check_Authorization();
    if(Customer_ID > 0)
    {
        switch (account_type) {
        case Account_Type::LOAN_ACCOUNT:
        {
            QString Loan_Amount = Return_Item("Account","Balance",QString("WHERE Customer_ID = %1 AND Account_Type='%2'")
                                          .arg(Customer_ID)
                                          .arg("Loan_Account"));
            if(Loan_Amount == "No")
            {
                QMessageBox_Display("No Loan account found for this national number",QMessageBox::Warning);
            }
            else
            {
                QString Loan_Duration = Return_Item("Account", "Loan_Duration", QString("WHERE Customer_ID = %1 AND Account_Type='%2'")
                                                        .arg(Customer_ID)
                                                        .arg("Loan_Account"));

                QString Loan_Amount_Positive = QString::number(qAbs(Loan_Amount.toFloat()));

                ui->label_LA->setText("Loan Amount");
                ui->lineEdit_LA->setText(Loan_Amount_Positive);
                ui->label_LD->setText("Loan Duration (in months)");
                ui->lineEdit_LD->setText(Loan_Duration);
            }
            break;
        }
        case Account_Type::SAVING_ACCOUNT:
        {
            QString Saving_Amount = Return_Item("Account","Balance",QString("WHERE Customer_ID = %1 AND Account_Type='%2'")
                                            .arg(Customer_ID)
                                            .arg("Saving_Account"));
            if(Saving_Amount == "No")
            {
                QMessageBox_Display("No Saving account found for this national number",QMessageBox::Warning);
            }
            else
            {
                ui->label_LA->setText("Saving Amount");
                ui->lineEdit_LA->setText(Saving_Amount);
                ui->label_LD->setText(" ");
            }
            break;
        }
        case Account_Type::CHECKING_ACCOUNT:
        {

            QString Checking_Amount = Return_Item("Account","Balance",QString("WHERE Customer_ID = %1 AND Account_Type='%2'")
                                              .arg(Customer_ID)
                                              .arg("Checking_Account"));
            if(Checking_Amount == "No")
            {
                QMessageBox_Display("No Checking account found for this national number",QMessageBox::Warning);
            }
            else
            {
                QString Checking_Amount_Positive = QString::number(qAbs(Checking_Amount.toFloat()));
                ui->label_LA->setText("Cheking Amount");
                ui->lineEdit_LA->setText(Checking_Amount_Positive);
                ui->label_LD->setText(" ");
            }
            break;
        }
        default:
            break;
        }
    }
}

/**
 * @brief Loads account information based on the customer's credentials and selected account type.
 *
 * This function is triggered when the associated button is clicked. It first
 * checks the authorization of the customer by calling the `Check_Authorization`
 * method. If the authorization is successful (i.e., a valid customer ID is returned),
 * it retrieves and displays the relevant account information based on the selected
 * account type (Loan, Saving, or Checking).
 *
 * - For a Loan Account:
 *   - Retrieves the loan amount and duration.
 *   - If no loan account is found, a warning message is displayed.
 *
 * - For a Saving Account:
 *   - Retrieves the saving amount.
 *   - If no saving account is found, a warning message is displayed.
 *
 * - For a Checking Account:
 *   - Retrieves the checking amount.
 *   - If no checking account is found, a warning message is displayed.
 *
 * The function sets the corresponding labels and input fields with the retrieved
 * information or displays appropriate warning messages if accounts are not found.
 */

void Edit_Account::on_pushButton_2_clicked()
{
    //submit the edit
    int Customer_ID = Check_Authorization();
    if(Customer_ID > 0)
    {
        switch (account_type) {
        case Account_Type::LOAN_ACCOUNT:
        {
            QString Check = Return_Item("Account","Customer_ID",QString("WHERE Customer_ID = %1 AND Account_ID=%2")
                                                                      .arg(Customer_ID)
                                                                      .arg(1));
            if(Check == "No")
            {
                QMessageBox_Display("No Loan account found for this national number",QMessageBox::Warning);
            }
            else
            {
                float Interest_Rate;
                QString Loan_Amount = ui->lineEdit_LA->text();
                QString Loan_Duration = ui->lineEdit_LD->text();
                QString sql;
                if((Loan_Duration.toInt() > 24) || (Loan_Duration.toInt() <=0))
                {
                    QMessageBox_Display("Faild to update loan account \n the loan duration range is 1 to 24 month",QMessageBox::Critical);
                    return;
                }
                else if((Loan_Duration.toInt() > 0) && (Loan_Duration.toInt() <=6))
                {
                    Interest_Rate = 0.5;
                }
                else if((Loan_Duration.toInt() > 6) &&(Loan_Duration.toInt() <=12))
                {
                    Interest_Rate = 1.0;
                }
                else if((Loan_Duration.toInt() > 12) && (Loan_Duration.toInt() <=18))
                {
                    Interest_Rate = 1.5;
                }
                else if((Loan_Duration.toInt() > 18) && (Loan_Duration.toInt() <=24))
                {
                    Interest_Rate = 2.0;
                }

                sql = QString("UPDATE Account SET Balance=%1, Loan_Duration=%2, Interest_Rate=%3 WHERE Customer_ID=%4 AND Account_ID=%5")
                          .arg(-1*Loan_Amount.toFloat())
                          .arg(Loan_Duration.toInt())
                          .arg(Interest_Rate)
                          .arg(Customer_ID)
                          .arg(1);

                if(updateData(sql))
                {
                    QString text;
                    text = QString("Successfully Updated \n New balance is %1 \n New loan duration is %2 \n New interest rate is %3")
                               .arg(-1*Loan_Amount.toFloat())
                               .arg(Loan_Duration.toInt())
                               .arg(Interest_Rate);
                    QMessageBox_Display(text,QMessageBox::Information);
                }
                else
                {
                    QMessageBox_Display("Error !!! Something is wrong",QMessageBox::Critical);

                }
            }
            break;
        }
        case Account_Type::SAVING_ACCOUNT:
        {
            QString Check = Return_Item("Account","Customer_ID",QString("WHERE Customer_ID = %1 AND Account_ID=%2")
                                            .arg(Customer_ID)
                                            .arg(2));
            if(Check == "No")
            {
                QMessageBox_Display("No Loan account found for this national number",QMessageBox::Warning);
            }
            else
            {
                QString Loan_Amount = ui->lineEdit_LA->text();
                QString sql;
                sql = QString("UPDATE Account SET Balance=%1 WHERE Customer_ID=%2 AND Account_ID=%3")
                          .arg(Loan_Amount.toFloat())
                          .arg(Customer_ID)
                          .arg(2);

                if(updateData(sql))
                {
                    QMessageBox_Display("Successfully Updated",QMessageBox::Information);
                }
                else
                {
                    QMessageBox_Display("Error !!! Something is wrong",QMessageBox::Critical);

                }
            }
            break;
        }
        case Account_Type::CHECKING_ACCOUNT:
        {

            QString Check = Return_Item("Account","Customer_ID",QString("WHERE Customer_ID = %1 AND Account_ID=%2")
                                            .arg(Customer_ID)
                                            .arg(3));
            if(Check == "No")
            {
                QMessageBox_Display("No Loan account found for this national number",QMessageBox::Warning);
            }
            else
            {
                float Credit_Limit = Return_Item("Account","Credit_Limit",QString("WHERE Customer_ID = %1 AND Account_ID=%2")
                                                                               .arg(Customer_ID)
                                                                               .arg(3)).toFloat();
                QString Checking_Amount = ui->lineEdit_LA->text();
                QString sql;
                if(Checking_Amount.toFloat() > Credit_Limit)
                {
                    QString text;
                    text= QString("Failed to update \n You exceed the credit limit %1").arg(Credit_Limit);
                    QMessageBox_Display(text,QMessageBox::Critical);
                    return;

                }
                sql = QString("UPDATE Account SET Balance=%1 WHERE Customer_ID=%2 AND Account_ID=%3")
                          .arg(-1*Checking_Amount.toFloat())
                          .arg(Customer_ID)
                          .arg(3);

                if(updateData(sql))
                {
                    QString text;
                    text = QString("Successfully Updated \n New balance is %1 ")
                               .arg(-1*Checking_Amount.toFloat());
                    QMessageBox_Display(text,QMessageBox::Information);
                }
                else
                {
                    QMessageBox_Display("Error !!! Something is wrong",QMessageBox::Critical);

                }
            }
            break;

        }
        default:
            break;
        }
    }
}

/**
 * @brief Handles the deletion of the selected account type after user confirmation.
 *
 * This function is triggered when the associated button is clicked. It first checks
 * the authorization of the customer by calling the `Check_Authorization` method.
 * If the authorization is successful (i.e., a valid customer ID is returned), it
 * proceeds to check the selected account type (Loan, Saving, or Checking) and
 * attempts to delete the corresponding account if it exists.
 *
 * - For a Loan Account:
 *   - Checks if the customer has a loan account. If not, a warning message is displayed.
 *   - If the account exists, it prompts the user for confirmation before deletion.
 *   - On confirmation, the account is deleted from the database, and a success message is shown.
 *
 * - For a Saving Account:
 *   - Similar process as for the loan account.
 *
 * - For a Checking Account:
 *   - Similar process as for the loan account.
 *
 * If the deletion operation is successful, input fields for the loan amount and duration
 * are cleared. If an error occurs during the deletion, an error message is displayed.
 */
void Edit_Account::on_pushButton_3_clicked()
{
    int Customer_ID = Check_Authorization();
    if(Customer_ID > 0)
    {
        switch (account_type) {
        case Account_Type::LOAN_ACCOUNT:
        {
            QString Check = Return_Item("Account","Customer_ID",QString("WHERE Customer_ID = %1 AND Account_ID=%2")
                                            .arg(Customer_ID)
                                            .arg(1));
            if(Check == "No")
            {
                QMessageBox_Display("No Loan account found for this national number",QMessageBox::Warning);
            }
            else
            {
                int res;
                res=QMessageBox_Display("Are you sure to delete this account ?",QMessageBox::Question);
                if(res == QMessageBox::Yes)
                {
                    QString sql;
                    sql = QString("DELETE FROM Account WHERE Customer_ID=%1 AND Account_ID=%2")
                              .arg(Customer_ID)
                              .arg(1);

                    if(updateData(sql))
                    {
                        ui->lineEdit_LA->setText(" ");
                        ui->lineEdit_LD->setText(" ");
                        QMessageBox_Display("Successfully Deleted",QMessageBox::Information);
                    }
                    else
                    {
                        QMessageBox_Display("Error !!! Something is wrong",QMessageBox::Critical);

                    }
                }

            }
            break;
        }
        case Account_Type::SAVING_ACCOUNT:
        {
            QString Check = Return_Item("Account","Customer_ID",QString("WHERE Customer_ID = %1 AND Account_ID=%2")
                                            .arg(Customer_ID)
                                            .arg(2));
            if(Check == "No")
            {
                QMessageBox_Display("No Loan account found for this national number",QMessageBox::Warning);
            }
            else
            {
                int res;
                res=QMessageBox_Display("Are you sure to delete this account ?",QMessageBox::Question);
                if(res == QMessageBox::Yes)
                {
                    QString sql;
                    sql = QString("DELETE FROM Account WHERE Customer_ID=%1 AND Account_ID=%2")
                              .arg(Customer_ID)
                              .arg(2);

                    if(updateData(sql))
                    {
                        ui->lineEdit_LA->setText(" ");
                        ui->lineEdit_LD->setText(" ");
                        QMessageBox_Display("Successfully Deleted",QMessageBox::Information);
                    }
                    else
                    {
                        QMessageBox_Display("Error !!! Something is wrong",QMessageBox::Critical);

                    }
                }

            }
            break;
        }
        case Account_Type::CHECKING_ACCOUNT:
        {

            QString Check = Return_Item("Account","Customer_ID",QString("WHERE Customer_ID = %1 AND Account_ID=%2")
                                            .arg(Customer_ID)
                                            .arg(3));
            if(Check == "No")
            {
                QMessageBox_Display("No Loan account found for this national number",QMessageBox::Warning);
            }
            else
            {
                int res;
                res=QMessageBox_Display("Are you sure to delete this account ?",QMessageBox::Question);
                if(res == QMessageBox::Yes)
                {
                    QString sql;
                    sql = QString("DELETE FROM Account WHERE Customer_ID=%1 AND Account_ID=%2")
                              .arg(Customer_ID)
                              .arg(3);

                    if(updateData(sql))
                    {
                        ui->lineEdit_LA->setText(" ");
                        ui->lineEdit_LD->setText(" ");
                        QMessageBox_Display("Successfully Deleted",QMessageBox::Information);
                    }
                    else
                    {
                        QMessageBox_Display("Error !!! Something is wrong",QMessageBox::Critical);

                    }
                }

            }
            break;

        }
        default:
            break;
        }
    }
}
/**
 * @brief Updates the UI text based on the selected language from the combo box.
 *
 * This slot is triggered when the current text of the combo box changes.
 * It updates the labels and button texts in the user interface according
 * to the selected language (English, Arabic, French, or German).
 *
 * @param arg1 The new text of the combo box, representing the selected language.
 */
void Edit_Account::on_comboBox_currentTextChanged(const QString &arg1)
{
    if (arg1 == "English") {
        ui->label_NN->setText("National Number");
        ui->label_Name->setText("Name");
        ui->label_Pass->setText("Password");

        ui->pushButton->setText("Load Account Information");
        ui->pushButton_2->setText("Submit Edit");
        ui->pushButton_3->setText("Delete Account");
        ui->checkBox->setText("Show password");





        language = "English";

        if(account_type == Account_Type::LOAN_ACCOUNT)
        {
            ui->label_LA->setText("Loan Amount");
            ui->label_LD->setText("Loan Duration (in months)");
        }
        else if(account_type == Account_Type::SAVING_ACCOUNT)
        {
            ui->label_LA->setText("Saving Amount");
            ui->label_LD->setText(" ");

        }
        else if(account_type == Account_Type::CHECKING_ACCOUNT)
        {
            ui->label_LA->setText("Checking Amount");
            ui->label_LD->setText(" ");
        }
    }
    else if (arg1 == "Arabic") {
        ui->label_NN->setText("رقم القومي");
        ui->label_Name->setText("الاسم");
        ui->label_Pass->setText("كلمة المرور");

        ui->pushButton->setText("تحميل معلومات الحساب");
        ui->pushButton_2->setText("تأكيد التعديلات");
        ui->pushButton_3->setText("حذف الحساب");
        ui->checkBox->setText("اظهار كلمه المرور");

        language = "Arabic";

        if(account_type == Account_Type::LOAN_ACCOUNT)
        {
            ui->label_LA->setText("مبلغ القرض");
            ui->label_LD->setText("مدة القرض (بالشهور)");
        }
        else if(account_type == Account_Type::SAVING_ACCOUNT)
        {
            ui->label_LA->setText("مبلغ الادخار");
            ui->label_LD->setText(" ");

        }
        else if(account_type == Account_Type::CHECKING_ACCOUNT)
        {
            ui->label_LA->setText("مبلغ الحساب الجاري");
            ui->label_LD->setText(" ");
        }

    }
    else if (arg1 == "French") {
        ui->label_NN->setText("Numéro National");
        ui->label_Name->setText("Nom");
        ui->label_Pass->setText("Mot de passe");

        ui->pushButton->setText("Charger les informations du compte");
        ui->pushButton_2->setText("Soumettre la modification");
        ui->pushButton_3->setText("Supprimer le compte");
        ui->checkBox->setText("Afficher le mot de passe");
        language = "French";
        if(account_type == Account_Type::LOAN_ACCOUNT)
        {
            ui->label_LA->setText("Montant du prêt");
            ui->label_LD->setText("Durée du prêt (en mois)");
        }
        else if(account_type == Account_Type::SAVING_ACCOUNT)
        {
            ui->label_LA->setText("Montant de l'épargne");
            ui->label_LD->setText(" ");

        }
        else if(account_type == Account_Type::CHECKING_ACCOUNT)
        {
            ui->label_LA->setText("Montant du compte courant");
            ui->label_LD->setText(" ");
        }


    }
    else if (arg1 == "German") {
        ui->label_NN->setText("Nationale Nummer");
        ui->label_Name->setText("Name");
        ui->label_Pass->setText("Passwort");

        ui->pushButton->setText("Kontoinformationen laden");
        ui->pushButton_2->setText("Änderung speichern");
        ui->pushButton_3->setText("Konto löschen");
        ui->checkBox->setText("Passwort anzeigen");
        language = "German";

        if(account_type == Account_Type::LOAN_ACCOUNT)
        {
            ui->label_LA->setText("Darlehensbetrag");
            ui->label_LD->setText("Darlehensdauer (in Monaten)");
        }
        else if(account_type == Account_Type::SAVING_ACCOUNT)
        {
            ui->label_LA->setText("Einsparungsbetrag");
            ui->label_LD->setText(" ");

        }
        else if(account_type == Account_Type::CHECKING_ACCOUNT)
        {
            ui->label_LA->setText("Scheckbetrag");
            ui->label_LD->setText(" ");
        }

    }
}



/**
 * @brief Toggles the visibility of the password in the password input field.
 *
 * This slot is triggered when the checkbox for showing the password is clicked.
 * It sets the echo mode of the password input field to normal or password
 * based on the checkbox state.
 */
void Edit_Account::on_checkBox_clicked()
{
    if(ui->checkBox->isChecked())
    {
        ui->lineEdit_Password->setEchoMode(QLineEdit::Normal);
    }
    else
    {
        ui->lineEdit_Password->setEchoMode(QLineEdit::Password);
    }
}

