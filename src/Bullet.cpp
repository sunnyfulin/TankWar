#include "Bullet.h"

#include <QPainter>
#include <QBrush>
#include <QPen>

CBullet::CBullet(qreal drection, QGraphicsItem *parent)
    : QGraphicsObject(parent),
      _drection(drection),
      _velocity(8)
{
    //炮弹前进方向为坦克炮管的当前指向
    setRotation(180-_drection);
}

QRectF CBullet::boundingRect() const
{
    return QRectF(-2,-10,4,10);
}

void CBullet::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(Qt::black);
    painter->setBrush(Qt::black);

    QPainterPath p(QPoint(-0,-10));
    p.lineTo(-2,-6);
    p.lineTo(-2,0);
    p.lineTo(2,0);
    p.lineTo(2,-6);
    p.lineTo(0,-10);
    painter->drawPath(p);
}

void CBullet::advance(int step)
{
    if(!step)
        return;

    //炮弹自动前进
    setPos(mapToScene(0,-_velocity));

    //若炮弹飞出场景，则销毁
    if(x()>400 || x()<-400 || y()>400 || y()<-400)
    {
        hide();
        delete this;
    }
}
