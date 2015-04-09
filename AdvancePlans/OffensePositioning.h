#ifndef _OFFENSEPOSITIONING_H
#define _OFFENSEPOSITIONING_H

#include <WorldData.h>
#include <BasicUtils.h>
#include <BasicPlayer.h>
#include <Rectangle.h>
#include <Pass.h>
#include <Shoot-cir.h>

//findes uids of opponents defencers & goali :D

class OppDefencers {
public:
    //  OppDefencers(WorldData* newWorldData , BasicPlayer* newBasicPlayer , char areaofopp);
    void setData(WorldData* newWorldData, BasicPlayer* newBasicPlayer,
            char areaofopp);
    void findthem(); //har dafe (cycle) bayad ejra she ta id defencer ha va goaler ro update kone
    void findGoaler();

    int goaler; //id e goaler
    int uidList[6]; // id e defencer ha
    int uidnumbers; // tedade defencer ha

private:
    WorldData* pWorldData;
    BasicPlayer* pBasicPlayer;
    char area; //opponent ha too kodoom nimeye zamin hastand 'l' ya 'r'

};
//********************************************************/

class OfsPos {
private:
    WorldData* pWorldData;
    BasicPlayer* pBasicPlayer;
    char area; //opponent ha too kodoom nimeye zamin hastand 'l' ya 'r'

    //int oppDef; //tedade defencer haye opponent ha

    int uidList[4]; //id oon teammate haii ke offencer hastand
    int* uidStart;
    int offencer_num; // tedade oon teammate haii ke offencer hastand
    OppDefencers myOpp; //baraye taiin e tedad va id defencer haye opponent

    int usednum; //number of used uids (used for finding nearest teammate to a point)
    int usedUids[4];

private:

    struct Ptp //put to point
    {
        Point pos[4];
        double sum;
    };

    Point avp[4]; //computed points for defensers

    double ballX, ballY;
    double initializeX();
    Point firstOffender(int offset);
    int mycount; //which offencer am I ? first  second or third


public:
    OfsPos(WorldData* newWorldData, BasicPlayer* newBasicPlayer, int uids[], int defenersNum);
    OfsPos();
    void initializeWorld(WorldData* newWorldData, BasicPlayer* newBasicPlayer, int uids[], int defenersNum);
    // void opp_num_defencers();
    void position(); //taine position e offencer ha

    float aviliableTool;

    /**********IMPORTANT VARIABLE*************/
    /****************************************/
    //order:: order to go and position
    int resultnum; //number of ordered robots
    int resultId; //id of  ordered robots
    Point resultPos; //position of ordered robots
};
#endif