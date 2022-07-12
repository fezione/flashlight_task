#include "myview.h"

myView::myView(QWidget *parent):
    QGraphicsView(parent), scene()
{
    setScene( &scene );

    scene.setSceneRect( -50, -50, 200, 200 );

    setSceneRect( -50,-50, 100,100 );

    createFlashLight();
}

void myView::createFlashLight()
{
    scene.setBackgroundBrush( Qt::black );

    QPolygonF poly;
        poly << QPointF(50,20)
             << QPointF(30,40)
             << QPointF(15,60)
             << QPointF(15,110)
             << QPointF(-15,110)
             << QPointF(-15,60)
             << QPointF(-30,40)
             << QPointF(-50,20);
    scene.addPolygon( poly, QPen(QColor(Qt::blue)), QBrush(QColor(Qt::gray)) );


    QPolygonF light;
    light << QPointF(100,-40)
           << QPointF(50,20)
           << QPointF(-50,20)
           << QPointF(-100,-40);
    polyLight.setPolygon( light );
    polyLight.setPen( Qt::NoPen );
    scene.addItem( &polyLight );
}

void myView::slt_drawFlashLight(QColor color)
{
    polyLight.setBrush( QBrush(QColor(color)) );
    repaint();
}

void myView::mousePressEvent(QMouseEvent *event)
{
    qDebug() << event->pos();
}

