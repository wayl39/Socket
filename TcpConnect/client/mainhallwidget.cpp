#include "mainhallwidget.h"
#include "ui_mainhallwidget.h"

#include "protocol.h"
#include <QObject>
#include <QCloseEvent>

MainHallWidget::MainHallWidget(QTcpSocket *socket, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainHallWidget),
    socket(socket)
{
    ui->setupUi(this);

    QObject::connect(MainHallWidget::ui->btnExit,SIGNAL(click()),this,SLOT(on_btnExit_clicked()));

    QObject::connect(ui->createRoom,SIGNAL(click()),this,SLOT(on_createRoom_clicked()));

    QObject::connect(ui->btnFresh,SIGNAL(click()),this,SLOT(on_btnFresh_clicked()));
}

MainHallWidget::~MainHallWidget()
{
    delete ui;
}

void MainHallWidget::closeEvent(QCloseEvent *event)
{
    Protocol p(Protocol::login);
    p["type"] = "quit";
    p["username"] = username;

    socket->write(p.pack());


    event->accept();
}

void MainHallWidget::on_createRoom_clicked()
{

    Protocol p(Protocol::createRoom);
    p["type"] = "createRoom";
    p["username"] = username;
    p["flag"]  = true;

    socket->write(p.pack());
}

void MainHallWidget::on_btnExit_clicked()
{
    Protocol p(Protocol::login);
    p["type"] = "quit";
    p["username"] = username;

    socket->write(p.pack());
    this->hide();
    emit mysignal();
}

/**
 * @brief MainHallWidget::on_btnFresh_clicked   :打包刷新数据包
 */
void MainHallWidget::on_btnFresh_clicked()
{
    Protocol p(Protocol::freshUser);
    p["type"] = "freshUser";
    p["username"] = username;

    socket->write(p.pack());
}

/**
 * @brief MainHallWidget::addItemSlot       :添加列表用户
 */
void MainHallWidget::addItemSlot(QVector<QString>& arr)
{
    QListWidgetItem *ite = new QListWidgetItem();
    QVector<QString>::iterator it;
    for(it = arr.begin();it != arr.end();--it){
        QString iteText =*it;
        if (iteText.isEmpty())        return;
        ite->setText(iteText);
        ui->listWidget->addItem(ite);
    }
}
