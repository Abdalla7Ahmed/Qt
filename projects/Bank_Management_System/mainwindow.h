#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QHoverEvent>
#include <QPushButton>
#include <QTimer>
// #include "customer.h"
// #include "account.h"
#include "show.h"
#include "help.h"
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}


class BankDataBase;
class Customer;
class Account;
class Customer_Edit;
QT_END_NAMESPACE


/**
 * @brief The MainWindow class serves as the main interface of the application.
 *
 * This class inherits from QMainWindow and contains various slots to handle user
 * interactions with the main window, such as navigating to customer operations,
 * showing help, and displaying account information. It also manages timers for
 * periodic updates.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    ~MainWindow();
private slots:
    void on_pushButton_Customer_clicked();

    void on_pushButton_Operations_clicked();

    void on_pushButton_Help_clicked();

    void on_pushButton_show_clicked();


    void TimeOutCallBack(void);

    void Time_Update_CallBack(void);


private:
    Ui::MainWindow *ui;   /**< Pointer to the UI elements of the MainWindow. */
    QTimer *timer;        /**< Timer for general timeout events. */
    QTimer *timer_Update; /**< Timer for periodic UI updates. */

    Customer *Customer_Window;    /**< Pointer to the customer window. */
    Account *account_Window;      /**< Pointer to the account window. */
    Show *show;                   /**< Pointer to the show window. */
    Help *help;                   /**< Pointer to the help window. */
    Customer_Edit *customer_edit; /**< Pointer to the customer edit window. */

    BankDataBase *bankdatabase; /**< Pointer to the bank database. */

    // // Function declarations
    // bool verifyCredentials(const QString& username, const QString& password);
    // QString generateOTP();
    // void sendOtpByEmail(const QString& toEmail, const QString& otp);

    // QString storedOtp;  // Store the generated OTP
    // QDateTime otpGenerationTime;  // Store the time when OTP was generated

protected:
    bool eventFilter(QObject *watched, QEvent *event) override;

};

#endif // MAINWINDOW_H
