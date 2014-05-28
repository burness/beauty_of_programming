#ifndef TOPLIST_H
#define TOPLIST_H

#include <QTextStream>
#include <QSettings>
#include <QStringList>
#include <QString>
#include <QVector>
#include <QList>

const int MaxTopListSize=15;

struct Record
{
    Record(QString name_,int score_):name(name_),score(score_){}
    Record(){}
    QString name;
    int score;
};

class TopList
{
public:
    TopList(){
        Record nullRecord("",0);
        for(int i=0;i<MaxTopListSize;++i){
            topList.push_back(nullRecord);
        }
    }
    TopList(QStringList nameList,QList<int> scoreList){
        for(int i=0;i<MaxTopListSize && i<nameList.size();++i){
            Record record(nameList.at(i),scoreList.at(i));
            topList.push_back(record);
        }
    }
    void loadFromList(QStringList nameList,QList<int> scoreList){
        for(int i=0;i<MaxTopListSize && i<nameList.size();++i){
            Record record(nameList.at(i),scoreList.at(i));
            insertToTopList(record);
        }
    }
    int isScoreAmongList(int score){
        for(int i=0;i<topList.size();++i){
            if(topList.at(i).score<score)
                return i;
        }
        return -1;
    }

    bool insertToTopList(QString name,int score){
        for(int i=0;i<topList.size();++i){
            if(topList.at(i).score<score){
                topList.insert(i,Record(name,score));
                topList.erase(topList.end()-1);
                return true;
            }
        }
        return false;
    }

    bool insertToTopList(Record record){
        for(int i=0;i<topList.size();++i){
            if(topList.at(i).score<=record.score){
                topList.insert(i,record);
                topList.erase(topList.end()-1);
                return true;
            }
        }
        return false;
    }

    QStringList nameList(){
        QStringList list;
        for(QVector<Record>::iterator i=topList.begin();
            i != topList.end(); ++i){
            list.push_back(i->name);
        }
        return list;
    }
    QList<int> scoreList(){
        QList<int> list;
        for(QVector<Record>::iterator i=topList.begin();
            i != topList.end(); ++i){
            list.push_back(i->score);
        }
        return list;
    }

    Record at(int i){
        return topList.at(i);
    }

    int size(){
        return topList.size();
    }

    /// [ Test ]
    void printList(){
        QTextStream out(stdout);
        out<<endl<<"List Size: "<<topList.size()<<endl;
        QVector<Record>::iterator i;

        for(i=topList.begin();i!=topList.end();++i)
            out<<i->name<<"        "<<i->score<<endl;
    }

private:
    QVector<Record> topList;
};

#endif // TOPLIST_H
