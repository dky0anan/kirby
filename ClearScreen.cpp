#include "ClearScreen.h"

#include <QGraphicsPixmapItem>
#include <QKeyEvent>

ClearScreen::ClearScreen() {
    setSceneRect(0, 0, 1620, 1080);

    QPixmap bg(":/Image/Image/bg/clear.png");
    QGraphicsPixmapItem *item = new QGraphicsPixmapItem(
        bg.scaled(1620, 1080, Qt::IgnoreAspectRatio, Qt::SmoothTransformation)
    );
    addItem(item);
}

void ClearScreen::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter) {
        emit pressEnter();
    }
}

