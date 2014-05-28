#ifndef DRAWAREA_H
#define DRAWAREA_H

#include <QWidget>
#include <QPixmap>
#include <QVector>
#include "public-header.h"

class QMouseEvent;
class QTimerEvent;
class QLabel;

/******************************************************
 * 这是用于连连看游戏中实现绘图区的类，实现对于连连看数据区的主要操作。
 * 主要功能接口包括：加载地图、混乱面板、提示、消块
*******************************************************/

struct Pos{
    Pos(){x=0;y=0;}
    Pos(int x_,int y_):x(x_),y(y_){}
    int x;
    int y;
};

class DrawArea:public QWidget
{
    Q_OBJECT
public:
    explicit DrawArea(QWidget *parent = 0);
    QSize size() const;
    QSize sizeHint() const;

    void initLevel(const Map &);
    //RTM Paint Operations
    void drawBoard();
    void drawEmbrace(const int &x,const int &y);
    void drawLine(const int &x1,const int &y1,
                  const int &x2,const int &y2);
    void drawRedMark(const int &x,const int &y);

    //Test Functions
    void print();
    void loadPixmap();
    void loadMapFromFile(std::string fileName);    
public slots:
    void disorder(int nDisorder); //对现在的图进行乱序
    void hint();
    void autoDestroy();
protected:
    void mousePressEvent(QMouseEvent *);
    void timerEvent(QTimerEvent *);

    int board[X_MAX][Y_MAX];
signals:
    void select();
    void hit(int nHit);
    void sameYetUnlinkable();
    void levelClear();
    void godTouchOn();

    void errorNotify(QString);
private:
    //Inner Logic Functions
    bool isPosLinkable(int,int,int,int,int *nPos=NULL,Pos *p1=NULL,Pos *p2=NULL);
    void clickPos(int,int);
    bool isDead();

    bool findinteractPoint(const int &,const int &,int &,int &);
    bool isLineLinkable(int,int,int,int);
    inline bool isBlank(const int &x,const int &y);
    inline bool isValid(const int &x,const int &y);
    inline bool isSame(const int&,const int&,const int&,const int&);

    //Runtime attributes
    bool isHintUsed;
    int lastX;
    int lastY;
    int pairLeft;
    int multiHit;
    bool godTouch;
    bool isLevelOver;
    Pos hintA;
    Pos hintB;
    int lineTimer;
    int hitTimer;
    //UI elements
    QLabel *drawArea;
    QPixmap background;
    QPixmap store;
    QVector<QPixmap> pixmap;
    int xMax;
    int yMax;
};

#endif // DRAWAREA_H
