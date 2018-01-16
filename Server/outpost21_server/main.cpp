#include "server_process_packets.h"
#include "inih/cpp/INIReader.h"
#include "server_core.h"
#include <map>
#include "main.h"


//just gonna have this so porting the older code will be easy. Mostly just server configs all loaded in one place.
serverCore serverObj;


int main()
{
    ///load server configs
    std::string get_port = "2727";
    std::string get_mapPath = "";
    int get_tickRate = 60;
    int get_mapLoadShow = 0;
    int get_entityLoadShow = 0;
    int get_securityLoadShow = 0;
    int get_mtu = 256;

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
        get_tickRate = stoi(reader.Get("ServerData", "Tick_rate", "60"));
        get_mapLoadShow = stoi(reader.Get("ServerData", "ShowMapLoading", "0"));
        get_entityLoadShow = stoi(reader.Get("ServerData", "ShowEntityLoading", "0"));
        get_securityLoadShow = stoi(reader.Get("ServerData", "ShowSecurityLoading", "0"));
        get_mtu = stoi(reader.Get("ServerData", "maxMTU", "256"));
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
    serverObj.MaxByteslMTU = get_mtu;

    ///set if loading should give data
    serverObj.showMapLoad = (get_mapLoadShow > 0);
    serverObj.showEntityLoad = (get_entityLoadShow > 0);
    serverObj.showSecurityLoad = (get_securityLoadShow > 0);

    ///load asset index
    entityLibrary::entity_template_creation();

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
                nanosleep(&sleepValue, nullptr);
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
                            pthread_create(serverObj.SocketThreads[i], nullptr, &server_recieving_packets::serverProcessLoop, (void *)i);
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
            for(std::map<unsigned int, entity*>::iterator it = serverObj.entity_map.begin(); it != serverObj.entity_map.end(); it++ ) {
                entity* getEnt = it->second;

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


            //keep track of map entities to drop at the end of the loop.
            std::map<unsigned int, mapConstruction*> MapConstruction_RemoveList;
            //send maps out to clients
            for(std::map<unsigned int, client_struct*>::iterator it = serverObj.clientNumberMap.begin(); it != serverObj.clientNumberMap.end(); it++ ) {
                client_struct* getClient = it->second;

                if(getClient->mapDownloadQueue.size() > 0) {
                    //if the queue is any value other then 0, send the map tile at the top!
                    mapConstruction* currentConstruction = getClient->mapDownloadQueue.front();

                    if(currentConstruction != nullptr) {
                        //conditions if we load or unload
                        if(currentConstruction->remove_flag == false) {
                            //transmit it to the client
                            client_transmission_packets::cpacket_map_object_load( *getClient, currentConstruction);
                        }
                        else
                        {
                            //transmit it to the client
                            client_transmission_packets::cpacket_map_object_drop( *getClient, currentConstruction);

                            //load it up to be removed
                            MapConstruction_RemoveList[currentConstruction->map_entity] = currentConstruction;
                        }
                    }

                    //cleanup
                    getClient->mapDownloadQueue.pop_front();
                }
            }

            //remove map constructions if they were cleared in this loop
            for(std::map<unsigned int, mapConstruction*>::iterator it = MapConstruction_RemoveList.begin(); it != MapConstruction_RemoveList.end(); it++ ) {
                mapConstruction* getConstruct = it->second;

                //it's dead Jim
                delete getConstruct;
            }

            //transmit client packets! Limit under MTU!
            for(std::map<unsigned int, client_struct*>::iterator it = serverObj.clientNumberMap.begin(); it != serverObj.clientNumberMap.end(); it++ ) {
                client_struct* getClient = it->second;

                while(getClient->ByteTotalMTU < serverObj.MaxByteslMTU ) {
                    //if we have packets to send!
                    if(getClient->packetQueue.size() > 0) {
                        byte_buffer* getPacket = getClient->packetQueue.front();
                        getClient->mySocket.send(getPacket->data, getPacket->buffer_get_pos());

                        //increase mtu bytes
                        getClient->ByteTotalMTU += getPacket->buffer_get_pos();

                        //clean up
                        getClient->packetQueue.pop_front();
                        delete getPacket;
                    }
                    else
                    {
                        break; //endloop
                    }
                }

                //reset for next loop
                getClient->ByteTotalMTU = 0;
            }


            //std::cout << "Time: " << (work_time + sleep_time).count() << std::endl;
        }
    }


    return 0;
}
