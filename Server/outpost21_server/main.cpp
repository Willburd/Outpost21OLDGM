#include <iostream>
#include <cstring>
#include <SFML/Network.hpp>
#include <pthread.h>
#include <chrono>  // for high_resolution_clock
#include <ctime> // for nanosleep

#include "main.h"
#include "inih/cpp/INIReader.h"
#define NANO_SECOND_MULTIPLIER  1000000  // 1 millisecond = 1,000,000 Nanoseconds

//just gonna have this so porting the older code will be easy. Mostly just server configs all loaded in one place.
serverCore serverObj;


int main()
{
    ///load server configs
    std::string get_port = "2727";
    std::string get_mapPath = "";
    int get_tickRate = 60;
    INIReader reader( serverObj.serverdata_file_path);
    if (reader.ParseError() < 0) {
        std::cout << "Can't load '" << serverObj.serverdata_file_path << "'" << std::endl;
    }
    else
    {
        std::cout << "Config loaded from '" << serverObj.serverdata_file_path << "'" << std::endl;

        //get passhash from server data
        get_port = reader.Get("ServerData", "Port", "2727");
        get_mapPath = reader.Get("ServerData", "Map_path", "");
        get_tickRate =  stoi(reader.Get("ServerData", "Tick_rate", "60"));
    }


    /// bind the listener to a port
    serverObj.server_port = stoi(get_port);
    //clean out clients
    for (int i = 0; i < serverObj.server_maxplayers; i++)
    {
        serverObj.SocketThreads[i] = nullptr;
    }

    ///set update rate
    serverObj.server_tickrate = get_tickRate;

    ///load the ingame map! and all entities with it!
    serverObj.gameMapLoad(get_mapPath);


    ///start server
    if (serverObj.listener.listen( serverObj.server_port ) != sf::Socket::Done)
    {
        // error...
        std::cout << "Failed to start server. Port '" << get_port << "' already in use!" << std::endl;
    }
    else
    {
        //setup tick timer
        std::chrono::system_clock::time_point a = std::chrono::system_clock::now();
        std::chrono::system_clock::time_point b = std::chrono::system_clock::now();

        //process server
        bool server_quit = false;
        while(server_quit == false) {
            /// Maintain designated update frequency
            float work_frequency = 1000/serverObj.server_tickrate;
            a = std::chrono::system_clock::now();
            std::chrono::duration<double, std::milli> work_time = a - b;

            if (work_time.count() < work_frequency)
            {
                std::chrono::duration<double, std::milli> delta_ms(work_frequency - work_time.count());
                auto delta_ms_duration = std::chrono::duration_cast<std::chrono::milliseconds>(delta_ms);

                timespec sleepValue = {0};
                sleepValue.tv_nsec = delta_ms_duration.count() * NANO_SECOND_MULTIPLIER;
                nanosleep(&sleepValue, NULL);
            }

            b = std::chrono::system_clock::now();
            std::chrono::duration<double, std::milli> sleep_time = b - a;

            ///handle new clients!
            if(serverObj.spawn_new_socket == true) {

                //allow a new socket to be opened
                serverObj.spawn_new_socket = false;
                for (int i = 0; i < serverObj.server_maxplayers+1; i++)
                {
                    if(i < serverObj.server_maxplayers) {
                        if(serverObj.SocketThreads[i] == nullptr) {
                            serverObj.SocketThreads[i] = new pthread_t;
                            pthread_create(serverObj.SocketThreads[i], NULL, &server_recieving_packets::serverProcessLoop, (void *)i);
                            break;
                        }
                    }
                    else
                    {
                        std::cout << "Failed to create new socket, max players reached!" << std::endl;
                    }
                }
            }

            //process entity personal steps!
            for(unsigned int i = 0; i < serverObj.entity_map.size(); i++) {
                entity* getEnt = serverObj.entity_map[i];

                if(getEnt != nullptr) {
                    if(getEnt->x == serverObj.entity_deletion_abyss || getEnt->y == serverObj.entity_deletion_abyss) {
                        //drag up to item abyss if y is wrong.
                        getEnt->y = serverObj.entity_deletion_abyss;

                        if( getEnt->x > serverObj.entity_deletion_abyss-5 ) {
                            //repeatedly send unloads to all clients
                            getEnt->x -= 1;
                        }
                        else
                        {
                            //force destruction of entity
                            serverObj.entity_map[getEnt->entity_number] = nullptr;
                            delete getEnt;
                        }
                    }
                    else
                    {
                        getEnt->entity_step();
                    }
                }
            }


            //handle server processing


            //increment cycle counter
            serverObj.entity_process_cycle += 1;


            //std::cout << "Time: " << (work_time + sleep_time).count() << std::endl;
        }
    }


    return 0;
}
