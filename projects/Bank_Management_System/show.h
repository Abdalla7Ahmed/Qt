#ifndef SHOW_H
#define SHOW_H

#include <QDialog>
#include <QApplication>
#include <QPushButton>
#include <QTableView>
#include <QVBoxLayout>
#include <QSqlDatabase>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QMessageBox>

#include "database.h"

namespace Ui {
class Show;
}
/**
 * @brief The Show class provides a dialog for displaying bank account information.
 *
 * This class inherits from QDialog and BankDataBase, allowing it to manage
 * the display of data from the bank's database. It features various slots
 * to handle user interactions such as button clicks and combo box selections.
 */
class Show : public QDialog ,public BankDataBase
{
    Q_OBJECT

public:
    explicit Show(QWidget *parent = nullptr);
    ~Show();

private slots:

    void on_pushButton_clicked();

    void on_comboBox_currentTextChanged(const QString &arg1);

    void on_pushButton_2_clicked();

    void on_checkBox_clicked();

    void on_comboBox_2_currentTextChanged(const QString &arg1);

private:
    Ui::Show *ui;          ///< Pointer to the UI elements.
    QTableView *tableView; ///< Table view for displaying account information.
    QVBoxLayout *layout;   ///< Layout manager for arranging UI elements.
    QString m_Type;        ///< Type of the data to display (e.g., account type).
};

#endif // SHOW_H
