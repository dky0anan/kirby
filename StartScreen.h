#ifndef STARTSCREEN_H
#define STARTSCREEN_H

#pragma once
#include <QGraphicsScene>

class StartScreen : public QGraphicsScene {
    Q_OBJECT
public:
    StartScreen();

signals:
    void pressEnter();

protected:
    void keyPressEvent(QKeyEvent *event) override;
};

#endif // STARTSCREEN_H
