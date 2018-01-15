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
        entity_generic(std::string set_object_index,double set_x,double set_y, float set_dir, double set_spd, bool set_indestructable);

        using entity::entity_set_inventorylimits;
        using entity::entity_securityInit;

        void entity_personal_step();
    };


    class entity_arrivalshuttle : public entity {


        bool SS_collision_ignores_walls = false;
        double SS_decelerator = 1; //no slowdown!

        public:
        entity_arrivalshuttle(std::string set_object_index,double set_x,double set_y, float set_dir, double set_spd, bool set_indestructable);
        using entity::entity_set_inventorylimits;
        using entity::entity_securityInit;

        void entity_personal_step();
    };


    class entity_player : public entity {
        public:
        entity_player(std::string set_object_index,double set_x,double set_y, float set_dir, double set_spd, bool set_indestructable);
        using entity::entity_set_inventorylimits;
        using entity::entity_securityInit;

        void entity_personal_step();
    };


    class entity_borb : public entity {
        double SS_bouncyness = 1.25;
        double SS_decelerator = 0.98;


        public:
        entity_borb(std::string set_object_index,double set_x,double set_y, float set_dir, double set_spd, bool set_indestructable);
        using entity::entity_set_inventorylimits;
        using entity::entity_securityInit;

        void entity_personal_step();
    };


    class entity_laserpoint : public entity {

        public:
        entity_laserpoint(std::string set_object_index,double set_x,double set_y, float set_dir, double set_spd, bool set_indestructable);
        using entity::entity_set_inventorylimits;
        using entity::entity_securityInit;

        void entity_personal_step();
    };


    class entity_coffee : public entity {
        public:
        entity_coffee(std::string set_object_index,double set_x,double set_y, float set_dir, double set_spd, bool set_indestructable);
        using entity::entity_set_inventorylimits;
        using entity::entity_securityInit;

        void entity_personal_step();
    };


    class entity_powercell : public entity {
        public:
        entity_powercell(std::string set_object_index,double set_x,double set_y, float set_dir, double set_spd, bool set_indestructable);
        using entity::entity_set_inventorylimits;
        using entity::entity_securityInit;

        void entity_personal_step();
    };


    class entity_securitycard : public entity {
        public:
        entity_securitycard(std::string set_object_index,double set_x,double set_y, float set_dir, double set_spd, bool set_indestructable);
        using entity::entity_set_inventorylimits;
        using entity::entity_securityInit;

        void entity_personal_step();
    };



    class entity_machine : public entity {
        public:
        entity_machine(std::string set_object_index,double set_x,double set_y, float set_dir, double set_spd, bool set_indestructable);
        using entity::entity_set_inventorylimits;
        using entity::entity_securityInit;

        void entity_personal_step();
    };











    ///library creation functions
    /*
        add new entities to BOTH of these! it needs to
        know what kind of class to instantiate as well
        as a bunch of object creation stuff!
    */

    void entity_template_creation();
    entity* entity_template_library(std::string set_object_index,double set_x,double set_y, float set_dir, double set_spd, bool set_indestructable);
    int toolkit_template_library( std::string set_object_index, double set_x, double set_y, float set_dir, double set_spd, bool set_indestructable);
    std::string job_getStartToolkit( uint16_t jobEnum); //request toolkit based on the job a player starts as
};








#endif
