#include "order.h"

Order::Order(QString m_Order_Summary,bool m_Order_PaymentStatus,QString m_Order_ShippingDetails):
    m_Order_Summary(m_Order_Summary),
    m_Order_PaymentStatus(m_Order_PaymentStatus),
    m_Order_ShippingDetails(m_Order_ShippingDetails)
{

}
void Order::Set_Order_Summary(QString m_Order_Summary)
{
    this->m_Order_Summary = m_Order_Summary;
}
void Order::Set_Order_PaymentStatus(bool m_Order_PaymentStatus)
{
    this->m_Order_PaymentStatus = m_Order_PaymentStatus;
}
void Order::Set_Order_ShippingDetails(QString m_Order_ShippingDetails)
{
    this->m_Order_ShippingDetails = m_Order_ShippingDetails;
}


QString Order::Get_Order_Summary(void)
{
    return this->m_Order_Summary;
}
bool Order::Get_Order_PaymentStatus(void)
{
    return this->m_Order_PaymentStatus;
}
QString Order::Get_Order_ShippingDetails(void)
{
    return this->m_Order_ShippingDetails;
}
