#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include "myview.h"
#include "tcpclient.h"
#include "flashl.h"

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
    void sgn_changeColor(QColor);

private:
    Ui::MainWindow *ui;

    QLineEdit *le_adress;
    QLineEdit *le_port;

    myView *view = nullptr;

    tcpClient *socket = nullptr;

    commandsType *puf;

    bool onSocket{false};

private slots:
    void slt_getDataFromSocket();
    void slt_startTcpSocket();
};

#endif // MAINWINDOW_H
