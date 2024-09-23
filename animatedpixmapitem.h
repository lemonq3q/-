#ifndef ANIMATEDPIXMAPITEM_H
#define ANIMATEDPIXMAPITEM_H

#include <QObject>
#include <QGraphicsPixmapItem>

class ChessScene;

class AnimatedPixmapItem : public QObject , public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    AnimatedPixmapItem(QObject *parent = nullptr);

public:
    void move(int endX, int endY, int duration);
    void startShow(int spath[64][2],int spathAmount);
    void moveStep();
    void stopShow();

signals:
    void signalStartPlace();
    void stepStart();
    void showFinish();
    void hasStop();

private slots:
    void moveSlot();

private:
    QTimer *timer;
    QTimer *intervalTimer;
    int endX;
    int endY;
    float rangeX;
    float rangeY;
    int havePaint;
    int amount;
    int path[64][2];
    int pathAmount;
    int nowAmount;
    int isAnimation;
    int isShow;
};

#endif // ANIMATEDPIXMAPITEM_H
