#include "chessscene.h"
#include "chessstruct.h"
#include "animatedpixmapitem.h"
#include "mdiaolog.h"
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QtDebug>
#include <cmath>

ChessScene::ChessScene(QObject *parent)
    : QGraphicsScene{parent}
{
    this->setSceneRect(0,0,800,800);
    plaids = chessPaint(this);  //绘制棋盘
    // plaids[0][1]->setOpacity(0.5);   //测试数组存的对不对

    actShow = new AnimatedPixmapItem(this);  //实体棋子item
    actShow->setPixmap(QPixmap(":/img/horse.png"));

    // qDebug() << "size:" << actShow->pixmap().size();  获取棋子的大小

    tmpShow = new AnimatedPixmapItem(this);  //虚拟棋子item
    tmpShow->setPixmap(QPixmap(":/img/horse.png"));
    tmpShow->setOpacity(0.5);
    tmpShow->setPos(-100,-100);   //隐藏起来
    this->addItem(tmpShow);

    redFlag = new AnimatedPixmapItem(this);  //起点的棋子
    redFlag->setPixmap(QPixmap(":/img/flag.png"));
    redFlag->setPos(-100,-100);
    this->addItem(redFlag);

    tmpShow1 = new AnimatedPixmapItem(this);       //指示棋子初始化
    tmpShow1->setPixmap(QPixmap(":/img/horse.png"));
    tmpShow1->setOpacity(0.5);
    tmpShow1->setPos(-100,-100);
    this->addItem(tmpShow1);
    tmpShow2 = new AnimatedPixmapItem(this);
    tmpShow2->setPixmap(QPixmap(":/img/horse.png"));
    tmpShow2->setOpacity(0.5);
    tmpShow2->setPos(-100,-100);
    this->addItem(tmpShow2);
    tmpShow3 = new AnimatedPixmapItem(this);
    tmpShow3->setPixmap(QPixmap(":/img/horse.png"));
    tmpShow3->setOpacity(0.5);
    tmpShow3->setPos(-100,-100);
    this->addItem(tmpShow3);
    tmpShow4 = new AnimatedPixmapItem(this);
    tmpShow4->setPixmap(QPixmap(":/img/horse.png"));
    tmpShow4->setOpacity(0.5);
    tmpShow4->setPos(-100,-100);
    this->addItem(tmpShow4);
    tmpShow5 = new AnimatedPixmapItem(this);
    tmpShow5->setPixmap(QPixmap(":/img/horse.png"));
    tmpShow5->setOpacity(0.5);
    tmpShow5->setPos(-100,-100);
    this->addItem(tmpShow5);
    tmpShow6 = new AnimatedPixmapItem(this);
    tmpShow6->setPixmap(QPixmap(":/img/horse.png"));
    tmpShow6->setOpacity(0.5);
    tmpShow6->setPos(-100,-100);
    this->addItem(tmpShow6);
    tmpShow7 = new AnimatedPixmapItem(this);
    tmpShow7->setPixmap(QPixmap(":/img/horse.png"));
    tmpShow7->setOpacity(0.5);
    tmpShow7->setPos(-100,-100);
    this->addItem(tmpShow7);
    tmpShow8 = new AnimatedPixmapItem(this);
    tmpShow8->setPixmap(QPixmap(":/img/horse.png"));
    tmpShow8->setOpacity(0.5);
    tmpShow8->setPos(-100,-100);
    this->addItem(tmpShow8);

    own = new ChessStruct;           //初始化结构体
    isPlaced = false;

    succeedDialog = new MDiaolog("游戏成功","再来一次");
    defeatDiaolog = new MDiaolog("游戏失败","再来一次");

    connect(actShow,&AnimatedPixmapItem::signalStartPlace,this,&ChessScene::tmpShowPlace); //建立动画播放完毕信号连接
    connect(succeedDialog,&MDiaolog::diaologClose,this,&ChessScene::reSet);   //建立窗口关闭完重置场景的信号连接
    connect(defeatDiaolog,&MDiaolog::diaologClose,this,&ChessScene::reSet);
    connect(actShow,&AnimatedPixmapItem::stepStart,this,&ChessScene::stepStartHandler);
    connect(actShow,&AnimatedPixmapItem::hasStop,this,&ChessScene::reSet);
}

QGraphicsRectItem ***ChessScene::chessPaint(QGraphicsScene *scene)
{
    QColor white(231,210,172);   //白格子颜色
    QColor black(146,64,5);      //黑格子颜色
    QGraphicsRectItem ***itemss = new QGraphicsRectItem**[8];  //生成二维指针数组
    for(int i=1;i<=8;i++){      //for循环绘制棋盘
        QGraphicsRectItem **items = new QGraphicsRectItem*[8];
        for(int j=1;j<=8;j++){
            if(i%2!=0){
                if(j%2!=0){
                    items[j-1] = scene->addRect(QRectF((i-1)*100,(j-1)*100,100,100),QPen(QColor(0,0,0,0)),QBrush(white));
                }
                else{
                    items[j-1] = scene->addRect(QRectF((i-1)*100,(j-1)*100,100,100),QPen(QColor(0,0,0,0)),QBrush(black));
                }
            }
            else{
                if(j%2!=0){
                    items[j-1] = scene->addRect(QRectF((i-1)*100,(j-1)*100,100,100),QPen(QColor(0,0,0,0)),QBrush(black));
                }
                else{
                    items[j-1] = scene->addRect(QRectF((i-1)*100,(j-1)*100,100,100),QPen(QColor(0,0,0,0)),QBrush(white));
                }
            }
        }
        itemss[i-1] = items;
    }
    return itemss;
}

int ChessScene::transPos(int pos)
{
    int x = (pos + 100)/100;
    if(x!=9){
        return x-1;
    }
    else{
        return 7;
    }
}

void ChessScene::judgeFinish()
{
    if( own->isVisited(actX+1,actY+2)&& own->isVisited(actX+2,actY+1) && own->isVisited(actX+1,actY-2) && own->isVisited(actX+2,actY-1)
        && own->isVisited(actX-1,actY+2) && own->isVisited(actX-2,actY+1) && own->isVisited(actX-1,actY-2) &&  own->isVisited(actX-2,actY-1) ){
        int flag = 0;
        for(int i=0;i<8;i++){
            for(int j=0;j<8;j++){
                if(!own->isVisited(i,j)){
                    flag = 1;
                    break;
                }
            }
            if(flag==1){
                break;
            }
        }
        if(flag==1){
            defeatDiaolog->exec();
        }
        else{
            succeedDialog->exec();
        }
    }
}

void ChessScene::reSet()
{
    emit textClear();
    tmpShow->setPos(-100,-100);   //重新设置指示的棋子
    redFlag->setPos(-100,-100);  //重新设置红旗位置
    this->addItem(tmpShow);
    this->removeItem(actShow);   //删除当前棋子
    own->reSet();    //重设棋盘数据结构
    isPlaced = false; //设置为未放置棋子
    isFindPath = 0; //还为开始找路
    //重绘棋盘
    QColor white(231,210,172);   //白格子颜色
    QColor black(146,64,5);      //黑格子颜色
    for(int i=1;i<=8;i++){
        for(int j=1;j<=8;j++){
            if(i%2!=0){
                if(j%2!=0){
                    plaids[i-1][j-1]->setBrush(white);
                    plaids[i-1][j-1]->setPen(QColor(0,0,0,0));
                }
                else{
                    plaids[i-1][j-1]->setBrush(black);
                    plaids[i-1][j-1]->setPen(QColor(0,0,0,0));
                }
            }
            else{
                if(j%2!=0){
                    plaids[i-1][j-1]->setBrush(black);
                    plaids[i-1][j-1]->setPen(QColor(0,0,0,0));
                }
                else{
                    plaids[i-1][j-1]->setBrush(white);
                    plaids[i-1][j-1]->setPen(QColor(0,0,0,0));
                }
            }
        }
    }
    tmpShowReset();   //重设指示棋子
}

void ChessScene::tmpShowPlace()
{
    this->actX = this->tmpX;  //恢复鼠标操作
    this->actY = this->tmpY;
    plaids[actX][actY]->setBrush(QColor(105,105,105)); //代表该格子不能再走
    plaids[actX][actY]->setPen(QColor(169,169,169));
    if(!own->isVisited(actX+1,actY+2)){       //遍历所有可能走的节点，看看需不需要提示
        tmpShow1->setPos((actX+1)*100+10,(actY+2)*100+12);
    }else{
        tmpShow1->setPos(-100,-100);
    }
    if(!own->isVisited(actX+2,actY+1)){
        tmpShow2->setPos((actX+2)*100+10,(actY+1)*100+12);
    }else{
        tmpShow2->setPos(-100,-100);
    }
    if(!own->isVisited(actX+1,actY-2)){
        tmpShow3->setPos((actX+1)*100+10,(actY-2)*100+12);
    }else{
        tmpShow3->setPos(-100,-100);
    }
    if(!own->isVisited(actX+2,actY-1)){
        tmpShow4->setPos((actX+2)*100+10,(actY-1)*100+12);
    }else{
        tmpShow4->setPos(-100,-100);
    }
    if(!own->isVisited(actX-1,actY+2)){
        tmpShow5->setPos((actX-1)*100+10,(actY+2)*100+12);
    }else{
        tmpShow5->setPos(-100,-100);
    }
    if(!own->isVisited(actX-2,actY+1)){
        tmpShow6->setPos((actX-2)*100+10,(actY+1)*100+12);
    }else{
        tmpShow6->setPos(-100,-100);
    }
    if(!own->isVisited(actX-1,actY-2)){
        tmpShow7->setPos((actX-1)*100+10,(actY-2)*100+12);
    }else{
        tmpShow7->setPos(-100,-100);
    }
    if(!own->isVisited(actX-2,actY-1)){
        tmpShow8->setPos((actX-2)*100+10,(actY-1)*100+12);
    }else{
        tmpShow8->setPos(-100,-100);
    }

    judgeFinish(); //判断游戏是否结束
}

void ChessScene::tmpShowReset()
{
    tmpShow1->setPos(-100,-100);
    tmpShow2->setPos(-100,-100);
    tmpShow3->setPos(-100,-100);
    tmpShow4->setPos(-100,-100);
    tmpShow5->setPos(-100,-100);
    tmpShow6->setPos(-100,-100);
    tmpShow7->setPos(-100,-100);
    tmpShow8->setPos(-100,-100);
}

bool ChessScene::tips()
{
    if(!isPlaced){
        pathInformation = "笨蛋，你还没有放棋子";
        emit StringReady();
        return false;
    }
    if(actX==-100&&actY==-100){
        pathInformation = "我知道你很急，但你先别急，等棋子移动完毕";
        emit StringReady();
        return false;
    }
    if(own->findPath(actX,actY,sourceX,sourceY)){
        isFindPath = 1;
        pathInformation = "每个括号内第一个为列，第二个为行，路径如下：由当前点开始，依次经过";
        int i;
        QString tmp;
        for(i=0;i<=own->stepAmount;i++){
            tmp = "("+QString::number(own->path[i][0]+1)+","+QString::number(own->path[i][1]+1)+")";
            pathInformation = pathInformation + " " + tmp;
        }
        emit StringReady();
        return true;
    }
    else{
        pathInformation = "电脑cpu烧了，你再走几步试试再来问电脑吧，让电脑缓缓";
        emit StringReady();
        return false;
    }
}

void ChessScene::showPath()
{
    if(tips()){
        if(redFlag->pos().x()==-100){
            redFlag->setPos(actX*100+15,actY*100+15);
        }
        actX = -100;  //禁止掉鼠标操作
        actY = -100;
        tmpShowReset();
        actShow->startShow(own->path,own->stepAmount);
    }
}

void ChessScene::stepStartHandler()
{
    int x = transPos(actShow->pos().x());
    int y = transPos(actShow->pos().y());
    plaids[x][y]->setBrush(QColor(105,105,105));
    plaids[x][y]->setPen(QColor(169,169,169));
}

void ChessScene::mainwindowReset()
{
    actShow->stopShow();
}

void ChessScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    int x = event->scenePos().x();
    int y = event->scenePos().y();
    // qDebug() << "x:" << x << "y:" << y;
    // qDebug() << "actx:" << actX << "acty:" << actY;
    if(x<0 || x>800 || y<0 || y>800){    //判断鼠标的位置是否合法
        return;
    }
    if(!isPlaced){
        this->removeItem(tmpShow);  //删除虚拟棋子
        actShow->setPos(transPos(x)*100+10,transPos(y)*100+12);   //设置棋子位置
        this->addItem(actShow);   //添加棋子

        own->setVisited(transPos(x),transPos(y));  //设为已经过
        plaids[transPos(x)][transPos(y)]->setBrush(QColor(105,105,105)); //代表该格子不能再走
        this->tmpX = transPos(x); //设置当前坐标
        this->tmpY = transPos(y);
        this->sourceX = transPos(x);  //设置源点
        this->sourceY = transPos(y);

        isPlaced = true;  //已放下棋子
        tmpShowPlace();
    }
    else{
        if( ( (abs(transPos(x)-this->actX)==2 && abs(transPos(y)-this->actY)==1) || (abs(transPos(x)-this->actX)==1 && abs(transPos(y)-this->actY)==2) )
            && !own->isVisited(transPos(x),transPos(y)) ){
            if(redFlag->pos().x()==-100){
                redFlag->setPos(actX*100+15,actY*100+15);  //设置红旗的位置
            }
            tmpShowReset();
            this->tmpX = transPos(x);
            this->tmpY = transPos(y);
            this->actX = -100;   //设置无法移动的坐标禁止鼠标操作
            this->actY = -100;
            actShow->move(transPos(x)*100+10,transPos(y)*100+12,250);  //移动棋子
            own->setVisited(transPos(x),transPos(y));  //设为已经过
            isFindPath = 0;  //已经找到的路失效了
        }
    }

}

void ChessScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if(!isPlaced){
        int x = event->scenePos().x();
        int y = event->scenePos().y();
        if(x<20 || x>780 || y<20 || y>780){    //判断鼠标的位置是否合法,设置20px的阈值防止鼠标移动太快系统反应不过来，虽然还是无法完美解决这个问题
            tmpShow->setPos(-100,-100);
            return;
        }
        tmpShow->setPos(transPos(x)*100+10,transPos(y)*100+12);
    }
}

