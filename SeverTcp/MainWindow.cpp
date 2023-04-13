#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QTcpSocket>

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

void MainWindow::slotListenClicked()
{
    unsigned short port = ui->lineEdit->text().toUShort();
    m_s->listen(QHostAddress::Any, port);
    ui->pb_startSever->setDisabled(true);
}

void MainWindow::slotNewConnection()
{
    m_tcp = m_s->nextPendingConnection();
    m_status->setText("已连接");

    // 检测是否可以接收数据
    connect(m_tcp, &QTcpSocket::readyRead, this, [=](){
        QByteArray data = m_tcp->readAll();
        ui->msg_history->append("客户端say:" + data);
    });

    connect(m_tcp, &QTcpSocket::disconnected, this, [=]{
        m_tcp->close();
        m_tcp->deleteLater();
        m_status->setText("未连接");
    });
}

void MainWindow::slotSendMsg()
{
    QString msg = ui->msg_sent->toPlainText();
    m_tcp->write(msg.toUtf8());
    ui->msg_history->append("服务器say:" + msg);
}

void MainWindow::createWidget()
{
    setWindowTitle("服务器");
    m_s = new QTcpServer(this);
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
    connect(ui->pb_startSever, &QPushButton::clicked, this, &MainWindow::slotListenClicked);

    connect(m_s, &QTcpServer::newConnection, this, &MainWindow::slotNewConnection);

    connect(ui->pb_sendMsg, &QPushButton::clicked, this, &MainWindow::slotSendMsg);
}
