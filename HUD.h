#ifndef HUD_H
#define HUD_H

#pragma once
#include <QGraphicsItem>
#include <QObject>
#include <QPixmap>
#include "Kirby.h"

class HUD : public QObject, public QGraphicsItem {
    Q_OBJECT
public:
    explicit HUD(Kirby *kirby);
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem*, QWidget*) override;

public slots:
    void update();

private:
    Kirby *kirby;
    QPixmap life;  // 卡比頭像
    QPixmap hp1;    // HP 格圖片
    QPixmap hp0;
};

#endif // HUD_H
