#include "BattleField.h"
#include "Bullet.h"
#include "Tank.h"

#include <QDebug>


CBattleField::CBattleField(int x, int y, int w, int h)
    : QGraphicsScene(x,y,w,h)
{
    setItemIndexMethod(QGraphicsScene::NoIndex);

    _tank = new CTank;
    addItem(_tank);

    _tank->grabKeyboard();
    _tank->childItems().first()->grabMouse();

    //炮塔开炮，则创建炮弹
    connect(_tank->Turret,&CTurret::SiFireBullet,this,&CBattleField::OnFireBullet);

    //场景边框
    addRect(-400,-400,800,800,QPen(Qt::black));
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


