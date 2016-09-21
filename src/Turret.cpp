#include "Turret.h"

#include <QPainter>
#include <QSound>
#include <QGraphicsSceneMouseEvent>

#include <QDebug>

CTurret::CTurret(QGraphicsItem * parent)
    : QGraphicsObject(parent),
      _curAngle(180),
      _omega(1),
      _isLocked(false),
      _isFire(false),
      _delta(0),
      _pOutter(QPoint(-4,-30)),
      _pInner(QPoint(-4,-30)),
      _pOut(QPoint(-3,-85)),
      _pIn(QPoint(-2,-86)),
      _pCore(QPoint(-1,-88))
{
    _pOutter.lineTo(-10,-30);
    _pOutter.lineTo(-26,-21);
    _pOutter.lineTo(-20,26);
    _pOutter.lineTo(-16,30);
    _pOutter.lineTo(16,30);
    _pOutter.lineTo(20,26);
    _pOutter.lineTo(26,-21);
    _pOutter.lineTo(8,-30);
    _pOutter.lineTo(-10,-30);

    _pInner.lineTo(-20,-20);
    _pInner.lineTo(-16,30);
    _pInner.lineTo(16,30);
    _pInner.lineTo(20,-20);
    _pInner.lineTo(4,-30);
    _pInner.lineTo(-4,-30);

    _pOut.lineTo(-10,-130);
    _pOut.lineTo(-8,-115);
    _pOut.lineTo(-5,-125);
    _pOut.lineTo(-2,-120);
    _pOut.lineTo(0,-130);
    _pOut.lineTo(2,-130);
    _pOut.lineTo(5,-125);
    _pOut.lineTo(8,-115);
    _pOut.lineTo(10,-130);
    _pOut.lineTo(3,-85);
    _pOut.lineTo(-3,-85);

    _pIn.lineTo(-8,-114);
    _pIn.lineTo(-6,-110);
    _pIn.lineTo(-3,-119);
    _pIn.lineTo(-1,-114);
    _pIn.lineTo(0,-124);
    _pIn.lineTo(1,-114);
    _pIn.lineTo(3,-119);
    _pIn.lineTo(6,-110);
    _pIn.lineTo(8,-114);
    _pIn.lineTo(2,-86);
    _pIn.lineTo(-2,-86);

    _pCore.lineTo(-3,-110);
    _pCore.lineTo(-1,-105);
    _pCore.lineTo(0,-115);
    _pCore.lineTo(1,-105);
    _pCore.lineTo(3,-110);
    _pCore.lineTo(1,-88);
    _pCore.lineTo(-1,-88);
}

void CTurret::UpdateCursor(const QPointF &cp)
{
    _endPoint = cp;
}

QRectF CTurret::boundingRect() const
{
    return QRectF(-26,-130,52,170);
}

void CTurret::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    //炮塔后部的菜篮子
    painter->setPen(Qt::black);
    painter->drawRect(-15,30,30,10);
    painter->drawRect(-5,30,10,10);

    //炮管
    painter->setBrush(QColor(199,175,87));
    painter->drawRect(-3,-90 + _delta ,6,60);
    painter->drawRect(-4,-70 + _delta ,8,14);

    //炮塔底座轮廓
    painter->setBrush(QColor(141,123,113));
    painter->drawPath(_pOutter);
    painter->drawLine(-26,-21,26,-21);

    //炮塔顶部轮廓
    painter->setBrush(QColor(199,175,87));
    painter->drawPath(_pInner);

    //炮盾
    painter->drawRect(-5,-30,10,10);

    //矩形舱盖
    painter->drawRect(-10,15,20,10);

    //圆形舱盖
    painter->setBrush(QColor(141,123,113));
    painter->drawEllipse(-1,-11,20,20);
    painter->drawEllipse(2,-8,14,14);

    //开炮后的火焰效果
    if(_isFire)
    {
        painter->setPen(Qt::NoPen);
        painter->setBrush(QColor(255,255,255));
        painter->drawPath(_pOut);

        painter->setBrush(QColor(255,128,0));
        painter->drawPath(_pIn);

        painter->setBrush(QColor(255,0,0));
        painter->drawPath(_pCore);
    }
}

void CTurret::advance(int step)
{
    if(!step)
        return;

    //开炮特效：炮管收缩，开炮完毕，炮管还原
    if(_isFire)
    {
        if(_delta < 10)
            _delta += 1;
        else
            _isFire = false;
    }
    else if(_delta >0)
    {
        _delta -= 0.5;
    }

    //若炮塔锁定，则禁止炮塔旋转
    if(_isLocked)
        return;

    //旋转炮塔，跟随鼠标
    QLineF startLine(QPointF(0,0),QPointF(0,-1));
    QLineF endLine(QPointF(0,0),mapFromScene(_endPoint));

    qreal destAngle = endLine.angleTo(startLine);

    if(destAngle<0.5 || destAngle>359.5)
        return;

    if(_curAngle < destAngle)
        _curAngle += _omega;
    else
        _curAngle -= _omega;

    setRotation(180-_curAngle);
}

void CTurret::mousePressEvent(QGraphicsSceneMouseEvent *e)
{
    //左键开炮，启用开炮特效
    if((e->button() == Qt::LeftButton) && (!_isFire))
    {
        _isFire = true;

        QSound::play(":/sound/fire.wav");
        emit SiFireBullet(mapToScene(0,-90),_curAngle);
    }

    //右键锁定炮塔
    if(e->button() == Qt::RightButton)
        _isLocked = true;
}

void CTurret::mouseReleaseEvent(QGraphicsSceneMouseEvent *e)
{
    //右键松开，解除炮塔锁定
    if(e->button() == Qt::RightButton)
        _isLocked = false;
}


