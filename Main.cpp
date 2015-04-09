#include <iostream>
#include <string>
#include "Client.h"
#include "Connection.h"
#include "WorldData.h"
#include "BasicPlayer.h"
#include "ClientException.h"
#include "ClientConnector.h"
#include "PropertyStreamError.h"
#include "BadPropertyFormatException.h"
#include "AgentList.h"
#include "fstream"
#include "Vector.h"
#include "Rectangle.h"
//#include "Plans.h"
#include <cstdio>
#include <cstdlib>
#include <Types.h>
#include <Shoot-cir.h>
#include <Pass.h>
#include <Clear.h>
//#include <PenaltyPlan.h>
#include <PlanBackUp.h>

using namespace std;

Properties read_file_properties(const std::string& filename)
{
    PropertyReader fileReader;
    Properties props;

    try
    {
        /**
         * Read the file, if we can't read it just let the flow
         * throw an exception
         */
        props = fileReader.read(filename);
        return props;

    }
    catch (PropertyStreamError& ex)
    {
        std::cout << "Error reading property file" << std::endl;
    }
    catch (BadPropertyFormatException& ex)
    {
        std::cout << "Error in property format: " << ex.what() << std::endl;
    }

    throw ClientException("Could not read properties file");
}

/*
 *
 * Returns true if the program is supposed to continue
 * false otherwise
 */

bool override_properties_with_cmd(int argc, char ** argv, Properties& props)
{

    if (argc == 1)
    {
        // No properties to read
        return true;
    }
    else if (argc == 2)
    {
        std::string first_arg = argv[1];

        if (first_arg == "-help")
        {
            std::cout << "Available agents parameters: \n"
                    << " -p(ort team) - The team's port\n"
                    << " -n(ick name) - The players nickname\n"
                    << " -r(cID) The agent's robot control id\n"
                    << " -v(tID) the agent's robot control id"
                    << " -t(eamname) the agent team name";

            return false;
        }
        else
        {
            std::cout << "Invalid argument list" << std::endl;
            return false;
        }
    }
    else
    {
        for (int i = 1; i < argc; i += 2)
        {

            /*
             * A parameter is always followed by a value!
             * So read it by pairs
             *
             */
            if (i + 1 >= argc)
            {
                cout << "Missing argument for value " << argv[i] << endl;
                return false;
            }

            std::string arg = argv[i];
            std::string value = argv[i + 1];

            if (arg[0] == '-' && arg.size() > 1)
            {
                try
                {
                    switch (arg[1])
                    {
                        case 'p':
                        {
                            convert_to<int> (value);
                            props.setProperty("PORT_TEAM", value);
                        }
                            break;

                        case 'r':
                        {
                            convert_to<int> (value);
                            props.setProperty("RC_ID", value);
                        }
                            break;

                        case 'v':
                        {
                            convert_to<int> (value);
                            props.setProperty("VT_ID", value);
                        }
                            break;

                        case 't':
                        {
                            props.setProperty("TEAMNAME", value);
                        }
                            break;

                        case 'n':
                        {
                            props.setProperty("NICK_NAME", value);
                        }
                            break;

                        default:
                            cerr << "Error bad argument \"" << arg << "\"" << endl;
                            return false;
                    }
                }
                catch (std::exception& ex)
                {
                    std::cout << "Invalid argument exception: " << ex.what()
                            << "\n";
                    return false;
                }
            }
            else
            {
                std::cout << "Invalid argument" << std::endl;
            }
        }
    }

    return true;
}

mrTeam client_team(const ServerProperties& props, int port)
{
    if (props.GetInt("port_team_yellow") == port)
    {
        return TEAM_YELLOW;
    }
    else if (props.GetInt("port_team_blue") == port)
    {
        return TEAM_BLUE;
    }
    else
    {
        throw ClientException("The connected port is invalid (" + convert_to<
                std::string > (port) + ")");
    }
}

int main(int argc, char* argv[])
{
    Properties props;
    std::string host;
    int port;

    try
    {
        /**
         * Read the properties from the configuration files
         */
        props = read_file_properties("config.ini");

        /**
         * If necessary override those properties with any given command-line
         */
        if (!override_properties_with_cmd(argc, argv, props))
        {
            return -1;
        }

        host = props.propertyValue("SERVER_IP"); //ip server ro mide      => propertYValue string mo
        port = convert_to<int> (props.propertyValue("PORT_TEAM")); //port server ro mide

    }
    catch (ClientException& ex)
    {
        std::cout << ex.what() << std::endl;
        return -1;
    }

    ConnectionParameters params;
    params.nickname(props.Get("NICK_NAME"));
    params.teamname(props.Get("TEAMNAME"));
    params.vtId(convert_to<int> (props.Get("VT_ID")));
    params.rcId(convert_to<int> (props.Get("RC_ID")));
    params.movementMode("wheel_velocities");

    int tries = convert_to<int> (props.Get("TRIES"));
    int sleep = convert_to<int> (props.Get("SLEEP"));

    ServerProperties server_props;

    ClientConnector client_connector(host, port);
    client_connector.tries(tries);
    client_connector.retryTime(sleep);

    try
    {
        server_props = client_connector.ConnectToServer(params);
    }
    catch (ClientException& ex)
    {
        std::cout << ex.what() << std::endl;
        return -1;
    }

    mrTeam my_team = client_team(server_props, port);

    WorldData gWorldData(sleep, tries, my_team); /* sleep : meghdar zamani ke ta update beshe bazikon sleep bashe*/
    gWorldData.setConnection(client_connector.getConnection());
    std::cout << "World connection successfully initialized." << std::endl;

    BasicPlayer gPlayer(my_team);
    gPlayer.setConnection(client_connector.getConnection());
    std::cout << "Basic player connection successfully initialized."
            << std::endl;

    gPlayer.setWorldData(&gWorldData);

    bool quit = false;

    while (!quit)
    {
        if (gWorldData.updateAll())
        { //avalle har cycle world datamoon ro update mikonim

            if (gWorldData.is_game_on()) //agar bazi dar hale ejra bood
            {

            }

            else if (gWorldData.mrPlayMode() == "warn ending")
            {
                std::cout << "game near to the end." << std::endl;
            }

            else if (gWorldData.mrPlayMode() == "time over")
            { //age bazi tamoom shode bood
                quit = true; //az bazi kharej mishim
                continue;
            }
            //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<Main Cycle>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

            if(gWorldData.time() > 0)
                gWorldData.setPositions();

            for (int i = 0 ; i < gWorldData.mr_number_found_opponents() ; i++)
                cout<<"Opp ID(from 0) : "<<i<<endl<<"OppPos : "<<gWorldData.oppPositions[i]<<endl;


            int we;

            if (gWorldData.is_game_on() == true)
            {
                if (gWorldData.mr_number_found_opponents() != 0 && gWorldData.mr_number_found_teammates() != 0)
                {
                    if (gWorldData.mr_found_opponents()[0] >= gWorldData.mr_found_teammates()[0])
                        we = gWorldData.mr_number_found_teammates() + 1;
                    else if (gWorldData.mr_found_opponents()[0] < gWorldData.mr_found_teammates()[0])
                        we = 10;
                }

                if (!gWorldData.i_am_lost())
                {

                }

                if (gPlayer.can_kick())
                {
                }
                else
                {

                }

                /*
                 This is when the commands decided above will be actually
                 sent over the network. This function should be called
                 as only one time per cycle in the end of the main loop
                 */
                gPlayer.flush(); //commande set shode ro be server mifreste
            }
            else
            {
                // Just for the sake of clarity
                // std::cout << "Where I'am?!" << std::endl;
            }
        }
        else
        {
            std::cout << "Didn't receive any update message from server."
                    << std::endl;
        }
    }

    std::cout << "Ending program." << std::endl;
    exit(EXIT_SUCCESS);
}