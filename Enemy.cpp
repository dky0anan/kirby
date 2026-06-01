#include "Enemy.h"
#include "Kirby.h"
#include "Bullet.h"
#include <QGraphicsScene>
#include <QDebug>
#include <QPixmap>

#define _USE_MATH_DEFINES
#include <cmath>

Enemy::Enemy(EnemyType type, qreal startX, qreal startY, qreal patrolLeft, qreal patrolRight)
    : QObject(), QGraphicsPixmapItem(), enemyType(type), patrolL(patrolLeft), patrolR(patrolRight),groundY(startY) {

    loadPixmaps();
    qDebug() << "pixmap height:" << pixmap().height();  // 加這行
    setupTimers();
    setPos(startX, groundY - pixmap().height());
}

Enemy::~Enemy() = default;

void Enemy::loadPixmaps() {
    switch (enemyType) {
    case WADDLE_DEE:
        frameR1 = QPixmap(":/Image/Image/Waddle Dee/Waddle_Dee_5.png");
        frameR2 = QPixmap(":/Image/Image/Waddle Dee/Waddle_Dee_4.png");
        frameL1 = QPixmap(":/Image/Image/Waddle Dee/Waddle_Dee_0.png");
        frameL2 = QPixmap(":/Image/Image/Waddle Dee/Waddle_Dee_1.png");
        if (!frameR1.isNull()) setPixmap(frameR1);
        break;
    case GORDO:
        frame1 = QPixmap(":/Image/Image/Gordo/Gordo(0).png");
        frame2 = QPixmap(":/Image/Image/Gordo/Gordo(1).png");
        if (!frame1.isNull()) setPixmap(frame1);
        break;
    case HOT_HEAD:
        frameR1 = QPixmap(":/Image/Image/Hot Head/Hot_head_run_R.png");
        frameR2 = QPixmap(":/Image/Image/Hot Head/Hot_head_stop_R.png");
        frameL1 = QPixmap(":/Image/Image/Hot Head/Hot_head_run_L.png");
        frameL2 = QPixmap(":/Image/Image/Hot Head/Hot_head_stop_L.png");
        frameA_R = QPixmap(":/Image/Image/Hot Head/Hot_head_attack_L.png");
        frameA_L = QPixmap(":/Image/Image/Hot Head/Hot_head_attack_L.png");
        if (!frameR1.isNull()) setPixmap(frameR1);
        break;
    case SPARKY:
        frameR1 = QPixmap(":/Image/Image/Sparky/Sparky_right1.png");
        frameR2 = QPixmap(":/Image/Image/Sparky/Sparky_right2.png");
        frameL1 = QPixmap(":/Image/Image/Sparky/Sparky_left1.png");
        frameL2 = QPixmap(":/Image/Image/Sparky/Sparky_left2.png");
        sparkFrame1 = QPixmap(":/Image/Image/Sparky/Sparky_attack_1.png");
        sparkFrame2 = QPixmap(":/Image/Image/Sparky/Sparky_attack_2.png");
        if (!frameR1.isNull()) setPixmap(frameR1);
        break;
    }
}

void Enemy::setupTimers() {
    moveTimer = new QTimer(this);
    connect(moveTimer, &QTimer::timeout, this, &Enemy::move);
    moveTimer->start(50);
/*
    if (enemyType == SPARKY) {
        sparkToggleTimer = new QTimer(this);
        connect(sparkToggleTimer, &QTimer::timeout, this, &Enemy::toggleSpark);
        sparkToggleTimer->start(1500);
    }
*/
    if (enemyType == HOT_HEAD) {
        QTimer *fireCheckTimer = new QTimer(this);
        connect(fireCheckTimer, &QTimer::timeout, this, &Enemy::checkFireBall);
        fireCheckTimer->start(2000);
    }
}

void Enemy::move() {
    if (!scene()) return;

    // 碰撞 Kirby → 扣血
    QList<QGraphicsItem *> hits = collidingItems();
    for (auto *item : hits) {
        Kirby *kirby = dynamic_cast<Kirby*>(item);
        if (kirby) {
            if (enemyType == SPARKY && !sparkActive) break;
            kirby->takeDamage();
            // 讓敵人從場景中移除
            if (scene()) {
                scene()->removeItem(this);
            }
            this->deleteLater();
            return;
        }
    }

    switch (enemyType) {

    case WADDLE_DEE: {
        qreal speed = 2;

        // 移動
        if (movingRight) {
            setPos(x() + speed, y());
            if (x() >= patrolR) movingRight = false;
        } else {
            setPos(x() - speed, y());
            if (x() <= patrolL) movingRight = true;
        }

        // 動畫：每 10 tick 換一格
        animCount++;
        if (animCount >= 10) {
            animCount = 0;
            animFrame = (animFrame + 1) % 2; // 0,1,2,3 循環

            QPixmap pm;
            if (movingRight) {
                if      (animFrame == 0) pm = frameR1;
                else if (animFrame == 1) pm = frameR2;
            } else {
                if      (animFrame == 0) pm = frameL1;
                else if (animFrame == 1) pm = frameL2;
            }
            if (!pm.isNull()) setPixmap(pm);
        }
        break;
    }

    case GORDO: {
        gordoPhase = (gordoPhase + 1) % 360;
        qreal cx = (patrolL + patrolR) / 2.0;
        qreal rx = (patrolR - patrolL) / 2.0;
        qreal ry = 40;
        double rad = gordoPhase * M_PI / 180.0;
        setPos(cx + rx * std::cos(rad), groundY + ry * std::sin(rad));

        animCount++;
        if (animCount >= 10) {
            animCount = 0;
            animFrame = (animFrame + 1) % 2;
            QPixmap pm = (animFrame == 0 ? frame1 : frame2);
            if (!pm.isNull()) setPixmap(pm);
        }
        break;
    }

    case HOT_HEAD: {
        if (isBreathing) {
            breathCount++;
            if (breathCount >= 30) { isBreathing = false; breathCount = 0; }
            return;
        }
        qreal speed = 2;
        if (movingRight) {
            setPos(x() + speed, y());
            if (x() >= patrolR) movingRight = false;
        } else {
            setPos(x() - speed, y());
            if (x() <= patrolL) movingRight = true;
        }

        animCount++;
        if (animCount >= 10) {
            animCount = 0;
            animFrame = (animFrame + 1) % 2;

            QPixmap pm;
            if (movingRight) {
                if      (animFrame == 0) pm = frameR1;
                else if (animFrame == 1) pm = frameR2;
            } else {
                if      (animFrame == 0) pm = frameL1;
                else if (animFrame == 1) pm = frameL2;
            }
            if (!pm.isNull()) setPixmap(pm);
        }
        break;
    }
    case SPARKY: {
        // ── 1. 重力 ──
        vy += 1.5;
        qreal newY = y() + vy;
        if (newY >= groundY - pixmap().height()) {
            newY = groundY - pixmap().height();

            // 落地時自動跳（小幅跳躍）
            if (!onGround) {
                vy = -10;  // 跳躍力道，調大跳更高
            } else {
                vy = 0;
            }
            onGround = true;
        } else {
            onGround = false;
        }
        setPos(x(), newY);

        // ── 2. 週期性放電（每 80 tick 放一次，持續 40 tick）──
        sparkCount++;

        if (sparkCount <= 40) {
            // 放電中：顯示電流動畫
            sparkActive = true;
            animCount++;
            if (animCount >= 8) {
                animCount = 0;
                animFrame = (animFrame + 1) % 2;
                QPixmap pm = (animFrame == 0 ? sparkFrame1 : sparkFrame2);
                if (!pm.isNull()) setPixmap(pm);
            }
        } else {
            // 非放電：顯示移動動畫
            sparkActive = false;
            animCount++;
            if (animCount >= 10) {
                animCount = 0;
                animFrame = (animFrame + 1) % 2;
                QPixmap pm = (animFrame == 0 ? frame1 : frame2);
                if (!pm.isNull()) setPixmap(pm);
            }
        }

        if (sparkCount >= 80) sparkCount = 0;  // 重置週期

        // ── 3. 水平移動（放電時也繼續移動）──
        jumpCount++;
        if (jumpCount >= 30) {   // 每 30 tick 換方向
            jumpCount = 0;
            moveDir = -moveDir;
        }

        qreal speed = 2;
        qreal newX = x() + speed * moveDir;
        // 巡邏邊界
        if (newX <= patrolL) { newX = patrolL; moveDir =  1; }
        if (newX >= patrolR) { newX = patrolR; moveDir = -1; }
        setPos(newX, y());

        // ── 4. 碰撞傷害只在放電時有效（已在外層處理，這裡不用動）──
        break;
    }
    /*
    case SPARKY: {
        vy += 1.5;
        qreal newY = y() + vy;
        if (newY >= groundY - pixmap().height()) {
            newY = groundY - pixmap().height();
            vy = (onGround ? 0 : -14);
            onGround = true;
        } else {
            onGround = false;
        }
        setPos(x(), newY);

        animCount++;
        if (animCount >= 10) {
            animCount = 0;
            animFrame = (animFrame + 1) % 3; // 0,1,2,3 循環

            QPixmap pm;
            if (movingRight) {
                if      (animFrame == 0) pm = frameR1;
                else if (animFrame == 1) pm = frameR2;
            } else {
                if      (animFrame == 0) pm = frameL1;
                else if (animFrame == 1) pm = frameL2;
            }
            if (!pm.isNull()) setPixmap(pm);
        }

        break;
    }
    */
    }
}

void Enemy::toggleSpark() {
    if (enemyType != SPARKY) return;
    sparkActive = !sparkActive;
}

void Enemy::checkFireBall() {
    if (enemyType != HOT_HEAD || isBreathing || !scene()) return;

    for (auto *item : scene()->items()) {
        Kirby *kirby = dynamic_cast<Kirby*>(item);
        if (!kirby) continue;

        qreal dy = qAbs(kirby->y() - y());
        qreal dx = kirby->x() - x();

        if (dy < 60 && qAbs(dx) < 500) {
            bool kirbyIsRight = (dx > 0);
            if (kirbyIsRight == movingRight) {
                isBreathing = true;
                breathCount = 0;
                //emit fireBallLaunched(x(), y(), movingRight);
            }
        }
        break;
    }
}

void Enemy::shootFireBall() {
    if (enemyType != HOT_HEAD) return;
    isBreathing = true;
    breathCount = 0;
    //emit fireBallLaunched(x(), y(), movingRight);
}

