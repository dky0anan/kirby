#ifndef BLOCK_H
#define BLOCK_H

#pragma once
#include <QGraphicsPixmapItem>

class Block : public QGraphicsPixmapItem {
public:
    //Block(const QPixmap &pixmap, QGraphicsItem *parent = nullptr); // 原本的
    Block(int w, int h, bool isOneWay = false, QGraphicsItem *parent = nullptr);          // 新增：隱形矩形

    // 取得這塊 Block 是否為單向平台的函式
    bool getIsOneWay() const;

private:
    bool m_isOneWay;
};

#endif
