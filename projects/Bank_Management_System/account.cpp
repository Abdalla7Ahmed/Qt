#include "account.h"
#include "ui_account.h"
#include "mainwindow.h"
#include "saving_acount.h"
#include "loan_acount.h"
// #include "checking_acount.h"
#include "customer_operations.h"
#include "edit_account.h"
#include "checking_account.h"



/**
 * @brief Constructor for the Account class.
 * Initializes the Account dialog by setting up the user interface components.
 * It populates the language selection combo box with available options
 * (English, Arabic, German, French) and enables hover events for the buttons.
 * Event filters are installed on the buttons to handle hover interactions.
 *
 * @param parent The parent widget for this dialog, default is nullptr.
 */
Account::Account(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Account)
{
    ui->setupUi(this);

    ui->comboBox->addItem("English");
    ui->comboBox->addItem("Arabic");
    ui->comboBox->addItem("German");
    ui->comboBox->addItem("French");


    // Enable hover event for the buttons
    ui->pushButton_2->setAttribute(Qt::WA_Hover, true);
    ui->pushButton_loan->setAttribute(Qt::WA_Hover, true);
    ui->pushButton_saving->setAttribute(Qt::WA_Hover, true);
    ui->pushButton_Edit->setAttribute(Qt::WA_Hover, true);
    ui->pushButton_3->setAttribute(Qt::WA_Hover, true);

    // Install event filter on the buttons to handle hover events
    ui->pushButton_2->installEventFilter(this);
    ui->pushButton_loan->installEventFilter(this);
    ui->pushButton_saving->installEventFilter(this);
    ui->pushButton_Edit->installEventFilter(this);
    ui->pushButton_3->installEventFilter(this);

}
/**
 * @brief Destructor for Account.
 *
 * Cleans up resources used by the Account instance.
 */
Account::~Account()
{
    delete ui;
}


/**
 * @brief Filters events for specific buttons to handle hover effects.
 * This function checks if the event is for one of the specified buttons.
 * When the mouse enters the button area, it changes the button's style
 * to indicate a hover effect. When the mouse leaves, it reverts the
 * button's style to its original appearance.
 *
 * @param watched The object being watched for events.
 * @param event The event to be processed.
 * @return Returns true if the event was handled; otherwise, it calls
 *         the base class implementation and returns its result.
 */
bool Account::eventFilter(QObject *watched, QEvent *event)
{
    if (watched == ui->pushButton_2 || watched == ui->pushButton_3|| watched == ui->pushButton_loan ||  watched == ui->pushButton_saving ||  watched == ui->pushButton_Edit) {
        if (event->type() == QEvent::HoverEnter) {
            // Change background color when hovering
            dynamic_cast<QPushButton*>(watched)->setStyleSheet("QPushButton { color: 1E0342;font-weight: bold;font-size: 65px;border-radius: 50px;border: 10px solid 1E0342; }");
        }
        else if (event->type() == QEvent::HoverLeave) {
            // Revert background color when the mouse leaves the button
            dynamic_cast<QPushButton*>(watched)->setStyleSheet("QPushButton {color: #1E0342;\nfont-weight: bold;\nfont-size: 45px;\nborder-radius: 50px; \nborder: 2px solid #1E0342;\nbackground-color: #A0DEFF;}");
        }
    }
    return QWidget::eventFilter(watched, event);
}

/**
 * @brief Handles the click event for the loan account button.
 * This function hides the current Account dialog and opens the Loan Account
 * dialog in maximized mode.
 */
void Account::on_pushButton_loan_clicked()
{

    hide();
    loan_account = new Loan_Acount;
    loan_account->showMaximized();
}
/**
 * @brief Handles the click event for the edit account button.
 * This function hides the current Account dialog and opens the Edit Account
 * dialog in maximized mode.
 */
void Account::on_pushButton_Edit_clicked()
{
    hide();
    Edit_Account *edit_account;
    edit_account = new Edit_Account ;
    edit_account->showMaximized();

}
/**
 * @brief Handles the click event for the saving account button.
 * This function hides the current Account dialog and opens the Saving Account
 * dialog in maximized mode.
 */
void Account::on_pushButton_saving_clicked()
{
    hide();
    saving_account = new Saving_Acount;
    saving_account->showMaximized();
}

/**
 * @brief Handles the click event for the main window button.
 * This function hides the current Account dialog and opens the Main Window
 * in maximized mode.
 */
void Account::on_pushButton_clicked()
{
    MainWindow *Main_Window;
    hide();
    Main_Window = new MainWindow;
    Main_Window->showMaximized();
}

/**
 * @brief Handles the click event for the customer operations button.
 * This function hides the current Account dialog and opens the Customer
 * Operations dialog in maximized mode.
 */
void Account::on_pushButton_2_clicked()
{
    // windrow
    Customer_operations * customer_operations;
    hide();
    customer_operations = new Customer_operations;
    customer_operations->showMaximized();
}

/**
 * @brief Handles the click event for the checking account button.
 * This function hides the current Account dialog and opens the Checking
 * Account dialog in maximized mode.
 */
void Account::on_pushButton_3_clicked()
{
    checking_account = new Checking_Account;
    hide();
    checking_account->showMaximized();
}
/**
 * @brief Constructs a BankAccount object with customer details.
 * This constructor initializes a BankAccount instance with the provided
 * customer information such as name, national number, password, address,
 * age, phone number, and email.
 *
 * @param Customer_Name The name of the customer.
 * @param Customer_NN The national number of the customer.
 * @param Customer_Pass The password of the customer.
 * @param Customer_Address The address of the customer.
 * @param Customer_Age The age of the customer.
 * @param m_Customer_phone The phone number of the customer.
 * @param m_Customer_Email The email address of the customer.
 */
BankAccount::BankAccount(QString Customer_Name,QString Customer_NN,QString Customer_Pass,QString Customer_Address ,int Customer_Age,QString m_Customer_phone,QString m_Customer_Email ):
    Customer_Name(Customer_Name),
    Customer_NN(Customer_NN),
    Customer_Pass(Customer_Pass),
    Customer_Address(Customer_Address),
    Customer_Age(Customer_Age),
    m_Customer_phone(m_Customer_phone),
    m_Customer_Email(m_Customer_Email)
{
}
BankAccount::~BankAccount()
{

}

/**
 * @brief Sets the customer's name.
 *
 * This function updates the customer's name in the BankAccount instance.
 *
 * @param Customer_Name The new name of the customer.
 */
void BankAccount::Set_Customer_Name(QString Customer_Name)
{
    this->Customer_Name = Customer_Name;
}
/**
 * @brief Sets the customer's national number.
 *
 * This function updates the customer's national number in the BankAccount instance.
 *
 * @param Customer_NN The new national number of the customer.
 */
void BankAccount::Set_Customer_NN(QString Customer_NN)
{
    this->Customer_NN = Customer_NN;
}
/**
 * @brief Sets the customer's password.
 *
 * This function updates the customer's password in the BankAccount instance.
 *
 * @param Customer_Pass The new password of the customer.
 */
void BankAccount::Set_Customer_Pass(QString Customer_Pass)
{
    this->Customer_Pass = Customer_Pass;
}
/**
 * @brief Sets the customer's address.
 *
 * This function updates the customer's address in the BankAccount instance.
 *
 * @param Customer_Address The new address of the customer.
 */
void BankAccount::Set_Customer_Address(QString Customer_Address)
{
    this->Customer_Address = Customer_Address;

}
/**
 * @brief Sets the customer's age.
 *
 * This function updates the customer's age in the BankAccount instance.
 *
 * @param Customer_Age The new age of the customer.
 */
void BankAccount::Set_Customer_Age(int Customer_Age)
{
    this->Customer_Age = Customer_Age;

}
/**
 * @brief Sets the customer's phone number.
 *
 * This function updates the customer's phone number in the BankAccount instance.
 *
 * @param m_Customer_phone The new phone number of the customer.
 */
void BankAccount::Set_Customer_Phone(QString m_Customer_phone)
{
    this->m_Customer_phone = m_Customer_phone;

}
/**
 * @brief Sets the customer's email address.
 *
 * This function updates the customer's email address in the BankAccount instance.
 *
 * @param m_Customer_Email The new email address of the customer.
 */
void BankAccount::Set_Customer_Email(QString m_Customer_Email)
{
    this->m_Customer_Email = m_Customer_Email;

}
/**
 * @brief Sets the credit limit for the customer.
 *
 * This function updates the customer's credit limit in the BankAccount instance.
 *
 * @param m_Credit_Limit The new credit limit for the customer.
 */
void BankAccount::Set_Credit_Limit(float m_Credit_Limit)
{
    this->m_Credit_Limit = m_Credit_Limit;
}
/**
 * @brief Checks the account information against stored records.
 *
 * This function verifies the customer's national number and corresponding
 * name and password in the database. If the information matches, it
 * returns the customer's ID; otherwise, it returns -1.
 *
 * @return Returns the customer's ID if the information is correct;
 *         otherwise, returns -1 if the national number is not found
 *         or if the information does not match.
 */
int BankAccount::Check_Account_Info(void)
{
    int result =-1;
    qDebug() <<"Checking in progress";

    if(Return_Item("Person","*",QString("WHERE National_Number = %1").arg(Customer_NN)) != "No")
    {
        qDebug() <<"NN found , checking the correct information";
        QString name,pass,id;
        name = Return_Item("Person","Name",QString("WHERE National_Number = %1").arg(Customer_NN));
        pass = Return_Item("Person","Password",QString("WHERE National_Number = %1").arg(Customer_NN));
        id = Return_Item("Person","Customer_ID",QString("WHERE National_Number = %1").arg(Customer_NN));

        // qDebug() <<hashPassword(Customer_Pass);
        if((name == Customer_Name) && (pass == hashPassword(Customer_Pass)))
        {
            qDebug() <<"id = "<<id;
            result = id.toInt();
        }
    }
    else
    {
        qDebug() <<"NN not found return -1";

        result =-1;
    }
    return result;
}

/**
 * @brief Displays a message box with a specified text and icon type.
 *
 * This function creates and displays a QMessageBox with a given message
 * and icon type. It supports different types of messages including
 * questions, information, critical alerts, and warnings.
 *
 * @param text The message text to be displayed in the message box.
 * @param type The type of the message box, determining the icon
 *             and button configuration (e.g., QMessageBox::Question,
 *             QMessageBox::Information, QMessageBox::Critical,
 *             QMessageBox::Warning).
 *
 * @return Returns the result of the message box (e.g.,
 *         QMessageBox::Yes, QMessageBox::No) based on user interaction.
 */
int BankAccount::QMessageBox_Display(QString text,int type)
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("Confirmation Required"); // Set the title
    msgBox.setText(text); // Set the question text

    // Set the icon to a question mark
    if(type == QMessageBox::Question)
    {
        msgBox.setIcon(QMessageBox::Question);
        // Set the buttons and default button
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        msgBox.setDefaultButton(QMessageBox::No);
    }
    else if(type == QMessageBox::Information)
    {
        msgBox.setIcon(QMessageBox::Information);
    }
    else if(type == QMessageBox::Critical)
    {
        msgBox.setIcon(QMessageBox::Critical);
    }
    else if(type == QMessageBox::Warning)
    {
        msgBox.setIcon(QMessageBox::Warning);
    }
    // Optionally, set a fixed size and background color
    msgBox.setStyleSheet("background-color: lightyellow;"); // Change color for questions
    msgBox.setFixedSize(400, 200); // Set a fixed size

    // Show the message box and store the result
    int result = msgBox.exec();
    return result;
}

/**
 * @brief Deposits an amount into the bank account of a customer.
 *
 * This method handles the deposit process, including balance update,
 * OTP generation and validation, and transaction logging.
 *
 * @param Customer_id The ID of the customer making the deposit.
 * @param m_Amount The amount to deposit into the account.
 *
 * The method retrieves the current balance, calculates the new balance,
 * generates an OTP, and sends it via email. It prompts the user to enter
 * the OTP for verification. If the user provides a correct OTP, the
 * deposit is processed, and the new balance is updated in the database.
 *
 * If the deposit is successful, the transaction is logged, and the user
 * is prompted whether they want a report of the last operation. If the
 * user has a checking account and the new balance is non-negative,
 * the checking account is deleted.
 *
 * If the user cancels the operation or does not provide valid input,
 * appropriate warnings are displayed.
 */

void BankAccount::deposit(int Customer_id ,float m_Amount)
{
    QDateTime currentDateTime ;

    float current_balance = Return_Item("Person","Balance",QString("WHERE National_Number = %1").arg(Customer_NN)).toFloat();
    qDebug()<<Customer_NN <<"   current_balance is "<<current_balance;
    qDebug()<<Customer_NN <<"   Customer_id is "<<Customer_id;

    currentDateTime = QDateTime::currentDateTime();
    //update the person table
    float New_balance = current_balance + m_Amount;
    qDebug() <<"the New balance is "<<New_balance;

    QString updateBalance = QString("UPDATE Person SET Balance = %1 WHERE Customer_ID = %2")
                                .arg(New_balance)
                                .arg(Customer_id);


    // Generate OTP
    QString otp = generateOTP();
    qDebug()<< "Code generated : " << otp.toStdString() ;

    // Send OTP via email
    QString recipientEmail = m_Customer_Email;
    // sendEmail(otp, recipientEmail);


    // Show the input dialog
    bool ok;  // Variable to check if the user clicked "OK"
    QString userInput = QInputDialog::getText(nullptr, "Input Dialog",
                                      "We send email with verivication code : ", QLineEdit::Normal,
                                      QString(), &ok);

    // Check if the user clicked "OK"
    if (ok && !userInput.isEmpty()) {
        // Show a message box with the entered input

        // QMessageBox::information(nullptr, "User Input", "You entered: " + userInput);
        if(userInput == otp)
        {
            if(updateData(updateBalance))
            {
                QMessageBox_Display("The balance added successfully",QMessageBox::Information);
                QString transaction = QString("INSERT INTO Account_Transaction (Customer_ID, Date_Time, Transaction_Type, Amount) "
                                              "VALUES (%1, '%2', '%3', %4)")
                                          .arg(Customer_id)
                                          .arg(currentDateTime.toString("yyyy-MM-dd HH:mm:ss"))
                                          .arg("Deposit")
                                          .arg(m_Amount);
                updateData(transaction);
            }
            else
            {
                QMessageBox_Display("Error !!! something is wrong",QMessageBox::Critical);
            }



            if(New_balance >= 0)
            {

                QString check = Return_Item("Account","Customer_id",QString("WHERE Customer_ID=%1 AND Account_ID=%2")
                                                .arg(Customer_id)
                                                .arg(3));
                if(check != "No")
                {
                    //delete the checking account
                    qDebug() <<"he has checking account";
                    //
                    QString sql = QString ("DELETE FROM Account WHERE Customer_ID = %1 AND Account_ID=%2")
                                      .arg(Customer_id)
                                      .arg(3);
                    qDebug() <<sql;
                    updateData(sql);
                }
                else
                {
                    qDebug() <<"no checking account for this id ";

                }
            }
            // ask him if he need a report for the last operation
            QString question = "Are you need a report for the last operation ?";
            int result = QMessageBox_Display(question,QMessageBox::Question);
            // Check the user's response
            if (result == QMessageBox::Yes) {
                // User clicked Yes
                qDebug() <<"Yes";
                QString display_string;
                //date
                //name
                //national id
                //the deposit amount
                //total amount
                display_string = QString("Date : %1 \n Name : %2 \n National Number : %3 \n Deposit Amount : %4 \n Total Amount : %5 \n ")
                                     .arg(currentDateTime.toString("yyyy-MM-dd HH:mm:ss"))
                                     .arg(Customer_Name)
                                     .arg(Customer_NN)
                                     .arg(m_Amount)
                                     .arg(New_balance);

                QMessageBox_Display(display_string,QMessageBox::Information);
            }

        }
        else
        {
            QMessageBox::warning(nullptr, "Input Error", "the code is incorrect");
        }
    }
    else {
        // User canceled or didn't enter anything
        QMessageBox::warning(nullptr, "Input Error", "No input provided!");
    }




}
/**
 * @brief Withdraws an amount from the bank account of a customer.
 *
 * This method handles the withdrawal process, including balance verification,
 * OTP generation and validation, and potential actions when the balance is insufficient.
 * If the withdrawal amount exceeds the current balance, the user is prompted to open
 * a checking account or to withdraw the remaining balance.
 *
 * @param Customer_id The ID of the customer making the withdrawal.
 * @param m_Amount The amount to withdraw from the account.
 *
 * The method generates an OTP, sends it via email, and prompts the user to enter
 * the OTP for verification. If the user provides a correct OTP, the withdrawal is processed.
 * The method also records the transaction and displays confirmation messages.
 *
 * If the new balance is negative and exceeds the credit limit, an error message is displayed.
 * If the user opts to open a checking account, it will create a new account with the remaining
 * balance and update the person's balance accordingly.
 *
 * If the user cancels the operation or does not provide valid input, appropriate warnings
 * are displayed.
 */
void BankAccount::withdraw(int Customer_id ,float m_Amount)
{
    bool flag{false};
    QDateTime currentDateTime = QDateTime::currentDateTime();
    //update the person table
    float current_balance = Return_Item("Person","Balance",QString("WHERE National_Number = %1").arg(Customer_NN)).toFloat();

    float New_balance = current_balance - m_Amount;

    // Generate OTP
    QString otp = generateOTP();
    qDebug()<< "Code generated : " << otp.toStdString() ;

    // Send OTP via email
    QString recipientEmail = m_Customer_Email;
    // sendEmail(otp, recipientEmail);


    // Show the input dialog
    bool ok;  // Variable to check if the user clicked "OK"
    QString userInput = QInputDialog::getText(nullptr, "Input Dialog",
                                              "We send email with verivication code : ", QLineEdit::Normal,
                                              QString(), &ok);

    // Check if the user clicked "OK"
    if (ok && !userInput.isEmpty()) {
        // Show a message box with the entered input

        // QMessageBox::information(nullptr, "User Input", "You entered: " + userInput);
        if(userInput == otp)
        {
            if(New_balance < 0)
            {
                if(qAbs(New_balance) > m_Credit_Limit)
                {
                    // credit limit
                    QString display_question = "You have exceeded the credit limit \n The operation faild ";
                    QMessageBox_Display(display_question,QMessageBox::Critical);
                    return;
                }
                int retans;
                QDate Current_Date = QDate::currentDate();
                QString String_Date = Current_Date.toString("yyyy-MM-dd");
                // below zero
                QString display_question = "You havn't this amount into your account\ndo you want to open checking_account ?";
                retans = QMessageBox_Display(display_question,QMessageBox::Question);
                if(retans == QMessageBox::Yes)
                {
                    // checking account
                    qDebug()<<"open checking_account";
                    QString Data_To_Insert = QString("INSERT INTO Account (Account_ID, Account_Type, Balance, Credit_Limit, Interest_Rate, Principal_Amount, Last_Operation_Date , Loan_Duration, Customer_ID) "
                                                     "VALUES (%1, '%2', %3, '%4', %5, %6, '%7', %8, %9)")
                                                 .arg(3)
                                                 .arg("Checking_Account")
                                                 .arg(New_balance)
                                                 .arg(m_Credit_Limit)
                                                 .arg(1.5)
                                                 .arg(m_Amount)
                                                 .arg(String_Date)
                                                 .arg(0)
                                                 .arg(Customer_id);
                    insertData(Data_To_Insert);
                    QString updateBalance = QString("UPDATE Person SET Balance = %1 WHERE Customer_ID = %2")
                                                .arg(New_balance)
                                                .arg(Customer_id);
                    updateData(updateBalance);

                }
                else if(retans == QMessageBox::No)
                {
                    display_question = "do you want to withdraw the remaining or cancel the operation ?";
                    retans = QMessageBox_Display(display_question,QMessageBox::Question);
                    if(retans == QMessageBox::Yes)
                    {
                        qDebug()<<"withdraw the remaining";
                        QString updateBalance = QString("UPDATE Person SET Balance = %1 WHERE Customer_ID = %2")
                                                    .arg(0.0)
                                                    .arg(Customer_id);
                        updateData(updateBalance);
                        New_balance = 0;
                    }
                    else if(retans == QMessageBox::No)
                    {
                        flag = true;
                        qDebug()<<"cancel the operation ";

                    }
                }

            }
            else
            {
                // there is  enough balance
                QString updateBalance = QString("UPDATE Person SET Balance = %1 WHERE Customer_ID = %2")
                                            .arg(New_balance)
                                            .arg(Customer_id);
                qDebug() <<"befor update person table";
                updateData(updateBalance);

            }
            if(!flag)
            {

                QString question = "Are you need a report for the last operation ?";
                int result = QMessageBox_Display(question,QMessageBox::Question);
                // Check the user's response
                if (result == QMessageBox::Yes)
                {
                    // User clicked Yes
                    qDebug() <<"Yes";
                    QString display_string;
                    //date
                    //name
                    //national id
                    //the deposit amount
                    //total amount
                    display_string = QString("Date : %1 \n Name : %2 \n National Number : %3 \n withdraw Amount : %4 \n Total Amount : %5 \n ")
                                         .arg(currentDateTime.toString("yyyy-MM-dd HH:mm:ss"))
                                         .arg(Customer_Name)
                                         .arg(Customer_NN)
                                         .arg(m_Amount)
                                         .arg(New_balance);

                    QMessageBox_Display(display_string,QMessageBox::Information);
                }
                QString transaction = QString("INSERT INTO Account_Transaction (Customer_ID, Date_Time, Transaction_Type, Amount) "
                                              "VALUES (%1, '%2', '%3', %4)")
                                          .arg(Customer_id)
                                          .arg(currentDateTime.toString("yyyy-MM-dd HH:mm:ss"))
                                          .arg("Withdraw")
                                          .arg(m_Amount);
                updateData(transaction);
            }
        }
        else
        {
            QMessageBox::warning(nullptr, "Input Error", "the code is incorrect");
            return;
        }
    }
    else {
        // User canceled or didn't enter anything
        QMessageBox::warning(nullptr, "Input Error", "No input provided!");
        return;

    }
}




/**
 * @brief Displays the current balance of the customer.
 *
 * This function retrieves the current balance for the customer identified by their
 * national number and displays it in a message box.
 */

void BankAccount::balance_Enquiry(void)
{
    float current_balance = Return_Item("Person","Balance",QString("WHERE National_Number = %1").arg(Customer_NN)).toFloat();
    QString display_string = QString("Current balance is : %1").arg(current_balance);

    QMessageBox_Display(display_string,QMessageBox::Information);
}

/**
 * @brief Adds a new customer to the database.
 *
 * This method handles the process of adding a new customer by collecting
 * user input, generating an OTP for verification, and inserting customer
 * details into the database.
 *
 * The method constructs an SQL query to insert customer information into
 * the "Person" table. It generates a One-Time Password (OTP), which is
 * intended to be sent via email for user verification. The user is then
 * prompted to enter the OTP to confirm their identity.
 *
 * If the user provides a correct OTP, the method attempts to insert the
 * new customer's details into the database. A success or failure message
 * is displayed based on the result of the insertion.
 *
 * @note The actual sending of the OTP email is commented out in this implementation.
 */
void BankAccount::Add_New_Customer(void)
{
    // Create a variable to store the user input
    QString userInput;


    QString data = QString("INSERT INTO Person (Name, Address, National_Number, Password, Balance, Phone, Email, Age) "
                           "VALUES ('%1', '%2', '%3', '%4', %5, '%6', '%7', %8)")
                       .arg(Customer_Name)
                       .arg(Customer_Address)
                       .arg(Customer_NN)
                       .arg(hashPassword(Customer_Pass))
                       .arg(0.0)
                       .arg(m_Customer_phone)
                       .arg(m_Customer_Email)
                       .arg(Customer_Age);
    // Generate OTP
    QString otp = generateOTP();
    // Send OTP via email
    QString recipientEmail = m_Customer_Email;
    sendEmail(otp, recipientEmail);
    // Show the input dialog
    bool ok;  // Variable to check if the user clicked "OK"
    userInput = QInputDialog::getText(nullptr, "Input Dialog",
                                      "We send email with verivication code : ", QLineEdit::Normal,
                                      QString(), &ok);

    // Check if the user clicked "OK"
    if (ok && !userInput.isEmpty()) {
        // Show a message box with the entered input

        // QMessageBox::information(nullptr, "User Input", "You entered: " + userInput);
        if(userInput == otp)
        {
            if(insertData(data))
            {
                QMessageBox_Display("Successfully added",QMessageBox::Information);
            }
            else
            {
                QMessageBox_Display("Faild to add ",QMessageBox::Warning);
            }

        }
        else
        {
            QMessageBox::warning(nullptr, "Input Error", "the code is incorrect");
        }
    }
    else {
        // User canceled or didn't enter anything
        QMessageBox::warning(nullptr, "Input Error", "No input provided!");
    }


}

/**
 * @name BankAccount::Create_Saving_Account
 * @brief Creates or updates a saving account for the customer.
 *
 * This function checks if an account exists for the given national number. If it does, it verifies the customer's name,
 * password, and national number. If all data matches, it either creates a new saving account or updates the existing
 * one with the new balance after a deposit. The transaction details are also logged into the Account_Transaction table.
 *
 * @param Saving_Amount The amount to be deposited into the saving account.
 */
void BankAccount::Create_Saving_Account(float Saving_Amount)
{
    QString check;
    check = Return_Item("Person","National_Number",QString("WHERE National_Number = %1").arg(Customer_NN));
    if(check == "No")
    {
        QMessageBox_Display("there is no account with National_Number " ,QMessageBox::Critical);
    }
    else
    {
        QString name,pass,nn,id;
        name = Return_Item("Person","Name",QString("WHERE National_Number = %1").arg(Customer_NN));
        pass = Return_Item("Person","Password",QString("WHERE National_Number = %1").arg(Customer_NN));
        nn = Return_Item("Person","National_Number",QString("WHERE National_Number = %1").arg(Customer_NN));
        id = Return_Item("Person","Customer_ID",QString("WHERE National_Number = %1").arg(Customer_NN));
        if((name !=Customer_Name) || (pass !=hashPassword(Customer_Pass)) || (nn !=Customer_NN))
        {
            QMessageBox_Display("plese enter correct data",QMessageBox::Critical);
        }
        else
        {
            QDate Current_Date = QDate::currentDate();
            QString String_Date = Current_Date.toString("yyyy-MM-dd");
            QString check_if_exist;
            check_if_exist = Return_Item("Account","Customer_ID",QString("WHERE Customer_ID = %1 AND Account_Type = '%2'").arg(id,"Saving_Account"));
            QString Data_To_Insert;
            if(check_if_exist == "No")
            {
                Data_To_Insert = QString("INSERT INTO Account (Account_ID, Account_Type, Balance, Credit_Limit, Interest_Rate, Principal_Amount, Last_Operation_Date, Loan_Duration, Customer_ID) "
                                     "VALUES (%1, '%2', %3, '%4', %5, %6, '%7', %8, %9)")
                                 .arg(2)
                                 .arg("Saving_Account")
                                 .arg(Saving_Amount)
                                 .arg(0.0)
                                 .arg(1.5)
                                 .arg(Saving_Amount)
                                 .arg(String_Date)
                                 .arg(0)
                                 .arg(id);
                if(insertData(Data_To_Insert))
                {
                    QString text;
                    text = QString("Successfully added \nSaving Amount is %1\nInterest rate is %2")
                               .arg(Saving_Amount)
                               .arg(1.5);
                    QMessageBox_Display(text,QMessageBox::Information);
                    // write the transaction infromartion
                    QString transaction = QString("INSERT INTO Account_Transaction (Customer_ID, Date_Time, Transaction_Type, Amount) "
                                                  "VALUES (%1, '%2', '%3', %4)")
                                              .arg(id)
                                              .arg(String_Date)
                                              .arg("Deposit")
                                              .arg(Saving_Amount);

                    insertData(transaction);
                }
            }
            else
            {
                QMessageBox_Display("Account already exist go to the edit account window",QMessageBox::Warning);
                return ;

            }

        }


    }

}


/**
 * @brief Creates or updates a loan account for the customer.
 *
 * This function checks if an account exists for the given national number. It verifies the customer's name, password,
 * and national number. If the data matches, it calculates the new balance after applying the loan amount and interest.
 * If the loan account does not exist, it creates a new one; otherwise, it updates the existing account with the new balance
 * and loan duration. The transaction details are logged into the Account_Transaction table.
 *
 * @param Loan_Amount The amount of the loan to be created.
 * @param Loan_Duration The duration of the loan in months.
 * @param Interest_Rate The interest rate for the loan.
 */

void BankAccount::Create_Loan_Account(float Loan_Amount,int Loan_Duration,float Interest_Rate)
{
    QString name,pass,nn,id;
    name = Return_Item("Person","Name",QString("WHERE National_Number = %1").arg(Customer_NN));
    pass = Return_Item("Person","Password",QString("WHERE National_Number = %1").arg(Customer_NN));
    nn = Return_Item("Person","National_Number",QString("WHERE National_Number = %1").arg(Customer_NN));
    id = Return_Item("Person","Customer_ID",QString("WHERE National_Number = %1").arg(Customer_NN));

    if((name !=Customer_Name) || (pass !=hashPassword(Customer_Pass))|| (nn !=Customer_NN))
    {
        QMessageBox_Display("plese enter correct data",QMessageBox::Critical);

    }
    else
    {
        QDate Current_Date = QDate::currentDate();
        QString String_Date = Current_Date.toString("yyyy-MM-dd");
        QString check_if_exist;
        check_if_exist = Return_Item("Account","Customer_ID",QString("WHERE Customer_ID = %1 AND Account_Type = '%2'").arg(id,"Loan_Account"));
        QString Dat_To_Insert;
        if(check_if_exist == "No")
        {
            // the account doesn't exist
            // create new one
            Dat_To_Insert = QString("INSERT INTO Account (Account_ID, Account_Type, Balance, Credit_Limit, Interest_Rate, Principal_Amount, Last_Operation_Date, Loan_Duration, Customer_ID) "
                                 "VALUES (%1, '%2', %3, '%4', %5, %6, '%7', %8, %9)")
                             .arg(1)
                             .arg("Loan_Account")
                             .arg(-1*Loan_Amount)
                             .arg(0.0)
                             .arg(Interest_Rate)
                             .arg(Loan_Amount)
                             .arg(String_Date)
                             .arg(Loan_Duration)
                             .arg(id);
            if(insertData(Dat_To_Insert))
            {
                QString text;
                text = QString("Successfully added \nLoan Amount is %1\nLoan duration is %2\nInterest rate is %3")
                           .arg(Loan_Amount)
                           .arg(Loan_Duration)
                           .arg(Interest_Rate);
                QMessageBox_Display(text,QMessageBox::Information);

                // write the transaction infromartion
                QString transaction = QString("INSERT INTO Account_Transaction (Customer_ID, Date_Time, Transaction_Type, Amount) "
                                              "VALUES (%1, '%2', '%3', %4)")
                                          .arg(id)
                                          .arg(String_Date)
                                          .arg("Withdraw")
                                          .arg(Loan_Amount);
                insertData(transaction);
            }
        }
        else
        {
            QMessageBox_Display("Account already exist go to the edit account window",QMessageBox::Warning);
            return ;

        }


    }
}

/**
 * @brief Creates or updates a checking account for the customer.
 *
 * This function checks if an account exists for the given national number. It verifies the customer's name, password,
 * and national number. If the data matches, it creates a new checking account with the specified amount if it doesn't
 * exist, or updates the balance of the existing checking account by deducting the specified amount. The transaction details
 * are logged into the Account_Transaction table.
 *
 * @param Cheking_Amount The amount to be deposited into or deducted from the checking account.
 */
void BankAccount::Create_Checking_Account(float Cheking_Amount)
{
    QString check;
    check = Return_Item("Person","National_Number",QString("WHERE National_Number = %1").arg(Customer_NN));
    if(check == "No")
    {
        QMessageBox_Display("there is no account with National_Number " ,QMessageBox::Critical);
    }
    else
    {
        QString name,pass,nn,id,string_balance;
        float b,balance,New_balance_Checking;
        name = Return_Item("Person","Name",QString("WHERE National_Number = %1").arg(Customer_NN));
        pass = Return_Item("Person","Password",QString("WHERE National_Number = %1").arg(Customer_NN));
        nn = Return_Item("Person","National_Number",QString("WHERE National_Number = %1").arg(Customer_NN));
        id = Return_Item("Person","Customer_ID",QString("WHERE National_Number = %1").arg(Customer_NN));

        if((name !=Customer_Name) || (pass !=hashPassword(Customer_Pass)) || (nn !=Customer_NN))
        {
            QMessageBox_Display("plese enter correct data",QMessageBox::Critical);
        }
        else
        {
            QDate Current_Date = QDate::currentDate();
            QString String_Date = Current_Date.toString("yyyy-MM-dd");
            QString check_if_exist;
            check_if_exist = Return_Item("Account","Customer_ID",QString("WHERE Customer_ID = %1 AND Account_Type = '%2'").arg(id,"Checking_Account"));
            QString Data_To_Insert;
            if(check_if_exist == "No")
            {
                Data_To_Insert = QString("INSERT INTO Account (Account_ID, Account_Type, Balance, Credit_Limit, Interest_Rate, Principal_Amount, Last_Operation_Date, Loan_Duration, Customer_ID) "
                                         "VALUES (%1, '%2', %3, '%4', %5, %6, '%7', %8, %9)")
                                     .arg(3)
                                     .arg("Checking_Account")
                                     .arg(-1*Cheking_Amount)
                                     .arg(m_Credit_Limit)
                                     .arg(1.5)
                                     .arg(Cheking_Amount)
                                     .arg(String_Date)
                                     .arg(0)
                                     .arg(id);
                if(insertData(Data_To_Insert))
                {
                    QString text;
                    text = QString("Successfully added \nChecking Amount is %1\nInterest rate is %2")
                               .arg(Cheking_Amount)
                               .arg(1.5);
                    QMessageBox_Display(text,QMessageBox::Information);
                    // write the transaction infromartion
                    QString transaction = QString("INSERT INTO Account_Transaction (Customer_ID, Date_Time, Transaction_Type, Amount) "
                                                  "VALUES (%1, '%2', '%3', %4)")
                                              .arg(id)
                                              .arg(String_Date)
                                              .arg("Withdraw")
                                              .arg(Cheking_Amount);
                    insertData(transaction);
                }
            }
            else
            {
                QMessageBox_Display("Account already exist go to the edit account window",QMessageBox::Warning);
                return ;

            }

        }


    }
}
/**
 * @brief Generates a random One-Time Password (OTP).
 *
 * This method generates a 6-digit OTP using a random number generator
 * seeded from a hardware random device. The OTP is returned as a
 * QString.
 *
 * @return A QString containing the generated 6-digit OTP.
 */
QString BankAccount::generateOTP() {
    std::random_device rd;  // Obtain a random number from hardware
    std::mt19937 gen(rd()); // Seed the generator
    std::uniform_int_distribution<> distr(100000, 999999); // Define the range (6-digit number)

    int otp = distr(gen);  // Generate the random number
    return QString::number(otp);  // Convert to QString
}
/**
 * @brief Sends an OTP to a specified email address.
 *
 * This method uses a Python script to send an OTP via email. It starts
 * a QProcess to execute the Python script, passing the OTP and the
 * recipient's email address as arguments.
 *
 * @param otp The One-Time Password to be sent.
 * @param recipientEmail The email address of the recipient.
 *
 * @note Ensure that the Python script specified in `scriptPath` is
 * configured correctly to send emails.
 */
void BankAccount::sendEmail(const QString& otp, const QString& recipientEmail) {
    QString scriptPath = "/home/abdallah/Documents/Github/Embedded_Linux_Diploma/qt/1_Widget_applications/Bank_Management_System/send_email.py";
    QProcess process;
    process.start("python3", QStringList() << scriptPath << otp << recipientEmail);
    process.waitForFinished();
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
void Account::on_comboBox_currentTextChanged(const QString &arg1)
{
    if (arg1 == "English") {
        ui->pushButton_2->setText("Normal Operations");
        ui->pushButton_Edit->setText("Edit Account");
        ui->pushButton_loan->setText("Create Loan Account");
        ui->pushButton_saving->setText("Create Saving Account");
        ui->pushButton_3->setText("Create Checking Account");
    }
    else if (arg1 == "Arabic") {
        ui->pushButton_2->setText("عمليات عادية");
        ui->pushButton_Edit->setText("تعديل الحساب");
        ui->pushButton_loan->setText("إنشاء حساب قرض");
        ui->pushButton_saving->setText("إنشاء حساب توفير");
        ui->pushButton_3->setText("إنشاء حساب جاري");

    }
    else if (arg1 == "French") {
        ui->pushButton_2->setText("Opérations normales");
        ui->pushButton_Edit->setText("Modifier le compte");
        ui->pushButton_loan->setText("Créer un compte de prêt");
        ui->pushButton_saving->setText("Créer un compte d'épargne");
        ui->pushButton_3->setText("créer un compte courant");


    }
    else if (arg1 == "German") {
        ui->pushButton_2->setText("Normale Operationen");
        ui->pushButton_Edit->setText("Konto bearbeiten");
        ui->pushButton_loan->setText("Darlehenskonto erstellen");
        ui->pushButton_saving->setText("Sparkonto erstellen");
        ui->pushButton_3->setText("Girokonto erstellen");

    }

}



