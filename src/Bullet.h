#ifndef CBULLET_H
#define CBULLET_H

#include <QGraphicsItem>

class CBullet : public QGraphicsObject
{
public:
    CBullet(qreal drection, QGraphicsItem * parent = 0);

protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void advance(int step);

private:
    qreal _drection;
    int _velocity;
};

#endif // CBULLET_H
