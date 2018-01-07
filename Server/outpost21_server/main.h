#include <iostream>
#include <cstring>
#include <SFML/Network.hpp>

///NOTICE this needs to match the enum in the game maker side client!
namespace client_transmission_packets {
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
};


namespace server_recieving_packets{
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
        security_tool_toggledoorsecurity,
    };
};




int main();
