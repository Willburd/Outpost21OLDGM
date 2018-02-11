#ifndef SERVERCORE_H
#define SERVERCORE_H

//=================================
// forward declared dependencies
class entity;
struct mapConstruction;
struct byte_buffer;
struct client_struct;

//=================================
// included dependencies
#include <SFML/Network.hpp>
#include <pthread.h>
#include <vector>
#include <queue>
#include <map>
#include <fstream>
#include <iostream>
#include "json/json.hpp"





struct client_struct {
    sf::TcpSocket mySocket;
    int myNumber = -1;
    int myPlayerEntity = -1;

    int mapDownloadAllow = 0; ///0 is locked, 1 is unlocked, 2 is pending unlock next tick
    std::deque<mapConstruction*> mapDownloadQueue;
    int delayCounter = 10; //GM is a huge butt and requires a minimum delay between packets
    std::deque<byte_buffer*> packetQueue;
};

struct userAccount {
    std::string userName = "";
    std::string userHash = "";
};


struct securityLevel {
    std::string name = "";
    unsigned int color = 0;
};

struct mapConstruction {
    float angle = 0;
    int health = 100;
    unsigned int map_entity = 0;
    std::string obj = "obj_road";
    bool remove_flag = false;
    double x = 0;
    double y = 0;
};


class serverCore {
    //object_index list
    //create asset index list
    std::map <std::string, int> object_index;
    std::map <int, std::string> asset_index;

    //user account list
    std::vector<userAccount*> userAccountVector;

    public:
    //client list
    std::map< unsigned int, client_struct*> clientNumberMap;

    //construction list
    std::map< unsigned int, mapConstruction*> construction_map;

    //entity list
    std::map< unsigned int, entity*> entity_map;

    //security data list
    std::map< unsigned int, securityLevel*> mapSecurityLevels;

    //This function populates the asset and object indexs for reverse lookup of each!
    void CreateObjectAndAssetIndex(std::string inputAssetIndex);
    int assetIndex_currentEntry = 0;
    std::string getAssetOfIndex(int inputObjIndex);
    int getIndexOfAsset(std::string inputAstIndex);

    sf::TcpListener listener;
    int server_port = 0;
    int server_tickrate = 60; //ticks per second
    int clientMaxDelay = 0;
    bool showMapLoad = false;
    bool showEntityLoad = false;
    bool showSecurityLoad = false;

    //unique x and y locations
    const double entity_deletion_abyss = -4000;
    const double entity_item_storage = -2000;

    //constants
    const int entity_activation_range = 500;
    const double forced_movement_decelerator = 0.925;
    const double forced_movement_minimum_cutoff = 0.30;
    const double maximum_movement = 20;

    const int map_size = 16384;
    const int map_min_xlimit = 10;
    const int map_min_ylimit = 10;
    const int map_max_xlimit = map_size-10;
    const int map_max_ylimit = map_size-10;

    const int place_grab_range = 108;

    //socket threads
    pthread_t* SocketThreads[ 128];
    int server_maxplayers = 16;
    bool spawn_new_socket = true;

    //entities
    unsigned long long int entity_process_cycle = 0;
    bool entity_classStorageCheck( uint16_t input_item_class, uint16_t storage_class_allowed, client_struct& inputClient);

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
    void entity_releaseEntity(int entityToRelease, double inx, double iny);
    void set_update_flag( int entityNumberToUpdate, client_struct* clientInput, bool updateFlag);
    void set_update_flagALL( int entityNumberToUpdate, bool updateFlag);
    //main processing function
    void gameUpdate();
    //loading
    bool gameMapLoad(std::string mapFilePath);
    //sub functions of map loads
    void userdataLoad(nlohmann::json u);
    void securityMapLoad(nlohmann::json j);
    void entityMapLoad(nlohmann::json e);
    void entityConstructLoad(nlohmann::json c);
    entity* entityJsonDecode(nlohmann::json a);
    std::string entityJsonEncode( entity* inputEntity);
};
extern serverCore serverObj;


class entity {
    entity(const entity& that);
    std::string asset_index = "obj_puppet_generic";
    bool indestructable = false;
    //external inventory control
    int is_type_class = 0;
    bool is_liquid = false;
    int is_size = 0; //item is a physical size of
    //self inventory
    int grabbing_entity = -1;
    unsigned int contains_max = 0; //inventory max size
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
    std::map< client_struct*, bool > needsUpdate_map; //uses client's to check if it needs to update!
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
    entity(std::string set_object_index,double set_x,double set_y, float set_dir, double set_spd, bool set_indestructable);
    virtual ~entity();
    void entity_set_inventorylimits( int inventory_size, int max_storeable_item_size, int item_size, bool is_a_liquid, bool contains_a_liquid, int item_class, int inventory_storage_class);
    void entity_step(); //physics calc
    void entity_update_clients();
    void entity_securityInit();
    void entity_securityUpdate();

    //get only
    int entity_getObjectIndex();
    std::string entity_getAssetIndex();
    unsigned int entity_getInventoryMaxSize();
    int entity_getInventoryItemSizeMax();
    bool entity_getInventoryAllowLiquids();
    int entity_getInventoryItemClassAllowed();
    client_struct* entity_getPlayerClient();

    unsigned int entity_getGrabbed();
    bool entity_getConstructed();
    bool entity_getIndestructable();
    int entity_getItemClass();
    int entity_getItemSize();
    bool entity_getItemIsLiquid();

    void entity_setGrabbed(unsigned int entityNumber);
    void entity_setConstructed(bool setCon);
    void entity_setIndestructable(bool input);

    bool entity_checkProcessingCycle();
    void entity_updateProcessingCycle();

    bool entityIsPlayer();

    virtual void entity_personal_step();
};


#endif
