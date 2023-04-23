#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QTcpSocket>

#include "loginwidget.h"
#include "mainhallwidget.h"
#include "room.h"

/**
 * @brief Client
 * @details 主函数入口
*/
class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(QObject *parent = nullptr);
    ~Client();

    void show();

    QVector<QString> arr;
signals:

private slots:
    void onReadyRead();

private:
    QTcpSocket* socket;

    LoginWidget* loginWidget;
    MainHallWidget* mainHallWidget;
    Room* room;
};

#endif // CLIENT_H
