#include "customer.h"
#include "ui_customer.h"
#include "mainwindow.h"
#include "customer_edit.h"

Customer::Customer(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Customer)
{
    ui->setupUi(this);

    ui->comboBox->addItem("English");
    ui->comboBox->addItem("Arabic");
    ui->comboBox->addItem("German");
    ui->comboBox->addItem("French");




}
/**
 * @brief Destructor for the Customer class.
 *
 * Cleans up the allocated UI resources.
 */
Customer::~Customer()
{
    delete ui;

}
/**
 * @brief Handles the click event of the Home button.
 *
 * This method hides the current Customer dialog and opens the main window
 * in a maximized state.
 */
void Customer::on_pushButton_Home_clicked()
{
    MainWindow *Main_Window;
    hide();
    Main_Window = new MainWindow;
    Main_Window->showMaximized();
}

/**
 * @brief Handles the click event of the Next button.
 *
 * This method collects customer information from the UI, validates the
 * input, and creates a new BankCustomer object. If all required fields
 * are filled and the password confirmation matches, it adds a new customer.
 * If any fields are empty, it prompts the user to fill in all information.
 */

void Customer::on_pushButton_Next_clicked()
{
    QString Customer_Name;
    QString Customer_NN;
    QString Customer_Address;
    QString Customer_Age;
    QString Customer_Password;
    QString Confirm_Customer_Password;
    QString Customer_Phone;
    QString Customer_Email;


    Customer_Name = ui->lineEdit_Name->text();
    Customer_NN = ui->lineEdit_NN->text();
    Customer_Address = ui->lineEdit_Address->text();
    Customer_Age = ui->lineEdit_Age->text();
    Customer_Password = ui->lineEdit_Password->text();
    Confirm_Customer_Password = ui->lineEdit_Confirm_Password->text();
    Customer_Phone = ui->lineEdit_Phone->text();
    Customer_Email = ui->lineEdit_Email->text();

    BankCustomer bankcustomer(Customer_Name,
                              Customer_NN,
                              Customer_Address,
                              Customer_Age.toInt(),
                              Customer_Password,
                              Customer_Phone,
                              Customer_Email);
    bool flag{false};
    if(Customer_Name.isEmpty())
    {
        ui->lineEdit_Name->setText("*");
        flag =true;
    }
    if(Customer_Age.isEmpty())
    {
        ui->lineEdit_Age->setText("*");
        flag =true;
    }
    if(Customer_Address.isEmpty())
    {
        ui->lineEdit_Address->setText("*");
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
    if(Customer_Phone.isEmpty())
    {
        ui->lineEdit_Phone->setText("*");
        flag =true;
    }
    if(Customer_Email.isEmpty())
    {
        ui->lineEdit_Email->setText("*");
        flag =true;
    }

    if(!flag)
    {
        if(!(Confirm_Customer_Password == Customer_Password))
        {
            bankcustomer.QMessageBox_Display("the password doesn't match!!!",QMessageBox::Critical);
        }
        else
        {

            bankcustomer.Add_New_Customer();

        }

    }
    else
    {
        QString message = "Fill all informaion to complete";
        bankcustomer.QMessageBox_Display(message,QMessageBox::Warning);
    }
}


/**
 * @brief Constructs a BankCustomer object with the provided details.
 *
 * This constructor initializes the database and sets the customer details
 * such as name, national number, address, age, password, phone, and email.
 *
 * @param m_Customer_Name The name of the customer.
 * @param m_Customer_NN The national number of the customer.
 * @param m_Customer_Address The address of the customer.
 * @param m_Customer_Age The age of the customer.
 * @param m_Customer_Password The password for the customer account.
 * @param m_Customer_phone The phone number of the customer.
 * @param m_Customer_Email The email address of the customer.
 */
BankCustomer::BankCustomer(QString m_Customer_Name,
                           QString m_Customer_NN,
                           QString m_Customer_Address,
                           int m_Customer_Age,
                           QString m_Customer_Password,
                           QString m_Customer_phone,
                           QString m_Customer_Email)
{
    Initialize_Data_Base(Get_Data_Base_Name());


    Set_Customer_Name(m_Customer_Name);
    Set_Customer_NN(m_Customer_NN);
    Set_Customer_Pass(m_Customer_Password);
    Set_Customer_Address(m_Customer_Address);
    Set_Customer_Age(m_Customer_Age);
    Set_Customer_Phone(m_Customer_phone);
    Set_Customer_Email(m_Customer_Email);

}


BankCustomer::~BankCustomer()
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

void Customer::on_comboBox_currentTextChanged(const QString &arg1)
{
    if(arg1 == "English")
    {
        ui->label_Address->setText("Address");
        ui->label_Age->setText("Age");
        ui->label_CPass->setText("Confirm Password");
        ui->label_Email->setText("Email");
        ui->label_NN->setText("National Number");
        ui->label_Name->setText("Name");
        ui->label_Pass->setText("Password");
        ui->label_Phone->setText("Phone");
        ui->checkBox->setText("Show password");
    }
    else if (arg1 == "Arabic")
    {
        ui->label_Address->setText("العنوان");
        ui->label_Age->setText("العمر");
        ui->label_Pass->setText("كلمة المرور");
        ui->label_CPass->setText("تأكيد كلمة المرور");
        ui->label_Email->setText("البريد الإلكتروني");
        ui->label_NN->setText("الرقم القومي");
        ui->label_Name->setText("الاسم");
        ui->label_Phone->setText("الهاتف");
        ui->checkBox->setText("اظهار كلمه المرور");
    }
    else if (arg1 == "French") {
        ui->label_Address->setText("Adresse");
        ui->label_Age->setText("Âge");
        ui->label_CPass->setText("Confirmer le mot de passe");
        ui->label_Email->setText("Email");
        ui->label_NN->setText("Numéro national");
        ui->label_Name->setText("Nom");
        ui->label_Pass->setText("Mot de passe");
        ui->label_Phone->setText("Téléphone");
        ui->checkBox->setText("Afficher le mot de passe");

    }
    else if (arg1 == "German") {
        ui->label_Address->setText("Adresse");
        ui->label_Age->setText("Alter");
        ui->label_CPass->setText("Passwort bestätigen");
        ui->label_Email->setText("E-Mail");
        ui->label_NN->setText("Personalausweisnummer");
        ui->label_Name->setText("Name");
        ui->label_Pass->setText("Passwort");
        ui->label_Phone->setText("Telefon");
        ui->checkBox->setText("Passwort anzeigen");

    }
}

/**
 * @brief Opens the customer edit dialog when the edit button is clicked.
 *
 * This slot hides the current dialog and creates a new instance of
 * the Customer_Edit dialog, which is then displayed in a maximized state.
 */
void Customer::on_pushButton_clicked()
{
    hide();
    Customer_Edit *customeredit;
    customeredit = new Customer_Edit;
    customeredit->showMaximized();
}

/**
 * @brief Toggles the visibility of the password in the password input field.
 *
 * This slot is triggered when the checkbox for showing the password is clicked.
 * It sets the echo mode of the password input field to normal or password
 * based on the checkbox state.
 */
void Customer::on_checkBox_clicked()
{
    if(ui->checkBox->isChecked())
    {
        ui->lineEdit_Password->setEchoMode(QLineEdit::Normal);
        ui->lineEdit_Confirm_Password->setEchoMode(QLineEdit::Normal);
    }
    else
    {
        ui->lineEdit_Password->setEchoMode(QLineEdit::Password);
        ui->lineEdit_Confirm_Password->setEchoMode(QLineEdit::Password);

    }
}

