#include "StageTwo.h"
#include "Block.h"
#include "Item.h"
#include "Enemy.h"
#include <QGraphicsPixmapItem>
#include <QBrush>

StageTwo::StageTwo(QObject *parent)
    : StageBase(STAGE_WIDTH, STAGE_HEIGHT, parent)
{
    initMap();       // 1. 鋪設地形
    initStageCore(); // 2. 同樣一鍵啟動核心物理與卡比

    Item *tomato = new Item(Item::Tomato, 2500, 850);
    addItem(tomato);
    Item *oneUp = new Item(Item::OneUp, 4550, 240);
    addItem(oneUp);
}

void StageTwo::initMap() {
    int currentX = 0;

    // 1. 設定第二關專屬的新背景
    QGraphicsPixmapItem *singleBG = new QGraphicsPixmapItem();
    singleBG->setPixmap(QPixmap(":/Image/Image/bg/bg2(2).png")); // 第二關新背景路徑
    singleBG->setPixmap(singleBG->pixmap().scaled(STAGE_WIDTH, singleBG->pixmap().height() * STAGE_WIDTH / singleBG->pixmap().width(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    singleBG->setPos(0, 0);
    singleBG->setZValue(-100);
    addItem(singleBG);

    // 2. 地板
    int GroundLength0 = 2500; // 假設你想要的地板總長度

    // 準備圖片與筆刷
    QPixmap floorPix(":/Image/Image/bg/Stage2(1).png");
    QBrush floorBrush(floorPix); // 把圖片變成筆刷

    // 建立一個指定長寬的矩形，並塗上剛剛的圖片筆刷
    QGraphicsRectItem *floor0 = new QGraphicsRectItem(0, 0, GroundLength0, floorPix.height());
    floor0 ->setBrush(floorBrush);
    floor0 ->setPen(Qt::NoPen); // 去除矩形預設的黑邊框
    floor0 ->setPos(currentX, STAGE_HEIGHT - floorPix.height());
    floor0 ->setZValue(-50);
    addItem(floor0);
    // 一樣鋪設一塊巨大的隱形 Block 負責物理碰撞
    Block *g0 = new Block(GroundLength0, 230);
    g0->setPos(currentX, 850);
    addItem(g0);
    currentX += GroundLength0;
    int hole1_X = currentX;

    currentX += 750; // HoleLength = 750

    int GroundLength1 = 1500;
    QGraphicsRectItem *floor1 = new QGraphicsRectItem(0, 0, GroundLength1, floorPix.height());
    floor1 ->setBrush(floorBrush);
    floor1 ->setPen(Qt::NoPen); // 去除矩形預設的黑邊框
    floor1 ->setPos(currentX, STAGE_HEIGHT - floorPix.height());
    floor1 ->setZValue(-50);
    addItem(floor1);
    Block *g1 = new Block(GroundLength1, 230);
    g1->setPos(currentX, 850);
    addItem(g1);
    currentX += GroundLength1;

    currentX += 300; // HoleLength = 300

    int GroundLength2 = 250;
    // 建立一個指定長寬的矩形，並塗上剛剛的圖片筆刷
    QGraphicsRectItem *floor2 = new QGraphicsRectItem(0, 0, GroundLength2, floorPix.height());
    floor2 ->setBrush(floorBrush);
    floor2 ->setPen(Qt::NoPen); // 去除矩形預設的黑邊框
    floor2 ->setPos(currentX, 950);
    floor2 ->setZValue(-50);
    addItem(floor2);
    // 一樣鋪設一塊巨大的隱形 Block 負責物理碰撞
    Block *g2 = new Block(GroundLength2, 80);
    g2->setPos(currentX, 1000);
    addItem(g2);
    currentX += GroundLength2;

    int GroundLength3 = STAGE_WIDTH - currentX;
    // 建立一個指定長寬的矩形，並塗上剛剛的圖片筆刷
    QGraphicsRectItem *floor3 = new QGraphicsRectItem(0, 0, GroundLength3, floorPix.height());
    floor3 ->setBrush(floorBrush);
    floor3 ->setPen(Qt::NoPen); // 去除矩形預設的黑邊框
    floor3 ->setPos(currentX, STAGE_HEIGHT - floorPix.height());
    floor3 ->setZValue(-50);
    addItem(floor3);
    // 一樣鋪設一塊巨大的隱形 Block 負責物理碰撞
    Block *g3 = new Block(GroundLength3, 230);
    g3->setPos(currentX, 850);
    addItem(g3);

    // 4. 放置單向空中平台
    QPixmap platformPix(":/Image/Image/item/floor.png");
    QBrush platformBrush(platformPix); // 把圖片變成筆刷

    for (int i = 0; i < 3; i++) {
        QGraphicsPixmapItem *p0 = new QGraphicsPixmapItem(platformPix);
        p0->setPos(500 + i * platformPix.width(), 500);
        p0->setZValue(-10);
        addItem(p0);
    }
    Block *p0Block = new Block(platformPix.width() * 3, platformPix.height(), true);
    p0Block->setPos(500, 500);
    addItem(p0Block);

    for (int i = 0; i < 3; i++) {
        QGraphicsPixmapItem *p1 = new QGraphicsPixmapItem(platformPix);
        p1->setPos(900 + i * platformPix.width(), 300);
        p1->setZValue(-10);
        addItem(p1);
    }
    Block *p1Block = new Block(platformPix.width() * 3, platformPix.height(), true);
    p1Block->setPos(900, 300);
    addItem(p1Block);

    for (int i = 0; i < 2; i++) {
        QGraphicsPixmapItem *p2 = new QGraphicsPixmapItem(platformPix);
        p2->setPos(4500 + i * platformPix.width(), 300);
        p2->setZValue(-10);
        addItem(p2);
    }
    Block *p2Block = new Block(platformPix.width() * 2, platformPix.height(), true);
    p2Block->setPos(4500, 300);
    addItem(p2Block);

    for (int i = 0; i < 4; i++) {
        QGraphicsPixmapItem *p3 = new QGraphicsPixmapItem(platformPix);
        p3->setPos(7300 + i * platformPix.width(), 450);
        p3->setZValue(-10);
        addItem(p3);
    }
    Block *p3Block = new Block(platformPix.width() * 3, platformPix.height(), true);
    p3Block->setPos(7300, 450);
    addItem(p3Block);

    // 5. 放置小方塊
    QPixmap brickPix(":/Image/Image/item/brick.png");

    int bw = brickPix.width();
    int bh = brickPix.height();
    int startX = 2000;  // 三角形左下角的 X 位置
    int startY = STAGE_HEIGHT - floorPix.height();   // 三角形左下角的 Y 位置（配合你的地板高度）

    // 第幾排從下到上，數量分別是 3, 2, 1
    int counts[] = {3, 2, 1};
    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < counts[row]; col++) {
            // 圖片
            QGraphicsPixmapItem *b0 = new QGraphicsPixmapItem(brickPix);
            b0->setPos(startX + (counts[0] - counts[row]) * bw + col * bw, startY - row * bh);
            b0->setZValue(-10);
            addItem(b0);
            // 碰撞 Block
            Block *b0Block = new Block(bw, bh);
            b0Block->setPos(startX + (counts[0] - counts[row]) * bw + col * bw, startY - row * bh);
            addItem(b0Block);
        }
    }

    QGraphicsPixmapItem *b1 = new QGraphicsPixmapItem(brickPix);
    b1->setPos(hole1_X + 150, 950);
    b1->setZValue(-10);
    addItem(b1);
    Block *b1Block = new Block(brickPix.width(), brickPix.height());
    b1Block->setPos(hole1_X + 150, 950);
    addItem(b1Block);

    QGraphicsPixmapItem *b2 = new QGraphicsPixmapItem(brickPix);
    b2->setPos(hole1_X + 450, 950);
    b2->setZValue(-10);
    addItem(b2);
    Block *b2Block = new Block(brickPix.width(), brickPix.height());
    b2Block->setPos(hole1_X + 450, 950);
    addItem(b2Block);

    // 6. 通往通關畫面
    QPixmap doorPix(":/Image/Image/item/goal_door.png");
    QGraphicsPixmapItem *door = new QGraphicsPixmapItem(doorPix);
    door->setPos(p3Block->x() + 150, p3Block->y() - doorPix.height());
    door->setZValue(-1);
    door->setData(0, "door");
    addItem(door);

    // 敵人
    Enemy *e1 = new Enemy(SPARKY, 1000, 910, 400, 400);
    addItem(e1);

    Enemy *e2 = new Enemy(HOT_HEAD, 2000, 910, 900, 1500);
    addItem(e2);
}
