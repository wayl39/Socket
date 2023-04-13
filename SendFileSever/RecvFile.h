#ifndef RECVFILE_H
#define RECVFILE_H

#include <QThread>
#include <QTcpSocket>

class RecvFile : public QThread
{
    Q_OBJECT
public:
    explicit RecvFile(QTcpSocket* tcp, QObject *parent = nullptr);

protected:

    void run();
signals:
    void over();
public slots:

private:
    QTcpSocket* m_tcp{Q_NULLPTR};
};

#endif // RECVFILE_H
