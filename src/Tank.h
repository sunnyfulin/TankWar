#ifndef CTANK_H
#define CTANK_H

#include <QGraphicsObject>

#include "Turret.h"

class QTimer;
class QGraphicsSceneMouseEvent;

class CTank : public QGraphicsObject
{
    Q_OBJECT
public:
    CTank(QGraphicsItem *parent=0);

    void updateCursor(const QPointF & cp);

protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    void keyPressEvent(QKeyEvent * e);
    void keyReleaseEvent(QKeyEvent * e);

    void advance(int step) Q_DECL_OVERRIDE;

private:
    void MoveForward();
    void MoveBackward();
    void MoveLeft();
    void MoveRight();
    void MoveStop();

private:
    CTurret * _turret;

private:
    bool _isMoving;                //是否正在运动
    bool _isTurning;               //是否正在转弯

    qreal _angle;                //旋转角度
    qreal _omega;                //旋转角速度
    qreal _moveDrection;         //移动方向

    qreal _velocity;             //移动速度

    qreal _maxForwardVelocity;   //前进极速
    qreal _forwardAcceleration;  //加速度

    qreal _maxBackwardVelocity;      //倒车极速
    qreal _backwardAcceleration;     //倒车加速度
};

#endif // CTANK_H
