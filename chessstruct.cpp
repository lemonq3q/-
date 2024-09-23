#include "chessstruct.h"
#include <map>
#include <vector>
#include <algorithm>
#include <QApplication>


struct CmpByValue {           //设置辅助sort函数的结构体
    bool operator()(const std::pair<int, int>& lhs, const std::pair<int, int>& rhs) {
        return lhs.second < rhs.second;
    }
};

ChessStruct::ChessStruct() {
    reSet();
    int dx[8] = {-1,1,2,2,1,-1,-2,-2};
    int dy[8] = {-2,-2,-1,1,2,2,1,-1};
    int i;
    for(i=0;i<8;i++){
        dirX[i] = dx[i];
        dirY[i] = dy[i];
    }
}

void ChessStruct::reSet()
{
    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++){
            this->visited[i][j] = 0;
        }
    }
}

bool ChessStruct::isVisited(int x, int y)
{
    if(x<0 || x>7 || y<0 || y>7){   //配合ChessScene内的函数，给的是不合法的坐标返回true代表无法走
        return true;
    }
    if(visited[x][y]==0){
        return false;
    }
    else{
        return true;
    }
}

void ChessStruct::setVisited(int x, int y)
{
    visited[x][y] = 1;
}

bool ChessStruct::findPath(int startx, int starty, int sourcex, int sourcey)
{
    int i,j;
    visitedAmount = 0;
    stepAmount = -1;   //记录路径数组里有多少对值
    // dangerAmount = 0; //记录危险点数组里有多少对值
    // dangerousPoint[0][0] = sourcex;  //将源点作为危险点录入
    // dangerousPoint[0][1] = sourcey;
    this->startX = sourcex;    //记录玩家一开始选的哪个点
    this->startY = sourcex;


    for(i=0;i<8;i++){       //记录现在已经访问了多少个点了
        for(j=0;j<8;j++){
            findPathVisited[i][j] = visited[i][j];  //备份visited数组
            if(visited[i][j]==1){
                visitedAmount++;
            }
        }
    }

    int count = 0,flag = 0,pos;
    for(i=0;i<64;i++){
        if(isVisited(circuitPath[i][0],circuitPath[i][1])){
            flag = 1;   //判断是否被走过，如果走过，开始路径跟踪
            count++;
        }
        if(startx==circuitPath[i][0] && starty==circuitPath[i][1]){
            pos = i;
        }
        else{
            if(flag==1){  //判断是否开始过路径跟走，如果开始过代表已经结束
                if(count==visitedAmount){
                    flag = 2;
                }
                break;
            }
        }
    }

    if(flag==2){
        if(isVisited(circuitPath[(pos+1)%64][0],circuitPath[(pos+1)%64][1])&&!isVisited(circuitPath[(pos+63)%64][0],circuitPath[(pos+63)%64][1])){
            for(i=(pos+63)%64;;i=(i+63)%64){
                if(isVisited(circuitPath[i][0],circuitPath[i][1])){
                    return true;
                }
                stepAmount++;
                path[stepAmount][0] = circuitPath[i][0];
                path[stepAmount][1] = circuitPath[i][1];
            }
        }
        if(!isVisited(circuitPath[(pos+1)%64][0],circuitPath[(pos+1)%64][1])&&isVisited(circuitPath[(pos+63)%64][0],circuitPath[(pos+63)%64][1])){
            for(i=(pos+1)%64;;i=(i+1)%64){
                if(isVisited(circuitPath[i][0],circuitPath[i][1])){
                    return true;
                }
                stepAmount++;
                path[stepAmount][0] = circuitPath[i][0];
                path[stepAmount][1] = circuitPath[i][1];
            }
        }
        if(!isVisited(circuitPath[(pos+1)%64][0],circuitPath[(pos+1)%64][1])&&!isVisited(circuitPath[(pos+63)%64][0],circuitPath[(pos+63)%64][1])){
            for(i=(pos+1)%64;;i=(i+1)%64){
                if(isVisited(circuitPath[i][0],circuitPath[i][1])){
                    return true;
                }
                stepAmount++;
                path[stepAmount][0] = circuitPath[i][0];
                path[stepAmount][1] = circuitPath[i][1];
            }
        }
    }
    // std::future<bool> result = std::async(std::launch::async, std::bind(findNext, startx, starty));
    // bool judge = result.get();
    timeCount = 0;
    bool judge = findNext(startx,starty,1);
    for(i=0;i<8;i++){      //将visited数组恢复
        for(j=0;j<8;j++){
            visited[i][j] = findPathVisited[i][j];
        }
    }
    if(judge){
        return true;
    }
    else{
        return false;
    }
}

bool ChessStruct::findNext(int startx, int starty,int deep)
{
    timeCount++;
    if(deep>4){
        if(timeCount>=10000){
            return false;
        }
    }
    // if(timeCount>=7000000){
    //     return false;
    // }
    int i,tmp;
    if(visitedAmount==64){
        return true;
        // qDebug () << "点" << startx << starty << "到了";
    }
    std::map<int, int> dirmap;
    for(i=0;i<8;i++){      //寻找出口最少的下一个方向
        if(!isVisited(startx+dirX[i],starty+dirY[i])){
            dirmap.insert({i,findOutAmount(startx+dirX[i],starty+dirY[i])});   //路径与出口数存放到map内
        }
    }
    if(dirmap.size()==0){    //死胡同了，回溯
        return false;
    }
    std::vector<std::pair<int, int>> dirvector(dirmap.begin(),dirmap.end());    //map按值排序
    sort(dirvector.begin(),dirvector.end(),CmpByValue());

    for(i=0;i!=dirvector.size();i++){

        stepAmount++;

        // qDebug() << stepAmount;

        visited[startx+dirX[dirvector[i].first]][starty+dirY[dirvector[i].first]] = 1;
        path[stepAmount][0] = startx+dirX[dirvector[i].first];
        path[stepAmount][1] = starty+dirY[dirvector[i].first];
        visitedAmount++;
        if(deep<=4){
            timeCount = 0;
        }
        if(findNext(startx+dirX[dirvector[i].first],starty+dirY[dirvector[i].first],deep+1)){
            return true;
        }
        stepAmount--;  //路不通，回溯

        // qDebug() << stepAmount;

        visited[startx+dirX[dirvector[i].first]][starty+dirY[dirvector[i].first]] = 0;
        visitedAmount--;
    }
    return false;
}

int ChessStruct::findOutAmount(int x, int y)
{
    int i,count = 0;
    for(i=0;i<8;i++){     //遍历所有出口看看有几个合法出口
        if(!isVisited(x+dirX[i],y+dirY[i])){
            count++;
        }
    }
    return count;
}

bool ChessStruct::judgeDangerous(int x, int y)  //引入的危险点算法
{
    if(x==dangerousPoint[dangerAmount][0] && y==dangerousPoint[dangerAmount][1]){
        if(visitedAmount+dangerAmount==64){  //代表进入入口后只会向源点跳
            return true;
        }
        else{
            return false;
        }
    }
    int i,flag = 0,count = 0,tmpx,tmpy;
    for(i=1;i<dangerAmount;i++){   //想越过入口直接跳入危险点
        if(x==dangerousPoint[i][0] && y==dangerousPoint[i][1]){
            return false;
        }
    }
    for(i=0;i<8;i++){
        if(x==dangerousPoint[dangerAmount][0]+dirX[i] && y==dangerousPoint[dangerAmount][1]+dirY[i]){
            flag = 1;
            break;
        }
    }
    int vx,vy;
    if(flag==1){
        for(i=0;i<8;i++){     //遍历所有出口看看有几个合法出口
            if(!isVisited(dangerousPoint[dangerAmount][0]+dirX[i],dangerousPoint[dangerAmount][1]+dirY[i])){
                if(!(x==dangerousPoint[dangerAmount][0]+dirX[i] && y==dangerousPoint[dangerAmount][1]+dirY[i])){
                    tmpx = dangerousPoint[dangerAmount][0]+dirX[i];
                    tmpy = dangerousPoint[dangerAmount][1]+dirY[i];
                }
                count++;
            }
        }
        if(count==2){
            // dangerAmount++;
            // dangerousPoint[dangerAmount][0] = tmpx;
            // dangerousPoint[dangerAmount][1] = tmpy;
            visited[x][y] = 1;  //辅助入口点生成
            generateDangerous(tmpx,tmpy);
        }
    }
    return true;
}

void ChessStruct::generateDangerous(int x, int y)
{
    dangerAmount++;
    dangerousPoint[dangerAmount][0] = x;
    dangerousPoint[dangerAmount][1] = y;
    if(findOutAmount(x,y)==2){
        for(int i=0;i<8;i++){
            if(!isVisited(x+dirX[i],y+dirY[i])){
                if(!(x+dirX[i]==dangerousPoint[dangerAmount-1][0] && y+dirY[i]==dangerousPoint[dangerAmount-1][1])){
                    generateDangerous(x+dirX[i],y+dirY[i]);
                    break;
                }
            }
        }
    }

}

void ChessStruct::deleteDangerous()
{
    for(int i=1;i<dangerAmount-1;i++){
        if(findOutAmount(dangerousPoint[i][0],dangerousPoint[i][1])>=3){
            dangerAmount = i;
            break;
        }
    }
}
