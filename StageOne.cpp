#include "StageOne.h"
#include "Block.h"
#include "Enemy.h"
#include <QGraphicsPixmapItem>

StageOne::StageOne(QObject *parent)
    : StageBase(STAGE_WIDTH, STAGE_HEIGHT, parent)
{
    initMap();       // 1. 鋪設地形
    initStageCore(); // 2. 初始化核心物件與計時器
}

void StageOne::initMap() {
    int currentX = 0;

    // ----- 鋪設背景與地板 (這部分完整保留你原本的程式碼) -----
    QGraphicsPixmapItem *singleBG = new QGraphicsPixmapItem();
    singleBG->setPixmap(QPixmap(":/Image/Image/bg/bg.png"));
    singleBG->setPixmap(singleBG->pixmap().scaled(STAGE_WIDTH, singleBG->pixmap().height() * STAGE_WIDTH / singleBG->pixmap().width(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    singleBG->setPos(0, 0);
    singleBG->setZValue(-100);
    addItem(singleBG);

    // ── p0、p1、p2、p3 的 Block 鋪設 ──
    // ── p0：平地 ──────────────────────────
    QPixmap p0 = QPixmap(":/Image/Image/bg/Stage1(1).png");
    QGraphicsPixmapItem *bg0 = new QGraphicsPixmapItem(p0);
    bg0->setPos(currentX, 1080 - p0.height());
    bg0->setZValue(-50);
    addItem(bg0);

    Block *p0_g = new Block(1111, 170);
    p0_g->setPos(currentX, 910);
    addItem(p0_g);
    currentX += p0.width();

    // ── p1：高台 + 左右平地 ───────────────
    QPixmap p1 = QPixmap(":/Image/Image/bg/Stage1(2).png");
    p1 = p1.scaled(p1.width()*1.35, p1.height()*1.35, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    QGraphicsPixmapItem *bg1 = new QGraphicsPixmapItem(p1);
    bg1->setPos(currentX, 1080 - p1.height());
    bg1->setZValue(-50);
    addItem(bg1);

    Block *p1_gL   = new Block( 110, 170); p1_gL->setPos(currentX,       910); addItem(p1_gL);
    Block *p1_plat = new Block(110, 250); p1_plat->setPos(currentX + 110, 830); addItem(p1_plat);
    Block *p1_gR   = new Block(783, 170); p1_gR->setPos(currentX + 220,  910); addItem(p1_gR);
    currentX += p1.width();

    // ── p2：左平地 + 右高台 ───────────────
    QPixmap p2 = QPixmap(":/Image/Image/bg/Stage1(3).png");
    p2 = p2.scaled(p2.width()*1.1, p2.height()*1.1, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    QGraphicsPixmapItem *bg2 = new QGraphicsPixmapItem(p2);
    bg2->setPos(currentX, 1080 - p2.height());
    bg2->setZValue(-50);
    addItem(bg2);

    Block *p2_gL   = new Block(330, 170); p2_gL->setPos(currentX,        910); addItem(p2_gL);
    Block *p2_plat = new Block(400, 240); p2_plat->setPos(currentX + 330, 840); addItem(p2_plat); // 330+420=750
    Block *p2_gR   = new Block(400, 170); p2_gR->setPos(currentX + 730,  910); addItem(p2_gR);
    currentX += p2.width();

    // ── p3：塔頂 + 中層 + 左右平地 ────────
    QPixmap p3 = QPixmap(":/Image/Image/bg/Stage1(4).png");
    p3 = p3.scaled(p3.width()*2.7, p3.height()*2.7, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    QGraphicsPixmapItem *bg3 = new QGraphicsPixmapItem(p3);
    bg3->setPos(currentX, 1080 - p3.height());
    bg3->setZValue(-50);
    addItem(bg3);

    Block *p3_gL  = new Block(270,  240); p3_gL->setPos(currentX,        840); addItem(p3_gL);
    Block *p3_top = new Block(80,  540); p3_top->setPos(currentX + 270,  540); addItem(p3_top); // 237+178=415
    Block *p3_mid = new Block(100,  395); p3_mid->setPos(currentX + 350,  685); addItem(p3_mid); // 416+91=507
    Block *p3_gR  = new Block(1740, 200); p3_gR->setPos(currentX + 450,   880); addItem(p3_gR);
    currentX += p3.width();

    // 地圖的最後放上門
    QPixmap doorPix(":/Image/Image/item/door.png");
    QGraphicsPixmapItem *door = new QGraphicsPixmapItem(doorPix);
    door->setPos(currentX - 1000, 850 - doorPix.height()); // 放在關卡末端高台或平地上
    door->setZValue(-10);
    door->setData(0, "door"); // 打上 door 標籤
    addItem(door);

    // 敵人
    Enemy *e1 = new Enemy(WADDLE_DEE, 1000, 910, 400, 600);
    addItem(e1);

    Enemy *e2 = new Enemy(GORDO, 2000, 910, 900, 1500);
    addItem(e2);

}
