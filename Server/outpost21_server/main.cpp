#include <iostream>
#include <cstring>
#include <SFML/Network.hpp>

#include "main.h"
#include "inih/cpp/INIReader.h"


//just gonna have this so porting the older code will be easy. Mostly just server configs all loaded in one place.
global_vars global;


int main()
{
    sf::TcpListener listener;

    // bind the listener to a port
    if (listener.listen(2727) != sf::Socket::Done)
    {
        // error...
    }
    else
    {
        //make new client
        client_struct client;

        // accept a new connection
        if (listener.accept(client.mySocket) != sf::Socket::Done)
        {
            // error...
        }
        else
        {
            //first connection
            std::cout << "Connection recognition!" << std::endl;

            client_transmission_packets::cPacket_request_seen( client);
        }



        // use "client" to communicate with the connected client,
        // and continue to accept new connections with the listener

        bool quit = false;

        while(quit == false) {
            // TCP socket:
            byte_buffer* current_packet = new byte_buffer;
            if (client.mySocket.receive(current_packet->data, 255, current_packet->received) != sf::Socket::Done)
            {
                // error...
                quit = true;
            }

            //extract packet's opcode!
            uint16_t packetOpcode = current_packet->buffer_read_u16();
            std::cout << "=====Packet Opcode " << packetOpcode << std::endl;


            switch(packetOpcode) {
                case server_recieving_packets::login_requested:
                    {
                        std::cout << "-Login requested" << std::endl;

                        //login attempt!
                        std::string login_name      = current_packet->buffer_read_string(); //stores length and ignores null terminator!
                        std::string login_passhash  = current_packet->buffer_read_string(); //stores length and ignores null terminator!

                        std::cout << " Login name: " << login_name << "|" << std::endl;
                        std::cout << " passhash  : " << login_passhash << "|" << std::endl;

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
                            get_pass_data = reader.Get("UserData", login_name,"");
                            password_accepted = true;
                        }

                        //extracted passhash
                        std::cout << " E-hash    : " << get_pass_data << "|" << std::endl;

                        //login checks
                        if(get_pass_data.length() > 0) {
                            if(password_accepted == false) {
                                //send new user confirmations!
                                std::cout << "New user signup" << std::endl;
                                //scr_cpacket_login_newuser(connection_id,login_name,login_passhash);
                            }
                            else if(password_accepted == true)
                            {
                                //confirm loaded password
                                bool login_success = (get_pass_data == login_passhash);


                                if(login_success == true) {
                                    std::cout << "Login correct!" << std::endl;
                                    client_transmission_packets::cPacket_login_success( client, login_name);
                                }
                                else
                                {
                                    std::cout << "Login wrong!" << std::endl;
                                    client_transmission_packets::cPacket_login_failed( client, login_name);
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
                case server_recieving_packets::entity_create: break;
                case server_recieving_packets::entity_create_direction: break;
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


            //clear packet, we are done with it
            delete current_packet;
        }
    }

    std::cout << "Hello world!" << std::endl;
    return 0;
}
