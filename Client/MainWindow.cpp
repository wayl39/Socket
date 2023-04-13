#include "MainWindow.h"
#include "ui_MainWindow.h"
#include<QHostAddress>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    createWidget();
    createLayout();
    createConnect();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slotBtnConnectClicked()
{
    unsigned short port = ui->le_port->text().toUShort();
    QString ip = ui->le_ip->text();
    // 连接服务器
    m_tcp->connectToHost(QHostAddress(ip), port);
    ui->pb_connect->setDisabled(true);
    ui->pb_disconnect->setDisabled(false);
}

void MainWindow::slotBtnDisConnectClicked()
{
    m_tcp->close();
}

void MainWindow::slotSendMsg()
{
    QString msg = ui->msg_sent->toPlainText();
    m_tcp->write(msg.toUtf8());
    ui->msg_history->append("客户端say:" + msg);
}

void MainWindow::createWidget()
{
    setWindowTitle("客户端");
    m_tcp = new QTcpSocket(this);
    m_status = new QLabel;
    ui->statusBar->addWidget(new QLabel("连接状态："));
    ui->statusBar->addWidget(m_status);
    m_status->setText("未连接");
}

void MainWindow::createLayout()
{

}

void MainWindow::createConnect()
{
    connect(ui->pb_connect, &QPushButton::clicked, this, &MainWindow::slotBtnConnectClicked);

    connect(ui->pb_disconnect, &QPushButton::clicked, this, &MainWindow::slotBtnDisConnectClicked);
    // 检测是否可以接收数据
    connect(m_tcp, &QTcpSocket::readyRead, this, [=](){
        QByteArray data = m_tcp->readAll();
        ui->msg_history->append("服务器say:" + data);
    });

    connect(m_tcp, &QTcpSocket::disconnected, this, [=]{
        m_tcp->close();
//        m_tcp->deleteLater();
        ui->pb_connect->setDisabled(false);
        ui->pb_disconnect->setDisabled(true);
        m_status->setText("未连接");
    });

    connect(m_tcp, &QTcpSocket::connected, this, [=]{
        m_status->setText("已连接");
        ui->msg_history->append("已经连接到服务器");
        ui->pb_connect->setEnabled(false);
        ui->pb_disconnect->setEnabled(true);
    });

    connect(ui->pb_sendMsg, &QPushButton::clicked, this, &MainWindow::slotSendMsg);
}
