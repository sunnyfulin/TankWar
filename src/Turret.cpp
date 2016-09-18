#include "Turret.h"

#include <QTimer>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QCursor>
#include <QGraphicsScene>
#include <QGraphicsView>

#include <QDebug>

CTurret::CTurret(QGraphicsItem *)
    :_curAngle(0),
     _destAngle(0),
     _omega(1)
{

}

QRectF CTurret::boundingRect() const
{
    return QRectF(-26,-90,52,130);
}

void CTurret::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(Qt::black);
    painter->drawRect(-15,30,30,10);
    painter->drawRect(-5,30,10,10);

    painter->setBrush(QColor(199,175,87));
    painter->drawRect(-3,-90 ,6,60);
    painter->drawRect(-4,-70 ,8,14);

    QPainterPath pOutter(QPoint(-4,-30));
    pOutter.lineTo(-10,-30);
    pOutter.lineTo(-26,-21);
    pOutter.lineTo(-20,26);
    pOutter.lineTo(-16,30);
    pOutter.lineTo(16,30);
    pOutter.lineTo(20,26);
    pOutter.lineTo(26,-21);
    pOutter.lineTo(8,-30);
    pOutter.lineTo(-10,-30);

    painter->setBrush(QColor(141,123,113));
    painter->drawPath(pOutter);
    painter->drawLine(-26,-21,26,-21);

    QPainterPath pInner(QPoint(-4,-30));
    pInner.lineTo(-20,-20);
    pInner.lineTo(-16,30);
    pInner.lineTo(16,30);
    pInner.lineTo(20,-20);
    pInner.lineTo(4,-30);
    pInner.lineTo(-4,-30);
    painter->setBrush(QColor(199,175,87));
    painter->drawPath(pInner);

    painter->drawRect(-5,-30,10,10);
    painter->drawRect(-10,15,20,10);

    painter->setBrush(QColor(141,123,113));
    painter->drawEllipse(-1,-11,20,20);
    painter->drawEllipse(2,-8,14,14);
}

void CTurret::advance(int step)
{
    if(!step)
        return;

    QPointF endPoint = QCursor::pos();

    QLineF startLine(mapToScene(0,0),mapToScene(0,-100));
    QLineF endLine(mapToScene(0,0),endPoint);

    _destAngle = endLine.angleTo(startLine);

    if((_destAngle-_curAngle) >180)
    {
        _destAngle -= 360;
    }
    else if((_destAngle-_curAngle) < -180)
    {
        _destAngle +=360;
    }

    setRotation(_curAngle);

    if((_curAngle >= (_destAngle-1)) && (_curAngle <= (_destAngle+1)))
    {
        _curAngle = _destAngle;
        return;
    }

    if(_curAngle == _destAngle)
        return;
    else if(_curAngle < _destAngle)
        _curAngle += _omega;
    else
        _curAngle -= _omega;
}


