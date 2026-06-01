#ifndef STAGEBASE_H
#define STAGEBASE_H

#include <QGraphicsScene>
#include <QTimer>
#include "Kirby.h"
#include "HUD.h"

class StageBase : public QGraphicsScene {
    Q_OBJECT
public:
    // 定義畫面的固定寬高
    static const int VIEW_WIDTH = 1620;
    static const int VIEW_HEIGHT = 1080;
    StageBase(int stageWidth, int stageHeight, QObject *parent = nullptr);
    virtual ~StageBase();

signals:
    void stageClear();
    void gameOver();

protected:
    Kirby *kirby;
    HUD   *hud;
    QTimer *gameTimer;
    int m_stageWidth;
    int m_stageHeight;

    // 純虛擬函式：強迫所有子類別實作各自特有的地形
    virtual void initMap() = 0;

    // 基底類別的核心初始化流程（負責生成卡比、啟動計時器）
    void initStageCore();

    void gameLoop();
    void updateCamera(QGraphicsView* view);
};

#endif // STAGEBASE_H
