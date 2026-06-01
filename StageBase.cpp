#include "StageBase.h"
#include "Block.h"
#include "Item.h"
#include <QGraphicsView>
#include <QtGlobal>

StageBase::StageBase(int stageWidth, int stageHeight, QObject *parent)
    : QGraphicsScene(parent), kirby(nullptr), gameTimer(nullptr),
      m_stageWidth(stageWidth), m_stageHeight(stageHeight)
{
    setSceneRect(0, 0, m_stageWidth, m_stageHeight);
}

StageBase::~StageBase() {
    // 父類別解構時，Qt 會自動清空場景內指定了 parent 的物件
}

void StageBase::initStageCore() {
    kirby = new Kirby();
    kirby->setPos(100, 300);
    addItem(kirby);
    kirby->setFlag(QGraphicsItem::ItemIsFocusable);
    kirby->setFocus();

    // 加 HUD
    hud = new HUD(kirby);
    hud->setPos(0, 1000);
    addItem(hud);

    // 連接 HP/lives 信號
    connect(kirby, &Kirby::gameOver, this, [=]() {
        gameTimer->stop();
        emit gameOver();
    });

    gameTimer = new QTimer(this);
    connect(gameTimer, &QTimer::timeout, this, &StageBase::gameLoop);
    gameTimer->start(16);
}

void StageBase::gameLoop() {
    if (!kirby) return;

    kirby->processMovement();
    Kirby::State state = kirby->getCurrentState();

    // ===== 鏡頭更新 =====
    if (!views().isEmpty()) {
        updateCamera(views().first());
    }

    // ===== 碰撞與傳送門處理 =====
    QList<QGraphicsItem *> targets = collidingItems(kirby);
    bool hitBlock = false;

    for (QGraphicsItem *item : targets) {
        if (item->data(0).toString() == "door") {
            if (kirby->isPressingUp()) {
                gameTimer->stop();
                emit stageClear();
                return;
            }
        }

        Block *block = dynamic_cast<Block*>(item);
        if (!block) continue;

        // 取得邊界參數
        qreal blockTop    = block->mapToScene(block->boundingRect().topLeft()).y();
        qreal blockLeft   = block->mapToScene(block->boundingRect().topLeft()).x();
        qreal blockRight  = block->mapToScene(block->boundingRect().topRight()).x();
        qreal kirbyH      = kirby->pixmap().height();
        qreal kirbyW      = kirby->pixmap().width();
        qreal kirbyBottom = kirby->y() + kirbyH;
        qreal kirbyRight  = kirby->x() + kirbyW;
        qreal kirbyLeft   = kirby->x();

        qreal overlapTop   = kirbyBottom - blockTop;
        qreal overlapLeft  = kirbyRight  - blockLeft;
        qreal overlapRight = blockRight  - kirbyLeft;
        qreal minOverlap = qMin(overlapTop, qMin(overlapLeft, overlapRight));

        // ===== 單向平台的專屬判斷 ======
        if (block->getIsOneWay()) {
            // 條件：最淺的重疊是頂部，且重疊量小於 35 (容忍快速下墜的穿透量)，且沒有在按上鍵(往上飛)
            if (minOverlap == overlapTop && overlapTop > 0 && overlapTop <= 35 && !kirby->isPressingUp()) {
                kirby->setPos(kirby->x(), blockTop - kirbyH);
                if (state == Kirby::FastFalling || state == Kirby::Flying) {
                    kirby->landOnGround();
                }
                hitBlock = true;
            }
            // 單向平台不處理左右撞牆，處理完直接換下一個判定物件
            continue;
        }

        // ===== 一般實體 Block 判斷 =====
        hitBlock = true;
        if (minOverlap == overlapTop) {
            kirby->setPos(kirby->x(), blockTop - kirbyH);
            if (state == Kirby::FastFalling || state == Kirby::Flying) {
                kirby->landOnGround();
            }
        } else if (minOverlap == overlapLeft) {
            kirby->setPos(blockLeft - kirbyW, kirby->y());
        } else {
            kirby->setPos(blockRight, kirby->y());
        }
        break;
    }

    // ===== 離地偵測 =====
    if (state == Kirby::Standing || state == Kirby::Running || state == Kirby::Crouching) {
        QRectF feetRect(kirby->x() + 4, kirby->y() + kirby->pixmap().height(),
                        kirby->pixmap().width() - 8, 4);
        QList<QGraphicsItem *> below = items(feetRect);
        bool hasFloor = false;
        for (QGraphicsItem *it : below) {
            if (dynamic_cast<Block*>(it)) { hasFloor = true; break; }
        }
        if (!hasFloor) {
            kirby->setFalling();
        }
    }

    // ===== 掉洞偵測 =====
    if (kirby->y() > m_stageHeight + 100) {
        kirby->loseLife();
    }
    // ===== 道具偵測 =====
    for (QGraphicsItem *item : targets) {
        Item *collectible = dynamic_cast<Item*>(item);
        if (collectible) {
            // 根據道具的種類，給予卡比不同的效果
            if (collectible->getType() == Item::Tomato) {
                kirby->healFull(); // 蘋果：血量回滿到 3
            }
            else if (collectible->getType() == Item::OneUp) {
                kirby->addLife();  // 1UP：呼叫你寫好的加命函式
            }

            // 吃到後把道具從場景移除並釋放記憶體
            removeItem(collectible);
            delete collectible;
            continue;
        }
    }
}
void StageBase::updateCamera(QGraphicsView* view) {
    if (!view || !kirby) return;

    qreal targetX = kirby->x();
    qreal targetY = VIEW_HEIGHT / 2;

    qreal halfViewWidth = view->width() / 2;
    if (targetX < halfViewWidth) targetX = halfViewWidth;
    if (targetX > m_stageWidth - halfViewWidth) targetX = m_stageWidth - halfViewWidth;

    view->centerOn(targetX, targetY);

    // ★ HUD 跟著鏡頭 X 移動，Y 固定在畫面最底部
    if (hud) {
        qreal viewLeft = targetX - halfViewWidth;
        hud->setPos(viewLeft, 950);
    }
}
