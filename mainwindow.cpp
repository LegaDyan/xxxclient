#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    for (int i = 0; i < 5; i++) {
        thread[i] = new QThread;
    }
    connect(&tcpServer,SIGNAL(newConnection()),this,SLOT(acceptConnection()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::start() //开始监听
{
    qDebug() << "Start Listening";
    tcpServer.listen(QHostAddress("101.5.220.32"), 6666);
}

void MainWindow::acceptConnection()  //接受连接
{
    qDebug() << "Connected";
    bool f = 0;
    for (int i = 0; i < 5; i++) {
        if (!thread[i]->isRunning()) {
            fileTransClient* cc = new fileTransClient(i);
            cc->moveToThread(thread[i]);
            cc->tcpServerConnection = tcpServer.nextPendingConnection();
            connect(thread[i], SIGNAL(started()), cc, SLOT(run()));
            connect(cc, SIGNAL(updateLabel(QString,int)), this, SLOT(changeLabel(QString,int)));
            connect(cc, SIGNAL(updateProgressBar(int,int,int)), this, SLOT(changeProgressBar(int,int,int)));
            connect(cc->tcpServerConnection,SIGNAL(readyRead()),cc,SLOT(updateServerProgress()));
            changeLabel("Connected", i);
            thread[i]->start();
            f = 1;
            tcpServer.close();
            break;
        }
    }
    if (f == 0) {
        qDebug() << "Full";
    }
}

void MainWindow::on_pushButton_clicked()
{
    QByteArray data;
    QDataStream out(&data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_7);
    out << QString("101.5.220.32") << QString("6666") << ui->lineEdit->text();
    updSocket.writeDatagram(data, QHostAddress("101.5.220.32"), 5888);
    start();
}

void MainWindow::changeLabel(QString str, int type) {
    switch (type) {
    case 0:
        ui->label_1->setText(str);
        break;
    case 1:
        ui->label_2->setText(str);
        break;
    case 2:
        ui->label_3->setText(str);
        break;
    case 3:
        ui->label_4->setText(str);
        break;
    default:
        ui->label_5->setText(str);
        break;
    }
}

void MainWindow::changeProgressBar(int val, int type, int t) {
    if (t == 0) {
        switch (type) {
        case 0:
            ui->progressBar_1->setMaximum(val);
            break;
        case 1:
            ui->progressBar_2->setMaximum(val);
            break;
        case 2:
            ui->progressBar_3->setMaximum(val);
            break;
        case 3:
            ui->progressBar_4->setMaximum(val);
            break;
        default:
            ui->progressBar_5->setMaximum(val);
            break;
        }
    }
    else {
        switch (type) {
        case 0:
            ui->progressBar_1->setValue(val);
            break;
        case 1:
            ui->progressBar_2->setValue(val);
            break;
        case 2:
            ui->progressBar_3->setValue(val);
            break;
        case 3:
            ui->progressBar_4->setValue(val);
            break;
        default:
            ui->progressBar_5->setValue(val);
            break;
        }
    }
}
