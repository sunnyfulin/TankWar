﻿#ifndef CCOMMANDERVIEW_H
#define CCOMMANDERVIEW_H

#include <QGraphicsView>

class CBattleField;

class CCommanderView : public QGraphicsView
{
public:
    CCommanderView(CBattleField *scene);

public slots:
    void OnUpdateCursor();

private:
    CBattleField * _s;
};

#endif // CCOMMANDERVIEW_H
