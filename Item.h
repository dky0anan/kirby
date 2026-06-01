#ifndef ITEM_H
#define ITEM_H

#include <QGraphicsPixmapItem>

class Item : public QGraphicsPixmapItem {
public:
    enum ItemType { Tomato, OneUp };

    // 建構子現在需要傳入「道具種類」與「座標」
    Item(ItemType type, qreal x, qreal y);

    // 取得道具種類，讓碰撞偵測時知道卡比吃到什麼
    ItemType getType() const { return m_type; }

private:
    ItemType m_type;
};

#endif // ITEM_H
