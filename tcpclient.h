#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QDataStream>

class tcpClient : public QObject
{
    Q_OBJECT
public:
    tcpClient(const QString &_adress, const quint16 &_port, QObject *p = 0);
    ~tcpClient();

    quint8 getType() const;

    quint16 getLength() const;

    void changeHost(const QString &_adress, const quint16 &_port);

    quint8 getColor_r() const;

    quint8 getColor_g() const;

    quint8 getColor_b() const;

signals:
    void sgn_dataRead();

public slots:
    void send_msg();                        ///< отправляем сообщение на сервер
    void read_msg();                        ///< Считываем информацию, возвращаемую сервером
    void end_connent();                     ///< Запрос после отключения
    void slotError(QAbstractSocket::SocketError err); ///< обработка ошибок

private:
    quint8 type;
    quint16 length;
    quint8 color_r;
    quint8 color_g;
    quint8 color_b;

    QString hostAdress;
    quint16 port;
    QTcpSocket *tSocket;
};

#endif // TCPCLIENT_H
