#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "SendFile.h"
#include <QThread>
#include <QMessageBox>
#include <QFileDialog>


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

void MainWindow::createWidget()
{    
    qDebug() << "客户端主线程：" << QThread::currentThread();
    ui->le_ip->setText("127.0.0.1");
    ui->le_port->setText("8989");
    ui->progressBar->setRange(0, 100);
    ui->progressBar->setValue(0);

    // 创建线程对象
    QThread* t = new QThread;
    // 创建任务对象
    SendFile* work = new SendFile;

    work->moveToThread(t);

    connect(this, &MainWindow::signalStartConnect, work, &SendFile::connectServer);

    // 处理主线程发送的信号
    connect(work, &SendFile::signalConnectOk, this, [=](){
        QMessageBox::information(this, "连接服务器", "已经成功连接了服务器，恭喜！");
    });

    connect(work, &SendFile::signalDisConnect, this, [=](){
        // 资源释放
        t->quit();
        t->wait();
        work->deleteLater();
        t->deleteLater();
    });

    connect(this, &MainWindow::sendFile, work, &SendFile::sendFile);

    connect(work, &SendFile::signalProcess, this, [=](int precent){
        ui->progressBar->setValue(precent);
    });

    t->start();
}
void MainWindow::slotBtnConnectClicked()
{
    QString ip = ui->le_ip->text();
    unsigned short port = ui->le_port->text().toUShort();
    emit signalStartConnect(port, ip);
}

void MainWindow::slotBtnSendFileClicked()
{
    emit sendFile(ui->le_fileName->text());
}

void MainWindow::slotBtnSelectFileClicked()
{
    QString path = QFileDialog::getOpenFileName();
    if (path.isEmpty()){
        QMessageBox::warning(this, "打开文件", "选择文件路径不能为空！");
        return;
    }

    ui->le_fileName->setText(path);
}
void MainWindow::createLayout()
{

}

void MainWindow::createConnect()
{
    connect(ui->pb_connect, &QPushButton::clicked, this, &MainWindow::slotBtnConnectClicked);
    connect(ui->pb_sendFile, &QPushButton::clicked, this, &MainWindow::slotBtnSendFileClicked);
    connect(ui->pb_selectFile, &QPushButton::clicked, this, &MainWindow::slotBtnSelectFileClicked);
}
