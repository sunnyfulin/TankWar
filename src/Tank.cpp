#include "Tank.h"

#include <QPainter>
#include <QBrush>
#include <QPen>
#include <QMouseEvent>
#include <QDebug>
#include <QTimer>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsScene>
#include <QColor>

CTank::CTank(QGraphicsItem * parent)
    : QGraphicsObject(parent),
      _isMoving(false),
      _isTurning(false),
      _angle(0),
      _omega(2),
      _moveDrection(0),
      _velocity(0),
      _maxForwardVelocity(10),
      _forwardAcceleration(0.1),
      _maxBackwardVelocity(-4),
      _backwardAcceleration(0.1)
{
    _turret = new CTurret(this);
    _turret->setParentItem(this);
}

void CTank::updateCursor(const QPointF &cp)
{
    _turret->UpdateCursor(cp);
}

QRectF CTank::boundingRect() const
{
    return QRectF(-30,-50,60,100);
}

void CTank::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(Qt::black);
    painter->setBrush(QColor(135,120,117));
    painter->drawRect(QRect(-30,-50,16,100));
    painter->drawRect(QRect(14,-50,16,100));

    painter->setPen(Qt::black);
    painter->setBrush(QColor(199,175,87));
    painter->drawRect(-30,-44,60,92);

    painter->setBrush(QColor(182,162,92));
    painter->drawRect(-30,10,60,20);

    painter->drawLine(-14,-40,-14,0);
    painter->drawLine(14,-40,14,0);
    painter->drawLine(-14,-30,14,-30);
}

void CTank::keyPressEvent(QKeyEvent *e)
{
    if(e->key()!=Qt::Key_W && e->key()!=Qt::Key_S && e->key()!=Qt::Key_A && e->key()!=Qt::Key_D)
        return;

    switch (e->key())
    {
    case Qt::Key_W:
        _isMoving = true;
        MoveForward();
        break;
    case Qt::Key_S:
        _isMoving = true;
        MoveBackward();
        break;
    case Qt::Key_A:
        _isTurning = true;
        MoveLeft();
        break;
    case Qt::Key_D:
        _isTurning = true;
        MoveRight();
        break;
    default:
        break;
    }
}

void CTank::keyReleaseEvent(QKeyEvent *e)
{
    if(e->key()!=Qt::Key_W && e->key()!=Qt::Key_S && e->key()!=Qt::Key_A && e->key()!=Qt::Key_D)
        return;

    _isMoving = false;
    _isTurning = false;
}

void CTank::MoveForward()
{
    if(_velocity > _maxForwardVelocity)
    {
        _velocity = _maxForwardVelocity;
        return;
    }

    _velocity += _forwardAcceleration;
}

void CTank::MoveBackward()
{
    if(_velocity < _maxBackwardVelocity)
    {
        _velocity = _maxBackwardVelocity;
        return;
    }

    _velocity -= _backwardAcceleration;
}

void CTank::MoveLeft()
{
    if(_velocity>=0)
        _angle -= _omega;
    else
        _angle += _omega;
}

void CTank::MoveRight()
{
    if(_velocity>=0)
        _angle += _omega;
    else
        _angle -= _omega;
}

void CTank::advance(int step)
{
    if(!step)
        return;

    //移动
    if(!_isMoving)
    {
        MoveStop();
    }
    setPos(mapToParent(0,-_velocity));

    //转向
    setRotation(_angle);

    //更新
    update(boundingRect());
}

void CTank::MoveStop()
{
    if(_velocity > 0)
    {
        _velocity -= _forwardAcceleration;

        if(_velocity<=0)
        {
            _velocity = 0;

            _isMoving = false;
            return;
        }
    }
    else if(_velocity < 0)
    {
        _velocity += _backwardAcceleration;

        if(_velocity >= 0)
        {
            _velocity = 0;

            _isMoving = false;
            return;
        }
    }
}


