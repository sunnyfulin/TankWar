#include <QApplication>
#include <QGraphicsView>

#include "BattleField.h"

#include <QTimer>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::setOverrideCursor(Qt::CrossCursor);
//    QApplication::setOverrideCursor(Qt::BlankCursor);

    CBattleField bf(-400, -400, 800, 800);
    bf.setItemIndexMethod(QGraphicsScene::NoIndex);

    QGraphicsView view(&bf);
    view.setBackgroundBrush(QPixmap(":/images/cheese.jpg"));
    view.setBackgroundBrush(QColor(192,192,192));
    view.setRenderHint(QPainter::Antialiasing);
    view.setCacheMode(QGraphicsView::CacheBackground);
    view.setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    view.setWindowTitle("Tank War");
    view.setMouseTracking(true);
    view.resize(800,800);
    view.show();

    QTimer timer;
    QObject::connect(&timer, &QTimer::timeout, &bf, &QGraphicsScene::advance);
    timer.start(1000 / 60);

    return a.exec();
}
