#include "animatedpixmapitem.h"
#include <QObject>
#include <QTimer>

AnimatedPixmapItem::AnimatedPixmapItem(QObject *parent)
    : QObject(parent){
    timer = new QTimer(this);
    timer->setInterval(8);  //一副画面的间隔为8ms
    intervalTimer = new QTimer(this);
    intervalTimer->setInterval(125);   //棋子的移动间隔为125ms
    intervalTimer->setSingleShot(true); //每次只触发一次
    isAnimation = 0;
    isShow = 0;
}

void AnimatedPixmapItem::move(int endX, int endY, int duration)
{
    isShow = 1; //代表可以播放
    this->amount = 120*(duration/1000.0);  //计算画面数量
    this->endX = endX;   //设置终点坐标
    this->endY = endY;
    this->rangeX = (endX-this->pos().x())/float(amount);   //设置移动间隔
    this->rangeY = (endY-this->pos().y())/float(amount);
    this->havePaint = 0;
    connect(timer,&QTimer::timeout,this,&AnimatedPixmapItem::moveSlot);
    timer->start();
}

void AnimatedPixmapItem::startShow(int spath[64][2], int spathAmount)
{
    isShow = 1;  //代表可以播放
    pathAmount = spathAmount;   //存储路径与路径数量
    for(int i=0;i<=spathAmount;i++){
        path[i][0] = spath[i][0]*100+10;  //把路径转化为实际要走的坐标位置
        path[i][1] = spath[i][1]*100+12;
    }
    nowAmount = 0;
    isAnimation = 1; //代表现在是演示路径的动画
    moveStep();
}

void AnimatedPixmapItem::moveStep()
{
    disconnect(intervalTimer,&QTimer::timeout,this,&AnimatedPixmapItem::moveStep);  //关闭计时器以及连接节省资源
    intervalTimer->stop();
    amount = 30;  //画面数量
    if(isShow==0){
        emit hasStop();
        isAnimation = 0;  //修改回默认值
        return;
    }
    if(nowAmount<=pathAmount){  //判断还有没有路要播放
        endX = path[nowAmount][0];
        endY = path[nowAmount][1];
        rangeX = (endX-this->pos().x())/float(amount);   //设置移动间隔
        rangeY = (endY-this->pos().y())/float(amount);
        havePaint = 0;
        connect(timer,&QTimer::timeout,this,&AnimatedPixmapItem::moveSlot);
        timer->start();
    }
    else{
        // emit showFinish();  //代表全部路径已经播放完毕
        isAnimation = 0; //修改回默认值
        isShow = 0;//修改回默认值
    }
}

void AnimatedPixmapItem::stopShow()
{
    if(isShow==0){
        emit hasStop();
    }
    else{
        isShow = 0;
    }
}

void AnimatedPixmapItem::moveSlot()
{
    this->setPos(this->pos().x()+rangeX,this->pos().y()+rangeY);
    havePaint++;
    if(havePaint==amount){   //画面绘制数量够了之后
        timer->stop();
        disconnect(timer,&QTimer::timeout,this,&AnimatedPixmapItem::moveSlot);
        this->setPos(endX,endY);  //位置矫正
        if(isAnimation==0){
            emit signalStartPlace();   //发送这一步动画播放完毕的信号
            if(isShow==0){
                emit hasStop();
            }
            isShow = 0; //修改回默认值
        }
        else{
            emit stepStart();
            connect(intervalTimer,&QTimer::timeout,this,&AnimatedPixmapItem::moveStep);  //建立计时结束播放下一个动画的信号
            intervalTimer->start();
            nowAmount++;
        }
    }
}


