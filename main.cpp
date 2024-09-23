#include "mainwindow.h"
#include <QApplication>

// #include "chessstruct.h"

int main(int argc, char *argv[])
{
    // ChessStruct *test = new ChessStruct;
    // test->setVisited(2,2);
    // test->setVisited(4,1);
    // test->setVisited(6,2);
    // test->setVisited(3,4);
    // test->setVisited(5,4);
    // if(test->findPath(5,4,2,2)){
    //     for(int i=0;i<=test->stepAmount;i++){
    //         qDebug()<< "x:" << test->path[i][0] << "y:" << test->path[i][1];
    //     }
    // }
    // else{
    //     qDebug()<<"false";
    // }
    // return 0;

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}






