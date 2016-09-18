#include <QApplication>

#include <QTimer>
#include "CommanderView.h"
#include "BattleField.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::setOverrideCursor(Qt::CrossCursor);

    CBattleField bf(-400, -400, 800, 800);
    CCommanderView view(&bf);
    view.show();

    QTimer timer;
    QObject::connect(&timer, &QTimer::timeout, &view, &CCommanderView::OnUpdateCursor);
    QObject::connect(&timer, &QTimer::timeout, &bf, &QGraphicsScene::advance);
    timer.start(1000 / 60);

    return a.exec();
}
