#include "sqlmanager.h"

SqlManager::SqlManager()
    : db(QSqlDatabase::addDatabase("QMYSQL"))
{
    db.setDatabaseName("data");
    db.setHostName("localhost");
    db.setUserName("root");
    db.setPort(3306);
    db.setPassword("123456");
}

SqlManager* SqlManager::instance = nullptr;

SqlManager *SqlManager::getInstance()
{
    if(instance == nullptr) instance = new SqlManager;
    return instance;
}

bool SqlManager::open()
{
    return db.open();
}

void SqlManager::close()
{
    db.close();
}
