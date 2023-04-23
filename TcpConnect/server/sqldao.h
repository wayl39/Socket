#ifndef SQLDAO_H
#define SQLDAO_H

#include "sqluser.h"

/**
 * @class SqlDao
 * @brief 数据接口
 * @details
 * create table student(
 * username varchar(16) primary key unique,
 * password varchar(16) not null,
 * online tinyint);
*/
class SqlDao
{
public:
    SqlDao();

    bool insertUser(const SqlUser& user);
    bool selectUser(const QString& username, SqlUser& user);
    bool updateUserOnline(const QString& username, bool online);
    QVector<QString> findAllUser(bool online);
};

#endif // SQLDAO_H
