#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpServer>
#include <QLabel>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void slotListenClicked();

    void slotNewConnection();

    void slotSendMsg();
private:
    void createWidget();
    void createLayout();
    void createConnect();
private:
    Ui::MainWindow *ui;

    QTcpServer *m_s{Q_NULLPTR};

    QTcpSocket *m_tcp{Q_NULLPTR};
    QLabel *m_status{Q_NULLPTR};
};

#endif // MAINWINDOW_H
