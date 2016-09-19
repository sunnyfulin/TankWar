#ifndef CTURRET_H
#define CTURRET_H

#include <QGraphicsObject>

class CBullet;

class CTurret : public QGraphicsObject
{
    Q_OBJECT

public:
    CTurret(QGraphicsItem * parent =0);
    void UpdateCursor(const QPointF & cp);

protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void advance(int step);

    void mousePressEvent(QGraphicsSceneMouseEvent * e);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent * e);

signals:
    void SiFireBullet(QPointF, qreal);

private:
    qreal _omega;  //炮塔旋转角速度
    qreal _curAngle;  //当前炮塔相对于正前方的旋转的角度
    QPointF _endPoint;

    bool _isLocked;   //右键锁定炮塔

    bool _isFire;     //是否正在开炮中
    int _delta;       //炮管收缩长度
};

#endif // CTURRET_H
