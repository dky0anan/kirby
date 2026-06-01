#ifndef BULLET_H
#define BULLET_H
#include <QGraphicsRectItem>
#include <QGraphicsPixmapItem>
#include <QObject>

class Bullet: public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public:
    Bullet(bool faceRight);

public slots:
    void move();

private:
    QPixmap attackStarR;
    QPixmap attackStarL;
    int bulletTimes = 0;
    bool isGoingRight;
};

#endif // BULLET_H
