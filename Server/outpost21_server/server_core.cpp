#include "server_core.h"
#include "json/json.hpp"
#include "entitylibrary/entity_library.h"
#include <fstream>

///SERVER CORE
void serverCore::CreateObjectAndAssetIndex(std::string inputAssetIndex) {
    int get_last_index = object_index.size();

    //add latest index!
    object_index[inputAssetIndex] = get_last_index;
    asset_index[get_last_index] = inputAssetIndex;
}


std::string serverCore::getAssetOfIndex(int inputObjIndex) {
    return asset_index[inputObjIndex];
}
int serverCore::getIndexOfAsset(std::string inputAstIndex) {
    return object_index[inputAstIndex];
}

//accounts
void serverCore::userAccountAdd( std::string name, std::string passHash) {
    userAccount* getNewAccount = new userAccount;
    getNewAccount->userName = name;
    getNewAccount->userHash = passHash;

    userAccountVector.push_back(getNewAccount);
}

bool serverCore::userAccountLogin( std::string name, std::string passHash) {
    bool getLogin = false;

    for(std::vector<userAccount*>::iterator it = userAccountVector.begin(); it != userAccountVector.end(); ++it) {
        userAccount* getAcc = *it;

        if(getAcc->userName == name) {
            if(getAcc->userHash == passHash) {
                //password confirmed. deleting
                getLogin = true;
                break;
            }
        }
    }

    return getLogin;
}

bool serverCore::userAccountExists( std::string name) {
    bool userExists = false;

    for(std::vector<userAccount*>::iterator it = userAccountVector.begin(); it != userAccountVector.end(); ++it) {
        userAccount* getAcc = *it;

        if(getAcc->userName == name) {
            userExists = true;
            break;
        }
    }

    return userExists;
}

void serverCore::userAccountRemove( std::string name, std::string passHash) { //inputs are used to confirm delete
    for(std::vector<userAccount*>::iterator it = userAccountVector.begin(); it != userAccountVector.end(); ++it) {
        userAccount* getAcc = *it;

        if(getAcc->userName == name) {
            if(getAcc->userHash == passHash) {
                //password confirmed. deleting
                delete getAcc;
            }
        }
    }
}


void serverCore::securityLevelAdd( unsigned int index, std::string inputName, int inputColor) {

    securityLevel* newSec = new securityLevel;
    newSec->name = inputName;
    newSec->color = inputColor;

    //add to sec vector
    mapSecurityLevels[index] = newSec;
}

void serverCore::securityLevelRemove( unsigned int index) {
    //remove security level from map.
    if(mapSecurityLevels[index] == nullptr) {
        delete mapSecurityLevels[index];

        ///TODO!!!
        //update all entities to remove that clearance

        //set all doors with this clearance to remove it.
    }
}


int serverCore::entity_add(entity* entityToAdd) {
    int returnEnt = -1;

    for(unsigned int i = 0; i < entity_map.size()+1; i++) {
        if(i == entity_map.size()
        || entity_map[i] == nullptr) {

            std::cout << "Assigning entity number: " << i << std::endl;

            ///add at the end of list, or if a blank space is found
            entity_map[i] = entityToAdd;
            entityToAdd->entity_number = i;
            returnEnt = i;
            break;
        }
    }

    return returnEnt;
};


void serverCore::entity_set(entity* entityToAdd, unsigned int entityNumberToAssign) {
    if(entityNumberToAssign >= entity_map.size() || entity_map[entityNumberToAssign] == nullptr) {

        std::cout << "Assigning entity number: " << entityNumberToAssign << std::endl;

        ///add at the end of list, or if a blank space is found
        entity_map[entityNumberToAssign] = entityToAdd;
        entityToAdd->entity_number = entityNumberToAssign;
    }
};


void serverCore::entity_remove(int entityNumberToRemove) {
    if(entityNumberToRemove >= 0
    && entity_map[entityNumberToRemove] != nullptr) {
        //place entity in abyss so the clients are repeatedly FORCED to unload it!
        entity* get_ent = entity_map[entityNumberToRemove];
        get_ent->x = serverObj.entity_deletion_abyss;
        get_ent->y = serverObj.entity_deletion_abyss;
    }
};


void serverCore::entity_storeEntity( int entityToStore, int storageBoxEntity) {
    ///DIRECT storage, has NO safeties! NO inventory check limits! Can even store inside itself!
    //push storing entity into storagebox
    entity* getStorageEntity = entity_map[storageBoxEntity];
    entity* oldStorageEntity = nullptr;
    getStorageEntity->contains_vector.push_back(entityToStore);


    //remove storing entity from old inventory!
    entity* getStoredEntity = entity_map[entityToStore];
    if(getStoredEntity->inside_of_id != -1) {
        oldStorageEntity = entity_map[getStoredEntity->inside_of_id];

        for(std::vector<int>::iterator it = oldStorageEntity->contains_vector.begin(); it != oldStorageEntity->contains_vector.end();) {
            if(*it == entityToStore) {
                it = oldStorageEntity->contains_vector.erase(it);
                break;
            }
            else
            {
                ++it;
            }
        }
    }
    //tell storing entity to put itself inside storagebox
    getStoredEntity->inside_of_id = storageBoxEntity;
    getStoredEntity->x = entity_item_storage;
    getStoredEntity->y = entity_item_storage;
    getStoredEntity->dir = 0;
    getStoredEntity->spd = 0;
    getStoredEntity->entity_setConstructed(false);

    //security updates
    if(getStoredEntity->entity_getObjectIndex() == "obj_puppet_securitycard") {
        //update both as needed!
        getStoredEntity->entity_securityUpdate();
        getStorageEntity->entity_securityUpdate();
        if(oldStorageEntity != nullptr) oldStorageEntity->entity_securityUpdate();
    }

    //drop and load updates for clients
    serverObj.set_update_flagALL(entityToStore,true);
    serverObj.set_update_flagALL(storageBoxEntity,true);
    if(oldStorageEntity != nullptr) serverObj.set_update_flagALL(oldStorageEntity->entity_number,true);

    //send storagebox updates to clients to close inventory windows as needed
    ///TODO storagebox update function
}

void serverCore::entity_releaseEntity( int entityToRelease, double inx, double iny) {
    ///DIRECT inventory release! NO SAFETIES!
    //remove storing entity from old inventory!
    entity* oldStorageEntity = nullptr;
    entity* getStoredEntity = entity_map[entityToRelease];

    if(getStoredEntity->inside_of_id != -1) {
        oldStorageEntity = entity_map[getStoredEntity->inside_of_id];

        for(std::vector<int>::iterator it = oldStorageEntity->contains_vector.begin(); it != oldStorageEntity->contains_vector.end();) {
            if(*it == entityToRelease) {
                it = oldStorageEntity->contains_vector.erase(it);
                break;
            }
            else
            {
                ++it;
            }
        }
    }

    //tell storing entity to put itself inside storagebox
    getStoredEntity->inside_of_id = -1;
    getStoredEntity->x = inx;
    getStoredEntity->y = iny;

    //security updates
    if(getStoredEntity->entity_getObjectIndex() == "obj_puppet_securitycard") {
        //update both as needed!
        getStoredEntity->entity_securityUpdate();
        oldStorageEntity->entity_securityUpdate();
    }
}


bool serverCore::entity_classStorageCheck( uint16_t input_item_class, uint16_t storage_class_allowed, client_struct& inputClient) {
    bool allow_item = false;

    switch(storage_class_allowed) {
        case entityLibrary::itemdata::generic:
        case entityLibrary::itemdata::ship:
            //allows all classes inside!
            allow_item = true;
        break;

        case entityLibrary::itemdata::tools:
            //only tools and related allowed
            if(input_item_class == entityLibrary::itemdata::tools) allow_item = true;

            if(allow_item == false) {
                client_transmission_packets::cpacket_failed_action( inputClient, "Object can only hold tools.");
            }
        break;

        case entityLibrary::itemdata::sheets:
            if(input_item_class == entityLibrary::itemdata::sheets) allow_item = true;

            if(allow_item == false) {
                client_transmission_packets::cpacket_failed_action( inputClient, "Object can only hold sheets.");
            }
        break;

        case entityLibrary::itemdata::food:
            if(input_item_class == entityLibrary::itemdata::food) allow_item = true;

            if(allow_item == false) {
                client_transmission_packets::cpacket_failed_action( inputClient, "Object can only hold food.");
            }
        break;

        case entityLibrary::itemdata::machines:
            if(input_item_class == entityLibrary::itemdata::machines) allow_item = true;

            if(allow_item == false) {
                client_transmission_packets::cpacket_failed_action( inputClient, "Object can only hold machines.");
            }
        break;

        case entityLibrary::itemdata::machine_parts:
            if(input_item_class == entityLibrary::itemdata::machine_parts) allow_item = true;

            if(allow_item == false) {
                client_transmission_packets::cpacket_failed_action( inputClient, "Object can only hold machine parts.");
            }
        break;

        case entityLibrary::itemdata::clothing:
            if(input_item_class == entityLibrary::itemdata::clothing) allow_item = true;

            if(allow_item == false) {
                client_transmission_packets::cpacket_failed_action( inputClient, "Object can only hold clothing.");
            }
        break;

        case entityLibrary::itemdata::rifle:
            if(input_item_class == entityLibrary::itemdata::rifle) allow_item = true;
        case entityLibrary::itemdata::pistol:
            if(input_item_class == entityLibrary::itemdata::pistol) allow_item = true;

            if(allow_item == false) {
                client_transmission_packets::cpacket_failed_action( inputClient, "Object can only hold firearms.");
            }
        break;
    }

    return allow_item;
}


void serverCore::set_update_flag( int entityNumberToUpdate, int clientNumber, bool updateFlag) {
    if(entityNumberToUpdate >= 0
    && entity_map[entityNumberToUpdate] != nullptr) {
        //set the entities updateflag for this client!
        entity* get_ent = entity_map[entityNumberToUpdate];
        get_ent->needs_update[ clientNumber] = updateFlag;
    }
}

void serverCore::set_update_flagALL( int entityNumberToUpdate, bool updateFlag) {
    if(entityNumberToUpdate >= 0
    && entity_map[entityNumberToUpdate] != nullptr) {
        for (std::map<unsigned int,client_struct*>::iterator it = serverObj.clientNumberMap.begin(); it != serverObj.clientNumberMap.end(); it++ )
        {
            set_update_flag( entityNumberToUpdate, it->first, updateFlag);
        }
    }
}


void serverCore::userdataLoad(nlohmann::json u) {
    for (nlohmann::json::iterator it = u.begin(); it != u.end(); ++it) {
        //add all current logins!
        serverObj.userAccountAdd(it.key(),it.value());
    }
}


void serverCore::securityMapLoad(nlohmann::json j) {
    for (nlohmann::json::iterator it = j.begin(); it != j.end(); ++it) {
        nlohmann::json jsonSecurity = (nlohmann::json)*it;

        if(jsonSecurity.is_object()) {
            //add security level to vector
            std::cout << "====Loading Security level: " << std::endl;

            unsigned int getIndex = jsonSecurity.at("index").get<int>();
            std::cout << " |---------index: " << getIndex << std::endl;

            std::string getName = jsonSecurity.at("name").get<std::string>();
            std::cout << " |----------name: " << getName << std::endl;

            unsigned int getColor = jsonSecurity.at("color").get<int>();
            std::cout << " |---------color: " << getColor << std::endl;

            securityLevelAdd(getIndex,getName,getColor);
        }
    }
}

std::string serverCore::entityJsonEncode( entity* inputEntity) {
    nlohmann::json returnJson = {
        {"entity_number", inputEntity->entity_number},
        {"object_index", inputEntity->entity_getObjectIndex()},

        {"x", inputEntity->x},
        {"y", inputEntity->y},
        {"last_update_x", inputEntity->last_update_x},
        {"last_update_y", inputEntity->last_update_y},
        {"dir", inputEntity->dir},
        {"spd", inputEntity->spd},

        {"constructed", inputEntity->entity_getConstructed()},
        {"inside_of_id", inputEntity->inside_of_id},
        {"grabbing_entity", inputEntity->entity_getGrabbed()},
        {"indestructable", inputEntity->entity_getIndestructable()},

        {"SS_collision_ignores_walls", inputEntity->SS_collision_ignores_walls},
        {"SS_bouncyness", inputEntity->SS_bouncyness},
        {"SS_decelerator", inputEntity->SS_decelerator},

        {"contains_display", inputEntity->contains_display},
        {"contains_display_d", inputEntity->contains_display_d},
        {"contains_display_x", inputEntity->contains_display_x},
        {"contains_display_y", inputEntity->contains_display_y},

        {"contains_max", inputEntity->entity_getInventoryMaxSize()},
        {"contains_size", inputEntity->entity_getInventoryItemSizeMax()},
        {"contains_type_liquid", inputEntity->entity_getInventoryAllowLiquids()},
        {"contains_class", inputEntity->entity_getInventoryItemClassAllowed()},

        {"is_class", inputEntity->entity_getItemClass()},
        {"is_size", inputEntity->entity_getItemSize()},
        {"is_liquid", inputEntity->entity_getItemIsLiquid()},
        {"contains_map", inputEntity->contains_vector},
        {"security_levels", inputEntity->entitySecurityLevels}
    };

    //get the dynamic variables from the entity
    nlohmann::json jmap_Int(inputEntity->myIntVars);
    nlohmann::json jmap_String(inputEntity->myStringVars);

    //merge
    returnJson.insert(jmap_Int.begin(), jmap_Int.end());
    returnJson.insert(jmap_String.begin(), jmap_String.end());

    return returnJson.dump();
}


entity* serverCore::entityJsonDecode(nlohmann::json a) {
    //this takes all build in variables and assigns them, leaving the others to be picked up by
    //the entity's personal variables
    int getEntityNumber = -1;
    std::string get_objectindex = "";
    double getx = 0;
    double gety = 0;
    float getdir = 0;
    double getspd = 0;
    bool getindestruct = false;

    bool get_disp = false;
    int get_disp_d = 0;
    double get_disp_x = 0;
    double get_disp_y = 0;

    int getinsideof = -1;
    int getgrabbing_entity = -1;
    bool getconstructed = false;
    bool get_SS_ignorewalls = false;
    double get_SS_bouncyness = 0;
    double get_SS_decelerator = 1;

    int get_isclass = 0;
    int get_issize = 0;
    bool get_isliquid = false;
    int get_containsmax = 0;
    int get_containssize = 0;
    bool get_containsliquid = false;
    int get_containsclass = 0;

    std::map <std::string, int> get_myIntVars;
    std::map <std::string, std::string> get_myStringVars;

    std::vector<int> collectedInventory;

    std::cout << "====Loading entity====" << std::endl;
    for (nlohmann::json::iterator it = a.begin(); it != a.end(); ++it) {
        //itterate through entity's properties
        //allows us to set the hard internal values
        //and the soft item specific values
        std::string jsonKey = it.key();

        if(jsonKey == "entity_number") {
            getEntityNumber = a.at(jsonKey).get<int>();
            std::cout << " |------entityID: " << getEntityNumber << std::endl;
        }
        else if(jsonKey == "object_index") {
            get_objectindex = a.at(jsonKey).get<std::string>();
            std::cout << " |-----obj index: " << get_objectindex << std::endl;
        }
        else if(jsonKey == "x") {
            getx = a.at(jsonKey).get<double>();
            std::cout << " |-------------x: " << getx << std::endl;
        }
        else if(jsonKey == "y") {
            gety = a.at(jsonKey).get<double>();
            std::cout << " |-------------y: " << gety << std::endl;
        }
        else if(jsonKey == "last_update_x") {
            //ignore this,
            std::cout << " |----------prvX: DYNAMIC SET..." << std::endl;
        }
        else if(jsonKey == "last_update_y") {
            //ignore this,
            std::cout << " |----------prvY: DYNAMIC SET..." << std::endl;
        }
        else if(jsonKey == "needs_update") {
            //ignore this,
            std::cout << " |---user_update: DEPRICATED" << std::endl;
        }
        else if(jsonKey == "entity_last_process_cycle") {
            //ignore this,
            std::cout << " |----last_cycle: DEPRICATED" << std::endl;
        }
        else if(jsonKey == "dir") {
            getdir = a.at(jsonKey).get<float>();
            std::cout << " |-----------dir: " << getdir << std::endl;
        }
        else if(jsonKey == "spd") {
            getspd = a.at(jsonKey).get<double>();
            std::cout << " |-----------spd: " << getspd << std::endl;
        }
        else if(jsonKey == "indestructable") {
            getindestruct = (bool)a.at(jsonKey).get<int>();
            std::cout << " |----indestruct: " << getindestruct << std::endl;
        }
        else if(jsonKey == "inside_of_id") {
            getinsideof = a.at(jsonKey).get<int>();
            std::cout << " |-----insideent: " << getinsideof << std::endl;
        }
        else if(jsonKey == "grabbing_entity") {
            getgrabbing_entity = a.at(jsonKey).get<int>();
            std::cout << " |---grabbingent: " << getgrabbing_entity << std::endl;
        }
        else if(jsonKey == "constructed") {
            getconstructed = (bool)a.at(jsonKey).get<int>();
            std::cout << " |---constructed: " << getconstructed << std::endl;
        }
        else if(jsonKey == "SS_collision") {
            //ignore this,
            std::cout << " |----SS_coldata: DYNAMIC SET..." << std::endl;
        }
        else if(jsonKey == "SS_collision_ignores_walls") {
            get_SS_ignorewalls = (bool)a.at(jsonKey).get<int>();
            std::cout << " |---SS_ignwalls: " << get_SS_ignorewalls << std::endl;
        }
        else if(jsonKey == "SS_bouncyness") {
            get_SS_ignorewalls = a.at(jsonKey).get<double>();
            std::cout << " |---SS_bouncyns: " << get_SS_bouncyness << std::endl;
        }
        else if(jsonKey == "SS_decelerator") {
            get_SS_ignorewalls = a.at(jsonKey).get<double>();
            std::cout << " |---SS_decelera: " << get_SS_decelerator << std::endl;
        }
        else if(jsonKey == "contains_display") {
            get_disp = (bool)a.at(jsonKey).get<int>();
            std::cout << " |-------display: " << get_disp << std::endl;
        }
        else if(jsonKey == "contains_display_d") {
            get_disp_d = a.at(jsonKey).get<int>();
            std::cout << " |---display_dep: " << get_disp_d  << std::endl;
        }
        else if(jsonKey == "contains_display_x") {
            get_disp_x = a.at(jsonKey).get<double>();
            std::cout << " |-----display_x: " << get_disp_x << std::endl;
        }
        else if(jsonKey == "contains_display_y") {
            get_disp_y = a.at(jsonKey).get<double>();
            std::cout << " |-----display_y: " << get_disp_y << std::endl;
        }
        else if(jsonKey == "contains_max") {
            get_containsmax = a.at(jsonKey).get<int>();
            std::cout << " |---contain_max: " << get_containsmax << std::endl;
        }
        else if(jsonKey == "contains_map") {
            nlohmann::json inv_json = a.at(jsonKey);

            std::cout << " |------Extracting inventory!" << std::endl;
            for (nlohmann::json::iterator it = inv_json.begin(); it != inv_json.end(); ++it) {
                //add all current logins!
                collectedInventory.push_back((int)*it);

                std::cout << "|-------->>" << (int)*it << std::endl;
            }

        }
        else if(jsonKey == "contains_size") {
            get_containssize = a.at(jsonKey).get<int>();
            std::cout << " |--contain_size: " << get_containssize << std::endl;
        }
        else if(jsonKey == "contains_type_liquid") {
            get_containsliquid = (bool)a.at(jsonKey).get<int>();
            std::cout << " |-contain_liqud: " << get_containsliquid << std::endl;
        }
        else if(jsonKey == "contains_class") {
            get_containsclass = a.at(jsonKey).get<int>();
            std::cout << " |-contain_class: " << get_containsclass << std::endl;
        }
        else if(jsonKey == "is_class") {
            get_isclass = a.at(jsonKey).get<int>();
            std::cout << " |-------isclass: " << get_isclass << std::endl;
        }
        else if(jsonKey == "is_size") {
            get_issize = a.at(jsonKey).get<int>();
            std::cout << " |--------issize: " << get_issize << std::endl;
        }
        else if(jsonKey == "is_liquid") {
            get_isliquid = (bool)a.at(jsonKey).get<int>();
            std::cout << " |-------isliqud: " << get_isliquid << std::endl;
        }
        else if(jsonKey == "security_clearance") {
            ///THIS IS FOR SECURITY CARDS! Stores the security level to set to objects
            std::cout << " |------secClear: " << std::endl;

            ///TODO! need to add security data to security cards.
        }
        else if(jsonKey == "security_levels") {
            ///This is for the object's current security status (for doors to check!)
            //ignored. This is manually updated
            std::cout << " |------secLevel: DYNAMIC SET..." << std::endl;
        }
        else
        {
            nlohmann::json jsonEntry = (nlohmann::json)*it;

            std::cout << " |--Personal key: " << jsonKey;

            if(jsonEntry.is_object()) {
                std::cout << " ::objects not supported for custom variable loading" << std::endl;
            }
            else
            {
                if(jsonEntry.is_string()) {
                    get_myStringVars[jsonKey] = jsonEntry.get<std::string>();
                    std::cout << " ::string: " << get_myStringVars[jsonKey] << std::endl;
                }
                else
                {
                    get_myIntVars[jsonKey] = jsonEntry.get<int>();
                    std::cout << " ::int: " << get_myIntVars[jsonKey] << std::endl;
                }
            }
        }
    }

    //call entity create to make the base entity
    entity* make_entity = entityLibrary::entity_template_library(get_objectindex,getx,gety,getdir,getspd,getindestruct);
    make_entity->entity_number = getEntityNumber; ///EXTREMELY IMPORTANT!

    make_entity->entity_set_inventorylimits(get_containsmax,get_containssize,get_issize,get_isliquid,get_containsliquid,get_isclass,get_containsclass);

    make_entity->entity_setConstructed( getconstructed);
    make_entity->entity_setGrabbed( getgrabbing_entity);

    make_entity->contains_display = get_disp;
    make_entity->contains_display_d = get_disp_d;
    make_entity->contains_display_x = get_disp_x;
    make_entity->contains_display_y = get_disp_y;

    make_entity->SS_collision_ignores_walls = get_SS_ignorewalls;
    make_entity->SS_bouncyness = get_SS_bouncyness;
    make_entity->SS_decelerator = get_SS_decelerator;

    //manual storage stuff here, because the entity we want to be store inside might not even be loaded yet!!
    make_entity->contains_vector.clear();
    make_entity->contains_vector.swap(collectedInventory); //swap these two, the other will get dumped at function end.
    make_entity->inside_of_id = getinsideof;

    make_entity->myIntVars.clear();
    make_entity->myIntVars.insert(get_myIntVars.begin(), get_myIntVars.end());
    make_entity->myStringVars.clear();
    make_entity->myStringVars.insert(get_myStringVars.begin(), get_myStringVars.end());

    //fill entity with personal data!


    //pass back entity
    return make_entity;
}


void serverCore::entityMapLoad(nlohmann::json e) {
    //extract entities from the json data!
    for (nlohmann::json::iterator it = e.begin(); it != e.end(); ++it) {
        nlohmann::json jsonEntity = (nlohmann::json)*it;

        if(jsonEntity.is_object()) {
            entity* make_entity = serverObj.entityJsonDecode( jsonEntity);

            serverObj.entity_set( make_entity, make_entity->entity_number); //add to main list
        }
    }
}



bool serverCore::gameMapLoad(std::string mapFilePath) {
    //file finished loading
    bool finishedLoading = false;

    // read a JSON file
    std::ifstream inputFile( mapFilePath);

    if(inputFile.good() == false) {
        std::cout << "Map file '" << mapFilePath <<"' not found." << std::endl;
    }
    else
    {
        nlohmann::json jsonData;
        inputFile >> jsonData;

        //load userdata
        userdataLoad(jsonData["UserData"]);

        //extract security data first!
        securityMapLoad(jsonData["Security"]);

        //now for the entities!
        entityMapLoad(jsonData["Entities"]);

        //finally the map's walls!
    }



    return finishedLoading;
}




///ENTITY
entity::entity(std::string set_object_index,double set_x,double set_y, float set_dir, double set_spd, bool set_indestructable) {
    //constructor
    object_index = set_object_index;
    entity_number = -1; //index in entity vector
    x = set_x;
    y = set_y;
    last_update_x = set_x;
    last_update_y = set_y;
    dir = set_dir;
    spd = set_spd;
    indestructable = set_indestructable;

    //set all update flags
    for (int i = 0; i < serverObj.server_maxplayers; i++)
    {
        needs_update[i] = true; //is a list of player flags!
    }
}

entity::~entity(){
}

bool entity::entityIsPlayer() {
    return ( entity_getObjectIndex() == "obj_puppet_player" );
}

void entity::entity_set_inventorylimits( int inventory_size, int max_storeable_item_size, int item_size, bool is_a_liquid, bool contains_a_liquid, int item_class, int inventory_storage_class) {
    is_liquid = is_a_liquid;
    is_size = item_size; //item is a physical size of
    //self inventory
    is_type_class = item_class;
    contains_class = inventory_storage_class;
    contains_max = inventory_size; //inventory max size
    contains_type_liquid = contains_a_liquid;
    contains_size = max_storeable_item_size; //item physical size that can be held
}


void entity::entity_securityInit() {
    //set all security flags as disabled, entities calling security updates will correct this. This is just init.
    //largely because it is called before the inventory has been properly set for the object, so it can't check for
    //the security cards needed to set its clearances anyway.
    for (unsigned int i = 0; i < serverObj.mapSecurityLevels.size(); i++ )
    {
        entitySecurityLevels[ i] = false; //force set all security to disabled
    }
}

void entity::entity_securityUpdate() {
    //blank out all security levels for safety
    for (std::map<unsigned int,bool>::iterator it = entitySecurityLevels.begin(); it != entitySecurityLevels.end(); it++ )
    {
        it->second = false; //force set all security to disabled
    }

    ///TODO!!!

    //check inventory for cards in slots!

    //be sure to check if the security level exists, if not forcibly disable it!
}


void entity::entity_step() {
    //std::cout << "entity personal step: " << entity_number << " cycle: " << serverObj.entity_process_cycle << std::endl;

    //physics calculation, movement, and collisions
    if(entity_last_process_cycle != serverObj.entity_process_cycle) {
        //personal update
        entity_personal_step();

        //prevent update in the same frame somehow
        entity_last_process_cycle = serverObj.entity_process_cycle;
    }
}


void entity::entity_personal_step() {
    //enacts personal countdowns, or transforms it into other entities
    //for example, coffee cooling down and changing into cold coffee
}

std::string entity::entity_getObjectIndex() {
    return object_index;
}

int entity::entity_getInventoryMaxSize() {
    return contains_max;
}

int entity::entity_getInventoryItemSizeMax() {
    return contains_size;
}

bool entity::entity_getInventoryAllowLiquids() {
    return contains_type_liquid;
}

int entity::entity_getInventoryItemClassAllowed() {
    return contains_class;
}

int entity::entity_getItemClass() {
    return is_type_class;
}

int entity::entity_getItemSize() {
    return is_size;
}

bool entity::entity_getItemIsLiquid() {
    return is_liquid;
}



void entity::entity_setIndestructable(bool input){
    indestructable = input;
}

bool entity::entity_getIndestructable() {
    return indestructable;
}

void entity::entity_setConstructed(bool setCon){
    constructed = setCon;
}

bool entity::entity_getConstructed() {
    return constructed;
}

void entity::entity_setGrabbed(unsigned int entityNumber) {
    grabbing_entity = entityNumber;
}

unsigned int entity::entity_getGrabbed() {
    return grabbing_entity;
}
