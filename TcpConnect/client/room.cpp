#include "room.h"
#include "ui_room.h"

Room::Room(QTcpSocket* socket,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Room),
    socket(socket)
{
    ui->setupUi(this);
}

Room::~Room()
{
    delete ui;
}

void Room::setUsername(const QString &value)
{
    roomName = value;
}
