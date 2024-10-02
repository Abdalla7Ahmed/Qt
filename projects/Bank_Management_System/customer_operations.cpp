#include "customer_operations.h"
#include "ui_customer_operations.h"
#include "mainwindow.h"
#include "account.h"

/**
 * @brief Constructs a Customer_operations dialog.
 *
 * This constructor initializes the dialog and sets up the UI elements,
 * including populating the language selection combo box with options.
 *
 * @param parent Pointer to the parent widget for this dialog.
 */
Customer_operations::Customer_operations(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Customer_operations)
{
    ui->setupUi(this);
    ui->comboBox->addItem("English");
    ui->comboBox->addItem("Arabic");
    ui->comboBox->addItem("German");
    ui->comboBox->addItem("French");

}
/**
 * @brief Destructor for the Customer_operations class.
 *
 * Cleans up the allocated UI resources.
 */
Customer_operations::~Customer_operations()
{
    delete ui;
}
/**
 * @brief Performs a banking operation based on the specified operation type.
 *
 * This function retrieves user input for the customer's name, national number,
 * password, and the amount for the transaction. It validates the inputs and checks
 * if an account exists with the provided national number. Depending on the operation
 * type (deposit, withdraw, or balance enquiry), it executes the corresponding action.
 *
 * @param current_type The type of operation to perform, which can be one of:
 *        - Operation_Type::DEPOSIT
 *        - Operation_Type::WITHDRAW
 *        - Operation_Type::BALANCE_ENQUIRY
 *
 * This function also displays appropriate error messages if any input validation fails
 * or if the specified account does not exist.
 */
void Customer_operations::make_action(Operation_Type current_type)
{

    QString Customer_Name;
    QString Customer_NN;
    QString Customer_Password;
    float Amount;

    Customer_Name = ui->lineEdit_Name->text();
    Customer_NN = ui->lineEdit_NN->text();
    Customer_Password = ui->lineEdit_Password->text();
    Amount = ui->lineEdit_Amount->text().toFloat();
    Make_Operation operation(Customer_Name,Customer_NN,Customer_Password);
    bool flag{false};
    if(Customer_Name.isEmpty())
    {
        ui->lineEdit_Name->setText("*");
        flag =true;
    }
    if(Customer_NN.isEmpty())
    {
        ui->lineEdit_NN->setText("*");
        flag =true;
    }
    if(Customer_Password.isEmpty())
    {
        ui->lineEdit_Password->setText("*");
        flag =true;
    }

    if(!flag)
    {
        QString check;
        check = operation.Return_Item("Person","National_Number",QString("WHERE National_Number = %1").arg(Customer_NN));
        if(check == "No")
        {
            operation.QMessageBox_Display("there is no account with National_Number ",QMessageBox::Critical);
        }
        else
        {
            int id;
            float current_balance{};
            current_balance = operation.Return_Item("Person","Balance",QString("WHERE National_Number = %1").arg(Customer_NN)).toFloat();
            id = operation.Check_Account_Info();
            if(id ==-1)
            {
                operation.QMessageBox_Display("plese enter correct data",QMessageBox::Critical);

            }
            else
            {
                if(current_type == Operation_Type::BALANCE_ENQUIRY)
                {
                    operation.balance_Enquiry();
                }
                else if (current_type == Operation_Type::DEPOSIT)
                {

                    operation.deposit(id,Amount);

                }
                else if (current_type == Operation_Type::WITHDRAW)
                {
                    operation.withdraw(id,Amount);


                }
            }
        }

    }

}


/**
 * @brief Constructs a Make_Operation object with specified customer details.
 *
 * This constructor initializes the database connection and sets the customer
 * name, national number, and password for the operation.
 *
 * @param Customer_Name The name of the customer.
 * @param Customer_NN The national number of the customer.
 * @param Customer_Pass The password of the customer.
 */
Make_Operation::Make_Operation(QString Customer_Name,QString Customer_NN,QString Customer_Pass)
{
    Initialize_Data_Base(Get_Data_Base_Name());
    Set_Customer_Name(Customer_Name);
    Set_Customer_NN(Customer_NN);
    Set_Customer_Pass(Customer_Pass);

}



Make_Operation::~Make_Operation()
{

}
/**
 * @brief Handles the deposit button click event.
 *
 * This slot sets the current operation type to DEPOSIT and calls
 * make_action() to perform the deposit operation.
 */
void Customer_operations::on_pushButton_Deposit_clicked()
{
    //Deposit
    current_type = Operation_Type::DEPOSIT;
    make_action(current_type);
}
/**
 * @brief Handles the withdraw button click event.
 *
 * This slot sets the current operation type to WITHDRAW and calls
 * make_action() to perform the withdrawal operation.
 */
void Customer_operations::on_pushButton_Withdraw_clicked()
{
    //withdraw
    current_type = Operation_Type::WITHDRAW;
    make_action(current_type);
}

/**
 * @brief Handles the balance enquiry button click event.
 *
 * This slot sets the current operation type to BALANCE_ENQUIRY and calls
 * make_action() to perform the balance enquiry operation.
 */
void Customer_operations::on_pushButton_Balance_clicked()
{
    //Balance Enquiry
    current_type = Operation_Type::BALANCE_ENQUIRY;
    make_action(current_type);
}
/**
 * @brief Handles the home button click event.
 *
 * This slot hides the current dialog and opens the main window,
 * maximizing it.
 */
void Customer_operations::on_pushButton_Home_clicked()
{
    //home
    hide();
    MainWindow *mainwindow;
    mainwindow = new MainWindow;
    mainwindow->showMaximized();
}

/**
 * @brief Handles the back button click event.
 *
 * This slot hides the current dialog and opens the account window,
 * maximizing it.
 */
void Customer_operations::on_pushButton_Back_clicked()
{
    //back
    hide();
    Account *account;
    account = new Account;
    account->showMaximized();
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
void Customer_operations::on_comboBox_currentTextChanged(const QString &arg1)
{

    if(arg1 == "English")
    {
        ui->label_NN->setText("National Number");
        ui->label_Name->setText("Name");
        ui->label_A->setText("Amount");
        ui->label_Pass->setText("Password");

        ui->pushButton_Deposit->setText("Deposit");
        ui->pushButton_Withdraw->setText("Withdraw");
        ui->pushButton_Balance->setText("Balance Enquiry");

        ui->checkBox->setText("Show password");

    }
    else if (arg1 == "Arabic")
    {
        ui->label_NN->setText("الرقم القومي");
        ui->label_Name->setText("الاسم");
        ui->label_A->setText("الكمية");
        ui->label_Pass->setText("الرقم السري");

        ui->pushButton_Deposit->setText("ايداع");
        ui->pushButton_Withdraw->setText("سحب");
        ui->pushButton_Balance->setText("الاستعلام عن الرصيد");

        ui->checkBox->setText("اظهار كلمه المرور");

    }
    else if (arg1 == "French")
    {
        ui->label_NN->setText("Numéro national");
        ui->label_Name->setText("Nom");
        ui->label_A->setText("Montant");
        ui->label_Pass->setText("Mot de passe");

        ui->pushButton_Deposit->setText("Déposer");
        ui->pushButton_Withdraw->setText("Retirer");
        ui->pushButton_Balance->setText("Demande de solde");

        ui->checkBox->setText("Afficher le mot de passe");

    }
    else if (arg1 == "German")
    {
        ui->label_NN->setText("Personalausweisnummer");
        ui->label_Name->setText("Name");
        ui->label_A->setText("Betrag");
        ui->label_Pass->setText("Passwort");

        ui->pushButton_Deposit->setText("Einzahlen");
        ui->pushButton_Withdraw->setText("Abheben");
        ui->pushButton_Balance->setText("Kontostand abfragen");

        ui->checkBox->setText("Passwort anzeigen");

    }

}

/**
 * @brief Toggles the visibility of the password in the password input field.
 *
 * This slot is triggered when the checkbox for showing the password is clicked.
 * It sets the echo mode of the password input field to normal or password
 * based on the checkbox state.
 */
void Customer_operations::on_checkBox_clicked()
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

