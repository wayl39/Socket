/**
 *
 * ----------------------------------
 * @date 2019.09.05
 * @details 修改****
 * ----------------------------------
*/

#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QTcpServer>

/**
 * @class Server
 * @brief Server类管理QTcpServer套接字进行连接管理
*/
class Server : public QObject
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = nullptr);

signals:

private slots:
    void onNewConnection();
    void onReadyRead();
    void onDisconnected();
private:
    QTcpServer* server;

    void registHandler(const QString& username, const QString& password);
    void loginHandler(const QString& username, const QString password);
    void quitLoginHandler(const QString& username);
    void createRoomHandler(const QString& username,bool flag);
    void freshUserHandler(const QString& username);
};

#endif // SERVER_H
