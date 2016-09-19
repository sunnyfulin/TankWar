#ifndef CRUT_H
#define CRUT_H

#include <QGraphicsObject>

class CRut : public QGraphicsObject
{
public:
    CRut(qreal direction, QGraphicsItem * parent = 0);

protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void advance(int step);

private:
    QColor _color;
    int _alpha;
    qreal _direction;
};

#endif // CRUT_H
