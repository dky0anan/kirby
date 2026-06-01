#include "StartScreen.h"

#include <QGraphicsPixmapItem>
#include <QKeyEvent>

StartScreen::StartScreen() {
    setSceneRect(0, 0, 1620, 1080);

    QPixmap bg(":/Image/Image/bg/start.png");
    QGraphicsPixmapItem *item = new QGraphicsPixmapItem(
        bg.scaled(1620, 1080, Qt::IgnoreAspectRatio, Qt::SmoothTransformation)
    );
    addItem(item);
}

void StartScreen::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter) {
        emit pressEnter();
    }
}
