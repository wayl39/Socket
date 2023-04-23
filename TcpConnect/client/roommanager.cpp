#include "roommanager.h"

RoomManager::RoomManager()
{

}

RoomManager* RoomManager::instance = nullptr;

RoomManager* RoomManager::getInstance()
{
    if(instance == nullptr){
        instance = new RoomManager;
        return instance;
    }
    return instance;
}
