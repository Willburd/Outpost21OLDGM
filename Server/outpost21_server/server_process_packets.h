#ifndef SERVERPROCESS_H
#define SERVERPROCESS_H

#include "client_transmit_packets.h"
#include <SFML/Network.hpp>
#include <pthread.h>

namespace server_recieving_packets {
    ///NOTICE this needs to match the enum in the game maker side client!
    enum enum_server_packets : uint16_t {
        //logins
        login_requested,
        heartbeat_request,
        login_newuser,
        //character aquisition
        character_get_all_owned,
        character_query,
        character_created,
        character_loaded,
        //player entity
        player_object_request,
        player_release_grab,
        map_request_whole,
        client_map_preloaded,
        client_ready_for_map_download,
        map_object_create,
        map_object_destroy,
        map_request_securitydata,
        map_request_door_security,
        //movement
        movement_location_request,
        movement_location_update,
        //inventory
        entity_request_all,
        entity_create,
        entity_create_direction,
        entity_store,
        entity_throw, //flows into place
        entity_place,
        entity_drop, //not placing, unloading an entity from client inputs!
        entity_construct,
        entity_deconstruct,
        entity_inventory_request,
        entity_interact,
        //security tool editing doors
        security_tool_requestdoor,
        security_tool_toggledoorsecurity
    };

    void* serverProcessLoop(void *threadid);
};

#endif
