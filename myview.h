#ifndef MYVIEW_H
#define MYVIEW_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QAbstractGraphicsShapeItem>
#include <QMouseEvent>
#include <QDebug>

class myView : public QGraphicsView {
    Q_OBJECT
public:
    explicit myView( QWidget *parent = 0);
    ~myView() { }

protected slots:
    void mousePressEvent( QMouseEvent *event );

private:
    void createFlashLight();

    QGraphicsScene scene;

    QGraphicsPolygonItem polyLight;

private slots:
    void slt_drawFlashLight(QColor color);
};

#endif // MYVIEW_H
