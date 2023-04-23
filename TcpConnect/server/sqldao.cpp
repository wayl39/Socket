#include "sqldao.h"
#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>
#include <QVariant>
#include "sqlmanager.h"

SqlDao::SqlDao()
{

}

bool SqlDao::insertUser(const SqlUser &user)
{
    bool ret = false;
    SqlManager::getInstance();
    QSqlQuery query;
    query.prepare("insert into user(username, password)values(:username, :password);");
    query.bindValue(":username", user.getUsername());
    query.bindValue(":password", user.getPassword());

    ret = query.exec();
    if(!ret){
        qDebug()<<query.lastError().text();
    }else{}

    return ret;
}

bool SqlDao::selectUser(const QString &username, SqlUser &user)
{
    bool ret = false;

    QSqlQuery query;
    query.prepare("select * from user where username = :username;");
    query.bindValue(":username", username);

    ret = query.exec();
    if(!ret){
        qDebug()<<query.lastError().text();
    }else{
        ret = query.next();
        if(ret){
            user.setUsername(query.value("username").toString());
            user.setPassword(query.value("password").toString());
            user.setOnline(query.value("online").toBool());
        }
    }

    return ret;
}

bool SqlDao::updateUserOnline(const QString &username, bool online)
{
    bool ret = false;

    QSqlQuery query;
    query.prepare("update user set online = :online where username = :username;");
    query.bindValue(":username", username);
    query.bindValue(":online", online);

    ret = query.exec();
    if(!ret){
        qDebug()<<query.lastError().text();
    }else{}

    return ret;
}

QVector<QString> SqlDao::findAllUser(bool online)
{
    bool ret = false;
    QVector<QString> arr;
    QSqlQuery query;
    query.prepare("select * from user where online = :online;");
    query.bindValue(":online",online);

    ret = query.exec();
    if(!ret){
        qDebug()<<query.lastError().text();
    }else{
        while(query.next()){
            arr.push_back(query.value("username").toString());

        }
    }

    return arr;
}

