#include "Block.h"

Block::Block(int w, int h, bool isOneWay, QGraphicsItem *parent): QGraphicsPixmapItem(parent), m_isOneWay(isOneWay) {
    QPixmap pm(w, h);
    pm.fill(Qt::transparent);
    setPixmap(pm);
    setShapeMode(QGraphicsPixmapItem::BoundingRectShape);

    // 如果是單向平台，我們可以給他一個特別的 data 標籤以防萬一
    setData(0, isOneWay ? "oneway_floor" : "floor");
}

bool Block::getIsOneWay() const {
    return m_isOneWay;
}
