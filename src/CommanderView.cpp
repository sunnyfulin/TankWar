#include "CommanderView.h"

#include "BattleField.h"
#include <QCursor>
#include <QScrollBar>

CCommanderView::CCommanderView(CBattleField *scene)
    : QGraphicsView(scene),
      _s(scene)
{
    setBackgroundBrush(QPixmap(":/images/cheese.jpg"));
//    setBackgroundBrush(QColor(192,192,192));
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setRenderHint(QPainter::Antialiasing);
    setCacheMode(QGraphicsView::CacheBackground);
    setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    setMouseTracking(true);
    setWindowTitle("Tank War");
    setSceneRect(-4000,-4000,8000,8000);
    resize(800,800);
}

void CCommanderView::OnUpdateCursor()
{
    QPoint c = QCursor::pos();
    QPoint p(c.x()-geometry().x(),c.y()-geometry().y());
    QPointF cp = mapToScene(p);
    _s->UpdateCursor(cp);
}
