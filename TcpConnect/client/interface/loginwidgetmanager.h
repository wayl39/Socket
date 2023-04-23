#ifndef LOGINWIDGETMANAGER_H
#define LOGINWIDGETMANAGER_H

#include "loginwidget.h"

class LoginWidgetManager
{
private:
    LoginWidgetManager();
    LoginWidgetManager(const LoginWidgetManager& manager) = delete;
    static LoginWidgetManager* instance;

public:
    static LoginWidgetManager* getInstance();

};

#endif // LOGINWIDGETMANAGER_H
