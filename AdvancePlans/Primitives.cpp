#include <Primitives.h>

Primitives::Primitives(WorldData* newWorldData, BasicPlayer* newBasicPlayer)
{
    initializeWorld(newWorldData, newBasicPlayer);
}

Primitives::Primitives()
{
}

void
Primitives::initializeWorld(WorldData* newWorldData, BasicPlayer* newBasicPlayer)
{
    pWorldData = newWorldData;
    pBasicPlayer = newBasicPlayer;

    //initializing...
    ballPos = pWorldData->basedCenter(pWorldData->ball());
    actPass.initializeData(newWorldData, newBasicPlayer);
    actBlock.initializeWorld(newWorldData, newBasicPlayer);
    actClear.initializeData(newWorldData, newBasicPlayer);
    actShoot.initializeData(newWorldData, newBasicPlayer);
    actDribble.initializeData(newWorldData, newBasicPlayer);
    am_I_Near();
    owner = whoIsOwner();
    setFormation();
}

int Primitives::whoIsOwner()
{
    bool found = false;
    int tempowner;
    std::vector<int> teamms = pWorldData->mr_found_teammates();
    std::vector<int> opponts = pWorldData->mr_found_opponents();

    cout << "owner  me ? " << ballPos.getDistance(pWorldData->me(true)) << endl;
    if (ballPos.getDistance(pWorldData->me(true)) <= 36)
    {
        tempowner = OWNER_ME;
        found = true;
        return tempowner;
    }

    Point tmm;
    if (found == false)
    {
        for (int i = 0; i < teamms.size(); i++)
        {
            tmm = pWorldData->teammatePos[i];
            if (ballPos.getDistance(tmm) <= 36)
            {
                found = true;
                tempowner = OWNER_TEAMMATE;
                return tempowner;
                break;
            }
        }
    }

    if (found == false)
    {
        for (int i = 0; i < opponts.size(); i++)
        {

            if (ballPos.getDistance(pWorldData->oppPositions[i]) <= 36)
            {
                found = true;
                tempowner = OWNER_OPP;
                return tempowner;
                break;
            }
        }
    }

    if (found == false)
    {
        tempowner = OWNER_NOONE;
        return tempowner;
    }
    cout << "owner : " << owner << endl;
}

void Primitives::am_I_Near()
{
    Point Me;
    Me = pWorldData->me(true);
    if (ballPos.getDistance(Me) < 200)
        am_i_near = true;
    else am_i_near = false;
}

bool Primitives::isPassingToMe()
{
    actPass.setUid(owner);
    actPass.bestTeammateSelector();
    if (actPass.bestTeammate == pWorldData->my_id())
        return true;
    return false;
}

void Primitives::setFormation()
{
    char side; //our side

    if (pWorldData->ourPole1.getX() > 0)
        side = 'r';
    else
        side = 'l';
    cout << "side : " << side << std::endl;

    cout << "<Lunched>set formation</Lunched>\n";
    pWorldData->mrRoles[0] = MR_ROLE_GOALIE;
    cout << "pWorldData->mrRoles[0] " << pWorldData->mrRoles[0] << std::endl;

    int defenders[3]; //uids
    int defendersNum;

    int ofenders[3]; //uids
    int ofendersNum;

    double tempX;
    //*/ tempX = pWorldData->basedCenter(pWorldData->mrTopLeftCorner()).getX();
    double ballX = pWorldData->basedCenter(pWorldData->ball()).getX();
    tempX = pWorldData->realVectors[11].getX();
    ballX = ballX - tempX;
    //agar biroon e zamin bood haman 0 dar nazar migirimash
    if (ballX < 0)
    {
        ballX = 0;
    }
    int tmmids[5];

    if (pWorldData->my_id() >= 5)
    {
        for (int i = 5; i <= 9; i++)
            tmmids[i % 5] = i;
    }
    else if (pWorldData->my_id() < 5)
    {
        for (int i = 0; i <= 4; i++)
            tmmids[i] = i;
    }

    if (ballX <= (pWorldData->fieldTool() / 3))
    {
        if (side == 'l')
        {
            ofenders[0] = tmmids[4];
            defenders[0] = tmmids[1];
            defenders[1] = tmmids[2];
            defenders[2] = tmmids[3];

            pWorldData->mrRoles[tmmids[4]] = MR_ROLE_OFFENCE;
            pWorldData->mrRoles[tmmids[1]] = MR_ROLE_DEFENCE;
            pWorldData->mrRoles[tmmids[2]] = MR_ROLE_DEFENCE;
            pWorldData->mrRoles[tmmids[3]] = MR_ROLE_DEFENCE;



            ofendersNum = 1;
            defendersNum = 3;
        }
        else if (side == 'r')
        {
            ofenders[0] = tmmids[4];
            ofenders[1] = tmmids[3];
            ofenders[2] = tmmids[2];
            defenders[0] = tmmids[1];

            pWorldData->mrRoles[tmmids[1]] = MR_ROLE_DEFENCE;
            pWorldData->mrRoles[tmmids[2]] = MR_ROLE_OFFENCE;
            pWorldData->mrRoles[tmmids[3]] = MR_ROLE_OFFENCE;
            pWorldData->mrRoles[tmmids[4]] = MR_ROLE_OFFENCE;

            ofendersNum = 3;
            defendersNum = 1;

        }
    }
    else if (ballX > (pWorldData->fieldTool() / 3) && ballX
            <= (pWorldData->fieldTool() * 2 / 3))
    {
        cout << "2/3 \n";
        if (owner == OWNER_ME || owner == OWNER_TEAMMATE)
        {
            ofenders[0] = tmmids[4];
            defenders[0] = tmmids[1];
            defenders[1] = tmmids[2];

            pWorldData->mrRoles[tmmids[4]] = MR_ROLE_OFFENCE;
            pWorldData->mrRoles[tmmids[1]] = MR_ROLE_DEFENCE;
            pWorldData->mrRoles[tmmids[2]] = MR_ROLE_DEFENCE;
            pWorldData->mrRoles[tmmids[3]] = MR_ROLE_MIDDLE;

            ofendersNum = 1;
            defendersNum = 2;
        }
        else
        {
            ofenders[0] = tmmids[4];
            ofenders[1] = tmmids[3];
            defenders[0] = tmmids[1];

            pWorldData->mrRoles[tmmids[1]] = MR_ROLE_DEFENCE;
            pWorldData->mrRoles[tmmids[3]] = MR_ROLE_OFFENCE;
            pWorldData->mrRoles[tmmids[4]] = MR_ROLE_OFFENCE;
            pWorldData->mrRoles[tmmids[2]] = MR_ROLE_MIDDLE;


            ofendersNum = 2;
            defendersNum = 1;
        }

    }
    else if (ballX > (pWorldData->fieldTool() * 2 / 3))
    {
        cout << "3/3 \n";
        if (side == 'r')
        {
            ofenders[0] = tmmids[4];
            defenders[0] = tmmids[1];
            defenders[1] = tmmids[2];
            defenders[2] = tmmids[3];

            pWorldData->mrRoles[tmmids[4]] = MR_ROLE_OFFENCE;
            pWorldData->mrRoles[tmmids[1]] = MR_ROLE_DEFENCE;
            pWorldData->mrRoles[tmmids[2]] = MR_ROLE_DEFENCE;
            pWorldData->mrRoles[tmmids[3]] = MR_ROLE_DEFENCE;

            ofendersNum = 1;
            defendersNum = 3;
        }
        else if (side == 'l')
        {
            ofenders[0] = tmmids[4];
            ofenders[1] = tmmids[3];
            ofenders[2] = tmmids[2];
            defenders[0] = tmmids[1];

            pWorldData->mrRoles[tmmids[1]] = MR_ROLE_DEFENCE;
            pWorldData->mrRoles[tmmids[2]] = MR_ROLE_OFFENCE;
            pWorldData->mrRoles[tmmids[3]] = MR_ROLE_OFFENCE;
            pWorldData->mrRoles[tmmids[4]] = MR_ROLE_OFFENCE;

            ofendersNum = 3;
            defendersNum = 1;

        }

    }

    actDefence.initializeWorld(pWorldData, pBasicPlayer, defenders, defendersNum);
    if (side == 'r')
        side = 'l';
    else if (side == 'l')
        side = 'r';
    actOffence.initializeWorld(pWorldData, pBasicPlayer, ofenders,
            ofendersNum);

    actDefence.forceDefPosNOW();

    actOffence.position();
}

bool Primitives::shouldITry(Point target)
{
    //    cout<<"should I try lunched\n";
    Point Me;
    Me.x = pWorldData->me(true).getX();
    Me.y = pWorldData->me(true).getY();

    std::vector<int> tmms = pWorldData->mr_found_teammates();

    float minDist = 1000;
    Point tmm;

    for (int i = 0; i < tmms.size(); i++)
    {
        tmm = pWorldData->teammatePos[i];
        if (tmm.getDistance(target) < minDist)
            minDist = tmm.getDistance(target);

    }

    if (Me.getDistance(target) < minDist && minDist <= 200)
    {
        return true;
        //        cout << "Going to the Target....\n";
    }
    return false;
}

//designed for force

Point Primitives::PositionMe()
{
    int myUid = pWorldData->my_id();
    int oppNum = pWorldData->mr_number_found_opponents();
    if (pWorldData->mrRoles[myUid] == MR_ROLE_DEFENCE)
    {
        pWorldData->teamAction[myUid % oppNum] = ACTION_DEFPOS;
        return actDefence.resultPos;
    }
    else if (pWorldData->mrRoles[myUid] == MR_ROLE_OFFENCE)
    {
        pWorldData->teamAction[myUid % oppNum] = ACTION_OFSPOS;
        return actOffence.resultPos;
    }
    else if (pWorldData->mrRoles[myUid] == MR_ROLE_MIDDLE)
    {

    }
}

int Primitives::whichAct()
{
    actShoot.pointSelector();
    if (actShoot.can_i_shoot)
    {
        //actShoot.shootNow();
        return 1; //shooting
        cout << "shooting....\n";
    }
    else
    {
        actPass.setUid(pWorldData->my_id());
        actPass.bestTeammateSelector();
        actDribble.targetFinder();
        actClear.pointSelector();

        if (actPass.passLastValue() == 100 || (actPass.passLastValue()
                >= actDribble.dribbleLastValue() && actPass.passLastValue()
                >= 50))
        {
            return 2; //passing
            //actPass.passNow();
            cout << "Passing....\n";
        }
        else if (actDribble.dribbleLastValue() == 100
                || (actDribble.dribbleLastValue() >= actClear.clearLastValue()
                && actDribble.dribbleLastValue() >= 50))
        {
            return 3;
            //actDribble.decide();
            cout << "dribbling....\n";
        }
        else
        {
            return 4;
            //actClear.clearNow();
            cout << "clearing....\n";
        }
    }
}

