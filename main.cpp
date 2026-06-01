#include <QApplication>
#include <QGraphicsView>
#include "StartScreen.h"
#include "StageOne.h"
#include "StageTwo.h"
#include "ClearScreen.h"
#include "GameOver.h"

// 前向宣告，讓函式可以互相呼叫
void showStartScreen(QGraphicsView *view);
void showStage(QGraphicsView *view, int stageNum);
void showGameOver(QGraphicsView *view);
void showEnding(QGraphicsView *view);

// ===== 開始畫面 =====
void showStartScreen(QGraphicsView *view) {
    StartScreen *start = new StartScreen();
    view->setScene(start);

    QObject::connect(start, &StartScreen::pressEnter, [=]() {
        start->deleteLater();
        showStage(view, 1);  // 進入第一關
    });
}

// ===== 關卡 =====
void showStage(QGraphicsView *view, int stageNum) {
    StageBase *stage = nullptr;

    if (stageNum == 1)      stage = new StageOne();
    else if (stageNum == 2) stage = new StageTwo();

    if (!stage) return;
    view->setScene(stage);

    // 過關 → 下一關或結束畫面
    QObject::connect(stage, &StageBase::stageClear, [=]() {
        stage->deleteLater();
        if (stageNum < 2) {          // 2 是最後一關的編號
            showStage(view, stageNum + 1);
        } else {
            showEnding(view);        // 跳到結束畫面
        }
    });

    // Game Over
    QObject::connect(stage, &StageBase::gameOver, [=]() {
        stage->deleteLater();
        showGameOver(view);
    });
}

// ===== Game Over 畫面 =====
void showGameOver(QGraphicsView *view) {
    GameOver *go = new GameOver();
    view->setScene(go);

    // Enter 回到開始畫面
    QObject::connect(go, &GameOver::restartGame, [=]() {
        go->deleteLater();
        showStartScreen(view);
    });

    // Exit 頁按 Enter 跳出遊戲
    QObject::connect(go, &GameOver::exitGame, [=]() {
        QApplication::quit();
    });
}

// ===== Clear 畫面 =====
void showEnding(QGraphicsView *view) {
    // 假設結束畫面跟開始畫面類似，按 Enter 回選單
    ClearScreen *clear = new ClearScreen();
    view->setScene(clear);

    QObject::connect(clear, &ClearScreen::pressEnter, [=]() {
        clear->deleteLater();
        QApplication::quit();
    });
}

// ===== main =====
int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    QGraphicsView *view = new QGraphicsView();
    view->setFixedSize(1620, 1080);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->show();

    showStartScreen(view);  // 從開始畫面啟動

    return a.exec();
}
