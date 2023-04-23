#ifndef SQLUSER_H
#define SQLUSER_H

#include <QString>

/**
 * @class SqlUser
 * @brief 数据库user表单模型
*/
class SqlUser
{
public:
    SqlUser();
    SqlUser(const QString& username, const QString& password, bool online);

    inline QString getUsername()const{return this->username;}
    inline QString getPassword()const{return this->password;}
    inline bool getOnline()const{return this->online;}

    inline void setUsername(const QString& username){this->username = username;}
    inline void setPassword(const QString& password){this->password = password;}
    inline void setOnline(bool online){this->online = online;}

private:
    QString username;
    QString password;
    bool online;
};

#endif // SQLUSER_H
