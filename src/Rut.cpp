#include "Rut.h"

#include <QPainter>
#include <QBrush>
#include <QPen>

CRut::CRut(qreal direction, QGraphicsItem *parent)
  : QGraphicsObject(parent),
    _color(100,100,100),
    _alpha(255),
    _direction(direction)
{
    setZValue(-1);
    setRotation(_direction);
}

QRectF CRut::boundingRect() const
{
    return QRectF(-30,-50,60,100);
}

void CRut::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(_color);
    painter->setBrush(_color);

    painter->drawRect(-30,-50,16,5);
    painter->drawRect(14,-50,16,5);
    painter->drawRect(-30,-30,16,5);
    painter->drawRect(14,-30,16,5);
    painter->drawRect(-30,-10,16,5);
    painter->drawRect(14,-10,16,5);
    painter->drawRect(-30,10,16,5);
    painter->drawRect(14,10,16,5);
    painter->drawRect(-30,30,16,5);
    painter->drawRect(14,30,16,5);
}

void CRut::advance(int step)
{
    if(!step)
        return;

    _color.setAlpha(_alpha);

    _alpha-=2;

    if(_alpha <= 0)
    {
        delete this;
    }
}
