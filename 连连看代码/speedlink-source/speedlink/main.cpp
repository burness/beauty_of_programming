#include <QApplication>
#include <QTextCodec>
#include "gamewindow.h"
#include <stdio.h>
int main(int argc,char *argv[])
{
    QApplication app(argc,argv);

    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));

    QApplication::setOrganizationName("TangYanhan");
    QApplication::setOrganizationDomain("tang_yanhan@126.com");
    QApplication::setApplicationName("SuperLink");
    QApplication::setApplicationVersion("v1.0");
    //PlaySound(TEXT("WindowsStart.wav"),NULL,SND_FILENAME|SND_ASYNC);
    GameWindow dw;
    dw.show();

    return app.exec();
}
