#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <filetransclient.h>
#include <QtNetwork>
#include <QThread>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void acceptConnection();

public slots:
    void changeLabel(QString, int);
    void changeProgressBar(int, int, int);

private:
    Ui::MainWindow *ui;
    QThread* thread[5];
    QUdpSocket updSocket;
    QTcpServer tcpServer;
    void start();
};

#endif // MAINWINDOW_H
