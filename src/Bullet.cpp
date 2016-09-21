#include "Bullet.h"

#include <QPainter>
#include <QBrush>
#include <QPen>

CBullet::CBullet(qreal drection, QGraphicsItem *parent)
    : QGraphicsObject(parent),
      _direction(drection),
      _velocity(50),
      _pPath(QPoint(-0,-100))
{
    //炮弹前进方向为坦克炮管的当前指向
    setRotation(180-_direction);

    _pPath.lineTo(-2,-96);
    _pPath.lineTo(-2,-90);
    _pPath.lineTo(0,0);
    _pPath.lineTo(2,-90);
    _pPath.lineTo(2,-96);
    _pPath.lineTo(0,-100);
}

QRectF CBullet::boundingRect() const
{
    return QRectF(-2,-100,4,100);
}

void CBullet::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(QColor(255,255,255));
    painter->setBrush(QColor(255,255,255));
    painter->drawPath(_pPath);
}

void CBullet::advance(int step)
{
    if(!step)
        return;

    //炮弹自动前进
    setPos(mapToScene(0,-_velocity));

    //若炮弹飞出场景，则销毁
    if(x()>4000 || x()<-4000 || y()>4000 || y()<-4000)
    {
        hide();
        delete this;
    }
}
