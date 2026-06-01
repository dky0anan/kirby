#ifndef STAGEONE_H
#define STAGEONE_H

#include "StageBase.h"

class StageOne : public StageBase {
    Q_OBJECT
public:
    static const int STAGE_WIDTH = StageBase::VIEW_WIDTH * 3;
    static const int STAGE_HEIGHT = StageBase::VIEW_HEIGHT;

    StageOne(QObject *parent = nullptr);

protected:
    void initMap() override; // 覆寫並實作第一關地圖
};

#endif // STAGEONE_H
