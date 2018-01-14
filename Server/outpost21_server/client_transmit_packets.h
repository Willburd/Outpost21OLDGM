#ifndef CLIENTTRANSMIT_H
#define CLIENTTRANSMIT_H

#include <cstring>
#include "client_structure.h"
#include "byte_buffer.h"


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

    int cPacket_request_seen(client_struct& inputClient);
    //login_newuser,
    int cPacket_login_failed(client_struct& inputClient, std::string nameUsed);
    int cPacket_login_success(client_struct& inputClient, std::string nameUsed);
    int cpacket_character_transmit_data(client_struct& inputClient, std::string jsonStringOfEntity);
    //map_object_load,
    //map_object_drop,
    //map_security_reply,
    //map_door_open,
    //map_door_security_reply,
    ///character locking
    int cpacket_character_lock(client_struct& inputClient, int input_EntityNumber);
    int cpacket_playerentity_return( client_struct& inputClient, int input_EntityNumber, int get_object_index, double get_x, double get_y, bool get_hide);
    //player_security_reply,
    //movement_location_sync,
    ///entities
    //entity_load,
    int cpacket_entity_drop(client_struct& inputClient, int input_EntityNumber);
    //entity_reply,
    //entity_activate,
    //entity_grab_update,
    ///misc
    int cpacket_force_reset( client_struct& inputClient, std::string errorString);
    //failed_action, //just when normal things like being unable to fill a cup because it is full!
    int cpacket_server_alive(client_struct& inputClient);
    ///inventory
    //inventory_update,
    //storagebox_object_update,
};

#endif
