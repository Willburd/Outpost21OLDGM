#include "server_core.h"
#include "base64/base64.h"
#include "server_process_packets.h"
#include "byte_buffer.h"
#include "client_structure.h"
#include "entitylibrary/entity_library.h"
#include "inih/cpp/INIReader.h"
#include <map>



extern serverCore serverObj;

void* server_recieving_packets::serverProcessLoop(void *threadid) {
    int threadId;
    threadId = (int)threadid;
    std::cout << "Socket ready on port: " << serverObj.server_port << " inside thread: " << threadId << std::endl;

    //make new client
    client_struct client;

    // accept a new connection
    if (serverObj.listener.accept(client.mySocket) != sf::Socket::Done)
    {
        // error...
    }
    else
    {
        //first connection
        std::cout << "Connection recognition! Inside thread: " << threadId << std::endl;
        serverObj.spawn_new_socket = true;

        client.myNumber = threadId;
        client_transmission_packets::cPacket_request_seen( client);

        //create thread locking mutex, look into each packet opcode to see when they use this.
        pthread_mutex_t *mutex;
        const pthread_mutexattr_t *attr;
        pthread_mutex_init(mutex, attr);

        //main client processing loop,ALWAYS respond to packets ASAP compared to the server's tick rate
        bool quit = false;
        while(quit == false) {
            // TCP socket:
            byte_buffer* current_packet = new byte_buffer;
            if (client.mySocket.receive(current_packet->data, 255, current_packet->received) != sf::Socket::Done)
            {
                // client has been lost! exit loop
                std::cout << "Connection lost! Inside thread: " << threadId << std::endl;
                quit = true;
            }
            else
            {
                //pop first magic byte off!
                bool foundPacket = false;

                while(current_packet->buffer_get_pos() < current_packet->received) {
                    if(foundPacket == false)
                    {
                        unsigned char getbyte = current_packet->buffer_read_u8();
                        if(getbyte == 210) {
                            foundPacket = true;
                            std::cout << "MAGIC FOUND!" << std::endl;
                        }
                    }
                    else
                    {

                        //found packet, next time we check it we'll be looking for magic numbers
                        foundPacket = false;
                        //extract packet's opcode!
                        uint16_t packetOpcode = current_packet->buffer_read_u16();
                        std::cout << "=====Packet Opcode " << packetOpcode << " Inside thread: " << threadId << std::endl;

                        switch(packetOpcode) {
                            case server_recieving_packets::login_requested:
                                {
                                    std::cout << "-Login requested" << std::endl;

                                    //login attempt!
                                    std::string buffer_login_name      = current_packet->buffer_read_string(); //stores length and ignores null terminator!
                                    std::string buffer_login_passhash  = current_packet->buffer_read_string(); //stores length and ignores null terminator!

                                    std::cout << " Login name: " << buffer_login_name << "|" << std::endl;
                                    std::cout << " passhash  : " << buffer_login_passhash << "|" << std::endl;

                                    //check login
                                    bool user_exists = serverObj.userAccountExists( buffer_login_name);
                                    bool password_accepted = serverObj.userAccountLogin( buffer_login_name, buffer_login_passhash);

                                    //login checks
                                    if(buffer_login_name.length() > 0 && buffer_login_passhash.length() ) {
                                        if(user_exists == false) {
                                            //send new user confirmations!
                                            std::cout << "New user signup" << std::endl;
                                            client_transmission_packets::cpacket_login_newuser( client, buffer_login_name, buffer_login_passhash);
                                        }
                                        else
                                        {
                                            //confirm loaded password
                                            if(password_accepted == true) {
                                                std::cout << "Login correct!" << std::endl;
                                                client_transmission_packets::cPacket_login_success( client, buffer_login_name);
                                            }
                                            else
                                            {
                                                std::cout << "Login wrong!" << std::endl;
                                                client_transmission_packets::cPacket_login_failed( client, buffer_login_name);
                                            }
                                        }
                                    }
                                }
                            break;

                            case server_recieving_packets::heartbeat_request:
                                {
                                    client_transmission_packets::cpacket_server_alive( client);
                                }
                            break;

                            case server_recieving_packets::login_newuser:
                                {
                                    std::cout << "===Login details created!" << std::endl;
                                    //login attempt!
                                    std::string buffer_login_name      = current_packet->buffer_read_string(); //stores length and ignores null terminator!
                                    std::string buffer_login_passhash  = current_packet->buffer_read_string(); //stores length and ignores null terminator!

                                    std::cout << "user: " << buffer_login_name << std::endl;
                                    std::cout << "hash: " << buffer_login_passhash << std::endl;
                                    std::string get_pass_data = "";


                                    //load user data
                                    std::cout << "Config loaded from '" << serverObj.serverdata_file_path << "'" << std::endl;

                                    //check login
                                    bool user_exists = serverObj.userAccountExists( buffer_login_name);

                                    //get passhash from server data
                                    if(buffer_login_name.length() > 0 && buffer_login_passhash.length() ) {
                                        if(user_exists == true) {
                                            std::cout << " -a user tried to register the same name twice. This is not possible." << std::endl;
                                        }
                                        else
                                        {
                                            //reader.MakeKey("UserData",buffer_login_name,buffer_login_passhash);
                                            //auto login!
                                            client_transmission_packets::cPacket_login_success( client, buffer_login_name);
                                        }
                                    }
                                }
                            break;

                            //character acquisition
                            case server_recieving_packets::character_get_all_owned:
                                {
                                    std::cout << "===all owned characters requested" << std::endl;

                                    //check for character existance!
                                    std::string user_getname  = current_packet->buffer_read_string();

                                    //loop through all entities
                                    std::map<unsigned int, entity*>::iterator it;
                                    for (it = serverObj.entity_map.begin(); it != serverObj.entity_map.end(); it++) {
                                        entity* check_entity = it->second;

                                        //if the slot exists at all
                                        if(check_entity != nullptr) {
                                            //check if entity had player data and send it
                                            if(check_entity->entity_getObjectIndex() == "obj_puppet_player"
                                            && check_entity->myStringVars["player_name"] == user_getname) {
                                                //debug out
                                                std::cout << " ---sent entity: " << it->first << std::endl;
                                                std::cout << " -char name: " << check_entity->myStringVars["player_nickname"] << std::endl;
                                                //construct a string to transmit
                                                std::string transmit_string = serverObj.entityJsonEncode( check_entity);
                                                std::string base64_transmit = base64_encode(reinterpret_cast<unsigned const char*>(transmit_string.c_str()),(unsigned int)transmit_string.length());
                                                //send data to player
                                                client_transmission_packets::cpacket_character_transmit_data( client, base64_transmit);
                                            }
                                        }
                                    }
                                }
                            break;

                            case server_recieving_packets::character_query:
                                {
                                    std::cout << "===specific character by name requested" << std::endl;

                                    //check for character existance!
                                    std::string char_getname  = current_packet->buffer_read_string();

                                    //loop through all entities
                                    std::map<unsigned int, entity*>::iterator it;
                                    for (it = serverObj.entity_map.begin(); it != serverObj.entity_map.end(); it++) {
                                        entity* entity_data = it->second;

                                        //if the slot exists at all
                                        if(entity_data != nullptr) {

                                            //check if entity had player data and send it
                                            if(entity_data->entity_getObjectIndex() == "obj_puppet_player"
                                            && entity_data->myStringVars["player_nickname"] == char_getname) {
                                                //debug out
                                                std::cout << " ---sent entity: " << it->first << std::endl;
                                                std::cout << " -char name: " << entity_data->myStringVars["player_nickname"] << std::endl;
                                                //construct a string to transmit
                                                std::string transmit_string = serverObj.entityJsonEncode( entity_data);
                                                std::string base64_transmit = base64_encode(reinterpret_cast<unsigned const char*>(transmit_string.c_str()),(unsigned int)transmit_string.length());
                                                //send data to player
                                                client_transmission_packets::cpacket_character_transmit_data( client, base64_transmit);
                                            }
                                        }
                                    }
                                }
                            break;

                            case server_recieving_packets::character_created:
                                {
                                    std::cout << "===character created" << std::endl;

                                    //check for character existance!
                                    std::string char_getname       = current_packet->buffer_read_string();
                                    std::string char_getusername   = current_packet->buffer_read_string();
                                    unsigned int char_getrace      = current_packet->buffer_read_u8();
                                    unsigned int char_gethomeworld = current_packet->buffer_read_u8();
                                    unsigned int char_getbody      = current_packet->buffer_read_u8();
                                    unsigned int char_getjob       = current_packet->buffer_read_u8();
                                    unsigned int char_getjobprev   = current_packet->buffer_read_u8();
                                    unsigned int char_getguild     = current_packet->buffer_read_u8();
                                    unsigned int char_getlang_main = current_packet->buffer_read_u8();
                                    unsigned int char_getlang_alt  = current_packet->buffer_read_u8();
                                    unsigned int char_getage       = current_packet->buffer_read_u16();

                                    //a NEW player joined!
                                    entity* new_entity_data = entityLibrary::entity_template_library("obj_puppet_player",serverObj.entity_item_storage,serverObj.entity_item_storage,0,0,true,-1);
                                    new_entity_data->myIntVars["stasis"] = 1; //start in stasis
                                    int new_player_entity = serverObj.entity_add( new_entity_data); //add to main list

                                    new_entity_data->myStringVars["player_name"] = char_getusername; //backstore this, for quick reference if needed!
                                    new_entity_data->myStringVars["player_nickname"] = char_getname; //backstore this, for quick reference if needed! firstname + lastname on char creation!
                                    new_entity_data->myIntVars["stasis"] = false; //take player out of stasis
                                    new_entity_data->myIntVars["stat_race"] = char_getrace;
                                    new_entity_data->myIntVars["stat_homeworld"] = char_gethomeworld;
                                    new_entity_data->myIntVars["stat_body"] = char_getbody;
                                    new_entity_data->myIntVars["stat_job"] = char_getjob;
                                    new_entity_data->myIntVars["stat_jobprev"] = char_getjobprev;
                                    new_entity_data->myIntVars["stat_guild"] = char_getguild;
                                    new_entity_data->myIntVars["stat_lang_main"] = char_getlang_main;
                                    new_entity_data->myIntVars["stat_lang_alt"] = char_getlang_alt;
                                    new_entity_data->myIntVars["stat_age"] = char_getage;

                                    //invisible to others, due to arrival shuttle
                                    entity* arrival_shuttle_data = entityLibrary::entity_template_library("obj_puppet_arrivalshuttle",10,10,0,0,false,-1);
                                    int entity_arivalshuttle = serverObj.entity_add( arrival_shuttle_data);

                                    new_entity_data->myStringVars["inside_of_id"] = entity_arivalshuttle;
                                    arrival_shuttle_data->myStringVars["inside_of_id"] = new_player_entity; //hide inside self till loaded!

                                    //store player inside the shuttle
                                    serverObj.entity_storeEntity( new_player_entity, entity_arivalshuttle);

                                    //add starting toolkit to player inventory
                                    ///TODO! create toolkit definitions!
                                    /*
                                    var new_startitem_entity = scr_toolkit_template_library( global.job_mod[ char_getjob, enum_job_stat.stat_startkit], item_storage_pos, item_storage_pos, 0, 0, false, new_player_entity);
                                    storage_map[? string(new_startitem_entity)] = new_startitem_entity;
                                    */

                                    //lock the socket
                                    client.myPlayerEntity = new_player_entity;

                                    //send final connection packet
                                    std::cout << " -Locked player entity to: " << new_player_entity << std::endl;
                                    client_transmission_packets::cpacket_character_lock( client, new_player_entity); //will put me in the arrival shuttle automatically

                                    //update client with security
                                    new_entity_data->entity_securityUpdate();

                                    //done!
                                    ///TODO flag map for downloading!

                                }
                            break;

                            case server_recieving_packets::character_loaded:
                                {
                                    std::cout << "===character loaded" << std::endl;

                                     //use the entity we passed it before!
                                    unsigned int player_entity = current_packet->buffer_read_u32();

                                    //store the list reference number!
                                    client.myPlayerEntity = player_entity; //player list stores a reference to the player entity id
                                    std::cout << " -client's player entity set to: " << player_entity << std::endl;

                                    //setup entity itself
                                    entity* ply_data = serverObj.entity_map[ player_entity];
                                    if(ply_data != nullptr) {
                                        ply_data->myIntVars["stasis"] = false; //take player out of stasis
                                        ply_data->myIntVars["player_socket"] = client.myNumber;

                                        //send final connection packet
                                        std::cout << " -Locked player entity to: " << player_entity << std::endl;
                                        client_transmission_packets::cpacket_character_lock( client, player_entity);

                                        //update client with security
                                        ply_data->entity_securityUpdate();
                                    }
                                    else
                                    {
                                        //somehow... we lost it...
                                        client_transmission_packets::cpacket_force_reset( client," -Character was lost before loading could be finished.");
                                    }

                                    //flag as done
                                    ///TODO flag map for downloading!
                                }
                            break;

                            //player entity
                            case server_recieving_packets::player_object_request:
                                {
                                    std::cout << "===Player " << client.myNumber << " requested their entity number, and object." << std::endl;
                                    int player_entity = client.myPlayerEntity;
                                    bool hide_ent = false;

                                    entity* ply_data = serverObj.entity_map[ player_entity];

                                    if(ply_data != nullptr) {
                                        if(ply_data->inside_of_id != -1) {
                                            //send entity number of entity we are inside of!!

                                            //certain objects hide their puppets to specific clients.
                                            hide_ent = false;

                                            //backup filter
                                            entity* check_data = serverObj.entity_map[ player_entity];

                                            if(check_data != nullptr) {
                                                //update player entity to send
                                                player_entity = ply_data->inside_of_id;
                                                entity* ply_data = serverObj.entity_map[ player_entity];

                                                std::cout << " -returned CONTAINER entity " << player_entity << " is object: " << ply_data->entity_getObjectIndex() << std::endl;
                                            }
                                            else
                                            {
                                                std::cout << " -returned BACKUP entity " << player_entity << " is object: " << ply_data->entity_getObjectIndex() << std::endl;
                                            }
                                        }
                                        else
                                        {
                                            //send entity number!
                                            std::cout << " -returned entity " << player_entity << " is object: " << ply_data->entity_getObjectIndex() << std::endl;

                                            //certain objects hide their puppets to specific clients.
                                            hide_ent = true;
                                        }

                                        //transmit!
                                        client_transmission_packets::cpacket_playerentity_return( client, player_entity, serverObj.getIndexOfAsset((ply_data->entity_getObjectIndex())), ply_data->x, ply_data->y, hide_ent);
                                    }
                                    else
                                    {
                                        //somehow... we lost it...
                                        client_transmission_packets::cpacket_force_reset( client," -Character entity data was not found.");
                                    }
                                }
                            break;

                            case server_recieving_packets::player_release_grab: break;
                            case server_recieving_packets::map_request_whole: break;
                            case server_recieving_packets::client_map_preloaded: break;
                            case server_recieving_packets::client_ready_for_map_download: break;
                            case server_recieving_packets::map_object_create: break;
                            case server_recieving_packets::map_object_destroy: break;
                            case server_recieving_packets::map_request_securitydata: break;
                            case server_recieving_packets::map_request_door_security: break;
                            //movement
                            case server_recieving_packets::movement_location_request: break;
                            case server_recieving_packets::movement_location_update: break;
                            //inventory
                            case server_recieving_packets::entity_request_all: break;

                            case server_recieving_packets::entity_create:
                                {
                                    double buffer_getx = current_packet->buffer_read_f32();
                                    double buffer_gety = current_packet->buffer_read_f32();
                                    std::string buffer_get_objectindex = serverObj.getAssetOfIndex( current_packet->buffer_read_u16() );

                                    std::cout << "Server created entity: " << buffer_get_objectindex << std::endl;
                                    entity* make_entity = entityLibrary::entity_template_library(  buffer_get_objectindex,buffer_getx,buffer_gety,0,0,false,-1);
                                    serverObj.entity_add(make_entity); //add to main list//make a test entity
                                }
                            break;

                            case server_recieving_packets::entity_create_direction:
                                {
                                    double buffer_getx = current_packet->buffer_read_f32();
                                    double buffer_gety = current_packet->buffer_read_f32();
                                    std::string buffer_get_objectindex = serverObj.getAssetOfIndex( current_packet->buffer_read_u16() );
                                    float buffer_getdirection = (current_packet->buffer_read_u16() / 65534) * 360;

                                    std::cout << "Server created entity, with direction: " << buffer_get_objectindex << std::endl;
                                    entity* make_entity = entityLibrary::entity_template_library(buffer_get_objectindex,buffer_getx,buffer_gety,buffer_getdirection,0,false,-1);
                                    serverObj.entity_add(make_entity); //add to main list//make a test entity
                                }
                            break;

                            case server_recieving_packets::entity_store: break;

                            case server_recieving_packets::entity_throw: break; //flows into place
                            case server_recieving_packets::entity_construct: break;
                            case server_recieving_packets::entity_place: break;

                            case server_recieving_packets::entity_drop:
                                {
                                    //flag the entity as something not loaded!
                                    int entity_number = current_packet->buffer_read_u32();
                                    //show_debug_message("===Entity dropped: " + string(entity_number));

                                    //tell client that this entity is also unloaded
                                    client_transmission_packets::cpacket_entity_drop( client, entity_number);
                                    //set the object as needing to update when it can
                                    serverObj.set_update_flag( entity_number, client.myNumber, true);
                                }
                            break; //not placing, unloading an entity from client inputs!

                            case server_recieving_packets::entity_deconstruct: break;

                            case server_recieving_packets::entity_inventory_request: break;

                            /*******************************

                                This next section is
                                EXTREMELY context based,
                                mostly by the objects
                                calling it.

                            *******************************/

                            case server_recieving_packets::entity_interact: break;
                            //security tool editing doors
                            case server_recieving_packets::security_tool_requestdoor: break;
                            case server_recieving_packets::security_tool_toggledoorsecurity: break;

                        }
                    }

                }
            }

            //clear packet, we are done with it
            delete current_packet;
        }


        //thread finished!
        delete serverObj.SocketThreads[threadId];
        serverObj.SocketThreads[threadId] = nullptr;
        pthread_exit(NULL);
    }


    return nullptr;
}
