#ifndef __Defence_Positioning_H
#define __Defence_Positioning_H

#include <WorldData.h>
#include <BasicUtils.h>
#include <BasicPlayer.h>
#include <cstring>

class DefPos {
public:
	DefPos(WorldData* newWorldData, BasicPlayer* newBasicPlayer, int uids[],int defenersNum);
        DefPos();
        void initializeWorld(WorldData* newWorldData, BasicPlayer* newBasicPlayer, int uids[],int defenersNum);
	//deciders::
	void decideXLine();
	void decideLength();
	void decideYLine();
	void definePoints();
        void forceDefPosNOW();
        void forceResult();

	//   int nearestPlayer(Point place);

	int resultnum; //number of ordered robots
	int resultId;
	Point resultPos;

	int botnum; //number of robots

	int usednum; //number of used uids
	int uidList[6];

private:

	WorldData* pWorldData;
	BasicPlayer* pBasicPlayer;

	double botSize; //andazeye har robot

	char area;

	double fieldTool;
	double fieldArz;
	double aviliableTool; //yani dar kol (ba position haye mokhtalefe ball)
	//defenceline cheghadr mitavanad jabejaii dashte bashad

	double availableArz; //yani defence line chand vahed (ehtemalan px) ast (az bala be paiin)

	double ballX;
	double ballY;

	// int usedUids[6];



	double xLine;
	//balatarin makan e Y
	double y1Line;

	struct Ptp //put to point
	{
		Point pos[4];
		double sum;
	};

	Point avp[6]; //computed points for defensers

};
#endif