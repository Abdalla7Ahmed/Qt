#ifndef USER_H
#define USER_H
#include <QMainWindow>
class User
{
private:

    QString m_UserName;
    QString m_UserEmail;
    QString m_UserAddress;
    QString m_UserPhone;


public:
    User() = default;
    User(QString m_UserName,QString m_UserEmail,QString m_UserAddress,QString m_UserPhone);

    void Set_Name(QString m_UserName);
    void Set_Email(QString m_UserEmail);
    void Set_Address(QString m_UserAddress);
    void Set_Phone(QString m_UserPhone);


    QString Get_Name(void);
    QString Get_Email(void);
    QString Get_Address(void);
    QString Get_Phone(void);



};

#endif // USER_H
