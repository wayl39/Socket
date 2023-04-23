#ifndef SQLMANAGER_H
#define SQLMANAGER_H

#include <QSqlDatabase>

/**
 * @class SqlManager
 * @brief 数据库对象管理类
*/
class SqlManager
{
private:
    SqlManager();
    static SqlManager* instance;

    QSqlDatabase db;
public:
    static SqlManager* getInstance();

    bool open();
    void close();
};

#endif // SQLMANAGER_H
