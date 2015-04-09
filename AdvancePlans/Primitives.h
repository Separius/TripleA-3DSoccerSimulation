#ifndef _PRIMITIVES_H
#define _PRIMITIVES_H

#include <BasicPlayer.h>
#include <WorldData.h>
#include <Block.h>
#include <DefencePositioning.h>
#include <OffensePositioning.h>
#include <Shoot-cir.h>
#include <Pass.h>
#include <Clear.h>
#include <Dribble.h>

#define ROLE_SITUATION_MINE 1
#define ROLE_SITUATION_TEAMMATE 2
#define ROLE_SITUATION_OPP 3
#define ROLE_SITUATION_NOONE 4

#define OWNER_ME 1
#define OWNER_TEAMMATE 2
#define OWNER_OPP 3
#define OWNER_NOONE 4

#define MR_ROLE_UNKNOWN 0
#define MR_ROLE_GOALIE 1
#define MR_ROLE_DEFENCE 2
#define MR_ROLE_OFFENCE 3
#define MR_ROLE_MIDDLE 4

class Primitives
{
public:
	Primitives(WorldData* newWorldData, BasicPlayer* newBasicPlayer);
	Primitives();
	void initializeWorld(WorldData* newWorldData, BasicPlayer* newBasicPlayer);
	//functions :
	void setFormation();
	int whoIsOwner();
	void am_I_Near();
	bool shouldITry(Point target);
	Point PositionMe();
        bool isPassingToMe();
	/* @1 => shooting
	 * @2 => passing
	 * @3 => dribbling
	 * @4 => clearing
	 */
	int whichAct();
	Shoot actShoot;
	Pass actPass;
	Clear actClear;
	Dribble actDribble;
	Block actBlock;
	DefPos actDefence;
	OfsPos actOffence;

	//variables
	bool am_i_near;
	Point ballPos;
	int owner;// 1 for me | 2 for team | 3 for Opp | 4 for noOne

private:
	WorldData* pWorldData;
	BasicPlayer* pBasicPlayer;
};
#endif