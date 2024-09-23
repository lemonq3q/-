#ifndef CHESSSCENE_H
#define CHESSSCENE_H

#include <QGraphicsScene>

class ChessStruct;
class AnimatedPixmapItem;
class MDiaolog;

class ChessScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit ChessScene(QObject *parent = nullptr);

public:
    QGraphicsRectItem ***chessPaint(QGraphicsScene *scene);
    static int transPos(int pos);
    void judgeFinish();
    void reSet();
    void tmpShowPlace();
    void tmpShowReset();
    bool tips();
    void showPath();
    void stepStartHandler();
    void mainwindowReset();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);

signals:
    void StringReady();
    void textClear();

public:
    QString pathInformation;

private:
    QGraphicsRectItem ***plaids;
    AnimatedPixmapItem *actShow;
    AnimatedPixmapItem *tmpShow;
    AnimatedPixmapItem *tmpShow1;
    AnimatedPixmapItem *tmpShow2;
    AnimatedPixmapItem *tmpShow3;
    AnimatedPixmapItem *tmpShow4;
    AnimatedPixmapItem *tmpShow5;
    AnimatedPixmapItem *tmpShow6;
    AnimatedPixmapItem *tmpShow7;
    AnimatedPixmapItem *tmpShow8;
    AnimatedPixmapItem *redFlag;
    ChessStruct *own;
    MDiaolog *succeedDialog;
    MDiaolog *defeatDiaolog;
    bool isPlaced;
    int actX;
    int actY;
    int tmpX;
    int tmpY;
    int sourceX;
    int sourceY;
    int isFindPath;
};

#endif // CHESSSCENE_H
