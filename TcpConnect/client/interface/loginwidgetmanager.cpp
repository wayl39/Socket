#include "loginwidgetmanager.h"

LoginWidgetManager::LoginWidgetManager()
{

}

LoginWidgetManager* LoginWidgetManager::instance =nullptr;

LoginWidgetManager* LoginWidgetManager::getInstance()
{
    if(instance == nullptr) instance = new LoginWidgetManager;
    return instance;
}

