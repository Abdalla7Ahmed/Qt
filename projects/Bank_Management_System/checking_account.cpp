#include "checking_account.h"
#include "ui_checking_account.h"
#include "mainwindow.h"
#include "account.h"

/**
 * @brief The Checking_Account class provides a dialog for managing checking accounts.
 *
 * This class inherits from QDialog and allows users to create and manage their checking accounts.
 */
Checking_Account::Checking_Account(QWidget *parent)
    : QDialog(parent), ui(new Ui::Checking_Account)
{
    ui->setupUi(this);
    ui->comboBox->addItem("English");
    ui->comboBox->addItem("Arabic");
    ui->comboBox->addItem("German");
    ui->comboBox->addItem("French");
}
/**
 * @brief Destructor for Checking_Account.
 */
Checking_Account::~Checking_Account()
{
    delete ui;
}
/**
 * @brief Slot for handling the home button click.
 *
 * Navigates to the main window.
 */
void Checking_Account::on_pushButton_Home_clicked()
{
    MainWindow *Main_Window;
    Main_Window = new MainWindow;
    hide();
    Main_Window->showMaximized();
}
/**
 * @brief Slot for handling the back button click.
 *
 * Navigates back to the account window.
 */
void Checking_Account::on_pushButton_Back_clicked()
{
    Account *accountWindow;
    accountWindow = new Account;
    hide();
    accountWindow->showMaximized();
}
/**
 * @brief Slot for handling the next button click.
 *
 * Validates user input and creates a checking account.
 */
void Checking_Account::on_pushButton_Next_clicked()
{
    QString Customer_Name;
    QString Customer_NN;
    QString Customer_Password;
    QString Checking_Amount;
    Customer_Name = ui->lineEdit_Name->text();
    Customer_NN = ui->lineEdit_NN->text();
    Customer_Password = ui->lineEdit_Password->text();
    Checking_Amount = ui->lineEdit_SA->text();

    Bank_Checking bankchecking(Customer_Name, Customer_Password, Customer_NN);
    bool flag{false};
    if (Customer_Name.isEmpty())
    {
        ui->lineEdit_Name->setText("*");
        flag = true;
    }
    if (Customer_NN.isEmpty())
    {
        ui->lineEdit_NN->setText("*");
        flag = true;
    }
    if (Customer_Password.isEmpty())
    {
        ui->lineEdit_Password->setText("*");
        flag = true;
    }
    if (Checking_Amount.isEmpty())
    {
        ui->lineEdit_SA->setText("*");
        flag = true;
    }
    if (!flag)
    {
        if(Checking_Amount.toFloat() == 0)
        {
            bankchecking.QMessageBox_Display("Faild Write valid amount !!!!",QMessageBox::Warning);
            return;
        }
        bankchecking.Create_Checking_Account(Checking_Amount.toFloat());
    }
}
/**
 * @brief Constructs a Bank_Checking object with specified customer details.
 *
 * Initializes the checking account with customer information.
 *
 * @param Customer_Name The name of the customer.
 * @param Customer_Pass The password of the customer.
 * @param Customer_NN The national number of the customer.
 */
Bank_Checking::Bank_Checking(QString Customer_Name, QString Customer_Pass, QString Customer_NN)
{
    Initialize_Data_Base(Get_Data_Base_Name());
    Set_Customer_NN(Customer_NN);
    Set_Customer_Name(Customer_Name);
    Set_Customer_Pass(Customer_Pass);
    Set_Credit_Limit(m_Credit_Limit);
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
void Checking_Account::on_comboBox_currentTextChanged(const QString &arg1)
{
    if (arg1 == "English")
    {
        ui->label_NN->setText("National Number");
        ui->label_Name->setText("Name");
        ui->label_Pass->setText("Password");
        ui->label_SA->setText("Checking Amount");
        ui->checkBox->setText("Show password");
    }
    else if (arg1 == "Arabic")
    {
        ui->label_NN->setText("رقم وطني");
        ui->label_Name->setText("اسم");
        ui->label_Pass->setText("كلمة المرور");
        ui->label_SA->setText("المبلغ");
        ui->checkBox->setText("عرض كلمة المرور");
    }
    else if (arg1 == "German")
    {
        ui->label_NN->setText("Nationalnummer");
        ui->label_Name->setText("Name");
        ui->label_Pass->setText("Passwort");
        ui->label_SA->setText("Prüfbetrag");
        ui->checkBox->setText("Passwort anzeigen");
    }
    else if (arg1 == "French")
    {
        ui->label_NN->setText("Numéro national");
        ui->label_Name->setText("Nom");
        ui->label_Pass->setText("Mot de passe");
        ui->label_SA->setText("Montant de vérification");
        ui->checkBox->setText("Afficher le mot de passe");
    }
}
/**
 * @brief Toggles the visibility of the password in the password input field.
 *
 * This slot is triggered when the checkbox for showing the password is clicked.
 * It sets the echo mode of the password input field to normal or password
 * based on the checkbox state.
 */
void Checking_Account::on_checkBox_clicked()
{
    if (ui->checkBox->isChecked())
    {
        ui->lineEdit_Password->setEchoMode(QLineEdit::Normal);
    }
    else
    {
        ui->lineEdit_Password->setEchoMode(QLineEdit::Password);
    }
}
