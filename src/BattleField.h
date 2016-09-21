#ifndef CBATTLEFIELD_H
#define CBATTLEFIELD_H


#include <QGraphicsScene>

class CTank;

class CBattleField : public QGraphicsScene
{
    Q_OBJECT
public:
    CBattleField(int x, int y, int w, int h);

public:
    void UpdateCursor(const QPointF & cp);

public slots:
    void OnFireBullet(QPointF startPoint,qreal drection);
    void OnMakeRut(QPointF pos, qreal direction);

public:
    CTank * _tank;
};

#endif // CBATTLEFIELD_H
