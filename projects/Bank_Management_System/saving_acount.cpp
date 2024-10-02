#include "saving_acount.h"
#include "ui_saving_acount.h"
#include "mainwindow.h"
#include "account.h"


/**
 * @brief Constructs a Saving_Acount dialog with language selection.
 *
 * This constructor initializes the dialog and sets up the user interface.
 * It also populates the language combo box with available options.
 *
 * @param parent The parent widget of this dialog, default is nullptr.
 */
Saving_Acount::Saving_Acount(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Saving_Acount)
{
    ui->setupUi(this);
    ui->comboBox->addItem("English");
    ui->comboBox->addItem("Arabic");
    ui->comboBox->addItem("German");
    ui->comboBox->addItem("French");

}
/**
 * @brief Destructor for the Saving_Acount class.
 *
 * Cleans up the allocated UI resources.
 */
Saving_Acount::~Saving_Acount()
{
    delete ui;
}
/**
 * @brief Handles the click event for the main window button.
 * This function hides the current Account dialog and opens the Main Window
 * in maximized mode.
 */
void Saving_Acount::on_pushButton_Home_clicked()
{
    MainWindow *Main_Window;
    Main_Window = new MainWindow;
    hide();
    Main_Window->showMaximized();
}
/**
 * @brief Navigates back to the account window.
 *
 * This slot is called when the back button is clicked. It hides the current
 * Saving_Acount dialog and displays the Account window.
 */
void Saving_Acount::on_pushButton_Back_clicked()
{
    Account *accountWindow;
    accountWindow = new Account;
    hide();
    accountWindow->showMaximized();
}

/**
 * @brief Validates user input and creates a savings account.
 *
 * This slot is called when the next button is clicked. It retrieves the
 * customer's name, national number, password, and saving amount from the
 * input fields. It checks for empty fields and, if all fields are valid,
 * creates a new savings account.
 */
void Saving_Acount::on_pushButton_Next_clicked()
{
    // Bank_Saving banksaving;

    QString Customer_Name;
    QString Customer_NN;
    QString Customer_Password;
    QString Saving_Amount;
    Customer_Name = ui->lineEdit_Name->text();
    Customer_NN = ui->lineEdit_NN->text();
    Customer_Password = ui->lineEdit_Password->text();
    Saving_Amount = ui->lineEdit_SA->text();

    Bank_Saving banksaving(Customer_Name,Customer_Password,Customer_NN);
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
    if(Saving_Amount.isEmpty())
    {
        ui->lineEdit_SA->setText("*");
        flag =true;
    }
    if(!flag)
    {
        if(Saving_Amount.toFloat() == 0)
        {
            banksaving.QMessageBox_Display("Faild Write valid amount !!!!",QMessageBox::Warning);
            return;
        }
        banksaving.Create_Saving_Account(Saving_Amount.toFloat());
    }

}

/**
 * @brief Constructs a Bank_Saving object with customer details.
 *
 * This constructor initializes the database and sets the customer's
 * national number, name, and password.
 *
 * @param Customer_Name The name of the customer.
 * @param Customer_Pass The password of the customer.
 * @param Customer_NN The national number of the customer.
 */
Bank_Saving::Bank_Saving(QString Customer_Name,QString Customer_Pass,QString Customer_NN)
{
    Initialize_Data_Base(Get_Data_Base_Name());
    Set_Customer_NN(Customer_NN);
    Set_Customer_Name(Customer_Name);
    Set_Customer_Pass(Customer_Pass);
}
/**
 * @brief Default constructor for Bank_Saving.
 *
 * This constructor initializes the database without setting any customer details.
 */
Bank_Saving::Bank_Saving()
{
    Initialize_Data_Base(Get_Data_Base_Name());
}
/**
 * @brief Destructor for Bank_Saving.
 *
 */
Bank_Saving::~Bank_Saving()
{

}
/**
 * @brief Gets the interest rate for the saving account.
 *
 * @return The interest rate.
 */
int Bank_Saving::Get_Interset_Rate(void)
{
    return this->m_Interset_Rate;
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
void Saving_Acount::on_comboBox_currentTextChanged(const QString &arg1)
{
    if(arg1 == "English")
    {
        ui->label_NN->setText("National Number");
        ui->label_Name->setText("Name");
        ui->label_Pass->setText("Password");
        ui->label_SA->setText("Saving Amount");
        ui->checkBox->setText("Show password");

    }
    else if (arg1 == "Arabic")
    {
        ui->label_Pass->setText("كلمة المرور");
        ui->label_NN->setText("الرقم القومي");
        ui->label_Name->setText("الاسم");
        ui->label_SA->setText("مبلغ الادخار");
        ui->checkBox->setText("اظهار كلمه المرور");

    }
    else if (arg1 == "German")
    {
        ui->label_NN->setText("Personalausweisnummer");
        ui->label_Name->setText("Name");
        ui->label_Pass->setText("Passwort");
        ui->label_SA->setText("Sparbetrag");
        ui->checkBox->setText("Passwort anzeigen");

    }
    else if (arg1 == "French")
    {
        ui->label_NN->setText("Numéro national");
        ui->label_Name->setText("Nom");
        ui->label_Pass->setText("Mot de passe");
        ui->label_SA->setText("Montant d'épargne");
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
void Saving_Acount::on_checkBox_clicked()
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

