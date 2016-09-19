#include "BattleField.h"
#include "Bullet.h"
#include "Tank.h"

#include <QCursor>
#include <QDebug>


CBattleField::CBattleField(int x, int y, int w, int h)
    : QGraphicsScene(x,y,w,h)
{
    setItemIndexMethod(QGraphicsScene::NoIndex);

    _tank = new CTank;
    addItem(_tank);

    _tank->grabKeyboard();
    _tank->childItems().first()->grabMouse();

    _tank->setScale(0.8);

    connect(_tank->Turret,&CTurret::SiFireBullet,this,&CBattleField::OnFireBullet);
}

void CBattleField::UpdateCursor(const QPointF &cp)
{
    _tank->updateCursor(cp);
}

void CBattleField::OnFireBullet(QPointF startPoint, qreal drection)
{
    CBullet * b = new CBullet(drection-_tank->rotation());
    addItem(b);

    b->setPos(startPoint);
}


