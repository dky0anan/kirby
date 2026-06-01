#include "Bullet.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QList>
#include <QDebug>
#include "Enemy.h"

Bullet::Bullet(bool faceRight) {
    attackStarR = QPixmap(":/Image/Image/Kirby_normal/kirby_attack_star_R(1).png");
    attackStarL = QPixmap(":/Image/Image/Kirby_normal/kirby_attack_star_L(1).png");

    isGoingRight = faceRight;
    bulletTimes = 0;

    if (isGoingRight) {
        setPixmap(attackStarR);
    } else {
        setPixmap(attackStarL);
    }

    int newWidth = pixmap().width() / 2;
    int newHeight = pixmap().height() / 2;
    setPixmap(pixmap().scaled(newWidth, newHeight, Qt::KeepAspectRatio));

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));
    timer->start(50);
}

void Bullet::move() {
    QList<QGraphicsItem *> colliding_items = collidingItems();
    for (int i = 0, n = colliding_items.size(); i < n; i++) {
        Enemy *e = dynamic_cast<Enemy*>(colliding_items[i]);
        if (e != nullptr) {
            if (e->isInvincible()) {
                // Gordo：只有子彈消失
                scene()->removeItem(this);
                this->deleteLater();
            } else {
                // 一般敵人：兩個都消失
                scene()->removeItem(colliding_items[i]);
                scene()->removeItem(this);
                delete colliding_items[i];
                this->deleteLater();
            }
            return;
        }
    }

    if (isGoingRight) {
        setPos(x() + 10, y());
    } else {
        setPos(x() - 10, y());
    }

    bulletTimes++;

    if (bulletTimes >= 4) {
        scene()->removeItem(this);
        this->deleteLater();
    }
}
