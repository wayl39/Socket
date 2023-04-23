#ifndef MAINHALLWIDGET_H
#define MAINHALLWIDGET_H

#include <QWidget>
#include <QTcpSocket>
#include "loginwidget.h"

namespace Ui {
class MainHallWidget;
}

class MainHallWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainHallWidget(QTcpSocket* socket, QWidget *parent = 0);
    ~MainHallWidget();

    inline void setUsername(const QString& username){this->username = username;}
protected:
    virtual void closeEvent(QCloseEvent *event);

signals:
    void mysignal();
private slots:
    void on_createRoom_clicked();

    void on_btnExit_clicked();

    void on_btnFresh_clicked();

public :
    void addItemSlot(QVector<QString>& arr);
private:
    Ui::MainHallWidget *ui;

    QTcpSocket* socket;
    QString username;
//    LoginWidget* loginwidget;
};

#endif // MAINHALLWIDGET_H
