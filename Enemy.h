#ifndef ENEMY_H
#define ENEMY_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>

enum EnemyType { WADDLE_DEE, GORDO, HOT_HEAD, SPARKY };

class Enemy : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    explicit Enemy(EnemyType type, qreal startX, qreal startY, qreal patrolLeft = 0, qreal patrolRight = 200);
    ~Enemy() override;

    EnemyType getType()       const { return enemyType; }
    bool canBeInhaled()       const { return enemyType != GORDO; }
    bool isInvincible()       const { return enemyType == GORDO; }
    bool isSparkActive()      const { return sparkActive; }

public slots:
    void move();
    void toggleSpark();
    void shootFireBall();
    void checkFireBall();

signals:
    void fireBallLaunched(qreal x, qreal y, bool goRight);

private:
    EnemyType enemyType;

    qreal patrolL, patrolR;
    qreal groundY;
    bool  movingRight = true;

    // Gordo
    int gordoPhase = 0;

    // Sparky
    qreal vy        = 0;
    bool  onGround  = true;
    bool  sparkActive = false;
    int   sparkCount  = 0;      // 放電持續計數
    int   jumpCount   = 0;      // 跳躍週期計數
    int   moveDir     = 1;      // 1=右, -1=左

    // Hot Head
    bool isBreathing = false;
    int  breathCount = 0;

    // 動畫
    int animFrame = 0;
    int animCount = 0;

    QPixmap frameR1, frameR2, frameL1, frameL2;
    QPixmap frameA_R, frameA_L;
    QPixmap frame1, frame2;
    QPixmap sparkFrame1, sparkFrame2;

    void loadPixmaps();
    void setupTimers();

    QTimer *moveTimer        = nullptr;
    QTimer *sparkToggleTimer = nullptr;
};

#endif // ENEMY_H
