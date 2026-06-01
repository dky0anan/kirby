#include "Item.h"
#include <QPixmap>

Item::Item(ItemType type, qreal x, qreal y) : m_type(type) {
    QPixmap pix;

    // 根據道具種類載入對應的圖片
    if (type == Tomato) {
        pix = QPixmap(":/Image/Image/item/Maxim Tomato.png");   // 請替換為正確的蘋果路徑
    } else if (type == OneUp) {
        pix = QPixmap(":/Image/Image/item/1UP.png");     // 請替換為正確的加命圖路徑
    }

    // 統一縮放大小
    if (!pix.isNull()) {
        pix = pix.scaled(60, 60, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    }

    setPixmap(pix);
    setPos(x, y);
}
