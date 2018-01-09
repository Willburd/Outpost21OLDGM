#ifndef ENTITYLIB_H
#define ENTITYLIB_H


#include "../server_core.h"
namespace entityLibrary {
    namespace itemdata {
        enum enum_itemsize : uint16_t {
            none,
            tiny,
            smal,
            medium, //most appliances and containers
            large, //player sized objects in bins and lockers, furniture
            service_cart, //carts
            huge, //vehicles
        };

        enum enum_itemclass : uint16_t {
            generic,
            tools,
            sheets,
            food,
            machines,
            machine_parts,
            body,
            body_parts,
            clothing,
            rifle,
            pistol,
            ship,
        };
    };

    namespace guilds {
        enum enum_guilds : uint16_t {
            none,
            earthgov,
            unitedfed,
            western_front,
        };
    };

    namespace races {
        enum enum_races : uint16_t {
            human,
            nevrean,
            valekin,
        };
    };

    namespace homeworlds {
        enum enum_homeworlds : uint16_t {
            earth,
            luna,
            mars,
            offworld,
            not_set,
        };
    };

    namespace archetype {
        enum enum_archetype : uint16_t {
            muscle,
            nerd,
            fast,
            iron,
            every,
        };
    };

    namespace jobs {
        enum enum_job_stat : uint16_t {
            stat_name,
            stat_desc,
            stat_startkit,
        };

        enum enum_jobs : uint16_t {
            assistant,
            cargo,
            comms,
            weather,
            science,
            medical,
            engineering,
            mining,
            security,
            atmo,
            hydrophonics,
            filtration,
        };
    };

    namespace language {
        enum enum_language : uint16_t {
            galactic,
            terran,
            martian,
            pipperine,
            eltin,
        };
    };





    class entity_generic : public entity {

        public:
        using entity::entity; // Inherit Base's constructors.
        using entity::entity_set_inventorylimits;

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
        using entity::entity; // Inherit Base's constructors
        using entity::entity_set_inventorylimits;

        void entity_personal_step() {
            ///personal actions go here
        }
    };


    class entity_player : public entity {
        int stat_str = 10;
        int stat_int = 10;
        int stat_dex = 10;
        int stat_con = 10;

        int stat_race = races::nevrean;
        int stat_homeworld = homeworlds::offworld;
        int stat_body = archetype::every;
        int stat_job = 0;
        int stat_jobprev = 0;
        int stat_guild = 0;
        int stat_lang_main = 0;
        int stat_lang_alt = 0;
        int stat_age = 21;


        public:
        using entity::entity; // Inherit Base's constructors.
        using entity::entity_set_inventorylimits;

        void entity_personal_step() {
            ///personal actions go here
        }
    };


    class entity_borb : public entity {
        double SS_bouncyness = 1.25;
        double SS_decelerator = 0.98;


        public:
        using entity::entity; // Inherit Base's constructors.
        using entity::entity_set_inventorylimits;

        void entity_personal_step() {
            ///personal actions go here
        }
    };


    class entity_laserpoint : public entity {
        int firetime = 5;

        public:
        using entity::entity; // Inherit Base's constructors.
        using entity::entity_set_inventorylimits;

        void entity_personal_step() {
            ///personal actions go here
            if(firetime > 0) {
                //countdown
                firetime -= 1;
            }
            else
            {
                //delete me
            }
        }
    };





    //library creation function

    entity* entity_template_library(std::string set_object_index,double set_x,double set_y, float set_dir, double set_spd, bool set_indestructable, int set_insideid) {
        ///this function is largely for GM compatibility
        entity* returnPointer;

        //switches can't handle strings here, soooooooooo.....
        if(set_object_index == "obj_puppet_arrivalshuttle") {
            returnPointer = new entity_arrivalshuttle( set_object_index,set_x,set_y,set_dir,set_spd,set_indestructable,set_insideid);
            returnPointer->entity_set_inventorylimits(1, itemdata::huge, itemdata::large, false, false, itemdata::ship, itemdata::generic);
        }
        else if(set_object_index == "obj_puppet_player") {
            returnPointer = new entity_player( set_object_index,set_x,set_y,set_dir,set_spd,set_indestructable,set_insideid);
            returnPointer->entity_set_inventorylimits(12, itemdata::large, itemdata::medium, false, false, itemdata::body, itemdata::generic);
        }
        else if(set_object_index == "obj_puppet_borb") {
            returnPointer = new entity_borb( set_object_index,set_x,set_y,set_dir,set_spd,set_indestructable,set_insideid);
            returnPointer->entity_set_inventorylimits( 0, itemdata::tiny, itemdata::none, true, false, itemdata::body, itemdata::generic);
        }
        else if(set_object_index == "obj_puppet_laserpoint") {
            returnPointer = new entity_laserpoint( set_object_index,set_x,set_y,set_dir,set_spd,set_indestructable,set_insideid);
            returnPointer->entity_set_inventorylimits( 0, itemdata::medium, itemdata::none, false, false, itemdata::generic, itemdata::generic);
        }
        else
        {
            //Backup, object_index missing
            returnPointer = new entity_generic( "obj_puppet_generic",set_x,set_y,set_dir,set_spd,set_indestructable,set_insideid);
        }

        return returnPointer;
    };
};








#endif
