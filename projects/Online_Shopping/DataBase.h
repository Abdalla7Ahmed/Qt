#ifndef DATABASE_H
#define DATABASE_H

#include <QDialog>
#include <QtSql/QtSql>
#include <QtDebug>
#include <QMessageBox>
#include <QMainWindow>

class DataBase
{
private :


public:

    DataBase() = default;
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
    QSqlDatabase *db;
    QSqlQuery *query;
    QString m_DataBaseName{"Online_Shopping.db"};
    ~DataBase();

};
#endif // DATABASE_H
