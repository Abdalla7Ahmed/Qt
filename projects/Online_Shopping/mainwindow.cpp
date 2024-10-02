#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFormLayout>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    Discount_Code = "on789shop";
    ui->comboBox->addItem("All products");
    ui->comboBox->addItem("My Products");

    ui->comboBox_price->addItem("All");
    ui->comboBox_price->addItem("<100$");
    ui->comboBox_price->addItem("100$ - 500$");
    ui->comboBox_price->addItem("500$ - 1000$");
    ui->comboBox_price->addItem("1000$ - 1500$");
    ui->comboBox_price->addItem(">1500$");



    ui->lineEdit_search->setPlaceholderText("Search");
    ui->lineEdit_ID->setPlaceholderText("Product ID");
    ui->lineEdit_quantity->setPlaceholderText("quantity");
    ui->lineEdit_Discount->setPlaceholderText("Discount code");



    Initialize_Data_Base(Get_Data_Base_Name());



    cart = new Cart;
    user = new User;
    order = new Order;

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::getUserInput(void)
{
    // Create a new dialog
    QDialog dialog(this);
    dialog.setWindowTitle("Enter User Information");

    dialog.resize(400, 300); // Adjust these values as needed
    // Create input fields
    QLineEdit *nameEdit = new QLineEdit(&dialog);
    QLineEdit *addressEdit = new QLineEdit(&dialog);
    QLineEdit *phoneEdit = new QLineEdit(&dialog);
    QLineEdit *emailEdit = new QLineEdit(&dialog);
    QLineEdit *Price = new QLineEdit(&dialog);



    // Set placeholder text
    nameEdit->setPlaceholderText("Enter your name");
    addressEdit->setPlaceholderText("Enter your address");
    phoneEdit->setPlaceholderText("Enter your phone number");
    emailEdit->setPlaceholderText("Enter your email");
    Price->setPlaceholderText("Enter the price");


    // Create form layout and add the input fields
    QFormLayout *formLayout = new QFormLayout;
    formLayout->addRow("Name:", nameEdit);
    formLayout->addRow("Address:", addressEdit);
    formLayout->addRow("Phone:", phoneEdit);
    formLayout->addRow("Email:", emailEdit);
    formLayout->addRow("Peice:", Price);


    // Create OK and Cancel buttons
    QPushButton *okButton = new QPushButton("OK", &dialog);
    QPushButton *cancelButton = new QPushButton("Cancel", &dialog);

    // Connect the buttons to the dialog slots
    connect(okButton, &QPushButton::clicked, &dialog, &QDialog::accept);
    connect(cancelButton, &QPushButton::clicked, &dialog, &QDialog::reject);

    // Create a layout for buttons
    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(okButton);
    buttonLayout->addWidget(cancelButton);

    // Create main layout for the dialog
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(formLayout);
    mainLayout->addLayout(buttonLayout);

    // Set the main layout to the dialog
    dialog.setLayout(mainLayout);

    // Execute the dialog and check if the user pressed OK
    if (dialog.exec() == QDialog::Accepted)
    {
        // Retrieve input data
        QString name = nameEdit->text();
        QString address = addressEdit->text();
        QString phone = phoneEdit->text();
        QString email = emailEdit->text();
        user->Set_Name(name);
        user->Set_Email(email);
        user->Set_Address(address);
        user->Set_Phone(phone);
        Total_Price_Paid = Price->text().toFloat();
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    QString item_id = ui->lineEdit_ID->text();
    QString item_quantity = ui->lineEdit_quantity->text();
    if((item_id.isEmpty())|| (item_quantity.isEmpty()))
    {
        QMessageBox::critical(this,"critical","Failed to add , fill the fields");
    }
    else
    {
        cart->AddItem(item_id.toInt(),item_quantity.toInt());
    }
}


void MainWindow::on_pushButton_3_clicked()
{
    QString item_id = ui->lineEdit_ID->text();
    QString item_quantity = ui->lineEdit_quantity->text();
    if((item_id.isEmpty())|| (item_quantity.isEmpty()))
    {
        QMessageBox::critical(this,"critical","Failed to Remove , fill the fields");
    }
    else
    {
        cart->RemoveItem(item_id.toInt(),item_quantity.toInt());
    }
}


void MainWindow::on_comboBox_currentTextChanged(const QString &arg1)
{
    Initialize_Data_Base(Get_Data_Base_Name());

    // Clear the table widget contents and reset its state
    ui->tableWidget->clearContents();
    ui->tableWidget->setColumnCount(0);
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);


    QSqlQuery query;
    if(arg1 == "All products")
    {
        if (!query.exec(QString("SELECT * FROM %1").arg("products"))) {
            qDebug() << "Database query failed: " << query.lastError();
            return;
        }
        Table_Name = "products";
    }
    else if(arg1 == "My Products")
    {

        if (!query.exec(QString("SELECT * FROM %1").arg("Cart_Products"))) {
            qDebug() << "Database query failed: " << query.lastError();
            return;
        }
        Table_Name = "Cart_Products";

    }


    // Set the column count and column headers for the table
    int columnCount = query.record().count();
    ui->tableWidget->setColumnCount(columnCount);

    QStringList headers;
    for (int i = 0; i < columnCount; ++i) {
        headers << query.record().fieldName(i);
    }
    ui->tableWidget->setHorizontalHeaderLabels(headers);

    // Count the number of rows
    int rowCount = 0;
    while (query.next()) {
        rowCount++;
    }

    // Set the row count and rewind the query
    ui->tableWidget->setRowCount(rowCount);
    query.first();

    // Populate the table widget with data from the database
    int row = 0;
    do {
        for (int col = 0; col < columnCount; ++col) {
            QTableWidgetItem* item = new QTableWidgetItem(query.value(col).toString());
            ui->tableWidget->setItem(row, col, item);
        }
        row++;
    } while (query.next());



    // Additional checks to ensure no other settings interfere
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget->resizeColumnsToContents();  // Optional: adjust columns to content

}



void MainWindow::on_lineEdit_search_textChanged(const QString &arg1)
{
    Initialize_Data_Base(Get_Data_Base_Name());

    // Clear the table widget contents
    ui->tableWidget->clearContents();
    ui->tableWidget->setColumnCount(0);
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    QSqlQuery query;
    QString queryString;

    if (arg1.isEmpty()) {
        queryString = QString("SELECT * FROM %1").arg(Table_Name);
    } else {
        // Otherwise, filter by product names that start with the input text
        queryString = QString("SELECT * FROM %1 WHERE Name LIKE '%2%'").arg(Table_Name).arg(arg1 + "%");
    }
    // Execute the query
    if (!query.exec(queryString)) {
        qDebug() << "Database query failed: " << query.lastError();
        return;
    }

    // Set the column count and column headers
    int columnCount = query.record().count();
    ui->tableWidget->setColumnCount(columnCount);

    QStringList headers;
    for (int i = 0; i < columnCount; ++i) {
        headers << query.record().fieldName(i);
    }
    ui->tableWidget->setHorizontalHeaderLabels(headers);

    // Count the rows
    int rowCount = 0;
    while (query.next()) {
        rowCount++;
    }

    // Set the row count and rewind the query
    ui->tableWidget->setRowCount(rowCount);
    query.first();

    // Populate the table with filtered data
    int row = 0;
    do {
        for (int col = 0; col < columnCount; ++col) {
            QTableWidgetItem* item = new QTableWidgetItem(query.value(col).toString());
            ui->tableWidget->setItem(row, col, item);
        }
        row++;
    } while (query.next());

    // Adjust table settings
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget->resizeColumnsToContents();
}

void MainWindow::on_comboBox_price_currentTextChanged(const QString &arg1)
{
    Initialize_Data_Base(Get_Data_Base_Name());

    // Clear the table widget contents
    ui->tableWidget->clearContents();
    ui->tableWidget->setColumnCount(0);
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    QSqlQuery query;
    QString queryString;

    // Determine the price range based on the selected option
    if (arg1 == "<100$") {
        queryString = QString("SELECT * FROM $1 WHERE Price < 100").arg(Table_Name);
    }
    else if (arg1 == "100$ - 500$") {
        queryString = QString("SELECT * FROM %1 WHERE Price >= 100 AND Price <= 500").arg(Table_Name);
    }
    else if (arg1 == "500$ - 1000$") {
        queryString = QString("SELECT * FROM %1 WHERE Price > 500 AND Price <= 1000").arg(Table_Name);
    }
    else if (arg1 == "1000$ - 1500$") {
        queryString = QString("SELECT * FROM %1 WHERE Price > 1000 AND Price <= 1500").arg(Table_Name);
    }
    else if (arg1 == ">1500$") {
        queryString = QString("SELECT * FROM %1 WHERE Price > 1500").arg(Table_Name);
    }
    else if(arg1 =="All"){
        // If no valid range is selected, do not filter by price
        queryString = QString("SELECT * FROM %1").arg(Table_Name);
    }

    // Execute the query
    if (!query.exec(queryString)) {
        qDebug() << "Database query failed: " << query.lastError();
        return;
    }

    // Set the column count and column headers
    int columnCount = query.record().count();
    ui->tableWidget->setColumnCount(columnCount);

    QStringList headers;
    for (int i = 0; i < columnCount; ++i) {
        headers << query.record().fieldName(i);
    }
    ui->tableWidget->setHorizontalHeaderLabels(headers);

    // Count the rows
    int rowCount = 0;
    while (query.next()) {
        rowCount++;
    }

    // Set the row count and rewind the query
    ui->tableWidget->setRowCount(rowCount);
    query.first();

    // Populate the table with filtered data
    int row = 0;
    do {
        for (int col = 0; col < columnCount; ++col) {
            QTableWidgetItem* item = new QTableWidgetItem(query.value(col).toString());
            ui->tableWidget->setItem(row, col, item);
        }
        row++;
    } while (query.next());

    // Adjust table settings
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget->resizeColumnsToContents();
}



void MainWindow::on_pushButton_clicked()
{
    price_without_Discount = cart->CalculateTotal();
    price_with_Discount = cart->apply_discount(price_without_Discount);
    if(ui->lineEdit_Discount->text() == Discount_Code)
    {
        ui->lineEdit_Total_Price->setText("Total Price with Discount : "+ QString::number(price_with_Discount) + "$");
        Total_Price_to_Pay = price_with_Discount;
    }
    else
    {
        ui->lineEdit_Total_Price->setText("No Discount Found : "+ QString::number(price_without_Discount) + "$");
        Total_Price_to_Pay = price_without_Discount;
    }


    bool flag{false};
    getUserInput();
    QString paid_Info;

    QString User_Info;
    User_Info = QString("Name : %1 \n Email : %2 \n Phone : %3 \n Address : %4\n\n")
               .arg(user->Get_Name())
               .arg(user->Get_Email())
               .arg(user->Get_Phone())
               .arg(user->Get_Address());

    QString Order_Info;
    qDebug()<<"Total_Price_Paid"<<Total_Price_Paid;
    qDebug()<<"Total_Price_to_Pay"<<Total_Price_to_Pay;

    Order_Info = QString("Total Price before Discount : %1 \n Total Price after Discount : %2\n\n")
                     .arg(price_without_Discount)
                     .arg(price_with_Discount);


    if(QString::number(Total_Price_Paid) == QString::number(Total_Price_to_Pay))
    {
        // successfully
        flag = true;
        paid_Info = QString("You Pay : %1 \n No remaining").arg(Total_Price_Paid);

    }
    else if (Total_Price_Paid > Total_Price_to_Pay)
    {
        // successfully
        flag = true;
        paid_Info = QString("You Pay : %1 \n Remaining %2").arg(Total_Price_Paid).arg(Total_Price_Paid - Total_Price_to_Pay);


    }
    else
    {
        // faild
        QMessageBox::critical(this,"Order Detais","Failed to complete , Enter the correct pay value");
    }

    if(flag)
    {
        Initialize_Data_Base(Get_Data_Base_Name());

        QMessageBox::information(this,"Order Detais",User_Info + Order_Info + paid_Info);
        QSqlQuery query;
        QString sql = QString("DROP TABLE Cart_Products");
        if (!query.exec(sql)) {
            qDebug() << "Database query failed: " << query.lastError();
            return;
        }
    }
}


void MainWindow::on_pushButton_calc_clicked()
{
    price_without_Discount = cart->CalculateTotal();
    price_with_Discount = cart->apply_discount(price_without_Discount);
    if(ui->lineEdit_Discount->text() == Discount_Code)
    {
        ui->lineEdit_Total_Price->setText("Total Price with Discount : "+ QString::number(price_with_Discount) + "$");
        Total_Price_to_Pay = price_with_Discount;
    }
    else
    {
        ui->lineEdit_Total_Price->setText("No Discount Found : "+ QString::number(price_without_Discount) + "$");
        Total_Price_to_Pay = price_without_Discount;
    }
}

