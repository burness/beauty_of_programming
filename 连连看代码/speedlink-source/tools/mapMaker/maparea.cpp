#include "maparea.h"
#include <cstring>
#include <QPaintEvent>
#include <QMessageBox>
#include <QPainter>
#include <stdlib.h>
#include <stdio.h>
#include <map>
using namespace std;

MapArea::MapArea(QWidget *parent) :
    QLabel(parent)
{
    fillAll();
}

void MapArea::setBlank()
{
    for(int i=0;i<xMax;++i)
        for(int j=0;j<yMax;++j)
            board[i][j]=0;
    update();
    emit mapChanged();
}

void MapArea::fillAll()
{
    for(int i=0;i<xMax;++i)
        for(int j=0;j<yMax;++j)
            board[i][j]=1;
    update();
    emit mapChanged();
}

int MapArea::patternNum()
{
    int sum=0;
    for(int i=0;i<xMax;++i)
        for(int j=0;j<yMax;++j)
            if(board[i][j])
                ++sum;
    return sum;
}

int MapArea::pairNum()
{
    return patternNum()/2;
}

void MapArea::mousePressEvent(QMouseEvent *ev)
{
        int x=ev->y()/pixSize;
        int y=ev->x()/pixSize;
        if(board[x][y]){
            board[x][y]=0;
            update();
        }else{
            board[x][y]=1;
            update();
        }
        emit mapChanged();
}

void MapArea::mouseMoveEvent(QMouseEvent *ev)
{
    static int lastX=0;
    static int lastY=0;
    int x=ev->y()/pixSize;
    int y=ev->x()/pixSize;

    if(x==lastX && y==lastY){
        return;
    }else{
        lastX=x;
        lastY=y;
    }
    if(board[x][y]){
        board[x][y]=0;
        update();
    }else{
        board[x][y]=1;
        update();
    }
    emit mapChanged();
}

#include <iostream>
void MapArea::paintEvent(QPaintEvent *)
{

    QPainter painter(this);
    QBrush brush(Qt::blue);
    painter.setBrush(brush);
    for(int i=0;i<xMax;++i)
        for(int j=0;j<yMax;++j){
            if(board[i][j])
                brush.setColor(Qt::gray);
            else
                brush.setColor(Qt::white);
            painter.fillRect(j*pixSize+5,i*pixSize+5,pixSize-10,pixSize-10,brush);
        }
}

bool MapArea::checkMap()
{
    map<int,int>mapCount;
    for(int i=0;i<xMax;++i)
        for(int j=0;j<yMax;++j){
            if(board[i][j])
                mapCount[board[i][j]]++;
        }
    map<int,int>::iterator i;
    for(i=mapCount.begin();i!=mapCount.end();++i){
        pair<int,int> p=*i;
        if(p.first && p.second%2!=0)
            return false;
    }
    return true;
}

void MapArea::generateMap(int kindNum)
{
    int totalPatternNum=patternNum();
    int eachFillMax=2*(pairNum()/kindNum);
    int normalFillMax=pairNum()*kindNum;
    int totalFillMax=patternNum()/2;
    totalFillMax*=2;
    int kindCount =1;
    int fillCount =1;
    int filledSum =0;
    if(totalPatternNum%2!=0)
        for(int i=xMax-1;i>=0;--i)
            for(int j=yMax-1;j>=0;--j){
                if(board[i][j]){
                    board[i][j]=0;
                    goto next;
                }
            }
    next:
    for(int i=0;i<xMax;++i)
        for(int j=0;j<yMax;++j){
            if(board[i][j]){
                board[i][j]=kindCount;
                ++filledSum;
                if(filledSum<=totalFillMax){
                    ++fillCount;
                    if(fillCount>eachFillMax){
                        fillCount=1;
                        ++kindCount;
                        if(kindCount>kindNum)
                            kindCount=1;
                    }
                }
            }
        }
    update();
    emit mapChanged();
    if(!checkMap()){
        QMessageBox::critical(this,tr("Error"),tr("The map generated is illegal"));
    }
}

void MapArea::saveMap(QString fileName)
{
    FILE *mapFile=fopen(fileName.toAscii(),"w");
    if(!mapFile){
        QMessageBox::information(this,tr("Error"),tr("Cannot create file"));
        return;
    }
    fprintf(mapFile,"%d %d\n",xMax,yMax);
    for(int i=0;i<xMax;++i)
        for(int j=0;j<yMax;++j){
            fprintf(mapFile,"%2d ",board[i][j]);
            if(j==yMax-1)
                fprintf(mapFile,"\n");
        }
    fclose(mapFile);
}

void MapArea::resizePix(int x, int y)
{
    xMax=x;
    yMax=y;
    pixSize=std::min(WIDTH/yMax,HEIGHT/xMax);
    update();
}
