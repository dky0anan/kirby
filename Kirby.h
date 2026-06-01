#ifndef KIRBY_H
#define KIRBY_H
#include <QGraphicsPixmapItem>
#include <QKeyEvent>
#include <QObject>
#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QTimer>
// #include "Enemy.h"

class Enemy;

class Kirby: public QObject, public QGraphicsPixmapItem{
    Q_OBJECT

public:
    Kirby();

    // 定義狀態機
    enum State {
        Standing, Running, Crouching, Jumping, Flying,
        FastFalling, Inhaling, Fulling, Mouthful, Swallowing,
        Spitting, AbilityAttack, Attacking, Invincible, Dead
    };
    enum Direction { Left, Right };
    enum Ability   { None, Fire, Spark };

    void keyPressEvent(QKeyEvent * event)override;
    void keyReleaseEvent(QKeyEvent * event)override;
    void processMovement();

    bool hasEnemyInFront(int distance);
    Enemy* getEnemyInFront(int distance);


    void landOnGround();
    void setFalling();
    bool isBlockedHorizontally(int dx);
    void setPixmapWithBottomAnchor(const QPixmap &newPixmap);
    bool isPressingUp();

    int getHp()    { return hp; }
    int getLives() { return lives; }
    State getCurrentState() const { return currentState; }
    //bool isInvincible() { return currentState == Invincible; }
    bool isInvincible() { return invincible; }

    void takeDamage();      // 被攻擊扣 1 HP
    void loseLife();        // 扣 1 life，重置位置
    void addLife();         // 1UP
    void healFull();        // Maxim Tomato 回滿 HP

public slots:
    void advanceAnimation();
    // void spawn();
    void flyDown();
    void inhalePull();
    void endInvincible();
    //void takeDamage();

signals:
    void hpChanged();  //void hpChanged(int hp, int lives);     // HP 變動時通知 HUD 更新
    void livesChanged();    // lives 變動時通知 HUD 更新
    void abilityChanged(Ability a);
    void gameOver();            // lives = 0，通知 Game Over

private:
    QPixmap stopPix() const;
    QPixmap downPix() const;
    QPixmap fly1Pix() const;
    QPixmap fly2Pix() const;
    QPixmap runPix(int frame) const;

    // ────────── 動畫計數 ──────────
    int runFrame;
    int flyFrame;
    int pressCount = 0;
    // ────────── Timer ──────────
    QTimer *animTimer   = nullptr;
    QTimer *downTimer   = nullptr;
    QTimer *inhaleTimer = nullptr;
    QTimer *invincibleTimer = nullptr; //QTimer *invTimer    = nullptr;
    QTimer *blinkTimer  = nullptr;
    // ────────── 狀態 ──────────
    State     currentState   = Standing;
    Direction currentDir     = Right;
    Ability   currentAbility = None;
    Ability   pendingAbility = None;
    // ────────── 按鍵 ──────────
    bool pressUp = false;   // 記錄按鍵是否被按住
    bool pressRight = false;
    bool pressLeft = false;
    bool pressDown = false;

    int hp    = 3;
    int lives = 3;
    bool invincible = false;
    // ────────── 物理 ──────────
    qreal vy       = 0;
    bool  onGround = true;
    static constexpr qreal GROUND_Y = 300.0;
    static constexpr qreal GRAVITY  = 1.5;
    static constexpr qreal JUMP_VY  = -18.0;

    void loadPixmaps();

    //bool hasEnemyInFront(int distance);
    //Enemy* getEnemyInFront(int distance);

    //void setStanding();
    void startInhale();
    void stopInhale();
    void swallowEnemy(Enemy *e);
    void spitStar();
    void useAbility();
    void dropAbility();

    QPixmap runR1, runR2, runR3, runR4, stopR;
    QPixmap runL1, runL2, runL3, runL4, stopL;
    QPixmap downL, downR;
    QPixmap jump1, jump2, jump3;
    QPixmap flyR1, flyR2, flyL1, flyL2;
    QPixmap attackR, attackL;
    QPixmap mouthR, mouthL;
    // ────────── Fire 貼圖 ──────────
    QPixmap fRunR[3], fRunL[3];
    QPixmap fStopR, fStopL;
    QPixmap fDownR, fDownL;
    QPixmap fFlyR[2], fFlyL[2];
    QPixmap fAtkR,  fAtkL;
    QPixmap fFireR[3], fFireL[3];
    // ────────── Spark 貼圖 ──────────
    QPixmap sRunR[2], sRunL[2];
    QPixmap sStopR, sStopL;
    QPixmap sDownR, sDownL;
    QPixmap sFlyR[2], sFlyL[2];
    QPixmap sAtk[3];


};

#endif
