﻿#ifndef CTANK_H
#define CTANK_H

#include <QGraphicsObject>
#include <QSet>
#include <QSound>

#include "Turret.h"

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

    void advance(int step);

signals:
    void SiMakeRut(QPointF pos, qreal drection);

private:
    inline void MoveForward();
    inline void MoveBackward();
    inline void MoveLeft();
    inline void MoveRight();
    inline void MoveStop();

public:
    CTurret * Turret;

private:
    bool _isMoving;               //是否正在运动

    qreal _angle;                 //旋转角度
    qreal _omega;                 //旋转角速度
    qreal _velocity;              //移动速度
    qreal _maxForwardVelocity;    //前进极速
    qreal _forwardAcceleration;   //前进加速度
    qreal _maxBackwardVelocity;   //倒车极速
    qreal _backwardAcceleration;  //倒车加速度

    QSet<QString> _keyPressedSet; //当前按下的按键集合

    QSound _movingSound;
};

#endif // CTANK_H
