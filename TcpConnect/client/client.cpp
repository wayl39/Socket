#include "client.h"

#include "protocol.h"

#include <QHostAddress>
#include <QMessageBox>
#include <QVector>

#define ADDR "127.0.0.1"
#define PORT (12000)

/**
 * @brief 构造函数
*/
Client::Client(QObject *parent)
    : QObject(parent)
{
    /** @note 1. 初始化套接字 */
    socket = new QTcpSocket(this);
    socket->connectToHost(QHostAddress(ADDR), PORT);

    QObject::connect(socket, SIGNAL(readyRead()), this, SLOT(onReadyRead()));

    /** @note 2. 初始化界面 */
//    loginWidget = new LoginWidget(socket);
    mainHallWidget = new MainHallWidget(socket);
    room = new Room(socket);

    /** @note3. 接收到信号，切换界面  */
//    QObject::connect(mainHallWidget,SIGNAL(mysignal()),loginWidget,SLOT(show()));
}

Client::~Client()
{
//    delete loginWidget;
    delete mainHallWidget;
    delete room;
}

/**
 * @brief 显示主界面
*/
void Client::show()
{
//    loginWidget->setWindowTitle("登录界面");
//    loginWidget->show();
    mainHallWidget->show();
}

void Client::onReadyRead()
{
    QByteArray buffer = socket->readAll();

    Protocol p;
    int len = 0;
    while((len = p.unpack(buffer)) > 0){
        buffer = buffer.mid(len);

        switch(p.getType()){
            case Protocol::none:
                break;
            case Protocol::regist:
            {
                QString result = p["result"].toString();
                if(result == "success"){
                    QMessageBox::information(loginWidget, ("注册信息"), p["info"].toString());
                }else if(result == "failed"){
                    QMessageBox::warning(loginWidget, "注册信息", p["info"].toString());
                }
                break;
            }
            case Protocol::login:
            {
                QString result = p["result"].toString();
                if(result == "success"){
                    //界面切换
                    mainHallWidget->setUsername(p["username"].toString());
                    loginWidget->hide();
                    mainHallWidget->setWindowTitle("主大厅界面");
                    mainHallWidget->show();
                }else if(result == "failed"){
                    QMessageBox::warning(loginWidget, "登录信息", p["info"].toString());
                }
                break;
            }
            case Protocol::createRoom:
           {

                QString result = p["result"].toString();
                if(result == "success"){
                    //界面切换

                    arr.push_back(p["username"].toString());

                    room->setUsername(p["username"].toString());
                    mainHallWidget->hide();
                    room->setWindowTitle(p["username"].toString());
                    room->show();
                }else if (result == "failed"){
                    QMessageBox::warning(mainHallWidget,"创建我的房间",p["info"].toString());
                }
                break;
            }
            case Protocol::freshUser:
            {
                QString result = p["result"].toString();
                if(result == "success"){
#if 0
                    for(int i = p["n"].toInt(); i < 0 ;i--){
                        arr.push_back(p["i"].toString());

                    }
#endif
                    mainHallWidget->addItemSlot(arr);
                }

                break;
            }
        }
    }
}
