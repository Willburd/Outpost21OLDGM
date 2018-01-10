#include "server_core.h"
#include "server_process_packets.h"
#include "byte_buffer.h"
#include "client_structure.h"
#include "inih/cpp/INIReader.h"
#include "entitylibrary/entity_library.h"


extern global_vars global;

void* server_recieving_packets::serverProcessLoop(void *threadid) {
    int tid;
    tid = (int)threadid;
    std::cout << "Socket ready on port: " << global.server_port << " inside thread: " << tid << std::endl;

    //make new client
    client_struct client;

    // accept a new connection
    if (global.listener.accept(client.mySocket) != sf::Socket::Done)
    {
        // error...
    }
    else
    {
        //first connection
        std::cout << "Connection recognition! Inside thread: " << tid << std::endl;
        global.spawn_new_socket = true;

        client.myNumber = tid;
        client_transmission_packets::cPacket_request_seen( client);


        bool quit = false;
        while(quit == false) {


            // TCP socket:
            byte_buffer* current_packet = new byte_buffer;
            if (client.mySocket.receive(current_packet->data, 255, current_packet->received) != sf::Socket::Done)
            {
                // client has been lost! exit loop
                std::cout << "Connection lost! Inside thread: " << tid << std::endl;
                quit = true;
            }
            else
            {
                //extract packet's opcode!
                uint16_t packetOpcode = current_packet->buffer_read_u16();
                std::cout << "=====Packet Opcode " << packetOpcode << " Inside thread: " << tid << std::endl;


                switch(packetOpcode) {
                    case server_recieving_packets::login_requested:
                        {
                            std::cout << "-Login requested" << std::endl;

                            //login attempt!
                            std::string buffer_login_name      = current_packet->buffer_read_string(); //stores length and ignores null terminator!
                            std::string buffer_login_passhash  = current_packet->buffer_read_string(); //stores length and ignores null terminator!

                            std::cout << " Login name: " << buffer_login_name << "|" << std::endl;
                            std::cout << " passhash  : " << buffer_login_passhash << "|" << std::endl;

                            //confirmed password
                            bool password_accepted = false;
                            std::string get_pass_data = "";

                            //load user data
                            INIReader reader( global.serverdata_file_path);
                            if (reader.ParseError() < 0) {
                                std::cout << "Can't load '" << global.serverdata_file_path << "'" << std::endl;
                                get_pass_data = "";
                                password_accepted = false;
                            }
                            else
                            {
                                std::cout << "Config loaded from '" << global.serverdata_file_path << "'" << std::endl;

                                //get passhash from server data
                                get_pass_data = reader.Get("UserData", buffer_login_name,"");
                                password_accepted = true;
                            }

                            //extracted passhash
                            std::cout << " E-hash    : " << get_pass_data << "|" << std::endl;

                            //login checks
                            if(get_pass_data.length() > 0) {
                                if(password_accepted == false) {
                                    //send new user confirmations!
                                    std::cout << "New user signup" << std::endl;
                                }
                                else if(password_accepted == true)
                                {
                                    //confirm loaded password
                                    bool login_success = (get_pass_data == buffer_login_passhash);


                                    if(login_success == true) {
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
                            std::cout << "-Heartbeat" << std::endl;
                            //construct buffer to send data
                            byte_buffer send_buffer;
                            send_buffer.buffer_write_u8( 0); //client number
                            send_buffer.buffer_write_u16( client_transmission_packets::server_alive); //opcode

                            //transmit
                            client.mySocket.send(send_buffer.data, send_buffer.buffer_get_pos());
                        }
                    break;

                    case server_recieving_packets::login_newuser: break;
                    //character aquisition
                    case server_recieving_packets::character_get_all_owned:
                        current_packet->buffer_debug();
                    break;

                    case server_recieving_packets::character_query:
                        current_packet->buffer_debug();
                    break;

                    case server_recieving_packets::character_created:
                        current_packet->buffer_debug();
                    break;

                    case server_recieving_packets::character_loaded: break;
                    //player entity
                    case server_recieving_packets::player_object_request: break;
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
                            std::string buffer_get_objectindex = global.getAssetOfIndex( current_packet->buffer_read_u16() );

                            std::cout << "Server created entity: " << buffer_get_objectindex << std::endl;
                            entity* make_entity = entityLibrary::entity_template_library(  buffer_get_objectindex,buffer_getx,buffer_gety,0,0,false,-1);
                            global.entity_add(make_entity); //add to main list//make a test entity
                        }
                    break;
                    case server_recieving_packets::entity_create_direction:
                        {
                            double buffer_getx = current_packet->buffer_read_f32();
                            double buffer_gety = current_packet->buffer_read_f32();
                            std::string buffer_get_objectindex = global.getAssetOfIndex( current_packet->buffer_read_u16() );
                            float buffer_getdirection = (current_packet->buffer_read_u16() / 65534) * 360;

                            std::cout << "Server created entity, with direction: " << buffer_get_objectindex << std::endl;
                            entity* make_entity = entityLibrary::entity_template_library(buffer_get_objectindex,buffer_getx,buffer_gety,buffer_getdirection,0,false,-1);
                            global.entity_add(make_entity); //add to main list//make a test entity
                        }
                    break;
                    case server_recieving_packets::entity_store: break;
                    case server_recieving_packets::entity_throw: break; //flows into place
                    case server_recieving_packets::entity_place: break;
                    case server_recieving_packets::entity_drop: break; //not placing, unloading an entity from client inputs!
                    case server_recieving_packets::entity_construct: break;
                    case server_recieving_packets::entity_deconstruct: break;
                    case server_recieving_packets::entity_inventory_request: break;
                    case server_recieving_packets::entity_interact: break;
                    //security tool editing doors
                    case server_recieving_packets::security_tool_requestdoor: break;
                    case server_recieving_packets::security_tool_toggledoorsecurity: break;

                }
            }

            //clear packet, we are done with it
            delete current_packet;
        }


        //thread finished!
        delete global.SocketThreads[tid];
        global.SocketThreads[tid] = nullptr;
        pthread_exit(NULL);
    }


    return nullptr;
}
