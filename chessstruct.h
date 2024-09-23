#ifndef CHESSSTRUCT_H
#define CHESSSTRUCT_H

#include <QObject>

class QTimer;

class ChessStruct : public QObject
{
    Q_OBJECT
public:
    ChessStruct();

public:
    void reSet();
    bool isVisited(int x,int y);
    void setVisited(int x,int y);
    bool findPath(int startx,int starty,int sourcex,int sourcey);
    bool findNext(int startx,int starty,int deep);
    int findOutAmount(int x,int y);
    bool judgeDangerous(int x,int y);
    void generateDangerous(int x,int y);
    void deleteDangerous();

public:
    int stepAmount;
    int path[64][2];
    int circuitPath[64][2] = {{0,0},{2,1},{4,0},{5,2},{7,1},{5,0},{3,1},{2,3},{3,5},{4,3},{2,4},{0,5},{1,7},{3,6},{4,4},{3,2},{2,0},{0,1},{1,3},{2,5},
    {4,6},{3,4},{5,5},{6,7},{7,5},{6,3},{4,2},{5,4},{3,3},{4,1},{6,0},{7,2},{6,4},{7,6},{5,7},{4,5},{6,6},{4,7},{2,6},{0,7},{1,5},{2,7},{0,6},{1,4},{0,2},
    {1,0},{2,2},{0,3},{1,1},{3,0},{5,1},{7,0},{6,2},{7,4},{5,3},{6,1},{7,3},{6,5},{7,7},{5,6},{3,7},{1,6},{0,4},{1,2}};
private:
    int visited[8][8];
    int findPathVisited[8][8];
    int dirX[8];
    int dirY[8];
    int dangerousPoint[64][2];
    int dangerAmount;
    int visitedAmount;
    int startX;
    int startY;
    long long timeCount;
};

#endif // CHESSSTRUCT_H
