#ifndef DATABASE_H
#define DATABASE_H

#include <QDialog>
#include <QtSql/QtSql>
#include <QtDebug>
#include <QMessageBox>
namespace Ui {
class DataBase;
}
/**
 * @class DataBase
 * @brief Represents a dialog for database management.
 *
 * This class provides the user interface and functionality for managing
 * database operations within the application. It allows users to perform
 * various actions related to the database, such as viewing, editing,
 * and managing data.
 */
class DataBase : public QDialog
{
    Q_OBJECT

public:

    explicit DataBase(QWidget *parent = nullptr);

    ~DataBase();

private:
    Ui::DataBase *ui; ///< Pointer to the UI components for the DataBase dialog.
};
/**
 * @class BankDataBase
 * @brief Manages database operations for the library management system.
 *
 * This class provides methods to interact with the SQLite database,
 * allowing for the creation of tables, insertion and retrieval of
 * data, as well as updating and deleting records. It also provides
 * functionality for daily updates and password hashing.
 */
class BankDataBase
{
private :
    QSqlDatabase *db;                                       ///< Pointer to the QSqlDatabase instance.
    QSqlQuery *query;                                       ///< Pointer to the QSqlQuery instance.
    QString m_DataBaseName{"Bank_Management_System.db"}; ///< Name of the database.

public:

    BankDataBase() = default;
    int Initialize_Data_Base(QString dbName);
    int createTable(QString sql);
    int insertData(QString StringToInsert);
    QString Return_Item(QString TableName,QString select,QString condition);
    int deleteData(QString Table_name, int id);
    int updateData(QString newsql);
    bool checkTableExists(QString tableName);
    void Daily_Updating(void);
    QString Get_Data_Base_Name();
    QString hashPassword(const QString& password) ;
    void Write_Summary();
    ~BankDataBase();

};
#endif // DATABASE_H
