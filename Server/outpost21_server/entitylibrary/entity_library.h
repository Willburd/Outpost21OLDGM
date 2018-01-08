#ifndef ENTITYLIB_H
#define ENTITYLIB_H


#include "../server_core.h"

namespace entityLibrary {



    class entity_generic : public entity {

        public:
        void entity_personal_step() {
            ///personal actions go here
        }
    };



    class entity_arrivalshuttle : public entity {

        bool SS_collision_ignores_walls = false;
        double dest_x = x;
        double dest_y = y;
        entity* dropoff_padPointer = nullptr;
        double dropoff_x = -10;
        double dropoff_y = -10;
        bool dropoff_flag = false;
        int dropoff_waitcounter = 300;
        double SS_decelerator = 1; //no slowdown!

        public:
        void entity_personal_step() {
            ///personal actions go here
        }
    };


    class entity_player : public entity {
        int stat_str = 10;
        int stat_int = 10;
        int stat_dex = 10;
        int stat_con = 10;

        int stat_race = enum_races.nevrean;
        int stat_homeworld = enum_homeworlds.offworld;
        int stat_body = enum_archetype.every;
        int stat_job = 0;
        int stat_jobprev = 0;
        int stat_guild = 0;
        int stat_lang_main = 0;
        int stat_lang_alt = 0;
        int stat_age = 21;


        public:
        void entity_personal_step() {
            ///personal actions go here
        }
    };







    //library creation function

    entity* entity_template_library(std::string set_object_index,double set_x,double set_y, float set_dir, double set_spd, bool set_indestructable, int set_insideid) {
        ///this function is largely for GM compatibility
        entity* returnPointer;

        //switches can't handle strings here, soooooooooo.....
        if(set_object_index == "obj_puppet_arrivalshuttle") {
            returnPointer = new entity_arrivalshuttle( set_object_index,set_x,set_y,set_dir,set_spd,set_indestructable,set_insideid);
            returnPointer->entity_set_inventorylimits(1, enum_itemsize.huge, enum_itemsize.large, false, false, enum_itemclass.ship, enum_itemclass.generic);
        }
        else if(set_object_index == "obj_puppet_player") {
            returnPointer = new entity_player( set_object_index,set_x,set_y,set_dir,set_spd,set_indestructable,set_insideid);
            returnPointer->entity_set_inventorylimits(12, enum_itemsize.large, enum_itemsize.medium, false, false, enum_itemclass.body, enum_itemclass.generic);
        }
        else
        {
            //Backup, object_index missing
            returnPointer = new entity_generic( "obj_puppet_generic",set_x,set_y,set_dir,set_spd,set_indestructable,set_insideid);
        }

        return returnPointer;
    };
}








#endif
