#ifndef STAGETWO_H
#define STAGETWO_H

#include "StageBase.h"

class StageTwo : public StageBase {
    Q_OBJECT
public:
    // 第二關將長度加長，例如設為 8500 像素
    static const int STAGE_WIDTH = StageBase::VIEW_WIDTH * 5;
    static const int STAGE_HEIGHT = StageBase::VIEW_HEIGHT;

    StageTwo(QObject *parent = nullptr);

protected:
    void initMap() override; // 實作第二關專屬地形
};

#endif // STAGETWO_H
