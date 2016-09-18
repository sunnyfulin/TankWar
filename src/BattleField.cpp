#include "BattleField.h"
#include "Tank.h"

#include <QDebug>
#include <QFocusEvent>
#include <QCursor>

CBattleField::CBattleField(int x, int y, int w, int h)
    : QGraphicsScene(x,y,w,h)
{
    _tank = new CTank;
    addItem(_tank);

    _tank->grabKeyboard();
    _tank->childItems().first()->grabMouse();
}


