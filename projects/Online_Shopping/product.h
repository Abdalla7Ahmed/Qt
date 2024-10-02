#ifndef PRODUCT_H
#define PRODUCT_H
#include <QMainWindow>
class Product
{
private:
    QString m_ProductName;
    QString m_ProductDescription;
    float m_ProductPrice;
    int m_ProductStockQuantity;
public:
    Product(QString m_ProductName,QString m_ProductDescription,float m_ProductPrice,int m_ProductStockQuantity);
};

#endif // PRODUCT_H
