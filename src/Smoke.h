#ifndef CSMOKE_H
#define CSMOKE_H


#include <QGraphicsObject>

class CSmoke : public QGraphicsObject
{
public:
    CSmoke(qreal direction, QGraphicsItem * parent =0);

protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void advance(int step);

private:
    qreal _direction;

    int _alpha;

    QColor _outColor;
    QColor _innerColor;
    QColor _decorateColor;
};

#endif // CSMOKE_H
