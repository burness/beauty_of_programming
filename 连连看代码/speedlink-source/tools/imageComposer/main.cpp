#include <QtGui/QApplication>
#include <QDir>
#include <QPainter>
#include <QImage>
#include <QMessageBox>

int main(int argc,char *argv[])
{
    QApplication a(argc,argv);
    QDir dir;
    QStringList filters;
    filters<<"*.png"<<"*.PNG";
    dir.setNameFilters(filters);
    dir.setPath(".");
    QFileInfoList list = dir.entryInfoList();
    QFileInfo k;
    QImage image(46,list.size()*46,QImage::Format_RGB32);
    QPainter imgpainter(&image);
    QImage bk(":/bk/bk.png");
    bk=bk.scaled(46,46);
    for(int i=0;i<list.size();++i){
        QImage im;
        k=list[i];
        im.load(k.fileName());
        QImage temp=im.scaled(40,40);
        QImage paintDevice=bk;
        QPainter painter(&paintDevice);
        QPen pen;
        pen.setColor(QColor("#a5a9d7"));
        pen.setWidth(1);
        painter.setPen(pen);

        painter.drawRoundedRect(0,0,45,45,2,2);
        painter.drawImage(3,3,temp);
        painter.end();
        qreal y=46.0*i;
        imgpainter.save();
        imgpainter.translate(0.0,y);
        imgpainter.drawImage(0,0,paintDevice);
        imgpainter.restore();
    }
    image.save("pattern.png","PNG");
    QMessageBox::information(0,"Notify","Image Composed Complete");
    exit(0);
    return a.exec();
}
