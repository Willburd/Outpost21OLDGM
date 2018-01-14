#ifndef SERVERCORE_H
#define SERVERCORE_H

#include "client_transmit_packets.h"
#include "json/json.hpp"
#include <SFML/Network.hpp>
#include <pthread.h>
#include <vector>
#include <map>



class entity;


struct userAccount {
    std::string userName = "";
    std::string userHash = "";
};


struct securityLevel {
    std::string name = "";
    unsigned int color = 0;
};


class serverCore {
    //object_index list
    //create asset index list
    std::map <std::string, int> object_index;
    std::map <int, std::string> asset_index;
    //user account list
    std::vector<userAccount*> userAccountVector;

    public:
    //entity list
    std::map< unsigned int, entity*> entity_map;

    //security data list
    std::map< unsigned int, securityLevel*> mapSecurityLevels;

    //This function populates the asset and object indexs for reverse lookup of each!
    void CreateObjectAndAssetIndex(std::string inputAssetIndex);
    std::string getAssetOfIndex(int inputObjIndex);
    int getIndexOfAsset(std::string inputAstIndex);

    sf::TcpListener listener;
    int server_port = 0;
    int server_tickrate = 60; //ticks per second

    //unique x and y locations
    const double entity_deletion_abyss = -4000;
    const double entity_item_storage = -2000;

    //constants
    static const int server_maxplayers = 16;
    const double forced_movement_decelerator = 0.925;
    const double forced_movement_minimum_cutoff = 0.30;
    const double maximum_movement = 20;

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

    //accounts
    void userAccountAdd( std::string name, std::string passHash);
    bool userAccountExists( std::string name);
    bool userAccountLogin( std::string name, std::string passHash);
    void userAccountRemove( std::string name, std::string passHash); //inputs are used to confirm delete

    //add entity
    void securityLevelAdd( unsigned int index,std::string inputName, int inputColor);
    void securityLevelRemove( unsigned int index);
    int entity_add(entity* entityToAdd); //dynamically add the entity to the vector
    void entity_set(entity* entityToAdd, unsigned int entityNumberToAssign); //forcibly set the new entity to a specific index, used for file loading
    void entity_remove(int entityNumberToRemove);
    void entity_storeEntity(int entityToStore,int storageBoxEntity);
    void entity_releaseEntity(int entityToStore,int storageBoxEntity, double inx, double iny);
    void set_update_flag( int entityNumberToUpdate, int clientNumber, bool updateFlag);

    bool gameMapLoad(std::string mapFilePath);
    //sub functions of map loads
    void userdataLoad(nlohmann::json u);
    void securityMapLoad(nlohmann::json j);
    void entityMapLoad(nlohmann::json e);
    entity* entityJsonDecode(nlohmann::json a);
    std::string entityJsonEncode( entity* inputEntity);
};


extern serverCore serverObj;


class entity {
    entity(const entity& that);
    std::string object_index = "obj_puppet_generic";
    bool indestructable = false;
    //external inventory control
    int is_type_class = 0;
    bool is_liquid = false;
    int is_size = 0; //item is a physical size of
    //self inventory
    int grabbing_entity = -1;
    int contains_max = 0; //inventory max size
    bool contains_type_liquid = false;
    int contains_size = 0; //item physical size that can be held
    int contains_class = 0; //item physical size that can be held
    //if constructed it does not move
    bool constructed = false;
    int entity_last_process_cycle = 0;

    public:
    int entity_number = -1; //index in entity vector
    int inside_of_id = -1;
    std::vector<int> contains_vector;
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
    //server side collision entitys
    int SS_collision = -1; //mass update handles this
    bool SS_collision_ignores_walls = false;
    double SS_bouncyness = 0.5;
    double SS_decelerator = serverObj.forced_movement_decelerator;

    ///personal variable map, because c++ does not support derived member access from pointers of base class! :D FUCK ME RIGHT?
    std::map <std::string, int> myIntVars;
    std::map <std::string, std::string> myStringVars;

    ///security clearance
    std::map <unsigned int,bool> entitySecurityLevels;

    ///functions
    entity(std::string set_object_index,double set_x,double set_y, float set_dir, double set_spd, bool set_indestructable, int set_insideid);
    virtual ~entity();
    void entity_set_inventorylimits( int inventory_size, int max_storeable_item_size, int item_size, bool is_a_liquid, bool contains_a_liquid, int item_class, int inventory_storage_class);
    void entity_step(); //physics calc
    void entity_securityInit();
    void entity_securityUpdate();

    //get only
    std::string entity_getObjectIndex();
    int entity_getInventoryMaxSize();
    int entity_getInventoryItemSizeMax();
    bool entity_getInventoryAllowLiquids();
    int entity_getInventoryItemClassAllowed();

    unsigned int entity_getGrabbed();
    bool entity_getConstructed();
    bool entity_getIndestructable();
    int entity_getItemClass();
    int entity_getItemSize();
    bool entity_getItemIsLiquid();

    void entity_setGrabbed(unsigned int entityNumber);
    void entity_setConstructed(bool setCon);
    void entity_setIndestructable(bool input);

    virtual void entity_personal_step();
};




#endif
