#ifndef ROOMMANAGER_H
#define ROOMMANAGER_H

#include <QVector>
#include "room.h"

class RoomManager
{
private:
    RoomManager();
    RoomManager(const RoomManager& roomManager) ;
    static RoomManager* instance;

    QVector<Room> rooms;        //用户管理所有的房间的容器

public:
    static RoomManager* getInstance();
};

#endif // ROOMMANAGER_H
