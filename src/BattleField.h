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

private:
    CTank * _tank;
};

#endif // CBATTLEFIELD_H
