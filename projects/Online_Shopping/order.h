#ifndef ORDER_H
#define ORDER_H
#include <QMainWindow>
class Order
{
private:
    QString m_Order_Summary;
    bool m_Order_PaymentStatus;
    QString m_Order_ShippingDetails;

public:
    Order() = default;
    Order(QString m_Order_Summary,bool m_Order_PaymentStatus,QString m_Order_ShippingDetails);
    void Set_Order_Summary(QString m_Order_Summary);
    void Set_Order_PaymentStatus(bool m_Order_PaymentStatus);
    void Set_Order_ShippingDetails(QString m_Order_ShippingDetails);


    QString Get_Order_Summary(void);
    bool Get_Order_PaymentStatus(void);
    QString Get_Order_ShippingDetails(void);
};

#endif // ORDER_H
