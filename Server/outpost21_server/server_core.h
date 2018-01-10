#ifndef SERVERCORE_H
#define SERVERCORE_H

#include "client_transmit_packets.h"
#include <SFML/Network.hpp>
#include <pthread.h>
#include <vector>
#include <map>

class entity;


class serverCore {
    //object_index list
    //create asset index list
    std::map <std::string, int> object_index;
    std::map <int, std::string> asset_index;

    public:
    //entity list
    std::vector<entity*> entity_vector;

    //This function populates the asset and object indexs for reverse lookup of each!
    void CreateObjectAndAssetIndex(std::string inputAssetIndex);
    std::string getAssetOfIndex(int inputObjIndex);
    int getIndexOfAsset(std::string inputAstIndex);

    sf::TcpListener listener;
    int server_port = 0;

    //unique x and y locations
    const double entity_deletion_abyss = -4000;
    const double entity_item_storage = -4000;

    //constants
    static const int server_maxplayers = 16;
    const double forced_movement_decelerator = 0.925;
    const double forced_movement_minimum_cutoff = 0.30;
    const double maximum_movement = 20;
    const int server_tickrate = 60; //ticks per second

    const int map_size = 16384;
    const int map_min_xlimit = 10;
    const int map_min_ylimit = 10;
    const int map_max_xlimit = map_size-10;
    const int map_max_ylimit = map_size-10;

    //socket threads
    pthread_t* SocketThreads[server_maxplayers];
    bool spawn_new_socket = true;

    //entities
    int entity_process_cycle = 0;


    //file paths
    const std::string serverdata_file_path = "server_data.ini";

    //add entity
    void entity_add(entity* entityToAdd);
    void entity_remove(int entityNumberToRemove);
    void set_update_flag( int entityNumberToUpdate, int clientNumber, bool updateFlag);
};


extern serverCore serverObj;


class entity {
    std::string object_index = "obj_puppet_generic";
    bool indestructable = false;
    //external inventory control
    bool is_liquid = false;
    int is_size = 0; //item is a physical size of
    //self inventory
    int grabbing_entity = -1;
    std::vector<int> contains_map;
    int contains_max = 0; //inventory max size
    bool contains_type_liquid = false;
    int contains_size = 0; //item physical size that can be held
    //server side collision entitys
    int SS_collision = -1; //mass update handles this
    bool SS_collision_ignores_walls = false;
    double SS_bouncyness = 0.5;
    double SS_decelerator = serverObj.forced_movement_decelerator;
    //if constructed it does not move
    bool constructed = false;
    int entity_last_process_cycle = 0;

    public:
    int entity_number = -1; //index in entity vector
    int inside_of_id = -1;
    bool needs_update[serverObj.server_maxplayers]; //is a list of player flags!
    //entity core
    double x = 0;
    double y = 0;
    double last_update_x = 0;
    double last_update_y = 0;
    float dir = 0;
    double spd = 0;
    //item displaying
    bool contains_display = false; //if true the object will display its contents on or in it
    double contains_display_x = 0; //relative to own x
    double contains_display_y = 0; //relative to own y
    int contains_display_d = 0; //relative to own depth

    ///personal variable map, because c++ does not support derived member access from pointers of base class! :D FUCK ME RIGHT?
    std::map <std::string, int> myIntVars;
    std::map <std::string, std::string> myStringVars;

    ///security clearance
    std::vector<bool> securityLevel;

    ///functions
    entity(std::string set_object_index,double set_x,double set_y, float set_dir, double set_spd, bool set_indestructable, int set_insideid);
    void entity_set_inventorylimits( int inventory_size, int max_storeable_item_size, int item_size, bool is_a_liquid, bool contains_a_liquid, int item_class, int inventory_storage_class);
    void entity_step(); //physics calc
    void entity_securityInit();
    virtual void entity_personal_step();
};




#endif
