#include "tcpclient.h"

#include <QByteArray>
#include <QHostAddress>
#include <QTcpSocket>
#include <iostream>
#include <QMessageBox>
#include "tcpclient.h"

tcpClient::tcpClient(const QString &_adress, const quint16 &_port, QObject *p):
    hostAdress(_adress), port(_port), QObject(p)
{
    tSocket = new QTcpSocket(this);
    std::cout << "--- Connect to Host ---" << std::endl;

    /* Отправляем запрос на подключение к серверу */
    tSocket->connectToHost( QHostAddress::LocalHost/*hostAdress*/, port);

    /* ------- Соединить сигнал и слот ------- */
    /* Отправить сообщение, как только вы подключитесь к серверу */
    connect(tSocket, SIGNAL(connected()),
        this, SLOT(send_msg()));
    /* сервер читает, если отвечает */
    connect(tSocket, SIGNAL(readyRead()),
        this, SLOT(read_msg()));

    /* сервер отправляет запрос при разрыве соединения */
    connect(tSocket, SIGNAL(disconnected()),
        this, SLOT(end_connent()));

    /* обработка ошибок подключения */
    connect( tSocket, SIGNAL(error(QAbstractSocket::SocketError)),
             this, SLOT(slotError(QAbstractSocket::SocketError)));

}

tcpClient::~tcpClient()
{
    delete tSocket;
}

void tcpClient::send_msg()
{
    std::cout << "--- Successfully Connected ---\n"
              << "--- Sending Message ---"
              << std::endl;

    /* Отправить сообщение */
    tSocket->write(QByteArray("Hello server!"));
}

void tcpClient::read_msg()
{
    quint16 nextBlockSize(0);

    qDebug() << "tSocketData - " << tSocket->bytesAvailable();    

    if ( tSocket->bytesAvailable() >= 3 ) {
//        QByteArray chunk = tSocket->read( sizeof(quint8) );

        ///< TO DO check inputData for BigEndian

        QDataStream in( tSocket );
        in.setVersion( QDataStream::Qt_DefaultCompiledVersion);

        forever {
            if ( !nextBlockSize ) {
                if ( tSocket->bytesAvailable() < sizeof(quint16)) {
                    break;
                }
                in >> nextBlockSize;
            }

            if ( tSocket->bytesAvailable() < nextBlockSize ) {
                break;
            }

//            if ( nextBlockSize == 0xFFFF ) {
//                //closeConnection();
//                break;
//            }

            quint8 l_type;
            quint16 l_length;
            quint8 l_color_r;
            quint8 l_color_g;
            quint8 l_color_b;
            in >> l_type >> l_length >> l_color_r >> l_color_g >> l_color_b;

            type = l_type;
            length = l_length;
            color_b = l_color_b;
            color_g = l_color_g;
            color_r = l_color_r;

            emit sgn_dataRead();

            qDebug() << type << " " << length;
        }
    }else{
        qDebug() << "Araay of data very small.";
    }
}

void tcpClient::end_connent()
{
    std::cout << "--- Connection Ended ---" << std::endl;
}

void tcpClient::slotError(QAbstractSocket::SocketError err)
{
    QString strerror =
            "Error: " + ( err == QAbstractSocket::HostNotFoundError  ?
                          "The host was not found." :
                          err == QAbstractSocket::RemoteHostClosedError ?
                          "The remote host is closed." :
                          err == QAbstractSocket::ConnectionRefusedError ?
                          "The connection was refused" :
                          QString(tSocket->errorString())
                        );
    QMessageBox msg;
    msg.setText( strerror );
    msg.exec();

    qDebug() << strerror;
}

quint8 tcpClient::getColor_b() const
{
    return color_b;
}

quint8 tcpClient::getColor_g() const
{
    return color_g;
}

quint8 tcpClient::getColor_r() const
{
    return color_r;
}

quint16 tcpClient::getLength() const
{
    return length;
}

void tcpClient::changeHost(const QString &_adress, const quint16 &_port)
{
    tSocket->connectToHost( _adress, _port);
}

quint8 tcpClient::getType() const
{
    return type;
}
