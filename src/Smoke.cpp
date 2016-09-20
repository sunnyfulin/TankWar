#include "Smoke.h"

#include <QPainter>
#include <QBrush>
#include <QPen>

CSmoke::CSmoke(qreal direction, QGraphicsItem *parent)
    : QGraphicsObject(parent),
      _direction(direction),
      _alpha(150),
      _outterColor(200,200,200),
      _innerColor(160,160,160)
{
    setZValue(1);
    setRotation(180-_direction);
}

QRectF CSmoke::boundingRect() const
{
    return QRectF(-10,-40,20,50);
}

void CSmoke::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(Qt::NoPen);
    painter->setBrush(_outterColor);
    painter->drawEllipse(QRectF(-10,-40,20,50));

    painter->setBrush(_innerColor);
    painter->drawEllipse(QRectF(-5,-30,10,40));
}

void CSmoke::advance(int step)
{
    if(!step)
        return;

    _outterColor.setAlpha(_alpha);
    _innerColor.setAlpha(_alpha);

    _alpha-=2;

    if(_alpha <= 0)
    {
        delete this;
    }
}
