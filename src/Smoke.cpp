#include "Smoke.h"

#include <QPainter>
#include <QBrush>
#include <QPen>

CSmoke::CSmoke(qreal direction, QGraphicsItem *parent)
    : QGraphicsObject(parent),
      _direction(direction),
      _alpha(255),
      _outColor(255,255,255),
      _innerColor(255,128,0),
      _decorateColor(255,0,0)
{
    setRotation(180-_direction);
}

QRectF CSmoke::boundingRect() const
{
    return QRectF(-10,-40,20,50);
}

void CSmoke::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(Qt::NoPen);
    painter->setBrush(_outColor);
    QPainterPath pOut(QPoint(-3,5));
    pOut.lineTo(-10,-40);
    pOut.lineTo(-8,-25);
    pOut.lineTo(-5,-35);
    pOut.lineTo(-2,-30);
    pOut.lineTo(0,-40);
    pOut.lineTo(2,-30);
    pOut.lineTo(5,-35);
    pOut.lineTo(8,-25);
    pOut.lineTo(10,-40);
    pOut.lineTo(3,5);
    pOut.lineTo(-3,5);
    painter->drawPath(pOut);

    painter->setBrush(_innerColor);
    QPainterPath pInner(QPoint(-2,4));
    pInner.lineTo(-8,-24);
    pInner.lineTo(-6,-20);
    pInner.lineTo(-3,-29);
    pInner.lineTo(-1,-24);
    pInner.lineTo(0,-34);
    pInner.lineTo(1,-24);
    pInner.lineTo(3,-29);
    pInner.lineTo(6,-20);
    pInner.lineTo(8,-24);
    pInner.lineTo(2,4);
    pInner.lineTo(-2,4);
    painter->drawPath(pInner);

    painter->setBrush(_decorateColor);
    QPainterPath p(QPoint(-1,2));
    p.lineTo(-3,-20);
    p.lineTo(-1,-15);
    p.lineTo(0,-25);
    p.lineTo(1,-15);
    p.lineTo(3,-20);
    p.lineTo(1,2);
    p.lineTo(-1,2);
    painter->drawPath(p);
}

void CSmoke::advance(int step)
{
    if(!step)
        return;

    _outColor.setAlpha(_alpha);
    _innerColor.setAlpha(_alpha);
    _decorateColor.setAlpha(_alpha);

    _alpha-=10;

    if(_alpha <= 0)
    {
        delete this;
    }
}
