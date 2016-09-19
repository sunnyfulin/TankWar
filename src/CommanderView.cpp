#include "CommanderView.h"

#include "BattleField.h"
#include <QCursor>

CCommanderView::CCommanderView(CBattleField *scene)
    : QGraphicsView(scene),
      _s(scene)
{
    setBackgroundBrush(QColor(192,192,192));
    setRenderHint(QPainter::Antialiasing);
    setCacheMode(QGraphicsView::CacheBackground);
    setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    setWindowTitle("Tank War");
    setMouseTracking(true);
    resize(1000,805);
}

void CCommanderView::OnUpdateCursor()
{
    QPoint c = QCursor::pos();

    if(c == _c)
        return;

    _c = c;

    QPoint p(_c.x()-geometry().x(),_c.y()-geometry().y());
    QPointF cp = mapToScene(p);
    _s->UpdateCursor(cp);
}
