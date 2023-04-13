#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QTcpSocket>

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
    void slotBtnConnectClicked();

    void slotBtnDisConnectClicked();

//    void slotNewConnection();

    void slotSendMsg();
private:
    void createWidget();
    void createLayout();
    void createConnect();


private:
    Ui::MainWindow *ui;
    QTcpSocket *m_tcp{Q_NULLPTR};
    QLabel *m_status{Q_NULLPTR};
};

#endif // MAINWINDOW_H
