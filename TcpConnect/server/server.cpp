#include "server.h"

#include <QHostAddress>
#include <QDebug>
#include <QTcpSocket>

#include "protocol.h"
#include "sqlmanager.h"
#include "sqldao.h"

#define ADDR "127.0.0.1"
#define PORT (12000)

/**
 * @brief 构造函数，创建TCP/IP服务器并开启监听序列
 * @variable parent -> 父控件
 * @retval   无
*/
Server::Server(QObject *parent)
    : QObject(parent)
{
//    SqlManager::getInstance()->open();

    /** @note 1. 创建套接字 */
    server = new QTcpServer(this);

    /** @note 2. 绑定 + 监听套接字 */
    if(server->listen(QHostAddress(ADDR), PORT)){
        qDebug()<<"监听成功 ip:"<<ADDR<<" port:"<<PORT;
    }else{
        qDebug()<<"监听失败 ip:"<<ADDR<<" port:"<<PORT;
    }

    /** @note 3. 监听套接字 */
    QObject::connect(server, SIGNAL(newConnection()), this, SLOT(onNewConnection()));
}

/**
 * @brief 槽函数，连接QTcpServer::newConnection，建立连接用
*/
void Server::onNewConnection()
{
    while(server->hasPendingConnections()){
        QTcpSocket* socket = server->nextPendingConnection();
        qDebug()<<"新的连接 ip:"<<socket->peerAddress().toString()<<" port:"<<socket->peerPort();

        /** @note 1. 管理套接字的读端 */
        QObject::connect(socket, SIGNAL(readyRead()), this, SLOT(onReadyRead()));

        /** @note 2. 管理套接字的断开 */
        QObject::connect(socket, SIGNAL(disconnected()), this, SLOT(onDisconnected()));
    }
}

/**
 * @brief 槽函数，连接QTcpSocket::readyRead信号，处理套接字读端
*/
void Server::onReadyRead()
{
    QTcpSocket* socket = static_cast<QTcpSocket*>(sender());
    QByteArray buffer = socket->readAll();

    Protocol p;
    int len = 0;
    while((len = p.unpack(buffer)) > 0){
        buffer = buffer.mid(len);

        switch(p.getType()){
        case Protocol::none:
            break;
        case Protocol::regist:
            registHandler(p["username"].toString(),p["password"].toString());
            break;
        case Protocol::login:
            if(p["type"].toString() == "login") loginHandler(p["username"].toString(), p["password"].toString());
            else if(p["type"].toString() == "quit") quitLoginHandler(p["username"].toString());
            break;
        case Protocol::createRoom:
            createRoomHandler(p["username"].toString(),p["flag"].toBool());
            break;
        case Protocol::freshUser:
            freshUserHandler(p["username"].toString());
            break;
        }
    }
}

/**
 * @brief 槽函数，连接QTcpSocket::disconneccted信号，管理套接字的断开
*/
void Server::onDisconnected()
{
    QTcpSocket* socket = static_cast<QTcpSocket*>(sender());
    socket->deleteLater();
}

/**
 * @brief 注册处理函数
*/
void Server::registHandler(const QString &username, const QString &password)
{
    SqlDao sd;

    QTcpSocket* socket = static_cast<QTcpSocket*>(sender());
    Protocol p(Protocol::regist);

    /** @note 1. 插入用户 */
    if(sd.insertUser(SqlUser(username, password, false))){
        //成功
        p["result"] = "success";
        p["info"] = "注册成功";
    }else{
        //失败
        p["result"] = "failed";
        p["info"] = "注册失败";
    }
    socket->write(p.pack());
}

/**
 * @brief 登录处理函数
*/
void Server::loginHandler(const QString &username, const QString password)
{
    SqlDao sd;

    QTcpSocket* socket = static_cast<QTcpSocket*>(sender());
    Protocol p(Protocol::login);

    //正常登录
    p["result"] = "failed";

    /** @note 1. 判断是否注册过 */
    SqlUser user;
    if(sd.selectUser(username, user) == false){
        p["info"] = "无此用户";
        socket->write(p.pack());
        return;
    }

    if(user.getOnline() == true){
        p["info"] = "重复登录";
        socket->write(p.pack());
        return;
    }

    if(user.getPassword() != password){
        p["info"] = "密码错误";
        socket->write(p.pack());
        return;
    }

    p["result"] = "success";
    p["info"] = "登录成功";
    p["username"] = username;
    sd.updateUserOnline(username, true);

    socket->write(p.pack());
    return;
}

void Server::quitLoginHandler(const QString &username)
{
    SqlDao sd;
    sd.updateUserOnline(username, false);
}

/**
 * @brief Server::createRoomHandler     :创建房屋的处理函数
 * @param username
 */
void Server::createRoomHandler(const QString &username,bool flag)
{
    QTcpSocket* socket = static_cast<QTcpSocket*>(sender());
    Protocol p(Protocol::createRoom);

    if(flag == true){
        p["result"] = "success";
        p["info"]   = "创建房间成功";
        p["username"] = username;
        p["flag"]   = flag;
        socket->write(p.pack());
    }else {
        p["result"] = "failed";
        p["info"]  = "创建房间失败";
        p["username"] = username;

        socket->write(p.pack());
    }
}

#if 0
/**
 * @brief Server::freshUserHandler      :打包所有在线用户信息
 * @param username
 */
void Server::freshUserHandler(const QString &username)
{
    SqlDao sd;

    QTcpSocket* socket = static_cast<QTcpSocket*>(sender());
    Protocol p(Protocol::freshUser);
    QVector<QString> arr = sd.findAllUser(true);

    p["result"] = "success";
    p["info"]   = "寻找到所有在线用户";
    p["username"] = username;
    QVector<QString>:: iterator it;
    int i = 0;
    for(it = arr.begin();it != arr.end();++it ){
        p["i"] = *it->toUtf8();
        i++;
    }
    p["n"] = i;
    socket->write(p.pack());
}
#endif

void Server::freshUserHandler(const QString &username)
{
    QTcpSocket* socket = static_cast<QTcpSocket*>(sender());
    Protocol p(Protocol::freshUser);

    p["result"] = "success";
    p["username"] = username;

    socket->write(p.pack());
}
