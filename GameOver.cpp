#include "GameOver.h"
#include <QGraphicsPixmapItem>
#include <QApplication>

GameOver::GameOver() {
    setSceneRect(0, 0, 1620, 1080);

    conti = QPixmap(":/Image/Image/bg/game_over_continue.png");
    quit = QPixmap(":/Image/Image/bg/game_over_quit.png");
    QGraphicsPixmapItem *item = new QGraphicsPixmapItem(conti);
    addItem(item);

    onExitScreen = false;
}

void GameOver::keyPressEvent(QKeyEvent *event) {
    if (!onExitScreen) {
        // 目前在 gameover 圖
        if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter) {
            emit restartGame();  // 回到開始畫面
        }
        else if (event->key() == Qt::Key_Down) {
            // 切換到 quit 圖
            onExitScreen = true;
            clear();  // 清掉目前的圖
            QGraphicsPixmapItem *item = new QGraphicsPixmapItem(quit);
            addItem(item);
        }
    }
    else {
        // 目前在 exit 圖
        if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter) {
            emit exitGame();  // 跳出遊戲
        }
        else if (event->key() == Qt::Key_Up) {
            // 切回 gameover 圖
            onExitScreen = false;
            clear();
            QGraphicsPixmapItem *item = new QGraphicsPixmapItem(conti);
            addItem(item);
        }
    }
}
