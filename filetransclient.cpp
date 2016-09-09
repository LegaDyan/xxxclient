#include "filetransclient.h"
#include <QHostAddress>
#include <QDebug>

fileTransClient::fileTransClient(int type) :type(type)
{
    totalBytes = 0;
    bytesReceived = 0;
    fileNameSize = 0;
}

void fileTransClient::run() {
    bytesReceived = 0;
}

void fileTransClient::updateServerProgress()  //更新进度条，接收数据
{
    qDebug() << "receive";
    QDataStream in(tcpServerConnection);
    in.setVersion(QDataStream::Qt_4_6);
    if(bytesReceived <= sizeof(qint64)*2)
    { //如果接收到的数据小于16个字节，那么是刚开始接收数据，我们保存到//来的头文件信息
        if((tcpServerConnection->bytesAvailable() >= sizeof(qint64)*2)
                && (fileNameSize == 0))
        { //接收数据总大小信息和文件名大小信息
            in >> totalBytes >> fileNameSize;
            bytesReceived += sizeof(qint64) * 2;
        }
        if((tcpServerConnection->bytesAvailable() >= fileNameSize)
                && (fileNameSize != 0))
        {  //接收文件名，并建立文件
            in >> fileName;
            emit updateLabel("receiving file " + fileName, type);
            bytesReceived += fileNameSize;
            localFile = new QFile(fileName);
            if(!localFile->open(QFile::WriteOnly))
            {
                qDebug() << "open file error!";
                return;
            }
        }
        else return;
    }
    if(bytesReceived < totalBytes)
    {  //如果接收的数据小于总数据，那么写入文件
        bytesReceived += tcpServerConnection->bytesAvailable();
        inBlock = tcpServerConnection->readAll();
        localFile->write(inBlock);
        inBlock.resize(0);
    }
    emit updateProgressBar(totalBytes, type, 0);
    emit updateProgressBar(bytesReceived, type, 1);
    if(bytesReceived == totalBytes)
    { //接收数据完成时
       // tcpServerConnection->close();
        localFile->close();
        emit updateLabel("Succeed receiving file " + fileName, type);
        return;
    }
}
