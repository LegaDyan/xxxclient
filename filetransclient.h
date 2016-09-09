#ifndef FILETRANSCLIENT_H
#define FILETRANSCLIENT_H

#include <QtNetwork>
#include <QThread>

class fileTransClient : public QObject
{

    Q_OBJECT

public:
    fileTransClient(int type);
    QTcpSocket *tcpServerConnection;

public slots:
    void run();
private:
    qint64 totalBytes;  //存放总大小信息
    qint64 bytesReceived;  //已收到数据的大小
    qint64 fileNameSize;  //文件名的大小信息
    QString fileName;   //存放文件名
    QFile *localFile;   //本地文件
    QByteArray inBlock;   //数据缓冲区
    int type;

signals:
    void updateLabel(QString, int);
    void updateProgressBar(int, int, int);

public slots:
    void updateServerProgress();  //更新进度条，接收数据
};

#endif // FILETRANSCLIENT_H
