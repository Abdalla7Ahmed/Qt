#ifndef CART_H
#define CART_H
#include "DataBase.h"

class Cart:public DataBase,public QWidget
{
public:
    Cart();
    void AddItem(int Product_ID,int Quantity);
    void RemoveItem(int Product_ID,int Quantity);
    void UpdateQuantity();
    float CalculateTotal(void);
    float apply_discount(float total_amount);
    ~Cart()= default;
};

#endif // CART_H
