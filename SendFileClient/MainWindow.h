#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void signalStartConnect(unsigned short port, QString ip);

    void sendFile(QString path);

private slots:
    void slotBtnConnectClicked();

    void slotBtnSendFileClicked();

    void slotBtnSelectFileClicked();

private:
    void createWidget();

    void createLayout();

    void createConnect();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
