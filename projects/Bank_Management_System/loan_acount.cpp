#include "ui_loan_acount.h"
#include "mainwindow.h"
#include "loan_acount.h"
#include <QMessageBox>
/**
 * @brief Constructs a Loan_Acount object.
 *
 * Initializes the Loan_Acount dialog and sets up the UI components,
 * including adding language options to the combo box.
 *
 * @param parent The parent widget, default is nullptr.
 */
Loan_Acount::Loan_Acount(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Loan_Acount)
{
    ui->setupUi(this);
    ui->comboBox->addItem("English");
    ui->comboBox->addItem("Arabic");
    ui->comboBox->addItem("German");
    ui->comboBox->addItem("French");
}
/**
 * @brief Destructor for the Loan_Acount class.
 *
 * Cleans up the allocated UI resources.
 */
Loan_Acount::~Loan_Acount()
{
    delete ui;
}
/**
 * @brief Navigates to the home screen.
 *
 * This slot is triggered when the home button is clicked. It hides
 * the current dialog and shows the main window.
 */
void Loan_Acount::on_pushButton_Home_clicked()
{
    MainWindow *Main_Window;
    hide();
    Main_Window = new MainWindow;
    Main_Window->showMaximized();
}

/**
 * @brief Navigates back to the previous screen.
 *
 * This slot is triggered when the back button is clicked. It hides
 * the current dialog and shows the account window.
 */
void Loan_Acount::on_pushButton_Back_clicked()
{
    Account *accountWindow;
    hide();
    accountWindow = new Account;
    accountWindow->showMaximized();
}

/**
 * @brief Proceeds to the next step in the loan application process.
 *
 * This slot is triggered when the next button is clicked. It validates
 * the user input, checks for existing accounts, and creates a loan
 * account if all conditions are met.
 */
void Loan_Acount::on_pushButton_Next_clicked()
{
    // BankLoan bankloan;

    QString Customer_Name;
    QString Customer_NN;
    QString Customer_Password;


    Customer_Name = ui->lineEdit_Name->text();
    Customer_NN = ui->lineEdit_NN->text();
    Customer_Password = ui->lineEdit_Password->text();
    BankLoan bankloan(Customer_Name,Customer_Password,Customer_NN);
    bankloan.Set_Loan_Amount(ui->lineEdit_LA->text().toFloat());
    bankloan.Set_Loan_Duration(ui->lineEdit_LD->text().toInt());


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
    if(ui->lineEdit_LA->text().isEmpty())
    {
        ui->lineEdit_LA->setText("*");
        flag =true;
    }
    if(ui->lineEdit_LD->text().isEmpty())
    {
        ui->lineEdit_LD->setText("*");
        flag =true;
    }


    if(!flag)
    {
        if((bankloan.Get_Loan_Duration() > 24) || (bankloan.Get_Loan_Duration()<=0))
        {
            bankloan.QMessageBox_Display("Faild to create loan account \n the loan duration range is 1 to 24 month",QMessageBox::Critical);
            return;
        }
        if(ui->lineEdit_LA->text().toFloat() == 0)
        {
            bankloan.QMessageBox_Display("Faild Write valid amount !!!!",QMessageBox::Warning);
            return;
        }
        QString check;
        check = bankloan.Return_Item("Person","National_Number",QString("WHERE National_Number = %1").arg(Customer_NN));
        if(check == "No")
        {
            bankloan.QMessageBox_Display("there is no account with National_Number",QMessageBox::Warning);
        }
        else
        {
            bankloan.Create_Loan_Account(bankloan.Get_Loan_Amount(),bankloan.Get_Loan_Duration(),bankloan.Get_Interest_Ratio());
        }

    }

}

/**
 * @brief Constructs a BankLoan object with specified customer details.
 *
 * Initializes the loan account with customer information and sets up the database.
 *
 * @param Customer_Name The name of the customer.
 * @param Customer_Pass The password of the customer.
 * @param Customer_NN The national number of the customer.
 */

BankLoan::BankLoan(QString Customer_Name,QString Customer_Pass,QString Customer_NN)
{
    Initialize_Data_Base(Get_Data_Base_Name());
    Set_Customer_NN(Customer_NN);
    Set_Customer_Name(Customer_Name);
    Set_Customer_Pass(Customer_Pass);

}
/**
 * @brief Default constructor for BankLoan.
 *
 * Initializes the database without setting customer details.
 */

BankLoan::BankLoan()
{
    Initialize_Data_Base(Get_Data_Base_Name());
}
/**
 * @brief Gets the interest ratio for the loan.
 *
 * @return The interest ratio as a float.
 */
float BankLoan::Get_Interest_Ratio(void)
{
    return this->m_Interest_Ratio;
}
/**
 * @brief Sets the loan amount.
 *
 * @param m_Loan_Amount The amount of the loan.
 */
void BankLoan::Set_Loan_Amount(float m_Loan_Amount)
{

    this->m_Loan_Amount = m_Loan_Amount;
}
/**
 * @brief Sets the loan duration and updates the interest ratio accordingly.
 *
 * @param m_Loan_Duration The duration of the loan in months.
 */
void BankLoan::Set_Loan_Duration(int m_Loan_Duration)
{
    this->m_Loan_Duration = m_Loan_Duration;
    // from 1 month to 6 months --> the interest_ration is 10%/month
    // from 7 month to 12 months --> the interest_ration is 15%/month
    // from 12 month to 18 months --> the interest_ration is 20%/month
    // from 18 month to 24 months --> the interest_ration is 25%/month
    if((m_Loan_Duration>0) && (m_Loan_Duration <= 6))
    {
        m_Interest_Ratio = 0.5;
    }
    else if((m_Loan_Duration>6) && (m_Loan_Duration <= 12))
    {
        m_Interest_Ratio = 1.0;
    }
    else if((m_Loan_Duration>12) && (m_Loan_Duration <= 18))
    {
        m_Interest_Ratio = 1.5;
    }
    else if((m_Loan_Duration>18) && (m_Loan_Duration <= 24))
    {
        m_Interest_Ratio = 2.0;
    }
}
/**
 * @brief Gets the loan amount.
 *
 * @return The loan amount as a float.
 */
float BankLoan::Get_Loan_Amount(void)
{
    return this->m_Loan_Amount;
}
/**
 * @brief Gets the loan duration.
 *
 * @return The loan duration in months as an integer.
 */
int BankLoan::Get_Loan_Duration(void)
{
    return this->m_Loan_Duration;
}

BankLoan::~BankLoan()
{

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
void Loan_Acount::on_comboBox_currentTextChanged(const QString &arg1)
{
    if(arg1 == "English")
    {
        ui->label_NN->setText("National Number");
        ui->label_Name->setText("Name");
        ui->label_Pass->setText("Password");
        ui->label_LA->setText("Loan Amount");
        ui->label_LD->setText("Loan duration (in months)");
        ui->checkBox->setText("Show password");

    }
    else if (arg1 == "Arabic")
    {
        ui->label_Pass->setText("كلمة المرور");
        ui->label_NN->setText("الرقم القومي");
        ui->label_Name->setText("الاسم");
        ui->label_LA->setText("كمية القرض");
        ui->label_LD->setText("مدة القرض (بالشهور)");
        ui->checkBox->setText("اظهار كلمه المرور");

    }
    else if (arg1 == "German")
    {
        ui->label_NN->setText("Personalausweisnummer");
        ui->label_Name->setText("Name");
        ui->label_Pass->setText("Passwort");
        ui->label_LA->setText("Kreditsumme");
        ui->label_LD->setText("Kreditlaufzeit (in Monaten)");
        ui->checkBox->setText("Passwort anzeigen");


    }
    else if (arg1 == "French")
    {
        ui->label_NN->setText("Numéro national");
        ui->label_Name->setText("Nom");
        ui->label_Pass->setText("Mot de passe");
        ui->label_LA->setText("Montant du prêt");
        ui->label_LD->setText("Durée du prêt (en mois)");
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
void Loan_Acount::on_checkBox_clicked()
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

