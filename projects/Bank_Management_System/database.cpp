#include "database.h"
#include "ui_database.h"

DataBase::DataBase(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::DataBase)
{
    ui->setupUi(this);
}
/**
 * @brief Destructor for the DataBase class.
 *
 * Cleans up the allocated UI resources.
 */
DataBase::~DataBase()
{
    delete ui;
}

/**
 * @brief Initializes the bank database by creating necessary tables and establishing a connection.
 *
 * This function attempts to open an SQLite database with the specified name.
 * If a default connection already exists, it will use that connection.
 * If not, it creates a new one. It then creates the `Person`, `Account`
 * `Account_Transaction` and 'Summary' tables if they do not already exist.
 *
 * @param dbName The name of the database to be opened or created.
 * @return Returns 1 (true) if the database was opened and initialized successfully, 0 (false) otherwise.
 */
int BankDataBase::Initialize_Data_Base(QString dbName)
{
    db = new QSqlDatabase();

    if (QSqlDatabase::contains("qt_sql_default_connection")) {
        *db = QSqlDatabase::database("qt_sql_default_connection");
    } else {
        // Create a new connection
        *db = QSqlDatabase::addDatabase("QSQLITE", "qt_sql_default_connection");
        db->setDatabaseName(dbName);
    }


    m_DataBaseName = dbName;
    query = new QSqlQuery();

    if (!db->open()) {
        QMessageBox::critical(nullptr, QObject::tr("Cannot open database"),
                              QObject::tr("Unable to establish a database connection.\n"
                                          "This example needs SQLite support. Please read "
                                          "the Qt SQL driver documentation for information how "
                                          "to build it.\n\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
        return false;
    }
    else

    {
    }


    // creat tables
    //1.person table
    QString sql_person;
    sql_person = "CREATE TABLE IF NOT EXISTS Person ("
                 "Customer_ID INTEGER PRIMARY KEY AUTOINCREMENT, "
                 "Name VARCHAR(50), "
                 "Address VARCHAR(50), "
                 "National_Number VARCHAR(20) UNIQUE, "
                 "Password VARCHAR(64), "
                 "Balance FLOAT, "
                 "Phone VARCHAR(20), "
                 "Email VARCHAR(20), "
                 "Age FLOAT)";

    createTable(sql_person);


    // Create the Account table with the foreign key
    QString sql_account;
    sql_account = "CREATE TABLE IF NOT EXISTS Account ("
                  "Account_ID INT, "
                  "Customer_ID INT, "
                  "Account_Type TEXT, "
                  "Balance FLOAT, "
                  "Credit_Limit FLOAT, "
                  "Interest_Rate FLOAT, "
                  "Principal_Amount FLOAT, "
                  "Last_Operation_Date TEXT, "
                  "Loan_Duration INT ,"
                  "FOREIGN KEY (Customer_ID) REFERENCES Person(Customer_ID))";
    createTable(sql_account);


    // Create the Account_Transaction table with the foreign key
    QString sql_transaction;
    sql_transaction = "CREATE TABLE IF NOT EXISTS Account_Transaction ("
                      "Transaction_ID INTEGER PRIMARY KEY AUTOINCREMENT, " // Add a primary key
                      "Customer_ID INT, " // Declare the foreign key column
                      "Date_Time DATETIME, "
                      "Transaction_Type TEXT, "
                      "Amount FLOAT, "
                      "FOREIGN KEY (Customer_ID) REFERENCES Person(Customer_ID))";
    createTable(sql_transaction);



    // create summary table
    QString sql_Summary;
    sql_Summary = "CREATE TABLE IF NOT EXISTS Summary ("
                 "Day_ID INTEGER PRIMARY KEY AUTOINCREMENT, "
                 "Number_Of_Members INT, "
                 "Deposit_Amount FLOAT, "
                 "withdraw_Amount FLOAT, "
                 "Date_Time DATETIME )";
    createTable(sql_Summary);

    return true;


}

/**
 * @brief Inserts data into the database using the provided SQL query.
 *
 * This function executes the given SQL insert query string to insert data into the database.
 *
 * @param StringToInsert The SQL query string used for data insertion.
 * @return Returns 1 (true) if the query was executed successfully, 0 (false) otherwise.
 */
int BankDataBase::insertData(QString StringToInsert)
{
    return query->exec(StringToInsert) ;
}
/**
 * @brief Creates a table in the database using the provided SQL query.
 *
 * This function executes the given SQL query to create a new table in the database.
 *
 * @param sql The SQL query string used to create the table.
 * @return Returns 1 (true) if the table was created successfully, 0 (false) otherwise.
 */
int BankDataBase::createTable(QString sql)
{
    return insertData(sql);
}
/**
 * @brief Retrieves a specific item from the database based on the given conditions.
 *
 * This function executes an SQL SELECT query on the specified table to return the desired item.
 * It constructs the query from the provided table name, selection, and condition.
 *
 * @param TableName The name of the table to query from.
 * @param select The column(s) to select in the query.
 * @param condition The condition to filter the query (e.g., WHERE clause).
 * @return Returns the selected item as a QString, or "No" if no matching record is found or if there is an error.
 */
QString BankDataBase::Return_Item(QString TableName, QString select, QString condition)
{
    QString result;
    QString sql = QString("SELECT %1 FROM %2 %3").arg(select,TableName,condition);
    if (!query->exec(sql)) {
        return "No";  // Return early on error
    }

    if (query->next()) {
        result = query->value(0).toString(); // Retrieve value from the selected index column
    } else {
        result = "No";
    }

    return result;
}
/**
 * @brief Deletes a record from the specified table based on the given Customer ID.
 *
 * This function constructs and executes an SQL DELETE query to remove a record
 * from the provided table where the Customer ID matches the given id.
 *
 * @param Table_name The name of the table from which the record will be deleted.
 * @param id The Customer ID used to identify the record to be deleted.
 * @return Returns 1 (true) if the deletion was successful, 0 (false) otherwise.
 */
int BankDataBase::deleteData(QString Table_name, int id)
{
    // QString sql = "DELETE FROM " + Table_name + " WHERE Customer_id = " + QString::number(id);
    QString sql = QString ("DELETE FROM %1 WHERE Customer_id = %2").arg(Table_name).arg(id);
    return insertData(sql);
}
/**
 * @brief Updates data in the database using the provided SQL query.
 *
 * This function executes an SQL UPDATE query to modify existing data in the database.
 *
 * @param newsql The SQL query string used for updating the data.
 * @return Returns 1 (true) if the query was executed successfully, 0 (false) otherwise.
 */

int BankDataBase::updateData(QString newsql)
{
    return insertData(newsql);
}
/**
 * @brief Checks if a specified table exists in the database.
 *
 * This function executes an SQL query to determine if the table with the provided name exists in the database.
 *
 * @param tableName The name of the table to check for existence.
 * @return Returns true if the table exists, false otherwise or if an error occurs.
 */

bool BankDataBase::checkTableExists(QString tableName)
{

    QString sql = QString("SELECT name FROM sqlite_master WHERE type='table' AND name='%1';").arg(tableName);
    if (!query->exec(sql)) {
        return false;  // Return false if there's an error in the query
    }

    return query->next();  // Returns true if a result is found
}
/**
 * @brief Performs daily updates on saving , loan and checking accounts.
 *
 * This function retrieves all accounts from the database and processes each record.
 * It checks if more than one month has passed since the last operation date.
 * Based on the account type (Loan, Saving, or Checking), it updates the balance
 * and loan duration if applicable, and records the new last operation date.
 *
 * This function also logs the processing steps and any issues encountered during
 * the execution of queries.
 */
void BankDataBase::Daily_Updating(void)
{
    // for testing
    //UPDATE Account SET Last_Operation_Date = '2024-08-19' WHERE Customer_ID = 2
    QSqlQuery query;
    if (!query.exec("SELECT Account_ID, Customer_ID, Balance,Principal_Amount, Interest_Rate, Last_Operation_Date, Loan_Duration FROM Account")) {
        return;
    }

    int count = 0;
    QDate currentDate = QDate::currentDate();

    while (query.next()) {
        count++;
        int accountId = query.value(0).toInt();
        int customerId = query.value(1).toInt();
        float balance = query.value(2).toFloat();
        float Principle_Amount = query.value(3).toFloat();
        float interestRate = query.value(4).toFloat();
        QDate operationDate = query.value(5).toDate();
        int loanDuration = query.value(6).toInt();

        // Check if more than one month has passed since the last operation
        if (operationDate.addMonths(1) <= currentDate) {

            QString queryStr;
            float newBalance = 0;

            // Loan Account
            if (accountId == 1) {
                if (loanDuration - 1 == 0) {
                }
                newBalance = balance - (Principle_Amount * interestRate / 100);
                loanDuration--; // Decrease loan duration

                queryStr = "UPDATE Account SET Balance = :balance, Loan_Duration = :loanDuration, Last_Operation_Date = :lastOperationDate WHERE Customer_ID = :customerId AND Account_ID = :accountId";
            }
            // Saving Account
            else if (accountId == 2) {
                newBalance = balance + (Principle_Amount * interestRate / 100);
                queryStr = "UPDATE Account SET Balance = :balance, Last_Operation_Date = :lastOperationDate WHERE Customer_ID = :customerId AND Account_ID = :accountId";
            }
            // Checking Account
            else if (accountId == 3) {
                newBalance = balance - (Principle_Amount * interestRate / 100);
                queryStr = "UPDATE Account SET Balance = :balance, Last_Operation_Date = :lastOperationDate WHERE Customer_ID = :customerId AND Account_ID = :accountId";
            }

            // Prepare and execute the update query
            QSqlQuery updateQuery;
            updateQuery.prepare(queryStr);
            updateQuery.bindValue(":balance", newBalance);
            updateQuery.bindValue(":loanDuration", loanDuration);
            updateQuery.bindValue(":lastOperationDate", currentDate.toString("yyyy-MM-dd"));
            updateQuery.bindValue(":customerId", customerId);
            updateQuery.bindValue(":accountId", accountId);

            if (!updateQuery.exec())
                return;
        }
    }

}
/**
 * @brief Retrieves the name of the database.
 *
 * This function returns the name of the currently initialized database.
 *
 * @return The name of the database as a QString.
 */

QString BankDataBase::Get_Data_Base_Name(void)
{
    return this->m_DataBaseName;
}

/**
 * @brief Hashes a password using SHA-256.
 *
 * This function takes a password as input, converts it to a UTF-8 byte array,
 * and computes its SHA-256 hash. The resulting hash is then returned as a
 * hexadecimal string.
 *
 * @param password The plaintext password to be hashed.
 * @return The hashed password as a hexadecimal QString.
 */

QString BankDataBase::hashPassword(const QString& password) {
    QByteArray passwordBytes = password.toUtf8();
    QByteArray hashedPassword = QCryptographicHash::hash(passwordBytes, QCryptographicHash::Sha256);
    return QString(hashedPassword.toHex());
}


/**
 * @brief Writes a daily summary of transactions to the database.
 *
 * This function retrieves data from the `Person` and `Account_Transaction` tables
 * to generate a daily summary. It computes the total number of members from the `Person`
 * table, sums the deposit and withdrawal amounts for the current day from the `Account_Transaction`
 * table, and then inserts this information into the `Summary` table.
 *
 * @details The process includes:
 * - Fetching the number of members from the `Person` table.
 * - Summing the deposit amounts for the current day.
 * - Summing the withdrawal amounts for the current day.
 * - Inserting the computed data (number of members, total deposits, total withdrawals) into
 *   the `Summary` table, with a timestamp indicating the current date and time.
 *
 * The function logs SQL errors in case of any issues while executing the queries.
 * The date is formatted as `yyyy-MM-dd` for consistency with the SQLite `Date()` function.
 *
 * @note This function assumes the `Summary` table exists in the database schema and is properly structured
 * to accept these fields: `Number_Of_Members`, `Deposit_Amount`, `Withdraw_Amount`, and `Date_Time`.
 *
 * @warning This function does not check for database integrity or schema correctness.
 * Ensure the database schema matches the expected structure before calling this function.
 *
 * @see BankDataBase::Daily_Updating()
 */
void BankDataBase::Write_Summary()
{
    QString sql_Summary;

    // Step 2: Get Number_Of_Members from the Person table
    QString sql_person_count = "SELECT COUNT(*) FROM Person";
    if (!query->exec(sql_person_count)) {
        return;
    }
    int number_of_members = 0;
    if (query->next()) {
        number_of_members = query->value(0).toInt();
    }

    // Step 3: Sum Deposit_Amount from Account_Transaction table (date format compatibility)
    QString current_date2 = QDateTime::currentDateTime().toString("yyyy-MM-dd");
    QString current_date = QDate::currentDate().toString("yyyy-MM-dd");
    QString sql_deposit_amount = "SELECT SUM(Amount) FROM Account_Transaction "
                                 "WHERE Transaction_Type = 'Deposit' "
                                 "AND (Date(Date_Time) = :currentDate )";
    query->prepare(sql_deposit_amount);
    query->bindValue(":currentDate", current_date);


    if (!query->exec()) {
        return;
    }

    double deposit_amount = 0;
    if (query->next()) {
        deposit_amount = query->value(0).toDouble();
    }
    // Step 4: Sum Withdraw_Amount from Account_Transaction table (date format compatibility)
    QString sql_withdraw_amount = "SELECT SUM(Amount) FROM Account_Transaction "
                                 "WHERE Transaction_Type = 'Withdraw' "
                                 "AND (Date(Date_Time) = :currentDate )";
    query->prepare(sql_withdraw_amount);
    query->bindValue(":currentDate", current_date);
    if (!query->exec()) {
        return;
    }
    double withdraw_amount = 0;
    if (query->next()) {
        withdraw_amount = query->value(0).toDouble();
    }
    // Step 5: Insert summary for the day
    QString sql_insert_summary = "INSERT INTO Summary (Number_Of_Members, Deposit_Amount, Withdraw_Amount, Date_Time) "
                                 "VALUES (:members, :deposit, :withdraw, datetime('now'))";
    query->prepare(sql_insert_summary);
    query->bindValue(":members", number_of_members);
    query->bindValue(":deposit", deposit_amount);
    query->bindValue(":withdraw", withdraw_amount);

    if (!query->exec()) {
        return;
    }
}



BankDataBase::~BankDataBase()
{
    //close database;

    // QSqlDatabase::addDatabase("QSQLITE", connname);
    db->close();

}
