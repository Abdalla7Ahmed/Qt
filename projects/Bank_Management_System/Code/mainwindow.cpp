#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QDateTime>
#include "customer.h"
#include "account.h"
#include "customer_edit.h"
#include <QProcess>




/**
 * @brief Constructs the MainWindow object and initializes its UI components.
 *
 * This constructor sets up the user interface, installs event filters for button hover events,
 * initializes timers for periodic updates, and sets up the bank database.
 *
 * @param parent The parent widget (default is nullptr).
 */





MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // Enable hover event for the buttons
    ui->pushButton_Customer->setAttribute(Qt::WA_Hover, true);
    ui->pushButton_Operations->setAttribute(Qt::WA_Hover, true);
    ui->pushButton_show->setAttribute(Qt::WA_Hover, true);
    ui->pushButton_Help->setAttribute(Qt::WA_Hover, true);

    // Install event filter on the buttons to handle hover events
    ui->pushButton_Customer->installEventFilter(this);
    ui->pushButton_Operations->installEventFilter(this);
    ui->pushButton_show->installEventFilter(this);
    ui->pushButton_Help->installEventFilter(this);

    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(TimeOutCallBack()));
    timer->start(1000);


    timer_Update = new QTimer(this);
    connect(timer_Update,SIGNAL(timeout()),this,SLOT(Time_Update_CallBack()));
    timer_Update->start(24 * 60 * 60 * 1000);


    // initialize the data base
    bankdatabase = new BankDataBase;
    bankdatabase->Initialize_Data_Base(bankdatabase->Get_Data_Base_Name());


    bankdatabase->Daily_Updating();
    bankdatabase->Write_Summary();
}


/**
 * @brief Performs daily updates on the bank database.
 *
 * This slot is triggered by a timer once every 24 hours. It calls the
 * `Daily_Updating` method of the `BankDataBase` class to execute
 * necessary updates or maintenance tasks on the bank's database.
 */
void MainWindow::Time_Update_CallBack(void)
{
    bankdatabase->Daily_Updating();
    bankdatabase->Write_Summary();
}

/**
 * @brief Filters events for specific widgets to provide hover effects.
 *
 * This function overrides the event filter to change the appearance of buttons
 * when the mouse enters or leaves their area. It adjusts the button's style sheet
 * dynamically based on hover events.
 *
 * @param watched The object being monitored for events.
 * @param event The event being processed.
 * @return Returns true if the event is handled; otherwise, it returns the base class implementation.
 */
bool MainWindow::eventFilter(QObject *watched, QEvent *event)
{
    if (watched == ui->pushButton_Customer || watched == ui->pushButton_Operations || watched == ui->pushButton_show ||  watched == ui->pushButton_Help) {
        if (event->type() == QEvent::HoverEnter) {
            // Change background color when hovering
            dynamic_cast<QPushButton*>(watched)->setStyleSheet("QPushButton { color: 1E0342;font-weight: bold;font-size: 65px;border-radius: 50px;border: 10px solid 1E0342; }");
        }
        else if (event->type() == QEvent::HoverLeave) {
            // Revert background color when the mouse leaves the button
            dynamic_cast<QPushButton*>(watched)->setStyleSheet("QPushButton {color: #1E0342;\nfont-weight: bold;\nfont-size: 45px;\nborder-radius: 50px; \nborder: 2px solid #1E0342;\nbackground-color: #A0DEFF;}");
        }
    }
    return QMainWindow::eventFilter(watched, event);

}
/**
 * @brief Destructor for the MainWindow class.
 *
 * Cleans up the allocated UI resources.
 */
MainWindow::~MainWindow()
{
    delete ui;
}
/**
 * @brief Updates the LCD displays with the current time.
 *
 * This slot is called by a timer every second. It retrieves the current
 * time and updates the LCD number displays for hours, minutes, and seconds.
 *
 */
void MainWindow::TimeOutCallBack(void)
{
    QTime time=QTime::currentTime();
    ui->lcdNumber_Hours->display(time.hour());
    ui->lcdNumber_Minutes->display(time.minute());
    ui->lcdNumber_Seconds->display(time.second());


    // Get the current date
    // QDate date = QDate::currentDate();

    // // Year display (split into digits)
    // int year = date.year();
    // ui->lcdNumber_Y1->display(year / 1000);            // Thousands place
    // ui->lcdNumber_Y2->display((year / 100) % 10);      // Hundreds place
    // ui->lcdNumber_Y3->display((year / 10) % 10);       // Tens place
    // ui->lcdNumber_Y4->display(year % 10);              // Ones place

    // // Month display (split into digits)
    // int month = date.month();
    // ui->lcdNumber_M1->display(month / 10);             // Tens place
    // ui->lcdNumber_M2->display(month % 10);             // Ones place

    // // Day display (split into digits)
    // int day = date.day();
    // ui->lcdNumber_D1->display(day / 10);               // Tens place
    // ui->lcdNumber_D2->display(day % 10);               // Ones place
}

/**
 * @brief Opens the account management window.
 *
 * This slot is triggered when the "Operations" button is clicked.
 * It hides the main window and opens the account management window
 * in a maximized state.
 */
void MainWindow::on_pushButton_Operations_clicked()
{
    hide();
    account_Window = new Account();
    account_Window->showMaximized();
}

/**
 * @brief Opens the help window.
 *
 * This slot is triggered when the "Help" button is clicked.
 * It hides the main window and opens the help window in a maximized state.
 */
void MainWindow::on_pushButton_Help_clicked()
{
    hide();
    help = new Help;
    help->showMaximized();
}

/**
 * @brief Opens the customer editing window.
 *
 * This slot is triggered when the "Customer" button is clicked.
 * It hides the main window and opens the customer editing window
 * in a maximized state.
 */
void MainWindow::on_pushButton_Customer_clicked()
{
    hide();
    // Customer_Window = new Customer;
    // Customer_Window->showMaximized();
    customer_edit= new Customer_Edit;
    customer_edit->showMaximized();
}

/**
 * @brief Opens the show window.
 *
 * This slot is triggered when the "Show" button is clicked.
 * It hides the main window and opens the show window in a maximized state.
 */
void MainWindow::on_pushButton_show_clicked()
{
    hide();
    show = new Show;
    show->showMaximized();
}

