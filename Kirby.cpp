#include "Kirby.h"
#include <QGraphicsScene>
#include <QKeyEvent>
#include "Bullet.h"
#include "Enemy.h"
#include "Block.h"
#include "StageOne.h"
#include <QPixmap>
#include <QTimer>
#include <QDebug>

// 1. 建構子
Kirby::Kirby() {
    animTimer   = new QTimer(this);
    downTimer   = new QTimer(this);
    inhaleTimer = new QTimer(this);
    invincibleTimer = new QTimer(this);
    blinkTimer  = new QTimer(this);

    connect(animTimer, SIGNAL(timeout()), this, SLOT(advanceAnimation())); //connect
    connect(downTimer, SIGNAL(timeout()), this, SLOT(flyDown()));
    connect(inhaleTimer, SIGNAL(timeout()), this, SLOT(inhalePull()));
    connect(invincibleTimer, SIGNAL(timeout()), this, SLOT(endInvincible()));
    downTimer->start(50);

    loadPixmaps();
    setPixmap(flyR1);
    currentState = FastFalling;
    pressUp = false;
    runFrame = 0;
    flyFrame = 0;

} // 建構子結束

void Kirby::loadPixmaps() {

    runR1 = QPixmap(":/Image/Image/Kirby_normal/kirby_run_1_R.png");
    runR2 = QPixmap(":/Image/Image/Kirby_normal/kirby_run_2_R.png");
    runR3 = QPixmap(":/Image/Image/Kirby_normal/kirby_run_3_R.png");
    runR4 = QPixmap(":/Image/Image/Kirby_normal/kirby_run_4_R.png");
    stopR = QPixmap(":/Image/Image/Kirby_normal/kirby_stop_R.png");
    runL1 = QPixmap(":/Image/Image/Kirby_normal/kirby_run_1_L.png");
    runL2 = QPixmap(":/Image/Image/Kirby_normal/kirby_run_2_L.png");
    runL3 = QPixmap(":/Image/Image/Kirby_normal/kirby_run_3_L.png");
    runL4 = QPixmap(":/Image/Image/Kirby_normal/kirby_run_4_L.png");
    stopL = QPixmap(":/Image/Image/Kirby_normal/kirby_stop_L.png");
    downL = QPixmap(":/Image/Image/Kirby_normal/kirby_down_L.png");
    downR = QPixmap(":/Image/Image/Kirby_normal/kirby_down_R.png");
    jump1 = QPixmap(":/Image/Image/Kirby_normal/kirby_jump(1).png");
    jump2 = QPixmap(":/Image/Image/Kirby_normal/kirby_jump(2).png");
    jump3 = QPixmap(":/Image/Image/Kirby_normal/kirby_jump(3).png");
    flyR1 = QPixmap(":/Image/Image/Kirby_normal/kirby_fly_1_R.png");
    flyR2 = QPixmap(":/Image/Image/Kirby_normal/kirby_fly_2_R.png");
    flyL1 = QPixmap(":/Image/Image/Kirby_normal/kirby_fly_1_L.png");
    flyL2 = QPixmap(":/Image/Image/Kirby_normal/kirby_fly_2_L.png");
    attackR = QPixmap(":/Image/Image/Kirby_normal/kirby_attack_R.png");
    attackL = QPixmap(":/Image/Image/Kirby_normal/kirby_attack_L.png");
    mouthR  = QPixmap(":/Image/Image/Kirby_normal/kirby_back.png");
    mouthL  = QPixmap(":/Image/Image/Kirby_normal/kirby_back.png");
    // Fire
    fRunR[0] = QPixmap(":/Image/Image/Kirby_fire/kirbyfire_run(1)_R.png");
    fRunR[1] = QPixmap(":/Image/Image/Kirby_fire/kirbyfire_run(2)_R.png");
    fRunR[2] = QPixmap(":/Image/Image/Kirby_fire/kirbyfire_run(3)_R.png");
    fRunL[0] = QPixmap(":/Image/Image/Kirby_fire/kirbyfire_run(1)_L.png");
    fRunL[1] = QPixmap(":/Image/Image/Kirby_fire/kirbyfire_run(2)_L.png");
    fRunL[2] = QPixmap(":/Image/Image/Kirby_fire/kirbyfire_run(3)_L.png");
    fStopR   = QPixmap(":/Image/Image/Kirby_fire/kirbyfire_stop_R.png");
    fStopL   = QPixmap(":/Image/Image/Kirby_fire/kirbyfire_stop_L.png");
    fDownR   = QPixmap(":/Image/Image/Kirby_fire/kirbyfire_down_R.png");
    fDownL   = QPixmap(":/Image/Image/Kirby_fire/kirbyfire_down_L.png");
    fFlyR[0] = QPixmap(":/Image/Image/Kirby_fire/kirbyfire_fly(1)_R.png");
    fFlyR[1] = QPixmap(":/Image/Image/Kirby_fire/kirbyfire_fly(2)_R.png");
    fFlyL[0] = QPixmap(":/Image/Image/Kirby_fire/kirbyfire_fly(1)_L.png");
    fFlyL[1] = QPixmap(":/Image/Image/Kirby_fire/kirbyfire_fly(2)_L.png");
    fAtkR    = QPixmap(":/Image/Image/Kirby_fire/kirbyfire_attack_R.png");
    fAtkL    = QPixmap(":/Image/Image/Kirby_fire/kirbyfire_attack_L.png");
    fFireR[0]= QPixmap(":/Image/Image/Kirby_fire/kirbyfire_fire(1)_R.png");
    fFireR[1]= QPixmap(":/Image/Image/Kirby_fire/kirbyfire_fire(2)_R.png");
    fFireR[2]= QPixmap(":/Image/Image/Kirby_fire/kirbyfire_fire(3)_R.png");
    fFireL[0]= QPixmap(":/Image/Image/Kirby_fire/kirbyfire_fire(1)_L.png");
    fFireL[1]= QPixmap(":/Image/Image/Kirby_fire/kirbyfire_fire(2)_L.png");
    fFireL[2]= QPixmap(":/Image/Image/Kirby_fire/kirbyfire_fire(3)_L.png");
    // Spark
    sRunR[0] = QPixmap(":/Image/Image/Kirby_spark/Kirby_spark_run(1)_R.png");
    sRunR[1] = QPixmap(":/Image/Image/Kirby_spark/Kirby_spark_run(2)_R.png");
    sRunL[0] = QPixmap(":/Image/Image/Kirby_spark/Kirby_spark_run(1)_L.png");
    sRunL[1] = QPixmap(":/Image/Image/Kirby_spark/Kirby_spark_run(2)_L.png");
    sStopR   = QPixmap(":/Image/Image/Kirby_spark/Kirby_spark_stop_R.png");
    sStopL   = QPixmap(":/Image/Image/Kirby_spark/Kirby_spark_stop_L.png");
    sDownR   = QPixmap(":/Image/Image/Kirby_spark/Kirby_spark_down_R.png");
    sDownL   = QPixmap(":/Image/Image/Kirby_spark/Kirby_spark_down_L.png");
    sFlyR[0] = QPixmap(":/Image/Image/Kirby_spark/Kirby_spark_fly(1)_R.png");
    sFlyR[1] = QPixmap(":/Image/Image/Kirby_spark/Kirby_spark_fly(2)_R.png");
    sFlyL[0] = QPixmap(":/Image/Image/Kirby_spark/Kirby_spark_fly(1)_L.png");
    sFlyL[1] = QPixmap(":/Image/Image/Kirby_spark/Kirby_spark_fly(2)_L.png");
    sAtk[0]  = QPixmap(":/Image/Image/Kirby_spark/Kirby_spark_attack(1).png");
    sAtk[1]  = QPixmap(":/Image/Image/Kirby_spark/Kirby_spark_attack(2).png");
    sAtk[2]  = QPixmap(":/Image/Image/Kirby_spark/Kirby_spark_attack(3).png");
}

QPixmap Kirby::stopPix() const {
    if (currentAbility == Fire)
        return currentDir == Right ? fStopR : fStopL;
    if (currentAbility == Spark)
        return currentDir == Right ? sStopR : sStopL;
    return currentDir == Right ? stopR : stopL;
}

QPixmap Kirby::fly1Pix() const {
    if (currentAbility == Fire) {
        return currentDir == Right ? fFlyR[0] : fFlyL[0];
    }
    if (currentAbility == Spark) {
        return currentDir == Right ? sFlyR[0] : sFlyL[0];
    }
    return currentDir == Right ? flyR1 : flyL1;
}

QPixmap Kirby::fly2Pix() const {
    if (currentAbility == Fire)
        return currentDir == Right ? fFlyR[1] : fFlyL[1];
    if (currentAbility == Spark)
        return currentDir == Right ? sFlyR[1] : sFlyL[1];
    return currentDir == Right ? flyR2 : flyL2;
}

QPixmap Kirby::runPix(int frame) const {
    if (currentAbility == Fire) {
        int f = frame % 3;
        return currentDir == Right ? fRunR[f] : fRunL[f];
    }
    if (currentAbility == Spark) {
        int f = frame % 2;
        return currentDir == Right ? sRunR[f] : sRunL[f];
    }
    // Normal
    if (currentDir == Right) {
        if (frame == 0) return runR1;
        if (frame == 1) return runR2;
        if (frame == 2) return runR4;
        return runR3;
    } else {
        if (frame == 0) return runL1;
        if (frame == 1) return runL2;
        if (frame == 2) return runL4;
        return runL3;
    }
}

void Kirby::advanceAnimation() {
    // 飛行動畫
    if (currentState == Flying) {
        flyFrame = (flyFrame + 1) % 2;
        setPixmap(flyFrame == 0 ? fly1Pix() : fly2Pix());
    }
    // 跑步動畫
    if (currentState == Running) {
        if (currentAbility == Fire)
            runFrame = (runFrame + 1) % 3;
        else if (currentAbility == Spark)
            runFrame = (runFrame + 1) % 2;
        else
            runFrame = (runFrame + 1) % 4;
        setPixmapWithBottomAnchor(runPix(runFrame));
    }
}
/*
void Kirby::advanceAnimation() {
    if (currentState == Flying) {
        flyFrame = (flyFrame + 1) % 2; // 讓它在 0 和 1 之間切換就好

        if (currentDir == Right) {
            setPixmap(flyFrame == 0 ? flyR1 : flyR2);
        } else {
            setPixmap(flyFrame == 0 ? flyL1 : flyL2);
        }
    }
    else if (currentState == Running) { // 跑步動畫的獨立循環
        runFrame = (runFrame + 1) % 4;

        if (currentDir == Right) {
            if (runFrame == 0) setPixmapWithBottomAnchor(runR1);
            else if (runFrame == 1) setPixmapWithBottomAnchor(runR2);
            else if (runFrame == 2) setPixmapWithBottomAnchor(runR4);
            else if (runFrame == 3) setPixmapWithBottomAnchor(runR3);
        } else {
            if (runFrame == 0) setPixmapWithBottomAnchor(runL1);
            else if (runFrame == 1) setPixmapWithBottomAnchor(runL2);
            else if (runFrame == 2) setPixmapWithBottomAnchor(runL4);
            else if (runFrame == 3) setPixmapWithBottomAnchor(runL3);
        }
     }
}
*/
void Kirby::flyDown() {
    if (!pressUp) { // 如果玩家沒有按住 UP 鍵，則處理環境重力
        if (currentState == Standing || currentState == Running || currentState == Crouching || currentState == Fulling || currentState == Attacking) {
            return;
        }
        animTimer->stop();
        switch (currentState) {
        case Flying:
            animTimer->stop();
            setPos(x(), y() + 15);  // 緩慢下降
            setPixmap(fly1Pix());
            break;
        case FastFalling:
            animTimer->stop();
            setPos(x(), y() + 25); // X鍵帶來的快速下墜
            setPixmap(jump3); // 下墜貼圖
            break;
        default:
            break;
        }
    }
}

void Kirby::inhalePull() {
    if (currentState != Inhaling || !scene()) return;

    Enemy *e = getEnemyInFront(150);
    if (e && e->canBeInhaled()) {
        swallowEnemy(e);
    }
}
void Kirby::startInhale() {
    currentState = Inhaling;
    setPixmap(currentDir == Right ? attackR : attackL);
    if (!inhaleTimer->isActive()) inhaleTimer->start(100);
}
void Kirby::stopInhale() {
    inhaleTimer->stop();
    landOnGround();
}
void Kirby::swallowEnemy(Enemy *e) {
    inhaleTimer->stop();
    pendingAbility = None;
    if (e->getType() == HOT_HEAD) pendingAbility = Fire;
    else if (e->getType() == SPARKY) pendingAbility = Spark;

    scene()->removeItem(e);
    delete e;

    currentState = Mouthful;
    setPixmap(currentDir == Right ? mouthR : mouthL);
}
void Kirby::spitStar() {
    pendingAbility = None;
    currentState = Spitting;
    setPixmap(currentDir == Right ? attackR : attackL);

    Bullet *bullet = new Bullet(currentDir == Right);
    bullet->setPos(currentDir == Right ? x() + 60 : x() - 40, y() + 20);
    scene()->addItem(bullet);

    QTimer::singleShot(500, this, [=]() { landOnGround(); });
}

void Kirby::useAbility() {
    if (currentAbility == None) return;
    currentState = AbilityAttack;

    if (currentAbility == Fire) {
        setPixmap(currentDir == Right ? fAtkR : fAtkL);
        int frame = 0;
        QTimer *fireAnim = new QTimer(this);
        connect(fireAnim, &QTimer::timeout, [=]() mutable {
            if (frame < 3) {
                setPixmap(currentDir == Right ? fFireR[frame] : fFireL[frame]);
                frame++;
            } else {
                fireAnim->stop();
                fireAnim->deleteLater();
                landOnGround();
            }
        });
        fireAnim->start(120);

    } else if (currentAbility == Spark) {
        int frame = 0;
        QTimer *sparkAnim = new QTimer(this);
        connect(sparkAnim, &QTimer::timeout, [=]() mutable {
            if (frame < 3) {
                setPixmap(sAtk[frame]);
                frame++;
            } else {
                sparkAnim->stop();
                sparkAnim->deleteLater();
                landOnGround();
            }
        });
        sparkAnim->start(120);
    }
}
void Kirby::dropAbility() {
    currentAbility = None;
    emit abilityChanged(None);
    landOnGround();
}

bool Kirby::hasEnemyInFront(int distance) {
    return getEnemyInFront(distance) != nullptr;
}
Enemy* Kirby::getEnemyInFront(int distance) {
    if (!scene()) return nullptr;
    QRectF radarRect;
    if (currentDir == Right)
        radarRect = QRectF(x() + pixmap().width(), y(), distance, pixmap().height());
    else
        radarRect = QRectF(x() - distance, y(), distance, pixmap().height());

    for (QGraphicsItem *item : scene()->items(radarRect)) {
        Enemy *e = dynamic_cast<Enemy*>(item);
        if (e) return e;
    }
    return nullptr;
}

void Kirby::endInvincible() {
    invincible = false;
    invincibleTimer->stop();
    blinkTimer->stop();
    setVisible(true);
}
// 處理落地瞬間的狀態與貼圖切換
void Kirby::landOnGround() {
    currentState = Standing;
    setPixmap(stopPix());
}
void Kirby::setFalling() {
    currentState = FastFalling;
}

bool Kirby::isBlockedHorizontally(int dx) {
    if (!scene()) return false;
    // 往移動方向探 dx 寬的矩形
    QRectF checkRect;
    if (dx > 0) {
        // 往右：檢查右側
        checkRect = QRectF(x() + pixmap().width(), y() + 4, dx, pixmap().height() - 8);
    } else {
        // 往左：檢查左側
        checkRect = QRectF(x() + dx, y() + 4, -dx, pixmap().height() - 8);
    }
    QList<QGraphicsItem *> hits = scene()->items(checkRect);
    for (QGraphicsItem *it : hits) {
        if (dynamic_cast<Block*>(it)) return true;
    }
    return false;
}

void Kirby::setPixmapWithBottomAnchor(const QPixmap &newPixmap) {
    // 1. 記下換圖前，卡比在場景中的「舊雙腳底部 Y 座標」
    qreal oldBottom = y() + pixmap().height();

    // 2. 更換圖片素材
    setPixmap(newPixmap);

    // 3. 如果在地上狀態（站立、跑步、蹲下），維持腳底貼齊地面，動態往回調整 y 座標（Top）
    if (currentState == Standing || currentState == Running || currentState == Crouching) {
        setPos(x(), oldBottom - newPixmap.height());
    }
}

bool Kirby::isPressingUp() { return pressUp; }

// 按鍵事件
void Kirby::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Right) pressRight = true;
    if (event->key() == Qt::Key_Left) pressLeft = true;
    if (event->key() == Qt::Key_Up) pressUp = true;
    if (event->key() == Qt::Key_Down) pressDown = true;

    // X 鍵攻擊是單次動作，保留在這裡
    if (event->key() == Qt::Key_X) {
        // 如果在空中 -> 變成快速下墜狀態
        if (currentState == Flying) {
            currentState = FastFalling;
        }
        // 如果在地上 -> 執行攻擊
        else if (currentState == Standing || currentState == Running) {
            Enemy *targetEnemy = getEnemyInFront(150);
            // 1. 播放卡比的攻擊動作
            setPixmap(currentDir == Right ? attackR : attackL);
            // 如果 targetEnemy 不是空的，代表前面真的有活生生的敵人！
            if (targetEnemy != nullptr) {

                // 2. 讓敵人從場景消失並釋放記憶體
                scene()->removeItem(targetEnemy);
                delete targetEnemy;

                // 3. 0.75 秒後卡比恢復原狀
                QTimer::singleShot(500, this, [=](){
                    currentState = Fulling;
                    setPixmap(currentDir == Right ? flyR1 : flyL1);
                });
            }
            else {
                QTimer::singleShot(500, this, [=](){
                    currentState = Standing;
                    setPixmap(currentDir == Right ? stopR : stopL);
                });
            }
        }
        else if (currentState == Fulling) {
            currentState = Attacking;

            if (currentDir == Right) {
                setPixmap(attackR);
                Bullet *bullet = new Bullet(true);
                bullet->setPos(x() + 150, y() + 40);
                scene()->addItem(bullet);
                QTimer::singleShot(750, this, [=](){
                    currentState = Standing;
                    setPixmap(stopR);
                });
            }
            else if (currentDir == Left) {
                setPixmap(attackL);
                Bullet *bullet = new Bullet(false);
                bullet->setPos(x() - 75, y() + 40);
                scene()->addItem(bullet);
                QTimer::singleShot(750, this, [=](){
                    currentState = Standing;
                    setPixmap(stopL);
                });
            }
        }
    }
    else if (event->key() == Qt::Key_Z) {
        if (currentState == Mouthful) {
            currentAbility = pendingAbility;
            pendingAbility = None;
            currentState   = Standing;
            emit abilityChanged(currentAbility);
            setPixmap(stopPix());
        } else if (currentState == Standing || currentState == Running) {
            startInhale();
        } else if (currentState == Inhaling) {
            stopInhale();
            spitStar();
        }
    }
    else if (event->key() == Qt::Key_Escape) {
        dropAbility();
    }
}

void Kirby::keyReleaseEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Right) pressRight = false;
    if (event->key() == Qt::Key_Left) pressLeft = false;
    if (event->key() == Qt::Key_Up) pressUp = false;
    if (event->key() == Qt::Key_Down) pressDown = false;
    if (event->key() == Qt::Key_Z) {
        if (currentState == Inhaling) stopInhale();
    }
}

void Kirby::processMovement() {
   qreal currentSceneWidth = scene()->width();
   bool isMovingHorizontally = false;
   // 先記錄下移動前的舊方向，用來判斷玩家有沒有中途轉身
   Direction oldDir = currentDir;

   // ─── 處理水平物理移動 ───
   if (pressRight) {
       currentDir = Right;
       isMovingHorizontally = true;
       if (!isBlockedHorizontally(10) && pos().x() < currentSceneWidth - 200) {
           setPos(x() + 5, y());
       }
   }
   else if (pressLeft) {
       currentDir = Left;
       isMovingHorizontally = true;
       if (!isBlockedHorizontally(-10) && pos().x() > 0) {
           setPos(x() - 5, y());
       }
   }

   // ─── 處理垂直物理移動 (飛行) ───
   if (pressUp) {
       currentState = Flying;
       if (y() > 10) {
           setPos(x(), y() - 5);
       }
       if (!animTimer->isActive()) {
           animTimer->start(150);
       }
   }

   // ─── 處理地上跑步動畫 ───
   if (currentState == Standing || currentState == Running) {
       if (isMovingHorizontally) {
           // 剛開始跑步的瞬間，立刻給第 1 張圖並啟動計時器
           if (currentState != Running) {
               currentState = Running;
               runFrame = 0;
               setPixmapWithBottomAnchor(currentDir == Right ? runR1 : runL1);
               if (!animTimer->isActive()) {
                   animTimer->start(250);
               }
           }
           // 如果已經在跑步中，但玩家按了反方向，立刻強制更換貼圖，操作才不會卡頓
           else if (currentDir != oldDir) {
               runFrame = 0;
               setPixmapWithBottomAnchor(currentDir == Right ? runR1 : runL1);
           }
       } else {
           // 沒有按左右鍵，如果是跑步狀態就恢復站立姿勢並停止計時器
           if (currentState == Running) {
               currentState = Standing;
               animTimer->stop();
               setPixmapWithBottomAnchor(currentDir == Right ? stopR : stopL);
           }
       }
   }

   // ─── 4. 處理蹲下 ───
   if (pressDown) {
       if (currentState == Standing || currentState == Running) {
           currentState = Crouching;
           setPixmapWithBottomAnchor(currentDir == Right ? downR : downL);
       }
   } else if (currentState == Crouching && !pressDown) {
       currentState = Standing;
       setPixmapWithBottomAnchor(currentDir == Right ? stopR : stopL);
   }
}

void Kirby::takeDamage() {
   // 1. 改用 bool 變數檢查，【絕對不要】改動 currentState
   if (invincible == true) return;

   hp--;
   emit hpChanged();
   if (hp <= 0) {
       loseLife();
       return;
   }

   // 2. 開啟無敵護盾
   invincible = true;

   // 3. 讓卡比閃爍 2 秒 (100ms * 20次)
   QTimer *blinkTimer = new QTimer(this);
   int blinkCount = 0;
   connect(blinkTimer, &QTimer::timeout, this, [=]() mutable {
       setVisible(!isVisible());
       blinkCount++;
       if (blinkCount >= 20) {
           blinkTimer->stop();
           blinkTimer->deleteLater();
           setVisible(true);

           // 4. 閃爍結束，關閉無敵護盾
           invincible = false;
       }
   });
   blinkTimer->start(100);
}
/*
void Kirby::takeDamage() {
    if (invincible) return;
    hp--;
    if (hp <= 0) {
        lives--;
        if (lives <= 0) {
            currentState = Dead;
            emit hpChanged();
            emit gameOver();
            return;
        }
        hp = 3;
    }
    invincible = true;
    emit hpChanged();
    invincibleTimer->start(2000);

    bool visible = true;
    blinkTimer->disconnect();
    connect(blinkTimer, &QTimer::timeout, [=]() mutable {
        visible = !visible;
        setVisible(visible);
    });
    blinkTimer->start(150);
}
*/
/*
void Kirby::takeDamage() {
    if (currentState == Invincible) return;  // 無敵中不扣血
    hp--;
    emit hpChanged();

    if (hp <= 0) {
        loseLife();
        return;
    }

    // 進入無敵狀態，閃爍 2 秒
    currentState = Invincible;
    QTimer *blinkTimer = new QTimer(this);
    int blinkCount = 0;
    connect(blinkTimer, &QTimer::timeout, this, [=]() mutable {
        setVisible(!isVisible());
        blinkCount++;
        if (blinkCount >= 20) {  // 閃 20 次
            blinkTimer->stop();
            blinkTimer->deleteLater();
            setVisible(true);
            if (currentState == Invincible)
                currentState = Standing;
        }
    });
    blinkTimer->start(100);  // 每 100ms 閃一次
}
*/
void Kirby::loseLife() {
    hp = 3;
    lives--;
    setVisible(true);
    currentState = Standing;
    emit livesChanged();
    emit hpChanged();

    if (lives <= 0) {
        lives = 0;
        emit gameOver();
        return;
    }
    // 回到起點
    setPos(100, 300);
}

void Kirby::addLife() {
    if (lives < 3) {
        lives++;
        emit livesChanged();
    }
}

void Kirby::healFull() {
    hp = 3;
    emit hpChanged();
}
