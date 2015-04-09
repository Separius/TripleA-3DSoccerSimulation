#ifndef PLANB_H
#define	PLANB_H

#include <iostream>
#include <WorldData.h>
#include <BasicPlayer.h>
#include <OffensePositioning.h>
#include <DefencePositioning.h>
#include <Goalie.h>
#include <Dribble.h>
#include <Block.h>

#include "Primitives.h"

#define OWNER_ME 1
#define OWNER_TEAMMATE 2
#define OWNER_OPP 3
#define OWNER_NOONE 4

#define MR_ROLE_UNKNOWN 0
#define MR_ROLE_GOALIE 1
#define MR_ROLE_DEFENCE 2
#define MR_ROLE_OFFENCE 3

class PlanBackUp
{
public:
    PlanBackUp(WorldData* newWorldData, BasicPlayer* newBasicPlayer);
    Primitives prePlane;
    Goalie goalKeeper;
    void start();

private:
    WorldData* pWorldData;
    BasicPlayer* pBasicPlayer;
    Primitives  PlanePrimitives;
    int myUid;
};

#endif	/* PLANB_H */
