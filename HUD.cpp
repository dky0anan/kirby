#include "HUD.h"
#include <QPainter>

HUD::HUD(Kirby *kirby) : kirby(kirby) {
    life = QPixmap(":/Image/Image/item/life.png"); // .scaled(50, 50, Qt::KeepAspectRatio)
    hp1 = QPixmap(":/Image/Image/item/HP_1.png"); // .scaled(40, 50, Qt::KeepAspectRatio)
    hp0 = QPixmap(":/Image/Image/item/HP_0.png");

    // 連接信號，HP 或 lives 變動時重繪
    connect(kirby, &Kirby::hpChanged,    this, &HUD::update);
    connect(kirby, &Kirby::livesChanged, this, &HUD::update);

    setZValue(100);  // 確保在最上層
}

QRectF HUD::boundingRect() const {
    return QRectF(0, 0, 1620, 150);
}

void HUD::paint(QPainter *painter, const QStyleOptionGraphicsItem*, QWidget*) {
    int blank = 450;
    // 卡比頭像 + lives 數字
    painter->drawPixmap(blank, 25, life);
    painter->setPen(Qt::red);
    painter->setFont(QFont("Arial", 32, QFont::Bold));
    //painter->drawText(blank + life.width() + 15, 25, QString("x%1").arg(kirby->getLives()));
    painter->drawText(blank + life.width() + 15, 5 + life.height(), QString("x%1").arg(kirby->getLives()));

    // HP 格：滿的顯示 hp1，空的顯示 hp0
    int maxHp = 3;
    blank += 150;
    for (int i = 0; i < maxHp; i++) {
        if (i < kirby->getHp()) {
            painter->drawPixmap(200 + i * 50 + blank, 25, hp1);   // 還有血
        } else {
            painter->drawPixmap(200 + i * 50 + blank, 65, hp0);  // 已扣血
        }
        blank += 50;
    }
}

void HUD::update() {
    prepareGeometryChange();
    QGraphicsItem::update();
}
