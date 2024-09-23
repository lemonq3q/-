#include "mainwindow.h"
#include "chessscene.h"
#include <QFrame>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QTextEdit>
#include <QLabel>
#include <QGraphicsView>

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    this->setFixedSize(1400,900);    //设置主窗口固定大小
    this->setWindowIcon(QPixmap(":/img/chess.png")); //设置标题图
    this->setWindowTitle("国际象棋益智小游戏");
    this->setStyleSheet("background-color:#B99A74");

    left = new QFrame(this);                //左部棋盘边框参数设置
    left->setFrameStyle(QFrame::Panel | QFrame::Raised);
    left->setFixedSize(823,823);
    left->setStyleSheet("background-color:#967057");

    chessboard = new QGraphicsView;      //棋盘的view
    chessboard->setSceneRect(0,0,800,800);
    chessboard->setRenderHint(QPainter::Antialiasing);     //抗锯齿
    chessboard->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);     //去除横竖的拖拽条
    chessboard->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    chessboard->setDragMode(QGraphicsView::NoDrag);        //不可拖动
    chessboard->setMouseTracking(true);    //设置鼠标跟踪

    chessScene = new ChessScene;        //创建棋盘场景

    chessboard->setScene(chessScene);

    //按钮设置
    start = new QPushButton("重置",this);    //重置按钮
    start->setFixedSize(100,35);
    start->setStyleSheet("background-color:#6B4C2B;color:#F1E8D6;font-size: 16px;");
    suggest = new QPushButton("提示",this);  //提示按钮
    suggest->setFixedSize(100,35);
    suggest->setStyleSheet("background-color:#6B4C2B;color:#F1E8D6;font-size: 16px;");
    autoplay = new QPushButton("播放路径",this);   //播放路径按钮
    autoplay->setFixedSize(100,35);
    autoplay->setStyleSheet("background-color:#6B4C2B;color:#F1E8D6;font-size: 16px;");
    QLabel *text = new QLabel("可走路径",this);
    text->setFixedHeight(15);
    text->setStyleSheet("color:#6B4C2B;font-size: 16px;");
    display = new QTextEdit();          //跳跃路径显示窗口
    display->setFixedSize(400,300);
    display->setReadOnly(true);         //设置为不可编辑
    display->setStyleSheet("background-color:#E7D2AC;border: 2px solid #6B4C2B;color:#6B4C2B;font-size: 16px;");
    //布局设置
    QHBoxLayout *hlayout = new QHBoxLayout(this);   //水平布局
    hlayout->setSpacing(50);
    hlayout->addWidget(left);
    hlayout->setAlignment(left,Qt::AlignLeft);
    hlayout->setContentsMargins(50,38,0,38);

    QVBoxLayout *rightLayout = new QVBoxLayout(this);   //右边垂直布局
    rightLayout->setSpacing(25);
    rightLayout->setContentsMargins(0,50,0,50);
    rightLayout->addWidget(start);
    rightLayout->addWidget(suggest);
    rightLayout->addWidget(autoplay);

    QVBoxLayout *textAreaLayout = new QVBoxLayout(this);   //文本框
    textAreaLayout->setSpacing(5);
    textAreaLayout->addWidget(text);
    textAreaLayout->addWidget(display);

    rightLayout->addLayout(textAreaLayout);
    rightLayout->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    hlayout->addLayout(rightLayout);
    QGridLayout *frameLeft = new QGridLayout(left);
    frameLeft->addWidget(chessboard);

    connect(start,&QPushButton::clicked,chessScene,&ChessScene::mainwindowReset); //重置功能
    connect(chessScene,&ChessScene::textClear,display,&QTextEdit::clear);
    connect(suggest,&QPushButton::clicked,chessScene,&ChessScene::tips); //提示功能
    connect(chessScene,&ChessScene::StringReady,this,&MainWindow::updateText); //更新文本框
    connect(autoplay,&QPushButton::clicked,chessScene,&ChessScene::showPath);

}

MainWindow::~MainWindow(){}

void MainWindow::updateText()
{
    if(display->document()->toPlainText()=="电脑cpu烧了，你再走几步试试再来问电脑吧，让电脑缓缓"){
        if(chessScene->pathInformation=="电脑cpu烧了，你再走几步试试再来问电脑吧，让电脑缓缓"){
            display->setText("cpu真的烧了，你再走几步");
            return;
        }
    }
    if(display->document()->toPlainText()=="cpu真的烧了，你再走几步"){
        if(chessScene->pathInformation=="电脑cpu烧了，你再走几步试试再来问电脑吧，让电脑缓缓"){
            display->setText("烦不烦，都说了蒙圈了");
            return;
        }
    }
    if(display->document()->toPlainText()=="烦不烦，都说了蒙圈了"){
        if(chessScene->pathInformation=="电脑cpu烧了，你再走几步试试再来问电脑吧，让电脑缓缓"){
            display->setText("啊啊啊蒙圈了，别点了");
            return;
        }
    }
    if(display->document()->toPlainText()=="啊啊啊蒙圈了，别点了"){
        if(chessScene->pathInformation=="电脑cpu烧了，你再走几步试试再来问电脑吧，让电脑缓缓"){
            display->setText("真滴想不明白，不要问我了");
            return;
        }
    }
    if(display->document()->toPlainText()=="真滴想不明白，不要问我了"){
        if(chessScene->pathInformation=="电脑cpu烧了，你再走几步试试再来问电脑吧，让电脑缓缓"){
            display->setText("这边建议您重开呢");
            return;
        }
    }
    if(display->document()->toPlainText()=="这边建议您重开呢"){
        if(chessScene->pathInformation=="电脑cpu烧了，你再走几步试试再来问电脑吧，让电脑缓缓"){
            display->setText("重开吧，别烦我了");
            return;
        }
    }
    if(display->document()->toPlainText()=="重开吧，别烦我了"){
        if(chessScene->pathInformation=="电脑cpu烧了，你再走几步试试再来问电脑吧，让电脑缓缓"){
            display->setText("快重开！");
            return;
        }
    }
    if(display->document()->toPlainText()=="快重开！"){
        if(chessScene->pathInformation=="电脑cpu烧了，你再走几步试试再来问电脑吧，让电脑缓缓"){
            display->setText("重开吧，别烦我了");
            return;
        }
    }
    display->setText(chessScene->pathInformation);
}
