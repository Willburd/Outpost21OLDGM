#ifndef CLIENTTRANSMIT_H
#define CLIENTTRANSMIT_H

//=================================
// forward declared dependencies
struct client_struct;
class mapConstruction;
struct byte_buffer;

//=================================
// included dependencies
#include <cstring>

namespace client_transmission_packets {
    ///NOTICE this needs to match the enum in the game maker side client!
    enum enum_client_packets : uint16_t {
        request_seen,
        //need to be right by each other in order
        login_newuser,
        login_failed,
        login_success,
        //back to normal, receiving map update
        character_transmit_data,
        map_object_load,
        map_object_drop,
        map_security_reply,
        map_door_open,
        map_door_security_reply,
        //character locking
        character_locked,
        player_entity_return,
        player_security_reply,
        movement_location_sync,
        //entities
        entity_load,
        entity_drop,
        entity_reply,
        entity_activate,
        entity_grab_update,
        //misc
        force_reset,
        failed_action, //just when normal things like being unable to fill a cup because it is full!
        server_alive,
        //inventory
        inventory_update,
        storagebox_object_update,
    };

    byte_buffer* cPacket_request_seen(client_struct& inputClient);
    byte_buffer* cpacket_login_newuser(client_struct& inputClient, std::string nameUsed, std::string hashUsed);
    byte_buffer* cPacket_login_failed(client_struct& inputClient, std::string nameUsed);
    byte_buffer* cPacket_login_success(client_struct& inputClient, std::string nameUsed);
    byte_buffer* cpacket_character_transmit_data(client_struct& inputClient, std::string jsonStringOfEntity);
    byte_buffer* cpacket_map_object_load(client_struct& inputClient,mapConstruction* inputConstruction);
    byte_buffer* cpacket_map_object_drop(client_struct& inputClient,mapConstruction* inputConstruction);
    //map_security_reply,
    //map_door_open,
    //map_door_security_reply,
    ///character locking
    byte_buffer* cpacket_character_lock(client_struct& inputClient, int input_EntityNumber);
    byte_buffer* cpacket_playerentity_return( client_struct& inputClient, int input_EntityNumber, int get_object_index, double get_x, double get_y, bool get_hide);
    //player_security_reply,
    //movement_location_sync,
    ///entities
    //entity_load,
    byte_buffer* cpacket_entity_drop(client_struct& inputClient, int input_EntityNumber);
    //entity_reply,
    //entity_activate,
    byte_buffer* cpacket_entity_grab_update(client_struct& inputClient, int input_EntityNumber);
    ///misc
    byte_buffer* cpacket_force_reset( client_struct& inputClient, std::string errorString);
    byte_buffer* cpacket_failed_action( client_struct& inputClient, std::string errorString); //just when normal things like being unable to fill a cup because it is full!
    byte_buffer* cpacket_server_alive(client_struct& inputClient);
    ///inventory
    //inventory_update,
    //storagebox_object_update,
}

#endif
