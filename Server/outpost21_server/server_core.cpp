#include "server_core.h"

///SERVER CORE
void global_vars::CreateObjectAndAssetIndex(std::string inputAssetIndex) {
    int get_last_index = object_index.size();

    //add latest index!
    object_index[inputAssetIndex] = get_last_index;
    asset_index[get_last_index] = inputAssetIndex;
}


std::string global_vars::getAssetOfIndex(int inputObjIndex) {
    return asset_index[inputObjIndex];
}
int global_vars::getIndexOfAsset(std::string inputAstIndex) {
    return object_index[inputAstIndex];
}


void global_vars::entity_add(entity* entityToAdd) {
    for(int i = 0; i < entity_vector.size()+1; i++) {
        if(i == entity_vector.size()
        || entity_vector[i] == nullptr) {
            ///add at the end of list, or if a blank space is found
            entity_vector[i] = entityToAdd;
            break;
        }
    }
};


///ENTITY

entity::entity(std::string set_object_index,double set_x,double set_y, float set_dir, double set_spd, bool set_indestructable, int set_insideid) {
    //constructor
    std::string object_index = set_object_index;
    int entity_number = -1; //index in entity vector
    double x = set_x;
    double y = set_y;
    double last_update_x = set_x;
    double last_update_y = set_y;
    float dir = set_dir;
    double spd = set_spd;
    int inside_of_id = set_insideid;
    bool indestructable = set_indestructable;

    //set all update flags
    for (int i = 0; i < global.server_maxplayers+1; i++)
    {
        needs_update[global.server_maxplayers] = true; //is a list of player flags!
    }
}


void entity::entity_set_inventorylimits( int inventory_size, int max_storeable_item_size, int item_size, bool is_a_liquid, bool contains_a_liquid, int item_class, int inventory_storage_class) {
    is_liquid = is_a_liquid;
    is_size = item_size; //item is a physical size of
    //self inventory
    int contains_max = inventory_size; //inventory max size
    bool contains_type_liquid = contains_a_liquid;
    int contains_size = max_storeable_item_size; //item physical size that can be held
}


void entity::entity_securityInit() {
    securityLevel[ 0] = false;
    securityLevel[ 1] = false;
    securityLevel[ 2] = false;
    securityLevel[ 3] = false;
    securityLevel[ 4] = false;
    securityLevel[ 5] = false;
    securityLevel[ 6] = false;
    securityLevel[ 7] = false;
    securityLevel[ 8] = false;
    securityLevel[ 9] = false;
}


void entity::entity_step() {
    //physics calculation, movement, and collisions
    if(entity_last_process_cycle != global.entity_process_cycle) {


        //personal update
        entity_personal_step();

        //prevent update in the same frame somehow
        entity_last_process_cycle = global.entity_process_cycle;
    }
}


void entity::entity_personal_step() {
    //enacts personal countdowns, or transforms it into other entities
    //for example, coffee cooling down and changing into cold coffee
}
