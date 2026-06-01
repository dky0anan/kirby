#ifndef GAMEOVER_H
#define GAMEOVER_H

#pragma once
#include <QGraphicsScene>
#include <QKeyEvent>

class GameOver : public QGraphicsScene {
    Q_OBJECT
public:
    GameOver();

signals:
    void restartGame();   // 按 Enter 回到開始畫面
    void exitGame();      // 在 exit 頁按 Enter 跳出遊戲

protected:
    void keyPressEvent(QKeyEvent *event) override;

private:
    bool onExitScreen = false;  // 目前是在 gameover 圖還是 exit 圖
    QPixmap conti;
    QPixmap quit;
};

#endif // GAMEOVER_H
