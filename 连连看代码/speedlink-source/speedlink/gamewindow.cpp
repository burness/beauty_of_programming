#include "gamewindow.h"
#include "ui_gamewindow.h"
#include <QStandardItemModel>
#include <QMessageBox>
#include <QTimerEvent>
#include <QCloseEvent>
#include <QKeyEvent>
#include <QSettings>
#include <QTextStream>
#include <QFile>
#include <QSound>

#include <windows.h>
#include <mmsystem.h>

#define MAP_FILE_NAME "./data/map.txt"
#define THEME_DIR "./theme/"
#define SOUND_DIR "./sound/"

const int N_BACKGROUND_MUSIC=3;

enum UIStackIndex{
    UIMain,
    UIGame,
    UIPause,
    UILevelSuccess,
    UIGameOver,
    UITopList,
    UIAbout,
    UISelectLevel
};


GameWindow::GameWindow(QWidget *parent) :
    QMainWindow(parent)
{
    setWindowFlags(Qt::Dialog);
    ui.setupUi(this);
    ui.uiStack->setCurrentIndex(UIMain);
    //Build Connections
    connect(ui.drawArea,SIGNAL(select()),this,SLOT(select()));
    connect(ui.drawArea,SIGNAL(sameYetUnlinkable()),this,SLOT(sameYetUnlinkable()));
    connect(ui.drawArea,SIGNAL(hit(int)),this,SLOT(updateScore(int)));
    connect(ui.drawArea,SIGNAL(levelClear()),this,SLOT(levelOver()));
    connect(ui.drawArea,SIGNAL(godTouchOn()),this,SLOT(godTouchOn()));
    connect(ui.startGameNormal,SIGNAL(mouseOver()),this,SLOT(startGameMouseOver()));
    connect(ui.startGameChallenge,SIGNAL(mouseOver()),this,SLOT(challengeModeMouseOver()));
    connect(ui.execiseMode,SIGNAL(mouseOver()),this,SLOT(execiseModeMouseOver()));
    connect(ui.topList,SIGNAL(mouseOver()),this,SLOT(topListMouseOver()));
    connect(ui.about,SIGNAL(mouseOver()),this,SLOT(aboutMouseOver()));
    connect(ui.exit,SIGNAL(mouseOver()),this,SLOT(exitMouseOver()));

    readSettings();
    ui.themeSelect->setCurrentIndex(theme);
    changeTheme(theme);

    loadLevelFromFile(MAP_FILE_NAME);
    createLevelList();
    backgroundMusicOn = true;
    foregroundMusicOn = true;
}

// 根据给定的游戏模式初始化游戏数据，加载进行游戏界面
void GameWindow::initGame(GameMode mode)
{
    score =0;
    currentLevel =0;
    gameMode = mode;

    if(gameMode == Normal)
        lifeLeft =1;
    else
        lifeLeft =1;
    ui.lifeLeft->setText(tr("x%1").arg(lifeLeft));
    ui.scoreLabel->setText(tr("%1").arg(score));
}

//根据指定的关卡索引加载指定关卡
void GameWindow::loadLevel(int levelIndex)
{
    if(levelIndex<0 || levelIndex>=levels.size()){
        QMessageBox::critical(this,tr("Error"),tr("关卡载入错误：无效的关卡索引"));
        return;
    }
    Level thisLevel=levels.at(levelIndex);
    if(gameMode==Normal)
        timeLeft=thisLevel.normalTimeLimit;
    else
        timeLeft=thisLevel.challengeTimeLimit;
    disorderLeft =3;
    hintLeft =3;
    //UI loading
    ui.levelLable->setText(tr(thisLevel.levelName));
    ui.timeLeft->setRange(0,timeLeft);
    ui.timeLeft->setValue(timeLeft);
    ui.hintLeft->setText(tr("x%1").arg(hintLeft));
    ui.disorderLeft->setText(tr("x%1").arg(disorderLeft));
    ui.drawArea->initLevel(thisLevel.mapData);
    timerID=startTimer(1000);
    MCISoundPlay(tr("%1level%2.mid").arg(SOUND_DIR).arg(levelIndex));
    ui.uiStack->setCurrentIndex(UIGame);
}

//从文件加载所有关卡数据
void GameWindow::loadLevelFromFile(QString fileName)
{
    int levelNum =0;
    FILE* fp=fopen(fileName.toAscii(),"r");
    if(!fp){
        QMessageBox::critical(this,tr("Map Error"),tr("无法找到地图文件"),QMessageBox::Ok);
        return;
    }
    if(fscanf(fp,"%d",&levelNum)==EOF){
        QMessageBox::critical(this,tr("Map Error"),tr("无法从文件中读取关卡数"),QMessageBox::Ok);
        return;
    }
    if(levelNum<=0){
        QMessageBox::critical(this,tr("Map Error"),tr("关卡数目错误：%1").arg(levelNum),QMessageBox::Ok);
        return;
    }
    Level l;
    for(int i=0;i<levelNum;++i){
        if(fscanf(fp,"%s",l.levelName)==EOF){
            QMessageBox::critical(this,tr("Map Error"),tr("读取 %1 关卡名错误").arg(i),QMessageBox::Ok);
            return;
        }
        if(fscanf(fp,"%d %d %d",&(l.normalTimeLimit),
               &(l.challengeTimeLimit),
               &(l.mapData.disorderCount))!=3){
            QMessageBox::critical(this,tr("Map Error"),tr("读取 %1 关卡基本设定错误").arg(i),QMessageBox::Ok);
            return;
        }
        int xMax=0;
        int yMax=0;
        if(fscanf(fp,"%d %d",&xMax,&yMax)!=2){
            QMessageBox::critical(this,tr("Map Error"),tr("读取 %1 关卡基本设定错误").arg(i),QMessageBox::Ok);
            return;
        }
        l.mapData.xMax=xMax;
        l.mapData.yMax=yMax;
        for(int x=0;x<xMax;++x)
            for(int y=0;y<yMax;++y)
                if(fscanf(fp,"%d",&(l.mapData.map[x][y]))!=1){
                    QMessageBox::critical(this,tr("Map Error"),tr("读取 %1 关卡地图排布数据缺失").arg(i),QMessageBox::Ok);
                    return;
                }
        levels.push_back(l);
    }
    fclose(fp);
}
#include <QListWidget>

void GameWindow::createLevelList()
{
    for(int i=0;i<levels.size();++i){
        QIcon icon(tr(":/levelPreview/level%1.png").arg(i+1));
        QString name=tr(levels.at(i).levelName);
        QListWidgetItem *item=new QListWidgetItem(icon,name);
        ui.levelListWidget->addItem(item);
    }
}

/// Game Operation Slots

void GameWindow::changeTheme(int type)
{
    QString themeFileName;
    QString dir=THEME_DIR;
    switch(type){
    case Golden:themeFileName="golden.qss";break;
    case SkyBlue:themeFileName="skyblue.qss";break;
    case Pink:themeFileName="pink.qss";break;
    default:
        QMessageBox::critical(this,tr("Error"),tr("未知的指定主题"));
    }
    themeFileName=dir+themeFileName;
    QFile file(themeFileName);
    if(!file.open(QFile::ReadOnly)){
        QMessageBox::critical(this,tr("Error"),tr("主题文件丢失，保持原主题"),QMessageBox::Ok);
        return;
    }
    QTextStream in(&file);
    QString style=in.readAll();
    this->setStyleSheet(style);
    file.close();
}

void GameWindow::playSound(SoundSituation situation)
{
    static QString soundDir=SOUND_DIR;
    if(foregroundMusicOn){
        switch(situation){
        case Select:
            QSound::play(soundDir+"select.wav");
            break;
        case Destroy:
            QSound::play(soundDir+"destroy.wav");
            break;
        case LevelSuccess:
            MCISoundPlay(soundDir+"levelSuccess.wav",false);
            break;
        case GameSuccess:
            MCISoundPlay(soundDir+"gameSuccess.wav",false);
            break;
        case GameFailure:
            MCISoundPlay(soundDir+"gameFailure.wav",false);
            break;
        case SameYetUnlinkable:
            QSound::play(soundDir+"notLinkable.wav");
            break;
        }
    }
}

void GameWindow::MCISoundPlay(QString fileName,bool repeat)
{
    QString command="open "+fileName+" alias media";
    if(backgroundMusicOn){
        char errBuf[255];
        mciSendStringA("stop media",NULL,0,NULL);
        mciSendStringA("close media",errBuf,255,NULL);
        mciSendStringA(command.toAscii(),NULL,0,NULL);
        if(repeat)
            mciSendStringA("play media",NULL,0,NULL);
        else
            mciSendStringA("play media",NULL,0,NULL);
    }
}

void GameWindow::select()
{
    playSound(Select);
}

void GameWindow::sameYetUnlinkable()
{
    playSound(SameYetUnlinkable);
}

//Update the game score if any pair destroyed
//Score for N pair destroyed = multi_hit_num *10
void GameWindow::updateScore(int nHit)
{
    score += 10*nHit;
    ui.scoreLabel->setText(tr("%1").arg(score));
    if(gameMode==Normal)
        addTime();
    if(nHit>1)
        ui.gameHint->setText(tr("连击次数越多，加分越多！加油啦！"));
    playSound(Destroy);
}

void GameWindow::godTouchOn()
{
    ui.gameHint->setText(tr("上帝模式：\n当没有可消的块时自动进入该模式，任何一对同花色块都可以直接消掉"));
}

//Add left time as bonus.
void GameWindow::addTime()
{
    int timeLimit = levels.at(currentLevel).normalTimeLimit;
    timeLeft += 2;
    if(timeLeft>timeLimit){
        timeLeft=timeLimit;
    }
    ui.timeLeft->setValue(timeLeft);
}

void GameWindow::levelOver()
{
    ++currentLevel;
    score +=timeLeft*15;
    killTimer(timerID);
    playSound(LevelSuccess);
    if(isSingleMode){
        ui.levelOverInfo->setText(tr("成功完成本关！分数为 %1").arg(score));
        ui.uiStack->setCurrentIndex(UILevelSuccess);
        ui.nextLevel->setText(tr("返回"));
        return;
    }
    if(currentLevel==levels.size())
        gameOver(Success);
    else{
        ui.levelOverInfo->setText(tr("成功完成本关！"));
        ui.nextLevel->setText(tr("下一关"));
        ui.uiStack->setCurrentIndex(UILevelSuccess);
    }
}

void GameWindow::gameOver(GameOverState state)
{
    if(isAmongTopList(score)){//进入前10
        ui.nameInputEdit->show();
        ui.nameInputLabel->show();
    }else{
        ui.nameInputEdit->hide();
        ui.nameInputLabel->hide();
    }

    switch(state){
        case Success:
            playSound(GameSuccess);
            if(!isAmongTopList(score)){
                ui.gameOverInfo->setText(tr("通关啦！再接再厉，争取进入英雄榜！"));
            }else{
                ui.gameOverInfo->setText(tr("恭喜你成功通关进入英雄榜！"));
            }
            break;
        case Failure:
            playSound(GameFailure);
            if(!isAmongTopList(score)){
                ui.gameOverInfo->setText(tr("哎呀，没赶上呢，再接再厉吧！"));
            }else{
                ui.gameOverInfo->setText(tr("恭喜你进入英雄榜！虽然未能通关，但是我相信以你的实力一定可以的！"));
            }
            break;
        default:
            QMessageBox::warning(this,tr("Error"),
                                 tr("gameOver function called with unexpected parameter"),
                                 QMessageBox::Ok);
    }

    ui.uiStack->setCurrentIndex(UIGameOver);
}

//显示传来的错误消息
void GameWindow::echoError(QString errorMessage)
{
    QMessageBox::information(this,tr("Error"),errorMessage,QMessageBox::Ok);
}

/// [ Settings Operation ]

void GameWindow::readSettings()
{
    QSettings settings;
    theme =settings.value("Theme").toInt();
    Record record;
    for(int i=0;i<normalTopList.size();++i){
        record.name =settings.value(tr("NormalName%1").arg(i)).toString();
        record.score=settings.value(tr("NormalScore%1").arg(i)).toInt();
        normalTopList.insertToTopList(record);
        record.name =settings.value(tr("ChallengeName%1").arg(i)).toString();
        record.score=settings.value(tr("ChallengeScore%1").arg(i)).toInt();
        challengeTopList.insertToTopList(record);
    }
}

void GameWindow::saveSettings()
{
    QSettings settings;
    settings.setValue("Theme",theme);
    Record record;
    for(int i=0;i<normalTopList.size();++i){
        record =normalTopList.at(i);
        settings.setValue(tr("NormalName%1").arg(i),record.name);
        settings.setValue(tr("NormalScore%1").arg(i),record.score);
        record =challengeTopList.at(i);
        settings.setValue(tr("ChallengeName%1").arg(i),record.name);
        settings.setValue(tr("ChallengeScore%1").arg(i),record.score);
    }
    settings.sync();
}


void GameWindow::displayTopList()
{
    QStandardItemModel* normalModel=new QStandardItemModel(0,2,this);
    QStandardItemModel* challengeModel=new QStandardItemModel(0,2,this);
    Record record;
    for(int i=0;i<normalTopList.size();++i){
        record=normalTopList.at(i);
        normalModel->insertRow(i);
        normalModel->setData(normalModel->index(i,0),record.name);
        normalModel->setData(normalModel->index(i,1),record.score);
        record=challengeTopList.at(i);
        challengeModel->insertRow(i);
        challengeModel->setData(challengeModel->index(i,0),record.name);
        challengeModel->setData(challengeModel->index(i,1),record.score);
    }
    ui.normalListView->setModel(normalModel);
    ui.challengeListView->setModel(challengeModel);
}


bool GameWindow::isAmongTopList(int score)
{
    if(gameMode==Normal){
        if(normalTopList.isScoreAmongList(score)<10)
            return true;
    }else{
        if(challengeTopList.isScoreAmongList(score)<10)
            return true;
    }
    return false;
}

void GameWindow::insertToTopList(QString name, int score)
{
    if(gameMode==Normal){
        normalTopList.insertToTopList(name,score);
    }
    if(gameMode==Challenge){
        challengeTopList.insertToTopList(name,score);
    }
}

/// Game Events

void GameWindow::timerEvent(QTimerEvent *event)
{
    if(event->timerId()==timerID){
        timeLeft -=1;
        ui.timeLeft->setValue(timeLeft);
        if(timeLeft == 0){
            --lifeLeft;
            if(lifeLeft ==0){
                killTimer(timerID);
                gameOver(Failure);//Game failure
                return;
            }else{
                ui.lifeLeft->setText(tr("x%1").arg(lifeLeft));
                timeLeft=levelTimeLimit();
                ui.timeLeft->setValue(timeLeft);
                QMessageBox::information(this,tr("提示"),tr("您只剩%1次机会了！\n尝试点击一下右边的小按钮，或许可以帮助到你哦").arg(lifeLeft),QMessageBox::Ok);
                return;
            }
        }
    }
}

void GameWindow::keyPressEvent(QKeyEvent *event)
{
#ifndef  NDEBUG
    if(event->key()==Qt::Key_Space)
        ui.drawArea->autoDestroy();
    if(event->key()==Qt::Key_O)
        this->levelOver();
#endif
}

void GameWindow::closeEvent(QCloseEvent *event)
{
    saveSettings();
    event->accept();
}

int GameWindow::levelTimeLimit()
{
    if(gameMode==Normal)
        return levels.at(currentLevel).normalTimeLimit;
    else
        return levels.at(currentLevel).challengeTimeLimit;
    mciSendStringA("close media",NULL,0,NULL);
}


void GameWindow::topListMouseOver()
{
    ui.selectHintArea->setText(tr("过来看看那些难以超越的成绩吧！"));
}

void GameWindow::aboutMouseOver()
{
    ui.selectHintArea->setText(tr("想知道更多关于程序的信息吗？更多的玩法、更多内容！"));
}

void GameWindow::exitMouseOver()
{
    ui.selectHintArea->setText(tr("你真的想退出游戏吗？"));
}

void GameWindow::on_topList_clicked()
{
    ui.uiStack->setCurrentIndex(UITopList);
    displayTopList();
}

void GameWindow::on_backFromTopList_clicked()
{
    ui.uiStack->setCurrentIndex(UIMain);
}

void GameWindow::on_themeSelect_currentIndexChanged(int index)
{
    theme = index;
    changeTheme(theme);
}

void GameWindow::on_backFromAbout_clicked()
{
    ui.uiStack->setCurrentIndex(UIMain);
}
/// Auto Connected Slots

void GameWindow::on_startGameNormal_clicked()
{
    isSingleMode=false;
    initGame(Normal);
    loadLevel(0);
}

void GameWindow::on_startGameChallenge_clicked()
{
    isSingleMode=false;
    initGame(Challenge);
    loadLevel(0);
}

void GameWindow::on_nextLevel_clicked()
{
    if(isSingleMode){
        isSingleMode = false;
        ui.uiStack->setCurrentIndex(UISelectLevel);
        return;
    }else{
        loadLevel(currentLevel);
        ui.uiStack->setCurrentIndex(UIGame);
    }
}


void GameWindow::on_hintButton_clicked()
{
    if(hintLeft){
        --hintLeft;
        ui.drawArea->hint();
        ui.hintLeft->setText(tr("x%1").arg(hintLeft));
    }
}

void GameWindow::on_disorderButton_clicked()
{
    if(disorderLeft){
        --disorderLeft;
        ui.drawArea->disorder(30);
        ui.disorderLeft->setText(tr("x%1").arg(disorderLeft));
    }
}

void GameWindow::on_pause_clicked()
{
    killTimer(timerID);
    ui.uiStack->setCurrentIndex(UIPause);
}

void GameWindow::on_backToGame_clicked()
{
    timerID=startTimer(1000);
    ui.uiStack->setCurrentIndex(UIGame);
}

void GameWindow::on_back_clicked()
{
    int ret=QMessageBox::information(this,tr("提示"),tr("游戏仍在进行中，你确定要返回主界面吗？"),QMessageBox::Yes,QMessageBox::No);
    if(ret == QMessageBox::Yes){
        killTimer(timerID);
        ui.uiStack->setCurrentIndex(UIMain);
    }
}

void GameWindow::on_successOverReturn_clicked()
{
    if(!ui.nameInputLabel->isHidden()){
        insertToTopList(ui.nameInputEdit->text(),score);
        ui.nameInputEdit->hide();
        ui.nameInputLabel->hide();
    }
    ui.uiStack->setCurrentIndex(UIMain);
}

void GameWindow::on_about_clicked()
{
    ui.uiStack->setCurrentIndex(UIAbout);
}

void GameWindow::on_exit_clicked()
{
    this->close();
}

void GameWindow::startGameMouseOver()
{
    ui.selectHintArea->setText(tr("用鼠标分别选定两个相同的图案，如果它们可以用一条两折之内的折线相连即可将其消除，在上方的时间条结束之前消除所有图案即可胜利\n游戏中如果出现无块可消的情况，会自动进入无敌模式，这时任何相同的图案都可以直接消除"));
}

void GameWindow::challengeModeMouseOver()
{
    ui.selectHintArea->setText(tr("每一关的时间一定，即使成功消块也不会使时间增加"));
}

void GameWindow::execiseModeMouseOver()
{
    ui.selectHintArea->setText(tr("在练习模式下，您可以选择单独的一个关卡来练习，每个关卡依旧可以以“普通模式”或“挑战模式”开始"));
}

void GameWindow::on_execiseMode_clicked()
{
    ui.uiStack->setCurrentIndex(UISelectLevel);
}

void GameWindow::on_toolButton_clicked()
{
    ui.uiStack->setCurrentIndex(UIMain);
}

void GameWindow::on_levelListWidget_itemEntered(QListWidgetItem *item)
{

}

void GameWindow::on_singleLevelNormal_clicked()
{
    int levelIndex=ui.levelListWidget->currentIndex().row();
    isSingleMode=true;
    initGame(Normal);
    loadLevel(levelIndex);
}

void GameWindow::on_singleLevelChallenge_clicked()
{
    int levelIndex=ui.levelListWidget->currentIndex().row();
    isSingleMode=true;
    initGame(Challenge);
    loadLevel(levelIndex);
}

void GameWindow::on_musicSwitch_clicked(bool checked)
{
    foregroundMusicOn = checked;
    if(checked)
        ui.statusForegroundMusic->setText(tr("开"));
    else
        ui.statusForegroundMusic->setText(tr("关"));
}

void GameWindow::on_backgroundMusicSwitch_clicked(bool checked)
{
    backgroundMusicOn = checked;
    if(checked){
        mciSendStringA("play media",NULL,0,NULL);
        ui.statusBackgroundMusic->setText(tr("开"));
    }else{
        mciSendStringA("pause media",NULL,0,NULL);
        ui.statusBackgroundMusic->setText(tr("关"));
    }
}
