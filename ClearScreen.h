#ifndef CLEARSCREEN_H
#define CLEARSCREEN_H

#pragma once
#include <QGraphicsScene>

class ClearScreen : public QGraphicsScene {
    Q_OBJECT
public:
    ClearScreen();

signals:
    void pressEnter();

protected:
    void keyPressEvent(QKeyEvent *event) override;
};

#endif // CLEARSCREEN_H
