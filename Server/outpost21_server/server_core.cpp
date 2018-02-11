#include "json/json.hpp"
#include "client_transmit_packets.h"
#include "entitylibrary/entity_library.h"
#include "toolbox/toolbox.h"
#include "server_core.h"
#include <algorithm>


extern serverCore serverObj;


///SERVER CORE
void serverCore::CreateObjectAndAssetIndex(std::string inputAssetIndex) {
    //add latest index!
    object_index[inputAssetIndex] = assetIndex_currentEntry;
    asset_index[assetIndex_currentEntry] = inputAssetIndex;

    //increment
    assetIndex_currentEntry += 1;
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

            //std::cout << "Assigning entity number: " << i << std::endl;

            ///add at the end of list, or if a blank space is found
            entity_map[i] = entityToAdd;
            entityToAdd->entity_number = i;
            returnEnt = i;
            break;
        }
    }

    return returnEnt;
}


void serverCore::entity_set(entity* entityToAdd, unsigned int entityNumberToAssign) {
    if(entityNumberToAssign >= entity_map.size() || entity_map[entityNumberToAssign] == nullptr) {

        //std::cout << "Assigning entity number: " << entityNumberToAssign << std::endl;

        ///add at the end of list, or if a blank space is found
        entity_map[entityNumberToAssign] = entityToAdd;
        entityToAdd->entity_number = entityNumberToAssign;
    }
}


void serverCore::entity_remove(int entityNumberToRemove) {
    if(entityNumberToRemove >= 0
    && entity_map[entityNumberToRemove] != nullptr) {
        //place entity in abyss so the clients are repeatedly FORCED to unload it!
        entity* get_ent = entity_map[entityNumberToRemove];
        get_ent->x = serverObj.entity_deletion_abyss;
        get_ent->y = serverObj.entity_deletion_abyss;
    }
}


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
    if(getStoredEntity->entity_getAssetIndex() == "obj_puppet_securitycard") {
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
    if(getStoredEntity->entity_getAssetIndex() == "obj_puppet_securitycard") {
        //update both as needed!
        getStoredEntity->entity_securityUpdate();
        oldStorageEntity->entity_securityUpdate();
    }
}


void serverCore::gameUpdate() {
    for(std::map<unsigned int, entity*>::iterator it = entity_map.begin(); it != entity_map.end(); it++ ) {
        //entity validation
        entity* getData = it->second;
        if(getData != nullptr) {
            //check if entity is in deletion area, if it is, repeatedly drop it from clients until it is!
            //this ensures the entity is unloaded fully
            if(getData->x <= entity_deletion_abyss || getData->y <= entity_deletion_abyss) {
                //drag up to item abyss if y is wrong.
                getData->y = entity_deletion_abyss;

                if( getData->x > entity_deletion_abyss-5 ) {
                    //repeatedly send unloads to all clients
                    getData->x -= 1;
                }
                else
                {
                    //force destruction of entity
                    entity_map[getData->entity_number] = nullptr;
                    delete getData;
                }
            }
            else
            {
                if(getData->entity_checkProcessingCycle()) {
                    //process physics
                    getData->entity_step();

                    //process personal data
                    getData->entity_personal_step();

                    //broadcast updates to clients
                    getData->entity_update_clients();

                    //prevent update in the same frame somehow
                    getData->entity_updateProcessingCycle();
                }
            }
        }
    }
}



bool serverCore::entity_classStorageCheck( uint16_t input_item_class, uint16_t storage_class_allowed, client_struct& inputClient) {
    bool allow_item = false;

    switch(storage_class_allowed) {
        default:
            std::cout << "classStorageCheck definition missing!! storageClass number: " << storage_class_allowed << std::endl;
            allow_item = false;
        break;

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


void serverCore::set_update_flag( int entityNumberToUpdate, client_struct* clientInput, bool updateFlag) {
    if(entityNumberToUpdate >= 0
    && entity_map[entityNumberToUpdate] != nullptr) {
        //set the entities updateflag for this client!
        entity* get_ent = entity_map[entityNumberToUpdate];
        get_ent->needsUpdate_map[ clientInput] = updateFlag;
    }
}

void serverCore::set_update_flagALL( int entityNumberToUpdate, bool updateFlag) {
    if(entityNumberToUpdate >= 0
    && entity_map[entityNumberToUpdate] != nullptr) {
        for (std::map<unsigned int,client_struct*>::iterator it = serverObj.clientNumberMap.begin(); it != serverObj.clientNumberMap.end(); it++ )
        {
            set_update_flag( entityNumberToUpdate, it->second, updateFlag);
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
    bool get_ShowMessages = serverObj.showSecurityLoad;
    for (nlohmann::json::iterator it = j.begin(); it != j.end(); ++it) {
        nlohmann::json jsonSecurity = (nlohmann::json)*it;

        if(jsonSecurity.is_object()) {
            //add security level to vector
            if(get_ShowMessages) std::cout << "====Loading Security level: " << std::endl;

            unsigned int getIndex = jsonSecurity.at("index").get<int>();
            if(get_ShowMessages) std::cout << " |---------index: " << getIndex << std::endl;

            std::string getName = jsonSecurity.at("name").get<std::string>();
            if(get_ShowMessages) std::cout << " |----------name: " << getName << std::endl;

            unsigned int getColor = jsonSecurity.at("color").get<int>();
            if(get_ShowMessages) std::cout << " |---------color: " << getColor << std::endl;

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
    bool get_ShowMessages = serverObj.showEntityLoad;

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

    if(get_ShowMessages) std::cout << "====Loading entity====" << std::endl;
    for (nlohmann::json::iterator itm = a.begin(); itm != a.end(); ++itm) {
        //itterate through entity's properties
        //allows us to set the hard internal values
        //and the soft item specific values
        std::string jsonKey = itm.key();

        if(jsonKey == "entity_number") {
            getEntityNumber = a.at(jsonKey).get<int>();
            if(get_ShowMessages) std::cout << " |------entityID: " << getEntityNumber << std::endl;
        }
        else if(jsonKey == "object_index") {
            get_objectindex = a.at(jsonKey).get<std::string>();
            if(get_ShowMessages) std::cout << " |-----obj index: " << get_objectindex << std::endl;
        }
        else if(jsonKey == "x") {
            getx = a.at(jsonKey).get<double>();
            if(get_ShowMessages) std::cout << " |-------------x: " << getx << std::endl;
        }
        else if(jsonKey == "y") {
            gety = a.at(jsonKey).get<double>();
            if(get_ShowMessages) std::cout << " |-------------y: " << gety << std::endl;
        }
        else if(jsonKey == "last_update_x") {
            //ignore this,
            if(get_ShowMessages) std::cout << " |----------prvX: DYNAMIC SET..." << std::endl;
        }
        else if(jsonKey == "last_update_y") {
            //ignore this,
            if(get_ShowMessages) std::cout << " |----------prvY: DYNAMIC SET..." << std::endl;
        }
        else if(jsonKey == "needs_update") {
            //ignore this,
            if(get_ShowMessages) std::cout << " |---user_update: DEPRICATED" << std::endl;
        }
        else if(jsonKey == "entity_last_process_cycle") {
            //ignore this,
            if(get_ShowMessages) std::cout << " |----last_cycle: DEPRICATED" << std::endl;
        }
        else if(jsonKey == "dir") {
            getdir = a.at(jsonKey).get<float>();
            if(get_ShowMessages) std::cout << " |-----------dir: " << getdir << std::endl;
        }
        else if(jsonKey == "spd") {
            getspd = a.at(jsonKey).get<double>();
            if(get_ShowMessages) std::cout << " |-----------spd: " << getspd << std::endl;
        }
        else if(jsonKey == "indestructable") {
            getindestruct = (bool)a.at(jsonKey).get<int>();
            if(get_ShowMessages) std::cout << " |----indestruct: " << getindestruct << std::endl;
        }
        else if(jsonKey == "inside_of_id") {
            getinsideof = a.at(jsonKey).get<int>();
            if(get_ShowMessages) std::cout << " |-----insideent: " << getinsideof << std::endl;
        }
        else if(jsonKey == "grabbing_entity") {
            getgrabbing_entity = a.at(jsonKey).get<int>();
            if(get_ShowMessages) std::cout << " |---grabbingent: " << getgrabbing_entity << std::endl;
        }
        else if(jsonKey == "constructed") {
            getconstructed = (bool)a.at(jsonKey).get<int>();
            if(get_ShowMessages) std::cout << " |---constructed: " << getconstructed << std::endl;
        }
        else if(jsonKey == "SS_collision") {
            //ignore this,
            if(get_ShowMessages) std::cout << " |----SS_coldata: DYNAMIC SET..." << std::endl;
        }
        else if(jsonKey == "SS_collision_ignores_walls") {
            get_SS_ignorewalls = (bool)a.at(jsonKey).get<int>();
            if(get_ShowMessages) std::cout << " |---SS_ignwalls: " << get_SS_ignorewalls << std::endl;
        }
        else if(jsonKey == "SS_bouncyness") {
            get_SS_ignorewalls = a.at(jsonKey).get<double>();
            if(get_ShowMessages) std::cout << " |---SS_bouncyns: " << get_SS_bouncyness << std::endl;
        }
        else if(jsonKey == "SS_decelerator") {
            get_SS_ignorewalls = a.at(jsonKey).get<double>();
            if(get_ShowMessages) std::cout << " |---SS_decelera: " << get_SS_decelerator << std::endl;
        }
        else if(jsonKey == "contains_display") {
            get_disp = (bool)a.at(jsonKey).get<int>();
            if(get_ShowMessages) std::cout << " |-------display: " << get_disp << std::endl;
        }
        else if(jsonKey == "contains_display_d") {
            get_disp_d = a.at(jsonKey).get<int>();
            if(get_ShowMessages) std::cout << " |---display_dep: " << get_disp_d  << std::endl;
        }
        else if(jsonKey == "contains_display_x") {
            get_disp_x = a.at(jsonKey).get<double>();
            if(get_ShowMessages) std::cout << " |-----display_x: " << get_disp_x << std::endl;
        }
        else if(jsonKey == "contains_display_y") {
            get_disp_y = a.at(jsonKey).get<double>();
            if(get_ShowMessages) std::cout << " |-----display_y: " << get_disp_y << std::endl;
        }
        else if(jsonKey == "contains_max") {
            get_containsmax = a.at(jsonKey).get<int>();
            if(get_ShowMessages) std::cout << " |---contain_max: " << get_containsmax << std::endl;
        }
        else if(jsonKey == "contains_map") {
            nlohmann::json inv_json = a.at(jsonKey);

            if(get_ShowMessages) std::cout << " |------Extracting inventory!" << std::endl;
            for (nlohmann::json::iterator it = inv_json.begin(); it != inv_json.end(); ++it) {
                //add all current logins!
                collectedInventory.push_back((int)*it);

                if(get_ShowMessages) std::cout << "|-------->>" << (int)*it << std::endl;
            }

        }
        else if(jsonKey == "contains_size") {
            get_containssize = a.at(jsonKey).get<int>();
            if(get_ShowMessages) std::cout << " |--contain_size: " << get_containssize << std::endl;
        }
        else if(jsonKey == "contains_type_liquid") {
            get_containsliquid = (bool)a.at(jsonKey).get<int>();
            if(get_ShowMessages) std::cout << " |-contain_liqud: " << get_containsliquid << std::endl;
        }
        else if(jsonKey == "contains_class") {
            get_containsclass = a.at(jsonKey).get<int>();
            if(get_ShowMessages) std::cout << " |-contain_class: " << get_containsclass << std::endl;
        }
        else if(jsonKey == "is_class") {
            get_isclass = a.at(jsonKey).get<int>();
            if(get_ShowMessages) std::cout << " |-------isclass: " << get_isclass << std::endl;
        }
        else if(jsonKey == "is_size") {
            get_issize = a.at(jsonKey).get<int>();
            if(get_ShowMessages) std::cout << " |--------issize: " << get_issize << std::endl;
        }
        else if(jsonKey == "is_liquid") {
            get_isliquid = (bool)a.at(jsonKey).get<int>();
            if(get_ShowMessages) std::cout << " |-------isliqud: " << get_isliquid << std::endl;
        }
        else if(jsonKey == "security_clearance") {
            ///THIS IS FOR SECURITY CARDS! Stores the security level to set to objects
            if(get_ShowMessages) std::cout << " |------secClear: " << std::endl;

            ///TODO! need to add security data to security cards.
        }
        else if(jsonKey == "security_levels") {
            ///This is for the object's current security status (for doors to check!)
            //ignored. This is manually updated
            if(get_ShowMessages) std::cout << " |------secLevel: DYNAMIC SET..." << std::endl;
        }
        else if(jsonKey == "player_socket") {
            //ignore this,
            if(get_ShowMessages) std::cout << " |--playerclient: DEPRICATED" << std::endl;
        }
        else
        {
            nlohmann::json jsonEntry = (nlohmann::json)*itm;

            if(get_ShowMessages) std::cout << " |--Personal key: " << jsonKey;

            if(jsonEntry.is_object()) {
                if(get_ShowMessages) std::cout << " ::objects not supported for custom variable loading" << std::endl;
            }
            else
            {
                if(jsonEntry.is_string()) {
                    get_myStringVars[jsonKey] = jsonEntry.get<std::string>();
                    if(get_ShowMessages) std::cout << " ::string: " << get_myStringVars[jsonKey] << std::endl;
                }
                else
                {
                    get_myIntVars[jsonKey] = jsonEntry.get<int>();
                    if(get_ShowMessages) std::cout << " ::int: " << get_myIntVars[jsonKey] << std::endl;
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

//map constructions
void serverCore::entityConstructLoad(nlohmann::json c) {
    bool get_ShowMessages = serverObj.showMapLoad;

    for (nlohmann::json::iterator itm = c.begin(); itm != c.end(); ++itm) {
        nlohmann::json jsonConstruction = (nlohmann::json)*itm;

        int get_mapEntity = 0;
        double get_x = 0;
        double get_y = 0;
        float get_angle = 0;
        int get_health = 0;
        bool get_removeFlag = false;
        std::string get_obj = "";

        if(jsonConstruction.is_object()) {
            if(get_ShowMessages) std::cout << "====Loading construction====" << std::endl;
            for (nlohmann::json::iterator it = jsonConstruction.begin(); it != jsonConstruction.end(); ++it) {
                //itterate through constructions properties
                std::string jsonKey = it.key();

                if(jsonKey == "map_entity") {
                    get_mapEntity = (int)it.value();
                    if(get_ShowMessages) std::cout << " |---------mapID: " << get_mapEntity << std::endl;
                }
                else if(jsonKey == "x") {
                    get_x = (double)it.value();
                    if(get_ShowMessages) std::cout << " |-------------x: " << get_x << std::endl;
                }
                else if(jsonKey == "y") {
                    get_y = (double)it.value();
                    if(get_ShowMessages) std::cout << " |-------------y: " << get_y << std::endl;
                }
                else if(jsonKey == "angle") {
                    get_angle = (float)it.value();
                    if(get_ShowMessages) std::cout << " |---------angle: " << get_angle << std::endl;
                }
                else if(jsonKey == "health") {
                    get_health = (int)it.value();
                    if(get_ShowMessages) std::cout << " |--------health: " << get_health << std::endl;
                }
                else if(jsonKey == "remove_flag") {
                    get_removeFlag = (int)it.value();
                    if(get_ShowMessages) std::cout << " |----removeFlag: " << get_removeFlag << std::endl;
                }
                else if(jsonKey == "obj") {
                    get_obj = it.value();
                    if(get_ShowMessages) std::cout << " |-----------obj: " << get_obj << std::endl;
                }
            }
        }

        //add construction to map!
        mapConstruction* newConstruction = new mapConstruction;
        serverObj.construction_map[get_mapEntity] = newConstruction; //add to list!

        //populate construction with data
        newConstruction->map_entity = get_mapEntity;
        newConstruction->x = get_x;
        newConstruction->y = get_y;
        newConstruction->angle = get_angle;
        newConstruction->health = get_health;
        newConstruction->remove_flag = (get_removeFlag > 0);
        newConstruction->obj = get_obj;
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
        std::cout << "Loading Map file '" << mapFilePath <<"'." << std::endl;

        nlohmann::json jsonData;
        inputFile >> jsonData;

        //load userdata
        userdataLoad(jsonData["UserData"]);

        //extract security data first!
        securityMapLoad(jsonData["Security"]);

        //map constructions
        entityConstructLoad(jsonData["MapConstructions"]);

        //now for the entities!
        entityMapLoad(jsonData["Entities"]);

        finishedLoading = true;
    }

    return finishedLoading;
}




///ENTITY
entity::entity(std::string set_object_index,double set_x,double set_y, float set_dir, double set_spd, bool set_indestructable) {
    //constructor
    asset_index = set_object_index;
    entity_number = -1; //index in entity vector
    x = set_x;
    y = set_y;
    last_update_x = set_x;
    last_update_y = set_y;
    dir = set_dir;
    spd = set_spd;
    indestructable = set_indestructable;
}

entity::~entity(){
}

bool entity::entityIsPlayer() {
    return ( entity_getAssetIndex() == "obj_puppet_player" );
}

client_struct* entity::entity_getPlayerClient() {
    ///returns -1 if the entity does not have a client, any other index if otherwise.
    if(entityIsPlayer()) {
        return serverObj.clientNumberMap[ myIntVars["player_socket"] ];
    }
    else
    {
        return nullptr; //not a player
    }
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

void entity::entity_update_clients() {
    std::vector<entity*> PostUpdateVector; //fills with entities that need their updates cleared after the loop!

    //check if inside of an object that can display it!
    bool inside_a_display_entity = false;
    bool inside_a_inventory_entity = false;

    //check if we need to set some container flags
    entity* containerData = nullptr;
    if( inside_of_id != -1 ) {
        containerData = serverObj.entity_map[inside_of_id];
        inside_a_inventory_entity = true;
        inside_a_display_entity = containerData->contains_display;
    }

    //central update loop (goes to all players)
    if(x > serverObj.entity_deletion_abyss || y > serverObj.entity_deletion_abyss || inside_a_display_entity == true) { //if something removed the entity before this, protect entity removal

        //standard update proceedure. see if in range of player, and then update if so!
        for (std::map<unsigned int,client_struct*>::iterator it = serverObj.clientNumberMap.begin(); it != serverObj.clientNumberMap.end(); it++ ) {
            client_struct* currentClient = it->second;

            //get if our host object is updating
            bool host_entity_wants_update = false;
            if(inside_a_inventory_entity == true) {
                host_entity_wants_update = containerData->needsUpdate_map[currentClient];
            }

            //get player entity
            int player_entity = currentClient->myPlayerEntity;
            entity* playerData = serverObj.entity_map[player_entity];

            //if the player doesn't exist, or is not set then what are we even doing!?
            if(playerData != nullptr) {
                //get if this is the same entity as the player that we are sending it to!
                bool is_player = (player_entity == entity_number);
                double plyx = playerData->x;
                double plyy = playerData->y;

                //if a player is inside another entity then use that entity x and y
                int get_ply_hostentity = playerData->inside_of_id;
                if(get_ply_hostentity != -1) {
                    entity* get_ply_hostdata = serverObj.entity_map[get_ply_hostentity];

                    if(get_ply_hostdata != nullptr) {
                        plyx = get_ply_hostdata->x;
                        plyy = get_ply_hostdata->y;
                    }
                }

                //check if the object has been marked as recently updated
                bool update = needsUpdate_map[currentClient];

                //checking the distance does most of the work.
                int entity_distance;
                if(inside_a_display_entity == false) {
                    //not inside a display container
                    entity_distance = toolbox::pointDistance(plyx,plyy,x,y);
                }
                else
                {
                    //inside a display container
                    entity_distance = toolbox::pointDistance(plyx,plyy,containerData->x,containerData->y);
                }


                //ranged activation
                if(entity_distance < serverObj.entity_activation_range || entity_getConstructed() == true) { //always try to load constructed entityies
                    //if it can be updated do so!
                    if(update == true || (host_entity_wants_update == true && inside_a_display_entity == true)) {
                        //do not send the afterimage of yourself.
                        if(is_player == false) {
                            //transmit location!
                            //show_debug_message("Player: " + string(player_entity) + " Loaded entity: " + string(argument0));
                            //pretty much anything done to an object flags this.
                            if(inside_a_display_entity == false) {
                                //normal entity drawing
                                ///TODO Find out why proximity loading is spamming, is the update flag being ignored?
                                /*client_transmission_packets::cpacket_entity_load( *currentClient
                                                       , entity_number
                                                       , entity_getObjectIndex()
                                                       , x
                                                       , y
                                                       , dir
                                                       , spd
                                                       , entity_getConstructed()
                                                       , 0);
                                //set for clearing later, clear flag
                                PostUpdateVector.push_back(this);*/
                            }
                            else
                            {
                                //on display in an object
                                client_transmission_packets::cpacket_entity_load( *currentClient
                                                       , entity_number
                                                       , entity_getObjectIndex()
                                                       , containerData->x + containerData->contains_display_x
                                                       , containerData->y + containerData->contains_display_y
                                                       , 0
                                                       , 0
                                                       , 0
                                                       , containerData->contains_display_d);
                            }

                            //set for clearing later, clear flag
                            PostUpdateVector.push_back(this);
                        }
                        else if(inside_a_inventory_entity == true) {
                            //this refers to players inside objects, they auto update their clients with the object they are inside of!
                            if(containerData != nullptr) {
                                client_transmission_packets::cpacket_entity_load( *currentClient
                                                       , entity_number
                                                       , containerData->entity_getObjectIndex()
                                                       , containerData->x
                                                       , containerData->y
                                                       , 0
                                                       , 0
                                                       , 0
                                                       , 0);
                            }
                        }
                    }
                }
                else if(inside_a_display_entity == false && inside_of_id != -1 && update == true) { //get_map[? "x"] == item_storage_pos and get_map[? "y"] == item_storage_pos
                    //in storage, keep out of view from everyone!
                    //show_debug_message("Player: " + string(player_entity) + " inventory dropped entity: " + string(argument0));
                    client_transmission_packets::cpacket_entity_drop( *currentClient,entity_number);
                    //set for clearing later, clear flag
                    PostUpdateVector.push_back(this);
                }
                else
                {
                    //hanging out at the edge of the activation range... maybe because unmoved or it's being weird, but it won't update yet.
                    if((update == false && host_entity_wants_update == false) && (inside_of_id == -1 || inside_a_display_entity == true)) {
                        serverObj.set_update_flag( entity_number, currentClient, true);
                    }
                }
            }
            else
            {
                //no client load yet, instantiate map with updates!
                serverObj.set_update_flag( entity_number, currentClient, true);
            }
        }
    }

    //set the entities that updated to not update again unless needed!
    while(PostUpdateVector.size() > 0) {
        entity* currentEnt = PostUpdateVector.back();
        serverObj.set_update_flagALL( currentEnt->entity_number, false);

        PostUpdateVector.pop_back();
    }
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

bool entity::entity_checkProcessingCycle() {
    return (entity_last_process_cycle !=  serverObj.entity_process_cycle);
}

void entity::entity_updateProcessingCycle() {
    entity_last_process_cycle = serverObj.entity_process_cycle;
}


void entity::entity_step() {
    //std::cout << "entity personal step: " << entity_number << " cycle: " << serverObj.entity_process_cycle << std::endl;

    //physics calculation, movement, and collisions
    if(x > serverObj.entity_item_storage && y > serverObj.entity_item_storage) {
        //entities in storage don't need to be updated with physics and collisions

        if(entity_getGrabbed() != -1) {
            //drag entity with me!
            int grab_entity = entity_getGrabbed();
            entity* grabData = serverObj.entity_map[grab_entity];

            if(grabData != nullptr) {
                if( inside_of_id != -1 && grabData->inside_of_id != -1 ) {
                    //if item storages have not changed (prevents dragging stuff in objects, or dragging while in an object!
                    //drag around!
                    double get_dis = toolbox::pointDistance(grabData->x,grabData->y,x,y);

                    if(get_dis > serverObj.place_grab_range) {
                        //release grab, too far!
                        std::cout << " Grab was released by: " << entity_getGrabbed() << " was too far away! Dis: " << get_dis << std::endl;
                        entity_setGrabbed(-1);

                        //inform player of grab change if it's a player!!
                        client_struct* getClient = entity_getPlayerClient();
                        if(getClient != nullptr) {
                            ///TODO scr_cpacket_entity_grab_update( getClient, -1);
                        }
                    }
                    else if(get_dis > 48) {
                        //pull around!
                        float dir_to_grab = toolbox::pointDirection(grabData->x,grabData->y,x,y);
                        ///TODO grabData->x += lengthdir_x(get_dis/2,dir_to_grab);
                        ///TODO grabData->y += lengthdir_y(get_dis/2,dir_to_grab);


                        client_struct* getClient = entity_getPlayerClient();
                        if(getClient != nullptr) {
                            //pull player around!
                            double getx = grabData->x;
                            double gety = grabData->y;
                            double getpreviousx = grabData->last_update_x;
                            double getpreviousy = grabData->last_update_y;
                            //if distance is big enough
                            if(toolbox::pointDistance(getx,gety,getpreviousx,getpreviousy) > 3) {
                                ///TODO scr_cpacket_location_sync( getClient,getx,gety,0,0);
                            }
                        }
                    }
                    else if(get_dis < 24) {
                        //pushing around!
                        float dir_to_grab = toolbox::pointDirection(grabData->x,grabData->y,x,y);
                        dir_to_grab = round(dir_to_grab/4)*4; //snap directions

                        ///TODO grabData->x += lengthdir_x(get_dis*1.2,dir_to_grab);
                        ///TODO grabData->y += lengthdir_y(get_dis*1.2,dir_to_grab);

                        client_struct* getClient = entity_getPlayerClient();
                        if(getClient != nullptr) {
                            //pull player around!
                            double getx = grabData->x;
                            double gety = grabData->y;
                            double getpreviousx = grabData->last_update_x;
                            double getpreviousy = grabData->last_update_y;
                            //if distance is big enough
                            if(toolbox::pointDistance(getx,gety,getpreviousx,getpreviousy) > 3) {
                                ///TODO scr_cpacket_location_sync( getClient,getx,gety,0,0);
                            }
                        }
                    }
                }
                else
                {
                    //release grab, this was put in an inventory, or the dragger was?!
                    std::cout << " Grab was released by: " << entity_getGrabbed() << " grab, or grabber, placed into inventory!" << std::endl;
                    entity_setGrabbed(-1);

                    //inform player of grab change if it's a player!!
                    client_struct* getClient = entity_getPlayerClient();
                    if(getClient != nullptr) {
                        ///TODO scr_cpacket_entity_grab_update( getClient, -1);
                    }
                }

                //flag for updoot
                if(toolbox::pointDistance(grabData->x,grabData->y,grabData->last_update_x,grabData->last_update_y) > 5) {
                    serverObj.set_update_flagALL(grabData->entity_number, true);
                }
            }
        }


        //entity processing cycle
        std::string object = entity_getAssetIndex();
        double getx = x;
        double gety = y;
        double getpreviousx = last_update_x;
        double getpreviousy = last_update_x;
        float getdir = dir;

        double decel = SS_decelerator;

        double maxMove = serverObj.maximum_movement;
        if(decel == 1) maxMove = 9999999; //decleration of 1 allows weird stuff.
        double getspd = toolbox::clamp(spd,-maxMove,maxMove);

        //store last location
        last_update_x = x;
        last_update_y = y;

        if(entity_getConstructed() == false) {
            //handle object movement and collisions!
            ///TODO double forcex = lengthdir_x(getspd, getdir);
            ///TODO double forcey = lengthdir_y(getspd, getdir);
            //x = toolbox::clamp(x + forcex, serverObj.map_mix_xlimit, serverObj.map_max_xlimit);
            //y = toolbox::clamp(y + forcey, serverObj.map_mix_ylimit, serverObj.map_max_ylimit);
        }
        else
        {
            //constructed entities DO NOT MOVE
            spd = 0;
        }

        //update movements
        if((spd > 1 || toolbox::pointDistance(getx,gety,getpreviousx,getpreviousy) > 0.20)
        && entity_getConstructed() == false) { //constructed entities cannot move
            //1 decel likely means it does some fancy shit.
            if(decel < 1) {
                //decelerate
                spd *= decel;

                //stop if needed
                if(spd < serverObj.forced_movement_minimum_cutoff) spd = 0;
            }

            //update collision server objects
            ///TODO handle object and map collisions.
            /*with get_map[? "SS_collision"] {
                //we are not in an object
                sprite_index = spr_serverside_entitycol;

                //update col
                x = get_map[? "x"];
                y = get_map[? "y"];

                //get potential collisions
                if get_map[? "SS_collision_ignores_walls"] == false {
                    var collision_found = collision_line(get_map[? "last_update_x"],get_map[? "last_update_y"],x,y,obj_serverside_colwall,true,true);
                    if collision_found == noone {
                        collision_found = collision_rectangle(x-5,y-5,x+5,y+5,obj_serverside_colwall,true,true);
                    }
                }
                else
                {
                    collision_found = noone;
                }


                if collision_found != noone {
                    //do wall damage calc
                    var wall_breaks = false;

                    if wall_breaks == true {
                        //break wall

                    }
                    else
                    {
                        //bounce off!
                        get_map[? "x"] = get_map[? "last_update_x"]
                        get_map[? "y"] = get_map[? "last_update_y"]
                        x = get_map[? "x"];
                        y = get_map[? "y"];

                        //reflect angle (update this later with some kind of entity type specific thing like EXPLODE instead
                        var xoffset = lengthdir_x( getspd, getdir);
                        var yoffset = lengthdir_y( getspd, getdir);

                        if collision_found.image_angle == 0 or collision_found.image_angle == 180 {
                            xoffset *= -1;
                            yoffset *=  1;
                        }
                        else
                        {
                            xoffset *=  1;
                            yoffset *= -1;
                        }

                        //set new direction, half speed
                        get_map[? "dir"] = point_direction(0,0,xoffset,yoffset);
                        get_map[? "spd"] *= get_map[? "SS_bouncyness"];
                    }
                }

                //update col with new data from collision
                x = get_map[? "x"];
                y = get_map[? "y"];

            }*/

            //set update flag
            serverObj.set_update_flagALL( entity_number, true);
        }
    }
}


void entity::entity_personal_step() {
    //enacts personal countdowns, or transforms it into other entities
    //for example, coffee cooling down and changing into cold coffee
}

std::string entity::entity_getAssetIndex() {
    return asset_index;
}

int entity::entity_getObjectIndex() {
    return serverObj.getIndexOfAsset(asset_index);
}

unsigned int entity::entity_getInventoryMaxSize() {
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
