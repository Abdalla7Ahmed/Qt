#include "show.h"
#include "ui_show.h"
#include <QMessageBox>
#include "mainwindow.h"

/**
 * @brief Constructs a Show dialog.
 *
 * This constructor initializes the dialog, sets up the user interface,
 * and populates the combo boxes with options for selecting data types
 * and languages.
 *
 * @param parent The parent widget (default is nullptr).
 */
Show::Show(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Show)
{
    ui->setupUi(this);

    Initialize_Data_Base(Get_Data_Base_Name());
    ui->comboBox->addItem("Person");
    ui->comboBox->addItem("Account");
    ui->comboBox->addItem("Account_Transaction");


    ui->comboBox_2->addItem("English");
    ui->comboBox_2->addItem("Arabic");
    ui->comboBox_2->addItem("German");
    ui->comboBox_2->addItem("French");
}
/**
 * @brief Destructor for the Show class.
 *
 * Cleans up the allocated UI resources.
 */
Show::~Show()
{
    delete ui;
}

/**
 * @brief Handles the button click event to display data in the table.
 *
 * This method retrieves the user's input from the interface and checks
 * if any required fields are empty. If fields are empty, it highlights
 * them and exits the function. If the input is valid, it checks if the
 * user is an admin or a regular user. It then fetches data from the
 * specified database table and populates a QTableWidget with the results.
 *
 * - Clears the existing table data and resets its state.
 * - Validates input fields for Name, National Number (NN), and Password.
 * - If input is valid, queries the database for the specified data type.
 * - Populates the table with the retrieved data.
 *
 * @note If the user is identified as an admin, all records from the selected
 *       table will be displayed.
 */

void Show::on_pushButton_clicked()
{
    // Clear the table widget and reset its state
    ui->tableWidget->clear();
    ui->tableWidget->setColumnCount(0);
    ui->tableWidget->setRowCount(0);

    QString Name = ui->lineEdit_Name->text();
    QString NN = ui->lineEdit_NN->text();
    QString Pass = ui->lineEdit_Pass->text();
    Pass = hashPassword(Pass);
    bool flag{false};
    if(Name.isEmpty())
    {
        ui->lineEdit_Name->setText("*");
        flag = true;
    }
    if(NN.isEmpty())
    {
        ui->lineEdit_NN->setText("*");
        flag = true;
    }
    if(Pass.isEmpty())
    {
        ui->lineEdit_Pass->setText("*");
        flag = true;
    }

    if(flag)
    {
        return;  // Exit if any fields are empty
    }

    QSqlQuery query;
    if((NN == "12345678912345") && (Name == "Admin") && (Pass == hashPassword("Admin_Pass")))
    {
        query.exec(QString("SELECT * FROM %1").arg(m_Type));

        // Check if "Summary" is already in the comboBox
        if(ui->comboBox->findText("Summary") == -1)  // -1 means "Summary" not found
        {
            ui->comboBox->addItem("Summary");
        }
    }

    else
    {
        ui->comboBox->removeItem(3);
        QString CName = Return_Item("Person", "Name", QString("WHERE National_Number = %1").arg(NN));
        QString CNN = Return_Item("Person", "National_Number", QString("WHERE National_Number = %1").arg(NN));
        QString CPass = Return_Item("Person", "Password", QString("WHERE National_Number = %1").arg(NN));
        int id = Return_Item("Person", "Customer_ID", QString("WHERE National_Number = %1").arg(NN)).toInt();

        if((CName == Name) && (CNN == NN) && (CPass == Pass))
        {
            query.exec(QString("SELECT * FROM %1 WHERE Customer_ID = %2").arg(m_Type).arg(id));
            ui->tableWidget->verticalHeader()->setDefaultSectionSize(40);  // Set row height
        }
        else
        {
            QMessageBox::critical(this, "Critical", "The information doesn't match");
            return;
        }
    }

    // Set the column count and column headers for the table
    ui->tableWidget->setColumnCount(query.record().count());
    QStringList headers;
    for (int i = 0; i < query.record().count(); ++i)
    {
        headers << query.record().fieldName(i);
    }
    ui->tableWidget->setHorizontalHeaderLabels(headers);

    // Populate the table widget with data from the database
    int row = 0;
    while (query.next())
    {
        ui->tableWidget->insertRow(row); // Insert a new row

        // Loop through the columns and set the data for each cell
        for (int col = 0; col < query.record().count(); ++col)
        {
            QTableWidgetItem* item = new QTableWidgetItem(query.value(col).toString());
            ui->tableWidget->setItem(row, col, item);
        }
        row++;
    }
}

/**
 * @brief Updates the table widget based on the selected data type.
 *
 * This slot is triggered when the current text of the combo box changes.
 * It clears the contents of the table widget and sets its column and row
 * counts to zero. The selected data type is stored in the member variable
 * m_Type for further processing.
 *
 * @param arg1 The new text selected in the combo box.
 */
void Show::on_comboBox_currentTextChanged(const QString &arg1)
{
    // Clear the current contents of the table widget
    ui->tableWidget->clear();
    ui->tableWidget->clearContents();
    ui->tableWidget->setColumnCount(0);
    ui->tableWidget->setRowCount(0);
    m_Type = arg1;

}

/**
 * @brief Navigates back to the main window.
 *
 * This slot is triggered when the second button is clicked. It creates
 * a new instance of MainWindow, hides the current dialog, and displays
 * the main window maximized.
 */
void Show::on_pushButton_2_clicked()
{
    MainWindow *mainwindow;
    mainwindow = new MainWindow;
    hide();
    mainwindow->showMaximized();
}

/**
 * @brief Toggles the visibility of the password field.
 *
 * This slot is triggered when the checkbox is clicked. If the checkbox
 * is checked, the password field will display the password in plain text;
 * otherwise, it will obscure the password.
 */
void Show::on_checkBox_clicked()
{
    if(ui->checkBox->isChecked())
    {
        ui->lineEdit_Pass->setEchoMode(QLineEdit::Normal);
    }
    else
    {
        ui->lineEdit_Pass->setEchoMode(QLineEdit::Password);
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
void Show::on_comboBox_2_currentTextChanged(const QString &arg1)
{
    if(arg1 == "English")
    {
        ui->label_3->setText("National Number");
        ui->label->setText("Name");
        ui->label_2->setText("Password");

        ui->pushButton->setText("Load");
        ui->pushButton_2->setText("Back");

        ui->checkBox->setText("Show password");
    }
    else if (arg1 == "Arabic")
    {
        ui->label_3->setText("الرقم القومي");
        ui->label->setText("الاسم");
        ui->label_2->setText("كلمة المرور");

        ui->pushButton->setText("تحميل");
        ui->pushButton_2->setText("رجوع");

        ui->checkBox->setText("إظهار كلمة المرور");
    }
    else if (arg1 == "German")
    {
        ui->label_3->setText("Nationalnummer");
        ui->label->setText("Name");
        ui->label_2->setText("Passwort");

        ui->pushButton->setText("Laden");
        ui->pushButton_2->setText("Zurück");

        ui->checkBox->setText("Passwort anzeigen");
    }
    else if (arg1 == "French")
    {
        ui->label_3->setText("Numéro National");
        ui->label->setText("Nom");
        ui->label_2->setText("Mot de passe");

        ui->pushButton->setText("Charger");
        ui->pushButton_2->setText("Retour");

        ui->checkBox->setText("Afficher le mot de passe");
    }

}

