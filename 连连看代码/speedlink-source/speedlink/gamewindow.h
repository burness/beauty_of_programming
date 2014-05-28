#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>
#include "public-header.h"
#include "drawarea.h"
#include "ui_gamewindow.h"
#include "toplist.h"

namespace Ui{
    class GameWindow;
}


struct Level{
    char levelName[255];
    int normalTimeLimit;
    int challengeTimeLimit;
    Map mapData;
};

enum GameOverState{
    Success,
    Failure
};

enum GameMode{
    Normal,
    Challenge
};

enum SoundSituation{
    Select,
    Destroy,
    LevelSuccess,
    GameSuccess,
    GameFailure,
    SameYetUnlinkable
};

#define   Golden  0
#define   SkyBlue (Golden+1)
#define   Pink    (Golden+2)


class QStandardItemModel;

class GameWindow : public QMainWindow,public Ui::GameWindow
{
    Q_OBJECT
public:
    explicit GameWindow(QWidget *parent = 0);

    void initGame(GameMode );
    void loadLevel(int levelIndex);
    void loadLevelFromFile(QString fileName);
private slots:
    /// Game Operation Slots
    void select();
    void sameYetUnlinkable();
    void updateScore(int nHit);
    void godTouchOn();
    void addTime();
    void levelOver();
    void gameOver(GameOverState);
    void echoError(QString);

    ///  MyOwn MouseOver Slots
    void startGameMouseOver();
    void challengeModeMouseOver();
    void execiseModeMouseOver();
    void topListMouseOver();
    void aboutMouseOver();
    void exitMouseOver();

    /// Auto Connected Slots
    void on_startGameNormal_clicked();
    void on_startGameChallenge_clicked();
    void on_nextLevel_clicked();
    void on_hintButton_clicked();
    void on_disorderButton_clicked();
    void on_pause_clicked();
    void on_backToGame_clicked();
    void on_back_clicked();
    void on_successOverReturn_clicked();
    void on_about_clicked();
    void on_exit_clicked();
    void on_topList_clicked();
    void on_backFromTopList_clicked();
    void on_themeSelect_currentIndexChanged(int index);

    void on_backFromAbout_clicked();

    void on_execiseMode_clicked();

    void on_toolButton_clicked();

    void on_levelListWidget_itemEntered(QListWidgetItem *item);

    void on_singleLevelNormal_clicked();

    void on_singleLevelChallenge_clicked();

    void on_musicSwitch_clicked(bool checked);

    void on_backgroundMusicSwitch_clicked(bool checked);

protected:
    void timerEvent(QTimerEvent *);
    void keyPressEvent(QKeyEvent *);
    void closeEvent(QCloseEvent *);
private:
    void createLevelList();
    void changeTheme(int type);
    void playSound(SoundSituation situation);
    void MCISoundPlay(QString fileName,bool repeat=true);

    /// TopList Operation
    void readSettings();
    void saveSettings();
    void displayTopList();
    bool isAmongTopList(int score);
    void insertToTopList(QString name,int score);

    int levelTimeLimit();

    int timerID;
    QVector<Level>levels;
    TopList normalTopList;
    TopList challengeTopList;
    int theme;

    /// Runtime Attributes
    GameMode gameMode;
    bool isSingleMode;
    int currentLevel;
    int score;
    int timeLeft;
    int lifeLeft;
    int disorderLeft;
    int hintLeft;
    bool backgroundMusicOn;
    bool foregroundMusicOn;
    /// UI Elements
    Ui::GameWindow ui;
};

#endif // GAMEWINDOW_H
