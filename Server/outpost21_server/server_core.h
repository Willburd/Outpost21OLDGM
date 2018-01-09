#ifndef SERVERCORE_H
#define SERVERCORE_H

#include "client_transmit_packets.h"
#include <SFML/Network.hpp>
#include <pthread.h>
#include <vector>

class entity;


struct global_vars {
    sf::TcpListener listener;
    int server_port = 0;
    static const int server_maxplayers = 16;

    //socket threads
    pthread_t* SocketThreads[server_maxplayers];
    bool spawn_new_socket = true;

    //constants
    double forced_movement_decelerator = 0.925;
    double forced_movement_minimum_cutoff = 0.30;
    double maximum_movement = 20;

    int map_size = 16384;
    int map_min_xlimit = 10;
    int map_min_ylimit = 10;
    int map_max_xlimit = map_size-10;
    int map_max_ylimit = map_size-10;

    //entities
    int entity_process_cycle = 0;
    std::vector<entity*> entity_vector;

    //file paths
    const std::string serverdata_file_path = "server_data.ini";
};


extern global_vars global;


class entity {
    std::string object_index = "obj_puppet_generic";
    int entity_number = -1; //index in entity vector
    bool needs_update[global.server_maxplayers]; //is a list of player flags!
    bool indestructable = false;
    //external inventory control
    int inside_of_id = -1;
    bool is_liquid = false;
    int is_size = 0; //item is a physical size of
    //self inventory
    int grabbing_entity = -1;
    std::vector<int> contains_map;
    int contains_max = 0; //inventory max size
    bool contains_type_liquid = false;
    int contains_size = 0; //item physical size that can be held
    //item displaying
    bool contains_display = false; //if true the object will display its contents on or in it
    double contains_display_x = 0; //relative to own x
    double contains_display_y = 0; //relative to own y
    int contains_display_d = 0; //relative to own depth
    //server side collision entitys
    int SS_collision = -1; //mass update handles this
    bool SS_collision_ignores_walls = false;
    double SS_bouncyness = 0.5;
    double SS_decelerator = global.forced_movement_decelerator;
    //if constructed it does not move
    bool constructed = false;
    int entity_last_process_cycle = 0;

    public:
    double x = 0;
    double y = 0;
    double last_update_x = 0;
    double last_update_y = 0;
    float dir = 0;
    double spd = 0;

    entity(std::string set_object_index,double set_x,double set_y, float set_dir, double set_spd, bool set_indestructable, int set_insideid);
    ~entity();
    void entity_set_inventorylimits( int inventory_size, int max_storeable_item_size, int item_size, bool is_a_liquid, bool contains_a_liquid, int item_class, int inventory_storage_class);
    void entity_step(); //physics calc
    virtual void entity_personal_step();
};




#endif
