#include "drawarea.h"
#include <iostream>
#include <QMouseEvent>
#include <QTimerEvent>
#include <QPainter>
#include <QLabel>
#include <QDir>
#include <QFileInfo>
#include <stdio.h>
#include <assert.h>

const int INTERVAL_LINE_TIMER=200;
const int INTERVAL_HIT_TIMER =2000;
const int PIX_SIZE   = 46;
const int AREA_WIDTH  = Y_MAX*PIX_SIZE;
const int AREA_HEIGHT = X_MAX*PIX_SIZE;


DrawArea::DrawArea(QWidget *parent) :
    QWidget(parent)
{
    loadPixmap();
    drawArea = new QLabel(this);
    drawArea->setGeometry(0,0,AREA_WIDTH,AREA_HEIGHT);
    drawArea->setPixmap(background);
    isHintUsed=false;
}

QSize DrawArea::size() const
{
    return QSize(AREA_WIDTH,AREA_HEIGHT);
}

QSize DrawArea::sizeHint() const
{
    return size();
}

/* 初始化关卡 */
void DrawArea::initLevel(const Map &mapData)
{
    lastX=mapData.xMax;
    lastY=mapData.yMax;
    lineTimer=0;
    hitTimer =0;
    multiHit =0;
    pairLeft =0;
    xMax=mapData.xMax;
    yMax=mapData.yMax;
    for(int i=0;i<xMax;++i)
        for(int j=0;j<yMax;++j){
            board[i][j]=mapData.map[i][j];
            if(board[i][j])
                ++pairLeft;
        }
    if(pairLeft%2!=0){
        emit errorNotify(tr("地图数据错误，地图存在不成对的块数"));
        return;
    }
    if(pairLeft==0){
        emit errorNotify(tr("地图数据为空"));
        return;
    }
    pairLeft =pairLeft/2;

    disorder(mapData.disorderCount);
    //刚开局就判断死局，一个是初始化上帝之手，
    //再一个最主要原因是为hint图块对赋值
    //上帝之手的初始化必须在地图数据加载之后进行
    if(isDead()){
        godTouch=true;
        emit godTouchOn();
    }else
        godTouch=false;

    isLevelOver = false;
    drawBoard();
}


//[Test]从文件加载地图及相关配置信息。
void DrawArea::loadMapFromFile(string fileName)
{
    int nDisorder;
    FILE *mapFile;
    mapFile=fopen(fileName.c_str(),"r");
    if(!mapFile)
        exit(-1);
    if(fscanf(mapFile,"%d %d",&nDisorder,&pairLeft)==EOF){
        emit errorNotify(tr("Test:地图数据加载失败"));
        return;
    }
    for(int i=0;i<xMax;++i)
    for(int j=0;j<yMax;++j){
        if(fscanf(mapFile,"%d",&board[i][j])==EOF){
            emit errorNotify(tr("Test:地图数据无法成功加载"));
            return;
        }
    }
    fclose(mapFile);
    disorder(nDisorder);
}

//根据指定的打乱次数 nDisorder对面板内的非零数据进行交换
void DrawArea::disorder(int nDisorder)
{
    srand(clock());
    //基本实现：将非零数据加入到一个足够长的数组中，随机产生两个
    //坐标进行交换
    int pos[xMax*yMax][2];
    int nBlock=0;
    for(int i=0;i<xMax;++i)
    for(int j=0;j<yMax;++j){
        if(board[i][j]){
            pos[nBlock][0]=i;
            pos[nBlock][1]=j;
            ++nBlock;
        }
    }

    for(int i=nDisorder;i;--i){
        int pos1=rand()%nBlock;
        generatePos2:
        int pos2=rand()%nBlock;
        if(pos1==pos2)
            goto generatePos2;

        int x1=pos[pos1][0];
        int y1=pos[pos1][1];
        int x2=pos[pos2][0];
        int y2=pos[pos2][1];
        std::swap(board[x1][y1],board[x2][y2]);
    }
    drawBoard();
}

/* 加载图块图片资源 */
void DrawArea::loadPixmap()
{
    background.load(":/background/background.png");
    background=background.scaled(size());
    QPixmap pix(":/pattern/pattern.png");
    int num=pix.height()/PIX_SIZE;
    for(int i=1;i<num;++i){
        qreal y=PIX_SIZE*i;
        QPixmap p=pix.copy(0,y,PIX_SIZE,PIX_SIZE);
        pixmap.push_back(p);
    }
}

//给玩家生成一对提示，并将其高亮显示
void DrawArea::hint()
{
    isHintUsed=true;
    //将找到的一对图块画上边框
    lastX=hintA.x;
    lastY=hintB.y;
    drawBoard();
}

/* Timer events.
 */
void DrawArea::timerEvent(QTimerEvent *event)
{
    if(event->timerId()==lineTimer){
        killTimer(lineTimer);
        lineTimer =0;
        drawBoard();
    }
    if(event->timerId()==hitTimer){
        multiHit=0;
        killTimer(hitTimer);
        hitTimer =0;
        drawBoard();
    }

}

/* 接受鼠标按下的消息并将其发生的相对屏幕坐标转换成数组坐标
 * 传入clickPos进行判断，同时将其画上选中标志。
 */
void
DrawArea::mousePressEvent(QMouseEvent *event)
{
    int y=(event->x()-drawArea->x())/PIX_SIZE;
    int x=(event->y()-drawArea->y())/PIX_SIZE;

    if(!isBlank(x,y)){
        emit select();
        isHintUsed = false;
        drawEmbrace(x,y);
        clickPos(x,y);
    }
}

/* 绘制面板，当回合未结束时，绘制面板上所有图块的内容。
 * 如果连击数不少于两次，则在屏幕正中心显示 "xN Hit"的字样
 */
void
DrawArea::drawBoard()
{
    store=background;
    QPainter painter(&store);
    if(!isLevelOver){
        painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
        for(int i=0;i<xMax;++i)
            for(int j=0;j<yMax;++j){
            painter.save();
            painter.translate(j*PIX_SIZE,i*PIX_SIZE);
            if(!isBlank(i,j) && board[i][j]<pixmap.size())
                painter.drawPixmap(0,0,PIX_SIZE,PIX_SIZE,pixmap[board[i][j]-1]);
            painter.restore();
        }
        if(multiHit>1){
            QFont font;
            QPen pen(Qt::SolidLine);
            pen.setColor(QColor(255,255,255,220));
            font.setFamily("Comic Sans MS");
            font.setPixelSize(30);
            font.setBold(true);
            painter.setPen(pen);
            painter.setFont(font);
            painter.drawText(QPointF(0,AREA_HEIGHT-15),tr("x%1   连击!").arg(multiHit));
        }
    }
    painter.end();
    drawArea->setPixmap(store);
    if(isHintUsed){
        drawEmbrace(hintA.x,hintA.y);
        drawEmbrace(hintB.x,hintB.y);
    }else
        drawEmbrace(lastX,lastY);
}

/* 为选中的图块画上标志 */
void DrawArea::drawEmbrace(const int &x,const int &y)
{
    if(isValid(x,y) && board[x][y]){
        QPainter painter(&store);
        painter.setCompositionMode(QPainter::RasterOp_SourceAndDestination);
        QPen pen;
        pen.setWidth(5);
        pen.setColor(Qt::blue);
        painter.setPen(pen);
        painter.translate(y*PIX_SIZE,x*PIX_SIZE);
        painter.drawRect(0,0,PIX_SIZE,PIX_SIZE);
        painter.end();
        drawArea->setPixmap(store);
    }
}

/* 在指定的图块上画一个红色的叉号 */
void DrawArea::drawRedMark(const int &x, const int &y)
{
    QPainter painter(&store);
    QPen pen(Qt::white);
    pen.setWidth(5);
    painter.setPen(pen);
    painter.translate(y*PIX_SIZE,x*PIX_SIZE);
    painter.drawLine(0,0,PIX_SIZE,PIX_SIZE);
    painter.drawLine(0,PIX_SIZE,PIX_SIZE,0);
    painter.end();
    drawArea->setPixmap(store);
}

/* 在两个给定点之间画一条较粗的直线 */
void DrawArea::drawLine(const int &aX, const int &aY,
                        const int &bX, const int &bY)
{
    QPainter painter(&store);
    int x1=aY*PIX_SIZE+ PIX_SIZE/2;
    int y1=aX*PIX_SIZE+PIX_SIZE/2;
    int x2=bY*PIX_SIZE+PIX_SIZE/2;
    int y2=bX*PIX_SIZE+PIX_SIZE/2;
    QPen pen(Qt::blue);
    pen.setStyle(Qt::SolidLine);
    pen.setWidth(5);
    painter.setPen(pen);
    painter.drawLine(x1,y1,x2,y2);
    painter.end();
    drawArea->setPixmap(store);
}

void DrawArea::autoDestroy()
{
    lastX=hintA.x;
    lastY=hintA.y;
    clickPos(hintB.x,hintB.y);
}

/****************************************
 *连连看逻辑实现相关函数
 ****************************************/

/* 判断是否已经进入死局，死局条件：
 * 在回合尚未结束的情况下遍历面板，无法找到一对可销图块
 * 则判定为死局。若找到一对可销图块，则将其记录为hintA
 * 和hintB,以供hint()函数利用。
 */
bool
DrawArea::isDead()
{
    int i,j,x,y;
    if(!pairLeft)
        return true;
    for(i=0;i<xMax;++i){
        for(j=0;j<yMax;++j){
            if(board[i][j]){
                for(x=i;x<xMax;++x){
                    if(x==i)    y=j+1;
                    else y=0;
                    
                    for(;y<yMax;++y){
                        if(board[x][y]==board[i][j]){
                            if(isPosLinkable(i,j,x,y)){//如果消块成功，那么这里就变成了0
                                hintA.x=i;
                                hintA.y=j;
                                hintB.x=x;
                                hintB.y=y;
                                return false;
                            }
                        }
                    }
                }
            }
        }
    }
    return true;
}

/* 在 (x,y)位置发生了点击,如果上次点击的点花色与之相同且位置不同,
 * 对于上帝模式，直接销块。
 * 否则，尝试判断是否可连接，如果可连接则进行连线，
 * 并随后进行死局判断，如进入死局则开启上帝模式
 * 否则将这个点记为上次点击的点。
 * 每次成功销块之后，立即增加连击计数并启动一个连击定时器，如果连击
 * 定时器过期，则连击计数清零。
 */
void 
DrawArea::clickPos(int x,int y)
{
    assert( isValid(x,y)  );
    assert( !isBlank(x,y) );

    vector <Pos> posVec;
    int nPos=0;
    Pos pos1,pos2;
    if(lastX==x &&lastY==y)
        return;
    if(!isValid(lastX,lastY)||
        !isSame(x,y,lastX,lastY)||//isSame must be placed after "isValid"
        isBlank(lastX,lastY)){
        lastX=x;
        lastY=y;
        drawBoard();
        return;
    }

    if(godTouch){
        drawRedMark(x,y);
        drawRedMark(lastX,lastY);
        goto Destroy_Blocks;
    }

    if(isPosLinkable(x,y,lastX,lastY,&nPos,&pos1,&pos2)){
        Pos a(x,y);
        Pos b(lastX,lastY);
        posVec.push_back(a);
        if(nPos>=1){
            posVec.push_back(pos1);
            if(nPos==2)
            posVec.push_back(pos2);
        }
        posVec.push_back(b);
        for(unsigned int i=0;i<posVec.size()-1;++i){
            drawLine(posVec[i].x,posVec[i].y,posVec[i+1].x,posVec[i+1].y);
        }

        goto Destroy_Blocks;
    }else{
        lastX=x;
        lastY=y;
        drawBoard();
        emit sameYetUnlinkable();
        return;
    }
    
    Destroy_Blocks:
    //销块操作
    if(hitTimer)
        killTimer(hitTimer);
    hitTimer =startTimer(INTERVAL_HIT_TIMER);
    ++multiHit;
    emit hit(multiHit);
    lineTimer=startTimer(INTERVAL_LINE_TIMER);

    //连线操作
    board[x][y]=0;
    board[lastX][lastY]=0;
    --pairLeft;
    if(!pairLeft){
        isLevelOver =true;
        emit levelClear();
        puts("Game Over");//GameOver
    }else{
        if(isDead()){
            godTouch=true;
            emit godTouchOn();
        }else
            godTouch=false;
    }
}

/*  */
inline bool 
DrawArea::isBlank(const int &x,const int &y)
{
    assert(isValid(x,y));
    
    return board[x][y]==0;
}

/* Check whether the position is valid */
inline bool 
DrawArea::isValid(const int &x,const int &y)
{
    if(x>=xMax||y>=yMax)
        return false;
    return true;
}

/* Check whether the two points are the same */
inline bool 
DrawArea::isSame(const int &x1,const int &y1,
                const int &x2,const int &y2)
{
    assert(isValid(x1,y1));
    assert(isValid(x2,y2));
    
    return board[x1][y1] == board[x2][y2];
}

/*
 */
bool 
DrawArea::isPosLinkable(int x1_,int y1_,int x2_,int y2_,
                            int *nPos,Pos *pos1,Pos *pos2)
{
    assert(isValid(x1_,y1_));
    assert(isValid(x2_,y2_));
    
    bool posFlag=false;//传入参数中是否有折点
    if(nPos){
        posFlag=true;
        if(!(pos1&&pos2))
            return false;
    }
    
    int x1=x1_;
    int x2=x2_;
    int y1=y1_;
    int y2=y2_;
    if(!isSame(x1,y1,x2,y2))
        return false;
        
    //First,check whether they can be directly linked
    if(isLineLinkable(x1,y1,x2,y2)){
        if(posFlag) *nPos=0;
        
        return true;
    }
    //Second,check whether they can be linked with one turning
    if(findinteractPoint(x1,y1,x2,y2)){
        if(posFlag){
            *nPos=1;
            pos1->x=x2;
            pos1->y=y2;
        }
        return true;
    }
    //Third,check x-direct point that can be linked with one turning
    for(int i=0;i<xMax;++i){
        if(isBlank(i,y1) && 
           isLineLinkable(i,y1,x1,y1) && 
           findinteractPoint(i,y1,x2,y2)){
               if(posFlag){
                    *nPos=2;
                    pos1->x=i;
                    pos1->y=y1;
                    pos2->x=x2;
                    pos2->y=y2;
                }
            return true;
        }
    }
    //Fourth,check y-direct point that can be linked with one turning
    for(int i=0;i<yMax;++i){
        if(isBlank(x1,i) && 
           isLineLinkable(x1,i,x1,y1) && 
           findinteractPoint(x1,i,x2,y2)){
               if(posFlag){
                    *nPos=2;
                    pos1->x=x1;
                    pos1->y=i;
                    pos2->x=x2;
                    pos2->y=y2;
                }
            return true;
        }
    }
    return false;
}
/* 
 * 寻找以 (x1,y1)和 (x2,y2)所在线段为对角线的矩形中对这两个点均可直线到达的顶点
 * 若找到，则将 (x2,y2)改写为该顶点，否则，返回false
 */
bool 
DrawArea::findinteractPoint(const int &x1,const int &y1,int &x2,int &y2)
{
    if(!board[x1][y2]){
        if(isLineLinkable(x1,y1,x1,y2) &&
            isLineLinkable(x2,y2,x1,y2)){
            x2=x1;
            return true;
        }
    }
    if(!board[x2][y1]){
            if(isLineLinkable(x1,y1,x2,y1)&&
                isLineLinkable(x2,y2,x2,y1)){
                y2=y1;
                return true;
            }
    }
    return false;
}
/*
 * 检验两点是否可以直线无障碍到达
 */
bool 
DrawArea::isLineLinkable(int x1,int y1,int x2,int y2)
{
    if(x1 == x2){
        if(y1>y2)    std::swap(y1,y2);
        
        for(y1+=1;y1<y2;++y1)
            if(board[x1][y1])
                return false;
            
    }else if(y1 == y2){
        if(x1>x2)    std::swap(x1,x2);
        
        for(x1+=1;x1<x2;++x1)
            if(board[x1][y1])
                return false;
    }else
        return false;
    
    return true;
}

 /// Test Functions
 void DrawArea::print()
 {
     puts("\n----------------Board Content----------------\n");
     printf("     ");
     for(int j=0;j<yMax;++j)printf("%2d ",j);
     printf("\n\n");
     for(int i=0;i<xMax;++i){
         printf("%2d   ",i);
         for(int j=0;j<yMax;++j){
             printf("%2d ",board[i][j]);
             if(j==yMax-1)
             printf("\n");
         }
     }
}
