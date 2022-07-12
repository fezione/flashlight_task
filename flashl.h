#ifndef FLASHL_H
#define FLASHL_H

#include <QObject>
#include <QColor>

class fonar
{
public:
    fonar( ) : color(Qt::yellow) {}
    ~fonar() {}

    void setColor(const QColor &value);

    QColor getColor() const;

private:
    QColor color;
};

class commandsType : public QObject
{
    Q_OBJECT
public:
    commandsType(QObject *p = 0) : QObject(p) {
        flash = new fonar();
        lst_baseComand << 16 << 17 << 32;
    }

    ~commandsType() {
        delete flash;
    }

    virtual void doWork( const quint8 &newCom, const quint8 &r, const quint8 &g, const quint8 &b ) {
        if ( (std::find(lst_baseComand.begin(), lst_baseComand.end(), newCom ) ) != lst_baseComand.end() ) {
            switch (newCom) {
            case 16:
                flash->setColor( Qt::yellow );
                sgn_showFlash( flash->getColor() );
                break;
            case 17:
                changeColor( Qt::black );
                sgn_showFlash( flash->getColor() );
                break;
            case 32:
                changeColor( QColor(r,g,b) );
                break;
            default:
                break;
            }
        }
    }

    QColor getColorFlash() const {
        QColor res = flash->getColor();
        return res;
    }

    QColor getColll() const;

signals:
    void sgn_flashOn();
    void sgn_flashOFF();

    void sgn_showFlash(QColor c);

protected:
    void changeColor( const QColor &color  ) {
        flash->setColor( color );
    }

    QList<int> lst_baseComand;

    QColor colll;

    fonar *flash;
};

/*
class glimmerComand : public commandsType
{
public:
    glimmerComand() {

    }
    ~glimmerComand() {

    }

    void doWork() {
        int q = 0;
        while ( q < 10 ) {
            changeColor( Qt::yellow );
            emit sgn_showFlash( flash->getColor() );
            changeColor( Qt::red );
            emit sgn_showFlash( flash->getColor() );
            ++q;
        }
    }
};
*/
#endif // FLASHL_H
