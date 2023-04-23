#ifndef ROOM_H
#define ROOM_H

#include <QWidget>
#include <QTcpSocket>
#include <QString>
#include <QHostAddress>
#include <QVector>

namespace Ui {
class Room;
}

typedef struct Myroom{
    QString userName;
    QTcpSocket* socket;

} Myroom_t;
class Room : public QWidget
{
    Q_OBJECT

public:
    explicit Room(QTcpSocket* socket,QWidget *parent = nullptr);
    ~Room();

    inline QString getUsername() const { return this->roomName ;}
    void setUsername(const QString &value);

private:
    Ui::Room *ui;

    QTcpSocket* socket;
    QString roomName;   //房间名字
    QTcpSocket* socketRoom; //房主的套接字
    QHostAddress groupAdress;   //广播组地址
    uint32_t groupPort; //广播组端口

    QVector<Myroom_t> roomAccouts;  //存放房间所有用户
};

#endif // ROOM_H
