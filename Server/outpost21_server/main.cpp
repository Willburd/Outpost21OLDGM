#include "main.h"
#include "byte_buffer.h"





int main()
{
    sf::TcpListener listener;

    // bind the listener to a port
    if (listener.listen(2727) != sf::Socket::Done)
    {
        // error...
    }

    // accept a new connection
    sf::TcpSocket client;
    if (listener.accept(client) != sf::Socket::Done)
    {
        // error...
    }
    else
    {
        //first connection
        std::cout << "Connection recognition!" << std::endl;

        //construct buffer to send data
        byte_buffer send_buffer;
        send_buffer.buffer_write_u8( 0); //client number
        send_buffer.buffer_write_u16( client_transmission_packets::request_seen); //opcode

        //transmit
        send_buffer.buffer_debug();
        client.send(send_buffer.data, send_buffer.buffer_get_pos());
    }

    // use "client" to communicate with the connected client,
    // and continue to accept new connections with the listener

    bool quit = false;

    while(quit == false) {
        // TCP socket:
        byte_buffer* current_packet = new byte_buffer;
        if (client.receive(current_packet->data, 255, current_packet->received) != sf::Socket::Done)
        {
            // error...
            quit = true;
        }

        std::cout << "Received " << current_packet->received << " bytes" << std::endl;
        uint16_t packetOpcode = current_packet->buffer_read_u16();
        std::cout << "Packet Opcode " << packetOpcode << std::endl;


        switch(packetOpcode) {
            case server_recieving_packets::login_requested:
                {
                    std::cout << " Login requested" << std::endl;

                    current_packet->buffer_debug();

                    //login attempt!
                    bool login_success   = false;
                    std::string login_name      = current_packet->buffer_read_string(); //stores length and ignores null terminator!
                    std::string login_passhash  = current_packet->buffer_read_string(); //stores length and ignores null terminator!

                    std::cout << " Login name: " << login_name << std::endl;
                    std::cout << " passhash  : " << login_passhash << std::endl;

                    //load user data
                    //ini_open(global.serverdata_file_path)
                    //    var get_pass = ini_read_string("UserData",login_name,-1);
                    //ini_close();

                    //login checks
                    //if string(get_pass) == "-1" {
                        //send new user confirmations!
                    //    scr_cpacket_login_newuser(connection_id,login_name,login_passhash);
                    //}
                    //else
                    //{
                        //confirm loaded password
                    //    login_success = (get_pass == login_passhash);

                        //for now no logins, just trigger to the client that they logged in!
                    //    scr_cpacket_login_return(connection_id,login_success,login_name);
                    //}
            }
            break;

            case server_recieving_packets::heartbeat_request:
                {
                    std::cout << " Heartbeat" << std::endl;
                    //construct buffer to send data
                    byte_buffer send_buffer;
                    send_buffer.buffer_write_u8( 0); //client number
                    send_buffer.buffer_write_u16( client_transmission_packets::server_alive); //opcode

                    //transmit
                    send_buffer.buffer_debug();
                    client.send(send_buffer.data, send_buffer.buffer_get_pos());
                }
            break;

            case server_recieving_packets::login_newuser: break;
            //character aquisition
            case server_recieving_packets::character_get_all_owned: break;
            case server_recieving_packets::character_query: break;
            case server_recieving_packets::character_created: break;
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

    std::cout << "Hello world!" << std::endl;
    return 0;
}
