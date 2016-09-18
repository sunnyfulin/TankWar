#include "Tank.h"

#include <QPen>
#include <QColor>
#include <QBrush>
#include <QDebug>
#include <QTimer>
#include <QPainter>
#include <QMouseEvent>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QKeySequence>
#include <QKeyEvent>

CTank::CTank(QGraphicsItem * parent)
    : QGraphicsObject(parent),
      _isMoving(false),
      _angle(0),
      _omega(2),
      _velocity(0),
      _maxForwardVelocity(3),
      _forwardAcceleration(0.2),
      _maxBackwardVelocity(-2),
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

    _keyPressedSet.insert(e->text());

    if(_keyPressedSet.find("w") != _keyPressedSet.end() && _keyPressedSet.find("a") != _keyPressedSet.end())
    {
        _isMoving = true;
        MoveForward();
        MoveLeft();
    }
    else if(_keyPressedSet.find("w") != _keyPressedSet.end() && _keyPressedSet.find("d") != _keyPressedSet.end())
    {
        _isMoving = true;
        MoveForward();
        MoveRight();
    }
    else if(_keyPressedSet.find("s") != _keyPressedSet.end() && _keyPressedSet.find("a") != _keyPressedSet.end())
    {
        _isMoving = true;
        MoveBackward();
        MoveLeft();
    }
    else if(_keyPressedSet.find("s") != _keyPressedSet.end() && _keyPressedSet.find("d")!= _keyPressedSet.end())
    {
        _isMoving = true;
        MoveBackward();
        MoveRight();
    }
    else if(_keyPressedSet.find("w") != _keyPressedSet.end())
    {
        _isMoving = true;
        MoveForward();
    }
    else if(_keyPressedSet.find("s") != _keyPressedSet.end())
    {
        _isMoving = true;
        MoveBackward();
    }
    else if(_keyPressedSet.find("a") != _keyPressedSet.end())
    {
        MoveLeft();
    }
    else if(_keyPressedSet.find("d") != _keyPressedSet.end())
    {
        MoveRight();
    }
}

void CTank::keyReleaseEvent(QKeyEvent *e)
{
    if(e->key()!=Qt::Key_W && e->key()!=Qt::Key_S && e->key()!=Qt::Key_A && e->key()!=Qt::Key_D)
        return;

    _keyPressedSet.remove(e->text());

    switch (e->key()) {
    case Qt::Key_W: case Qt::Key_S:
        _isMoving = false;
        break;
    default:
        break;
    }
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

    if(!_isMoving)
    {
        MoveStop();
    }

    setPos(mapToScene(0,-_velocity));

    setRotation(_angle);

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


