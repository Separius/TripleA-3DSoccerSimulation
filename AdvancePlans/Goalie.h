#ifndef _GOALIE_H
#define _GOALIE_H

#include <BasicPlayer.h>
#include <WorldData.h>
#include <Pass.h>
#include <Clear.h>

class Goalie
{
	public:
		Goalie(WorldData* newWorldData,BasicPlayer* newBasicPlayer);
                Goalie ();
                void initializeData(WorldData* newWorldData, BasicPlayer* newBasicPlayer);
		float getPassValue();
		float getClearValue();
//		int nearstOppToBall();
		void doPass();
		void doClear();
		void doPositioning();
		void doGo();
		void decide();
	private:
		WorldData* pWorldData;
		BasicPlayer* pBasicPlayer;

};
#endif