#include <DefencePositioning.h>

/* IMPORTANT
 * about uidList[] and uid array:
 * you have to give it an array with 6 blocks
 * and fill it with defencers uid's from [0]
 * IMPORTANT
 */
using namespace std;

DefPos::DefPos()
{
}

DefPos::DefPos(WorldData* newWorldData, BasicPlayer* newBasicPlayer,
        int uids[], int defenersNum)
{
    initializeWorld(newWorldData, newBasicPlayer, uids, defenersNum);

}

void
DefPos::initializeWorld(WorldData* newWorldData, BasicPlayer* newBasicPlayer, int uids[], int defenersNum)
{
    pWorldData = newWorldData;
    pBasicPlayer = newBasicPlayer;

    //size of the field
    fieldTool = pWorldData->fieldTool();
    fieldArz = pWorldData->fieldArz();
    //   cout<<"field tool   "<<fieldTool<<endl;
    // cout<<"field arz    "<<fieldArz<<endl;
    //team e ma dar kodam field ast
    if (pWorldData->ourPole1.getX() > 0)
        area = 'r';
    else
        area = 'l';

    //tedade nafarati ke barashoon Point moshakhas kardam
    resultnum = 0;
    //shomare e uid haye defencer ha
    //uid list ye pointer ast

    for (int i = 0; i < defenersNum; i++)
    {
        uidList[i] = uids[i];
        // cout << "uidlist[i] == " << uidList[i] << endl;
    }

    //tedad e defencer ha
    botnum = defenersNum;

    //khali kardan e list e uid haye estefade shode

    //seting up flags for use

    //Max 7 Min makene momken baraye defencer ha
    //in do baraye taiin e availableTool estefade mishavand
    double minX;
    double maxX;

    if (area == 'l' || area == 'L')
    {
        //*/ minX = pWorldData->basedCenter(pWorldData->mrTopLeftSmallArea()).getX();
        //*/ maxX = pWorldData->basedCenter(pWorldData->mrMiddleField()).getX();
        minX = pWorldData->realVectors[14].getX();
        maxX = pWorldData->realVectors[9].getX();
    }
    else if (area == 'r' || area == 'R')
    {
        //*/ maxX = pWorldData->basedCenter(pWorldData->mrTopRightSmallArea()).getX();
        //*/ minX = pWorldData->basedCenter(pWorldData->mrMiddleField()).getX();
        maxX = pWorldData->realVectors[18].getX();
        minX = pWorldData->realVectors[9].getX();
    }
    aviliableTool = maxX - minX;
    //        cout<<"avaailable tool : "<<aviliableTool<<endl;
    //based center e ball moshkel dare

    //tabdil e origin az markaz e zamin be gooshe ye bala chap
    double tempX;
    //*/ tempX = pWorldData->basedCenter(pWorldData->mrTopLeftCorner()).getX();
    ballX = pWorldData->basedCenter(pWorldData->ball()).getX();
    tempX = pWorldData->realVectors[11].getX();
    ballX = ballX - tempX;
    //agar biroon e zamin bood haman 0 dar nazar migirimash
    if (ballX < 0)
    {
        ballX = 0;
    }
    // cout<<"ballx top left(0,0):  "<<ballX<<endl;


    double tempY; //*/= pWorldData->basedCenter(pWorldData->mrTopLeftCorner()).getY();
    tempY = pWorldData->realVectors[11].getY();
    ballY = pWorldData->basedCenter(pWorldData->ball()).getY();
    //    cout<<"<ball>\n"<<"<y>\n"<<"<basedcenter>"<<ballY<<"</basedcenter>\n";
    ballY = tempY - ballY;
    //agar biroon e zamin bood haman 0 dar nazar migirimash
    if (ballY < 0)
    {
        ballY = 0;
    }
    //cout<<"ball pos : "<<ballX<<" , "<<ballY<<endl;
    //        cout<<"ball "<<ballX<<" , "<<ballY<<endl;
    // cout<<"<topleft>"<<ballY<<"<topleft>\n"<<"</y>\n"<<"</ball>\n";

}

/* tain e meakan e 'X' khate defence
 * -------------------------------
 * agar samte chap e zamin boodim
 * az mrLeftSmallArea ta miidle of the field
 * agar ballX == 0 bashad khate defence bayad rooye small area bashad
 * agar ballX == fieldTool bashad khate Defence bayad rooye khate middle bashad
 * -----------------------------------
 * agar samte rast boodim az middle of the field
 * ta mrRightAmallArea
 */
void DefPos::decideXLine()
{

    /*
     * inja ball based center nist  ta ba field tool khonsa shavad
     */

    if (area == 'l' || area == 'L')
    {
        xLine = (aviliableTool / fieldTool) * ballX + pWorldData->realVectors[14].getX();
        xLine -= 100;
        //*/ xLine = (aviliableTool / fieldTool) * ballX + pWorldData->basedCenter(pWorldData->mrTopLeftSmallArea()).getX();
    }
    else if (area == 'r' || area == 'R')
    {
        xLine = (aviliableTool / fieldTool) * ballX + pWorldData->realVectors[9].getX();
        xLine += 100;
        //*/ xLine = (aviliableTool / fieldTool) * ballX + pWorldData->basedCenter(pWorldData->mrMiddleField()).getX();
    }
    //    cout<<"X line : "<<xLine<<endl;
    /*cout << "middlefield: " << pWorldData->mrMiddleField().length << endl;
     cout << "middelefield.getx  : " << pWorldData->basedCenter(
     pWorldData->mrMiddleField()).getX() << endl;*/
    //     cout << "field tool:" << fieldTool << endl;
    //     cout<<"field tool world data "<<pWorldData->fieldTool()<<endl;
    //     cout << "avtool : " << aviliableTool << endl;
    //     cout << "ball: " << ballX << endl;
    //     cout<<"area : "<<area<<endl;
    //     cout<<"realVector[14] : "<<pWorldData->realVectors[14].getX()<<endl;
    //     cout<<"zarbeshoon : "<<(double)(aviliableTool / fieldTool) <<endl;
    //    cout << "Xline : " << xLine<< endl;

}

// tool e defenceLine ro taiin mikonea>:

void DefPos::decideLength()
{
    botSize = 22;
    Point temp1;
    Point temp2;

    double minTool;
    double maxTool;

    /* tavajoh::
     * in temp1 & temp2 be 'area' bastegi nadarad
     * chon faghat tool e darvaze ro bedast miavarim */
    //*/ temp1 = pWorldData->basedCenter(pWorldData->mrTopLeftPole());
    //*/ temp2 = pWorldData->basedCenter(pWorldData->mrBottomLeftPole());

    temp1 = (Point) pWorldData->realVectors[13];
    temp2 = (Point) pWorldData->realVectors[3];

    //min tool baraye vaghti ast ke x e DefenceLine rooye kamtarin meghdar (nazdik be darvaze) bashad
    minTool = temp1.getDistance(temp2);

    //*/ temp1 = pWorldData->basedCenter(pWorldData->mrTopCenter());
    //*/ temp2 = pWorldData->basedCenter(pWorldData->mrBottomCenter());
    temp1 = (Point) pWorldData->realVectors[10];
    temp2 = (Point) pWorldData->realVectors[0];

    //yani dar vasat e zamin Max e  length e defenceLine kamtar az fieldArz abshad
    //addad e 50 ke az khodam daravarodam hamin ro neshoon mideh
    maxTool = temp1.getDistance(temp2) - 100;
    if (area == 'l' || area == 'L')
    {

        availableArz = ((maxTool - minTool) / fieldTool) * ballX + minTool;
    }
    else if (area == 'r' || area == 'R')
    {
        availableArz = maxTool - ((maxTool - minTool) / fieldTool) * ballX;
    }
    //agar dar availablearz e taiin shode jaye kefi baraye istadan e robot ha nabashad
    //be andaze ye kafi arz ro zia kon
    if (availableArz < botnum * botSize)
        availableArz += (botnum * botSize) - availableArz;
    availableArz -= 100;

    //    cout << "availableArz : " << availableArz << endl;

}

void DefPos::decideYLine()
{
    /* agar ballY == 0  bashad y1Line ke makane balaye line ro taiin mikonad
     * bayad barabar e 10 bashad
     * albate '10 ro az khodam dar avordam va
     * karbordesh in ast ke defencer ha biroon e zamin naravand
     * ----------------------------------------------------------------------
     * agar ballY == fieldArz bashad y2Line bayad 10 (10 ro az khodam dar avordam)
     * vahed (px) balatar az fieldArz bashad ta defencer biroon e zamin  naravd
     * dar naije y1Line bayad barabae e meghdar e zir bashad
     */

    //y1 bar asas e top left ast (0,0)
    y1Line = (((fieldArz - (availableArz + 20)) / fieldArz) * ballY) + 10;

    //    cout << "<yline>" << y1Line<<"</yline>"<< endl;

}

void DefPos::forceResult()
{
    // cout << "in define Points used num (bayad =0)==" << usednum << endl;
    //  cout << "botnum" << botnum << endl;
    //   cout<<"<availaaleArz>"<<availableArz<<"</availaaleArz>"<<endl;
    //    cout<<"................\n";
    int mycount; //man chandomin defender am
    for (int i = 0; i < botnum; i++)
    {
        if (pWorldData->my_id() == uidList[i])
        {
            mycount = i;
            break;
        }
    }

    Point temp;
    temp.x = xLine;
    //bar asas e top left corner (0,0)
    if (botnum == 1)
        temp.y = y1Line + availableArz / 2;
    else temp.y = ((availableArz / (botnum - 1)) * mycount) + y1Line;
    //         cout<<"<Defenser>"<<endl;
    //         cout<<"<i> "<<i<<"</i>"<<endl;
    //         cout<<"<id>"<<uidList[i]<<"</id>"<<endl;
    //         cout<<"<y>"<<temp.y<<"</y>"<<endl;
    //         cout<<"<debug>"<<endl;
    //         cout<<"<avArz>"<<availableArz<<"</avArz>"<<endl;
    //         cout<<"<botnum>"<<botnum<<"</botnum>"<<endl;
    //         cout<<"<y1Line>"<<y1Line<<"</y1line>"<<endl;
    //         cout<<"<debug>"<<endl;
    //         cout<<"</Defenser>"<<endl;
    //tabdil e noghte az mokhtasat bar asas e goosheye bala samte chap be real center of the field
    //tempX va tempY mokhtasat e reaal center bar asas e gooshye chap va bala hastand
    //        double centerX;
    double centerY;
    //        centerX = pWorldData->basedCenter(pWorldData->mrTopLeftCorner()).x * -1;
    //*/ centerY = pWorldData->basedCenter(pWorldData->mrTopLeftCorner()).y;
    centerY = pWorldData->realVectors[11].getY();
    //        temp.x = temp.getX() - centerX;
    temp.y = centerY - temp.getY();
    if (area == 'r' || area == 'R')
    {
        if (temp.getX() > pWorldData->realVectors[7].getX() - 50)
            temp.x = pWorldData->realVectors[7].getX() - 50;

    }
    else if (area == 'l' || area == 'L')
    {
        if (temp.getX() < pWorldData->realVectors[3].getX() + 50)
            temp.x = pWorldData->realVectors[3].getX() + 50;
    }

    //        cout<<"avp["<<i<<"] = "<<avp[i]<<endl;
    resultPos = temp;
    resultId = pWorldData->my_id();

    resultnum = 1;
    //    cout<<"................\n";
}

void DefPos::forceDefPosNOW()
{
    decideXLine();
    decideLength();
    decideYLine();
    forceResult();
}


