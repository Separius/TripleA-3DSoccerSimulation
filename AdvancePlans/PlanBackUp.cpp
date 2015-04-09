#include<PlanBackUp.h>

using namespace std;

PlanBackUp::PlanBackUp(WorldData* newWorldData, BasicPlayer* newBasicPlayer)
{
    pWorldData = newWorldData;
    pBasicPlayer = newBasicPlayer;
    PlanePrimitives.initializeWorld(newWorldData, newBasicPlayer);
    myUid = pWorldData->my_id();
    prePlane.initializeWorld(newWorldData, newBasicPlayer);
    goalKeeper.initializeData(pWorldData, pBasicPlayer);
}

void PlanBackUp::start()
{
    if (myUid == 0 || myUid == 5) //I am the goalie
    {
        goalKeeper.decide();
        cout << "being goalie....\n";
    }
    else
    {
        if (prePlane.am_i_near == false)
        {
            Point posit = prePlane.PositionMe();
            pBasicPlayer->go(posit);
            cout << "positioning....\n";
        }
        else
        {
            // owner = whoIsOwner();
            cout << "***Owner is : " << prePlane.owner << endl;
            if (prePlane.owner == OWNER_ME)
            {
                cout << "I am owner\n";
                int actNum = prePlane.whichAct();

                if (actNum == 1)
                {
                    prePlane.actShoot.shootNow();
                    cout << "Shooting...\n";
                }
                else if (actNum == 2)
                {
                    prePlane.actPass.passNow();
                    cout << "Passing...\n";
                }
                else if (actNum == 3)
                {
                    prePlane.actDribble.decide();
                    cout << "Dribbling...\n";
                }
                else if (actNum == 4)
                {
                    prePlane.actClear.clearNow();
                    cout << "clearing...\n";
                }
            }
            else if (prePlane.owner == OWNER_TEAMMATE)
            {
                if (prePlane.isPassingToMe() == true)
                {
                    pBasicPlayer->stop();
                    cout << "recieving a pass...\n";
                }
                else
                {
                    if (pWorldData->mrRoles[myUid] == MR_ROLE_MIDDLE)
                    {
                        pBasicPlayer->go(prePlane.ballPos);
                        cout<<"middle capturing the ball...\n";
                    }
                    else
                    {
                        Point posit = prePlane.PositionMe();
                        pBasicPlayer->go(posit);
                        cout << "Positioning...\n";
                    }
                }
            }
            else
            {
                cout << "should I try to recievie the ball ?\n";
                if (prePlane.shouldITry(prePlane.ballPos) == true)
                {
                    pBasicPlayer->go(prePlane.ballPos);
                }
            }
        }
    }
}
