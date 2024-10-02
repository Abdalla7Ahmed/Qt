#include "help.h"
#include "ui_help.h"
#include "mainwindow.h"

/**
 * @brief Constructs a Help dialog.
 *
 * This constructor initializes the Help dialog and sets up the user interface.
 * It populates the combo box with various help topics related to bank operations.
 *
 * @param parent The parent widget, default is nullptr.
 */
Help::Help(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Help)
{
    ui->setupUi(this);
    ui->comboBox->addItem("About the bank");
    ui->comboBox->addItem("Create Customer Account");
    ui->comboBox->addItem("Create Account");
    ui->comboBox->addItem("Bank Operations");
    ui->comboBox->addItem("Show Transactions");

}
/**
 * @brief Destructor for the Help class.
 *
 * Cleans up the allocated UI resources.
 */
Help::~Help()
{
    delete ui;
}


/**
 * @brief Updates the help text displayed in the text edit based on the selected topic.
 *
 * This slot is triggered when the current text of the combo box changes. It updates the
 * contents of the text edit widget according to the selected topic.
 * The following topics are available:
 * - About the bank
 * - Create Customer Account
 * - Create Account
 * - Bank Operations
 * - Show Transactions
 *
 * @param arg1 The currently selected topic in the combo box.
 */
void Help::on_comboBox_currentTextChanged(const QString &arg1)
{
    int textEditWidth = ui->textEdit->width();
    int textEditHeight = ui->textEdit->height();


    QString uml= R"(


,---------------------------------------.
|BankLoan                               |
|---------------------------------------|
|- m_Loan_Amount: float                 |  ,------------------------------------------.                                                     ,--------------------------------------------.
|- m_Loan_Duration: int                 |  |Bank_Saving                               |   ,---------------------------------------------.   |Bank_Checking                               |
|- m_Interest_Ratio: float              |  |------------------------------------------|   |Make_Operation                               |   |--------------------------------------------|
|+ BankLoan(QString ,QString ,QString );|  |- m_Interset_Rate: int                    |   |---------------------------------------------|   |- m_Credit_Limit: int                       |
|+ Set_Loan_Amount(float): void         |  |+ Bank_Saving(QString ,QString ,QString );|   |+ Make_Operation(QString ,QString ,QString );|   |+ Bank_Checking(QString ,QString ,QString );|
|+ Set_Loan_Duration(int): void         |  |+ Get_Interset_Rate(): int                |   |+ ~Make_Operation()                          |   |+ Get_Interset_Rate(): int                  |
|+ Get_Loan_Amount(): float             |  |+ ~Bank_Saving()                          |   `---------------------------------------------'   |+ ~Bank_Checking()                          |
|+ Get_Loan_Duration(): int             |  `------------------------------------------'                                                     `--------------------------------------------'
|+ Get_Interest_Ratio(): float          |                   |                                       |                                                           |
|+ ~BankLoan()                          |                   |                                       |                                                           |
`---------------------------------------'                   |                                       |                   ________________________________________|
                |_____________________________________      |                                       |                   |
                                                      |     |                                       |                   |
                                                    ,-------------------------------------------------------------------------.
                                                    |BankCustomer                                                             |
                                                    |-------------------------------------------------------------------------|
                                                    |- m_Customer_ID: QString                                                 |
                                                    |- m_Customer_Name: QString                                               |
                                                    |- m_Customer_NN: QString                                                 |
                                                    |- m_Customer_Address: QString                                            |
                                                    |- m_Customer_phone: QString                                              |
                                                    |- m_Customer_Email: QString                                              |
                                                    |- m_Customer_Age: int                                                    |
                                                    |- m_Customer_Password: QString                                           |
                                                    |+ BankCustomer()                                                         |
                                                    |BankCustomer(QString ,QString ,QString ,int ,QString ,QString ,QString );|
                                                    |+ ~BankCustomer()                                                        |
                                                    `-------------------------------------------------------------------------'
                                                                                          |
                                                   ,---------------------------------------------------------------------------.
                                                   |BankAccount                                                                |
                                                   |---------------------------------------------------------------------------|
                                                   |- Customer_Name: QString                                                   |
                                                   |- Customer_NN: QString                                                     |
                                                   |- Customer_Pass: QString                                                   |
                                                   |- m_Customer_phone: QString                                                |
                                                   |- m_Customer_Email: QString                                                |
                                                   |- Customer_id: int                                                         |
                                                   |- m_Balance: float                                                         |
                                                   |- Customer_Address: QString                                                |
                                                   |- Customer_Age: int                                                        |
                                                   |- m_Credit_Limit: float                                                    |
                                                   |+ BankAccount(QString ,QString ,QString ,QString ,int  ,QString ,QString );|
                                                   |+ Set_Customer_Name(QString): void                                         |
                                                   |+ Set_Customer_NN(QString): void                                           |
                                                   |+ Set_Customer_Pass(QString): void                                         |
                                                   |+ Set_Customer_Address(QString): void                                      |
                                                   |+ Set_Customer_Age(int): void                                              |
                                                   |+ Set_Customer_Phone(QString): void                                        |
                                                   |+ Set_Customer_Email(QString): void                                        |
                                                   |+ Check_Acount_Info(): int                                                 |
                                                   |+ deposit(int, float): void                                                |
                                                   |+ withdraw(int, float): void                                               |
                                                   |+ balance_Enquiry(): void                                                  |
                                                   |+ QMessageBox_Display(QString, int): void                                  |
                                                   |+ Add_New_Customer(): void                                                 |
                                                   |+ Create_Saving_Acount(float): void                                        |
                                                   |+ Create_Loan_Acount(float, int, float): void                              |
                                                   |+ Create_Checking_Acount(float): void                                      |
                                                   |+ ~BankAccount()                                                           |
                                                   `---------------------------------------------------------------------------'
                                                                                          |
                                                                                          |
                                                                ,-------------------------------------------------.
                                                                |BankDataBase                                     |
                                                                |-------------------------------------------------|
                                                                |                                                 |
                                                                |- db: QSqlDatabase*                              |
                                                                |- query: QSqlQuery*                              |
                                                                |- m_DataBaseName: QString                        |
                                                                |+ BankDataBase()                                 |
                                                                |+ Initialize_Data_Base(QString): int             |
                                                                |+ createTable(QString): int                      |
                                                                |+ insertData(QString): int                       |
                                                                |+ Return_Item(QString, QString, QString): QString|
                                                                |+ deleteData(QString, int): int                  |
                                                                |+ updateData(QString): int                       |
                                                                |+ checkTableExists(QString): bool                |
                                                                |+ Daily_Updating(): void                         |
                                                                |+ Get_Data_Base_Name(): QString                  |
                                                                |+ hashPassword(const QString&): QString          |
                                                                |+ ~BankDataBase()                                |
                                                                `-------------------------------------------------'

)";

   QString aboutBank = R"(
        <h2>About Bank</h2>
        <p>
            <img src=':/images/images/banklogo.jpg' alt='Bank Logo'/>
        </p>
        <p>
                Banke MAnagement System is the oldest commercial bank in Egypt. It was established on June 25, 1898 with a capital of GBP 1 mn.
                Throughout its long history, NBE's functions and roles have continually developed to square with the different economic
                and political stages in Egypt. During the 1950s, NBE assumed the Central Bank's duties. After its nationalization in the 1960s,
                it acted purely as a commercial bank, but still carried out the functions of the Central Bank in areas where the latter had no branches.
                Moreover, since the mid-1960s, NBE has been in charge of issuing and managing investment certificates on behalf of the government.
        <p>
        <p>
                During the period from January 1, 2022 to December 31, 2022, NBE's performance results were unprecedented.
                Total financial position as at the end of December 2022 recorded EGP 4.4 trillion, growing EGP 1.2 trillion year-on-year.
                Accordingly, NBE's total assets accounted for 38.6% of total assets of Egyptian banks.
        <p>
        <p>
                Total deposits reached EGP 3.2 trillion as at the end of December 2022, with a growth rate of 33.3% year-on-year,
                accounting for 37.2% of total banks' deposits as at the end of December 2022. NBE's deposits approached EGP 3.4 trillion as at June 2023.
                Such leap was driven by the introduction of a diversified package of savings products in local and foreign currencies at competitively
                lucrative rates, which highlights the customers' confidence in our Bank.
        <p>
        <p>
                NBE has further provided a set of distinguished finance schemes that meet the needs of all key economic sectors.
                As at the end of December 2022, the total retail loan portfolio reached EGP 227 bn, growing by EGP 68 bn year-on-year,
                with a growth rate of 42.8%. Retail loans continued to surge to EGP 256 bn. in June 2023. NBE's market share reached 30.4% in February 2023.
        <p>
        <p>
                As for large corporate finance, NBE has also assumed an active role in funding key national economic sectors.
                Total large corporate loan portfolio surged 50.2% to reach EGP 1,358 bn as at the end of December 2022 year-on-year,
                and continued to rise up to EGP 1,563 bn as at the end of June 2023.
        <p>
        <p>
                In line with NBE's support to small and medium sized enterprises (SMEs), the total SME loan portfolio accounted
                for EGP 143 bn as at the end of December 2022, growing by EGP 33 bn or 30% compared to December 2021. The SME loan portfolio
                continued to rise, reaching EGP 159 bn as at June 2023.
        <p>
)";


   QString Create_Customer_Account = R"(
    <h2>Create Customer Account</h2>

    <h4>In this window you can fill your information to start any bank operation</h4>

    <h4>Steps:</h4>

    <p>
    1-Open Customer Window<br>
    2-Click to Create New Account<br>
    3-Fill your information<br>
    4-Submit to create new account<br>
    </p>
    <img src=':/images/images/create_customer_account.png' alt='NBE Logo'/>

)";



    QString Create_Account = R"(
    <h2>Create Account</h2>

    <p>There are three types of accounts that the bank supports:</p>

    <h3>1- Loan Account</h3>

    <p>
    A bank account that is set up as a repayment method for a customer who has been given a bank loan.
    </p>

    <h4>Steps:</h4>

    <p>
    1. Open Bank Operations Window<br>
    2. Click to Create Loan Account<br>
    3. Fill in your personal information<br>
    4. determine the amount and the loan duration<br>
    5. Submit to create a new Loan account
    </p>

    <p>
        <img src=':/images/images/Loan_Account.png' alt='Loan Account Image'/>
    </p>

    <h3>2- Saving Account</h3>

    <p>
    A savings account is a deposit account designed to hold money you don’t plan to spend immediately.
    </p>

    <h4>Steps:</h4>

    <p>
    1. Open Bank Operations Window<br>
    2. Click to Create Saving Account<br>
    3. Fill in your information<br>
    4. determine the saving amount<br>
    5. Submit to create a new Saving account
    </p>

    <p>
        <img src=':/images/images/Saving_Account.png' alt='Saving Account Image'/>
    </p>

    <h3>3- Checking Account</h3>

    <p>
    A checking account allows overdraft while withdrawing (making the balance go below zero up to the specified credit limit).
    </p>

    <h4>Steps:</h4>

    <p>
    If you have any balance and need to withdraw more than the balance, the system will inform you if you need to open a checking account or not.<br>
    1. Open Bank Operations Window<br>
    2. Click to Normal Operations<br>
    3. Fill in your information<br>
    4. Withdraw and submit to create a checking account

    <p>
    or<br>
    1. Open Bank Operations Window<br>
    2. Click to Create Checking Account<br>
    3. Fill in your information<br>
    4. determine the checking amount<br>
    5. Submit to create a new checking account
    </p>
    <p>
        <img src=':/images/images/Checking_Account.png' alt='Saving Account Image'/>
    </p>
    </p>
)";





    QString Bank_Operations = R"(
    <h2>Bank Operations</h2>

     <p> there are three main operations which the bank provide <p>
    <p>
    1. Deposit<br>
    2. withdraw<br>
    3. Balance Enquiry<br>
    </p>

    <p>
        <img src=':/images/images/Normal.png' alt='Bank Operations Account Image'/>
    </p>
)";


    QString Transactions = R"(
    <h2>Show Transactions</h2>

     <p> You can see all your transactions<p>

    <he4>Steps:<h4>

    <p>
    1-Open Show Transactions Window<br>
    2-write your name , passowrd and national number<br>
    3-Press load<br>
    4-select if you need account informations , customer information or transactions details<br>
    <p>

    <p>
        <img src=':/images/images/Transactions.png' alt='Transactiosn Image'/>
    </p>
)";

    // Create a QFont object with the desired properties
    QFont font("Arial", 18, QFont::Bold); // Change "Arial" and 16 to your preferred font and size
    ui->textEdit->setFont(font);

    // Set the text color to red
    QPalette palette = ui->textEdit->palette();
    // palette.setColor(QPalette::Text, Qt::red);
    palette.setColor(QPalette::Text, QColor("#1E0342"));
    ui->textEdit->setPalette(palette);
    // Make the textEdit read-only
    ui->textEdit->setReadOnly(true);

    if(arg1 == "About the bank")
    {
        ui->textEdit->clear();
        ui->textEdit->setText(aboutBank);
    }
    else if(arg1 == "Create Customer Account")
    {
        ui->textEdit->clear();
        ui->textEdit->setText(Create_Customer_Account);
    }
    else if(arg1 == "Create Account")
    {
        ui->textEdit->clear();
        ui->textEdit->setText(Create_Account);
    }

    else if(arg1 == "Bank Operations")
    {
        ui->textEdit->clear();
        ui->textEdit->setText(Bank_Operations);
    }
    else if(arg1 == "Show Transactions")
    {
        ui->textEdit->clear();
        ui->textEdit->setText(Transactions);
    }

}

/**
 * @brief Navigates back to the main window.
 *
 * This slot is triggered when the second button is clicked. It creates
 * a new instance of MainWindow, hides the current dialog, and displays
 * the main window maximized.
 */
void Help::on_pushButton_clicked()
{
    hide();
    MainWindow *mainwindow;
    mainwindow = new MainWindow;
    mainwindow->showMaximized();

}


