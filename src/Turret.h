#ifndef CTURRET_H
#define CTURRET_H

#include <QGraphicsObject>
#include <QMouseEvent>

class CTurret : public QGraphicsObject
{
    Q_OBJECT

public:
    CTurret(QGraphicsItem * parent =0);

protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void advance(int step);

private:
    qreal _omega;  //炮塔旋转角速度
    qreal _curAngle;  //当前炮塔相对于正前方的旋转的角度
    qreal _destAngle;  //目标角度
};

#endif // CTURRET_H
