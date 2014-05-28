#ifndef MAPAREA_H
#define MAPAREA_H

#include <QLabel>
#include <QMouseEvent>
#include "public-header.h"


const int NPIX_MAX=72;
const int X_MAX = 12;
const int Y_MAX = 18;
const int WIDTH=720;
const int HEIGHT=480;

class MapArea : public QLabel
{
    Q_OBJECT
public:
    explicit MapArea(QWidget *parent = 0);
    int patternNum();
    int pairNum();

    QSize size() const{
        return QSize(WIDTH,HEIGHT);
    }
    QSize sizeHint() const{
        return size();
    }
    bool checkMap();
    void resizePix(int,int);
protected:
    void mouseMoveEvent(QMouseEvent *ev);
    void mousePressEvent(QMouseEvent *ev);
    void paintEvent(QPaintEvent *);

signals:
    void mapChanged();
public slots:
    void setBlank();
    void fillAll();
    void generateMap(int kindNum);
    void saveMap(QString fileName);
private:
    int board[X_MAX][Y_MAX];
    int xMax;
    int yMax;
    int pixSize;
};

#endif // MAPAREA_H
