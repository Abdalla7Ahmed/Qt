#include "customer_edit.h"
#include "ui_customer_edit.h"
#include "mainwindow.h"
#include "customer.h"

/**
 * @brief Constructs a Customer_Edit dialog.
 *
 * Initializes the UI components and sets up the language selection
 * options in the combo box. Also initializes the database connection
 * using the specified database name.
 *
 * @param parent The parent widget (default is nullptr).
 */
Customer_Edit::Customer_Edit(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Customer_Edit)
{
    ui->setupUi(this);
    ui->comboBox->addItem("English");
    ui->comboBox->addItem("Arabic");
    ui->comboBox->addItem("German");
    ui->comboBox->addItem("French");


    Initialize_Data_Base(Get_Data_Base_Name());




    // Enable hover event for the buttons
    // ui->pushButton_CN->setAttribute(Qt::WA_Hover, true);
    // ui->pushButton_Submit->setAttribute(Qt::WA_Hover, true);
    // ui->pushButton_Load->setAttribute(Qt::WA_Hover, true);
    // ui->pushButton->setAttribute(Qt::WA_Hover, true);

    // // Install event filter on the buttons to handle hover events
    // ui->pushButton_CN->installEventFilter(this);
    // ui->pushButton_Submit->installEventFilter(this);
    // ui->pushButton_Load->installEventFilter(this);
    // ui->pushButton->installEventFilter(this);

    // // Set default styles for the buttons
    // ui->pushButton_CN->setStyleSheet("QPushButton {font-weight: bold;\nfont-size: 30px;\ncolor:red;}");
    // ui->pushButton_Submit->setStyleSheet("QPushButton {font-weight: bold;\nfont-size: 30px;\ncolor:red;}");
    // ui->pushButton_Load->setStyleSheet("QPushButton {font-weight: bold;\nfont-size: 30px;\ncolor:red;}");
    // ui->pushButton->setStyleSheet("QPushButton {font-weight: bold;\nfont-size: 30px;\ncolor:red;}");

}



bool Customer_Edit::eventFilter(QObject *watched, QEvent *event)
{
    // if (watched == ui->pushButton_CN|| watched == ui->pushButton_Submit ||  watched == ui->pushButton_Load ||  watched == ui->pushButton) {
    //     if (event->type() == QEvent::HoverEnter) {
    //         // Change background color when hovering
    //         dynamic_cast<QPushButton*>(watched)->setStyleSheet("QPushButton {color: white;font-weight: bold;font-size: 50px;border-radius: 50px;border: 5px solid red; }");
    //     }
    //     else if (event->type() == QEvent::HoverLeave) {
    //         // Revert background color when the mouse leaves the button
    //         dynamic_cast<QPushButton*>(watched)->setStyleSheet("QPushButton {font-weight: bold;\nfont-size: 30px;\ncolor:red;}");
    //     }
    // }
    return QWidget::eventFilter(watched, event);
}

/**
 * @brief Destroys the Customer_Edit dialog.
 *
 * Cleans up and releases any allocated resources,
 * including the UI components.
 */
Customer_Edit::~Customer_Edit()
{
    delete ui;
}

/**
 * @brief Checks if the customer's credentials are valid.
 *
 * This function retrieves the customer's name, national number,
 * and password from the input fields, hashes the password, and
 * compares the credentials with those stored in the database.
 *
 * @return
 * - The customer's ID if the credentials are valid.
 * - -1 if the credentials are invalid or if any input fields are empty.
 *
 */
int Customer_Edit::Check_Authorization()
{
    int result {-1};

    QString Customer__Name;
    QString Customer__NN;
    QString Customer__Pass;

    Customer__Name = ui->lineEdit__Name->text();
    Customer__NN = ui->lineEdit__NN->text();
    Customer__Pass = ui->lineEdit__Pass->text();

    Customer__Pass = hashPassword(Customer__Pass);
    bool flag{false};
    if(Customer__Name.isEmpty())
    {
        ui->lineEdit__Name->setText("*");
        flag =true;
    }
    if(Customer__Pass.isEmpty())
    {
        ui->lineEdit__Pass->setText("*");
        flag =true;
    }
    if(Customer__NN.isEmpty())
    {
        ui->lineEdit__NN->setText("*");
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
 * @brief Loads customer information into the input fields.
 *
 * This slot is triggered when the load button is clicked. It calls
 * the `Check_Authorization` method to verify the customer's credentials.
 * If the credentials are valid, it retrieves the customer's address, age,
 * phone number, and email from the database using the customer's ID and
 * populates the corresponding input fields in the UI.
 *
 * @note The password is not displayed for security reasons.
 */
void Customer_Edit::on_pushButton_Load_clicked()
{

    int Customer_ID = Check_Authorization();

    if(Customer_ID > 0)
    {
        QString Customer_Address;
        QString Customer_Age;
        QString Customer_Password;
        QString Customer_Phone;
        QString Customer_Email;

        // Customer_Password = Return_Item("Person","Password",QString("WHERE Customer_ID = %1").arg(Customer_ID));
        Customer_Address = Return_Item("Person","Address",QString("WHERE Customer_ID = %1").arg(Customer_ID));
        Customer_Age = Return_Item("Person","Age",QString("WHERE Customer_ID = %1").arg(Customer_ID));
        Customer_Phone = Return_Item("Person","Phone",QString("WHERE Customer_ID = %1").arg(Customer_ID));
        Customer_Email = Return_Item("Person","Email",QString("WHERE Customer_ID = %1").arg(Customer_ID));



        // ui->lineEdit_Password->setText(Customer_Password);
        ui->lineEdit_Age->setText(Customer_Age);
        ui->lineEdit_Address->setText(Customer_Address);
        ui->lineEdit_Email->setText(Customer_Email);
        ui->lineEdit_Phone->setText(Customer_Phone);
    }



}

/**
 * @brief Navigates to the Customer view.
 *
 * This slot is triggered when the change customer button is clicked.
 * It hides the current `Customer_Edit` dialog and opens the `Customer`
 * view in a maximized window.
 */
void Customer_Edit::on_pushButton_CN_clicked()
{
    hide();
    Customer *customer;
    customer = new Customer;
    customer->showMaximized();
}


/**
 * @brief Submits the edited customer information.
 *
 * This slot is triggered when the submit button is clicked. It collects
 * the customer information from the input fields, checks for any empty
 * fields, and then updates the customer record in the database if all
 * fields are filled and the customer is authorized. If the update is
 * successful, a confirmation message is displayed; otherwise, a warning
 * prompts the user to fill in all information.
 */
void Customer_Edit::on_pushButton_Submit_clicked()
{

    QString Customer_Address;
    QString Customer_Age;
    QString Customer_Password;
    QString Customer_Phone;
    QString Customer_Email;
    QString Customer_NN;


    Customer_Address = ui->lineEdit_Address->text();
    Customer_Age = ui->lineEdit_Age->text();
    Customer_Password = ui->lineEdit_Password->text();
    Customer_Phone = ui->lineEdit_Phone->text();
    Customer_Email = ui->lineEdit_Email->text();
    Customer_NN = ui->lineEdit__NN->text();
    bool flag{false};
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
    int Customer_ID = Check_Authorization();
    if(!flag)
    {
        if(Customer_ID > 0)
        {
            QString data = QString("UPDATE Person SET Address='%1', Password='%2', Phone='%5', Email='%6', Age=%7 WHERE Customer_ID = %8")
                               .arg(Customer_Address)
                               .arg(hashPassword(Customer_Password))
                               .arg(Customer_Phone)
                               .arg(Customer_Email)
                               .arg(Customer_Age)
                               .arg(Customer_ID);
            if(insertData(data))
            {
                QMessageBox_Display("Successfully Updated",QMessageBox::Information);
            }

        }
    }
    else
    {
        QString message = "Fill all informaion to complete";
        QMessageBox_Display(message,QMessageBox::Warning);
    }
}


/**
 * @brief Deletes the customer account.
 *
 * This slot is triggered when the delete button is clicked. It first checks
 * if the user is authorized to perform the action by verifying their
 * credentials. If authorized, it prompts the user for confirmation to
 * delete the account. If the user confirms, it attempts to delete the
 * account from the database. If successful, it clears the input fields
 * and shows a success message; otherwise, it displays an error message.
 */
void Customer_Edit::on_pushButton_clicked()
{
    int Customer_ID = Check_Authorization();

    if(Customer_ID > 0)
    {
        int res;
        res =QMessageBox_Display("Are you sure to delete the account ?",QMessageBox::Question);
        if(res == QMessageBox::Yes)
        {
            if(deleteData("Person",Customer_ID))
            {

                ui->lineEdit_Address->setText(" ");
                ui->lineEdit_Age->setText(" ");
                ui->lineEdit_Email->setText(" ");
                ui->lineEdit_Password->setText("");
                ui->lineEdit_Phone->setText(" ");
                QMessageBox_Display("Successfully Deleted",QMessageBox::Information);
            }
            else
            {
                QMessageBox_Display("Error !!! Something is wrong",QMessageBox::Critical);

            }

        }

    }



}


/**
 * @brief Navigates to the main window.
 *
 * This slot is triggered when the home button is clicked. It hides the
 * current customer edit dialog and opens a new instance of the main
 * window, displaying it maximized.
 */
void Customer_Edit::on_pushButton_Home_clicked()
{
    hide();
    MainWindow *mainwindow;
    mainwindow = new MainWindow;
    mainwindow->showMaximized();
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
void Customer_Edit::on_comboBox_currentTextChanged(const QString &arg1)
{
    if (arg1 == "English") {
        ui->label__NN->setText("National Number");
        ui->label__Name->setText("Name");
        ui->label__Pass->setText("Password");

        ui->label_Address->setText("Address");
        ui->label_Age->setText("Age");
        ui->label_Email->setText("Email");
        ui->label_Phone->setText("Phone");
        ui->label_Pass->setText("Password");

        ui->pushButton_CN->setText("Create New Account");
        ui->pushButton_Load->setText("Load Account Information");
        ui->pushButton_Submit->setText("Submit Edit");
        ui->pushButton->setText("Delete Account");


        ui->checkBox->setText("Show password");
        ui->checkBox_2->setText("Show password");

    }
    else if (arg1 == "Arabic") {
        ui->label__NN->setText("الرقم القومي");
        ui->label__Name->setText("الاسم");
        ui->label__Pass->setText("كلمة المرور");

        ui->label_Address->setText("العنوان");
        ui->label_Age->setText("العمر");
        ui->label_Email->setText("البريد الإلكتروني");
        ui->label_Phone->setText("الهاتف");
        ui->label_Pass->setText("كلمة المرور");


        ui->pushButton_CN->setText("إنشاء حساب جديد");
        ui->pushButton_Load->setText("تحميل معلومات الحساب");
        ui->pushButton_Submit->setText("تأكيد التعديل");
        ui->pushButton->setText("حذف الحساب");

        ui->checkBox->setText("اظهار كلمه المرور");
        ui->checkBox_2->setText("اظهار كلمه المرور");
    }
    else if (arg1 == "French") {
        ui->label__NN->setText("Numéro national");
        ui->label__Name->setText("Nom");
        ui->label__Pass->setText("Mot de passe");

        ui->label_Address->setText("Adresse");
        ui->label_Age->setText("Âge");
        ui->label_Email->setText("Email");
        ui->label_Phone->setText("Téléphone");
        ui->label_Pass->setText("Mot de passe");


        ui->pushButton_CN->setText("Créer un nouveau compte");
        ui->pushButton_Load->setText("Charger les informations du compte");
        ui->pushButton_Submit->setText("Soumettre la modification");
        ui->pushButton->setText("Supprimer le compte");

        ui->checkBox->setText("Afficher le mot de passe");
        ui->checkBox_2->setText("Afficher le mot de passe");
    }
    else if (arg1 == "German") {
        ui->label__NN->setText("Personalausweisnummer");
        ui->label__Name->setText("Name");
        ui->label__Pass->setText("Passwort");

        ui->label_Address->setText("Adresse");
        ui->label_Age->setText("Alter");
        ui->label_Email->setText("E-Mail");
        ui->label_Phone->setText("Telefon");
        ui->label_Pass->setText("Passwort");


        ui->pushButton_CN->setText("Neues Konto erstellen");
        ui->pushButton_Load->setText("Kontoinformationen laden");
        ui->pushButton_Submit->setText("Änderung einreichen");
        ui->pushButton->setText("Konto löschen");

        ui->checkBox->setText("Passwort anzeigen");
        ui->checkBox_2->setText("Passwort anzeigen");
    }
}
/**
 * @brief Toggles the visibility of the password in the password input field.
 *
 * This slot is triggered when the checkbox for showing the password is clicked.
 * It sets the echo mode of the password input field to normal or password
 * based on the checkbox state.
 */
void Customer_Edit::on_checkBox_clicked()
{
    if(ui->checkBox->isChecked())
    {
        ui->lineEdit__Pass->setEchoMode(QLineEdit::Normal);
    }
    else
    {
        ui->lineEdit__Pass->setEchoMode(QLineEdit::Password);
    }
}
/**
 * @brief Toggles the visibility of the password in the password input field.
 *
 * This slot is triggered when the checkbox for showing the password is clicked.
 * It sets the echo mode of the password input field to normal or password
 * based on the checkbox state.
 */

void Customer_Edit::on_checkBox_2_clicked()
{
    if(ui->checkBox_2->isChecked())
    {
        ui->lineEdit_Password->setEchoMode(QLineEdit::Normal);
    }
    else
    {
        ui->lineEdit_Password->setEchoMode(QLineEdit::Password);
    }
}


