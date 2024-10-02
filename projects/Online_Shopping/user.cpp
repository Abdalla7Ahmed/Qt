#include "user.h"


User::User(QString m_UserName,QString m_UserEmail,QString m_UserAddress,QString m_UserPhone):
    m_UserName(m_UserName),
    m_UserEmail(m_UserEmail),
    m_UserAddress(m_UserAddress),
    m_UserPhone(m_UserPhone)
{

}


void User::Set_Name(QString m_UserName)
{
    this->m_UserName = m_UserName;
}
void User::Set_Email(QString m_UserEmail)
{
    this->m_UserEmail = m_UserEmail;
}
void User::Set_Address(QString m_UserAddress)
{
    this->m_UserAddress = m_UserAddress;
}
void User::Set_Phone(QString m_UserPhone)
{
    this->m_UserPhone = m_UserPhone;
}


QString User::Get_Name(void)
{
    return this->m_UserName;
}
QString User::Get_Email(void)
{
    return this->m_UserEmail;

}
QString User::Get_Address(void)
{
    return this->m_UserAddress;

}
QString User::Get_Phone(void)
{
    return this->m_UserPhone;
}
