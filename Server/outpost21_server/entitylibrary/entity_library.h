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
        entity_generic(std::string set_object_index,double set_x,double set_y, float set_dir, double set_spd, bool set_indestructable, int set_insideid)
        : entity( set_object_index, set_x, set_y, set_dir, set_spd, set_indestructable, set_insideid) {
        }

        using entity::entity_set_inventorylimits;
        using entity::entity_securityInit;

        void entity_personal_step() {
            ///personal actions go here
        }
    };


    class entity_arrivalshuttle : public entity {


        bool SS_collision_ignores_walls = false;
        double SS_decelerator = 1; //no slowdown!

        public:
        entity_arrivalshuttle(std::string set_object_index,double set_x,double set_y, float set_dir, double set_spd, bool set_indestructable, int set_insideid)
        : entity( set_object_index, set_x, set_y, set_dir, set_spd, set_indestructable, set_insideid) {
            myIntVars["dest_x"] = set_x;
            myIntVars["dest_y"] = set_y;
            myIntVars["dropoff_padEntityId"] = -1;
            myIntVars["dropoff_x"] = -10;
            myIntVars["dropoff_y"] = -10;
            myIntVars["dropoff_flag"] = 0;
            myIntVars["dropoff_waitcounter"] = 300;
        }
        using entity::entity_set_inventorylimits;
        using entity::entity_securityInit;

        void entity_personal_step() {
            ///personal actions go here
        }
    };


    class entity_player : public entity {
        public:
        entity_player(std::string set_object_index,double set_x,double set_y, float set_dir, double set_spd, bool set_indestructable, int set_insideid)
        : entity( set_object_index, set_x, set_y, set_dir, set_spd, set_indestructable, set_insideid) {
            myIntVars["stat_str"] = 10;
            myIntVars["stat_int"] = 10;
            myIntVars["stat_dex"] = 10;
            myIntVars["stat_con"] = 10;

            myIntVars["stat_race"] = races::nevrean;
            myIntVars["stat_homeworld"] = homeworlds::offworld;
            myIntVars["stat_body"] = archetype::every;
            myIntVars["stat_job"] = 0;
            myIntVars["stat_jobprev"] = 0;
            myIntVars["stat_guild"] = 0;
            myIntVars["stat_lang_main"] = 0;
            myIntVars["stat_lang_alt"] = 0;
            myIntVars["stat_age"] = 21;

        }
        using entity::entity_set_inventorylimits;
        using entity::entity_securityInit;

        void entity_personal_step() {
            ///personal actions go here
        }
    };


    class entity_borb : public entity {
        double SS_bouncyness = 1.25;
        double SS_decelerator = 0.98;


        public:
        entity_borb(std::string set_object_index,double set_x,double set_y, float set_dir, double set_spd, bool set_indestructable, int set_insideid)
        : entity( set_object_index, set_x, set_y, set_dir, set_spd, set_indestructable, set_insideid) {
        }
        using entity::entity_set_inventorylimits;
        using entity::entity_securityInit;

        void entity_personal_step() {
            ///personal actions go here
        }
    };


    class entity_laserpoint : public entity {

        public:
        entity_laserpoint(std::string set_object_index,double set_x,double set_y, float set_dir, double set_spd, bool set_indestructable, int set_insideid)
        : entity( set_object_index, set_x, set_y, set_dir, set_spd, set_indestructable, set_insideid) {
            myIntVars["firetime"] = 5;
        }
        using entity::entity_set_inventorylimits;
        using entity::entity_securityInit;

        void entity_personal_step() {
            ///personal actions go here
            if(myIntVars["firetime"] > 0) {
                //countdown
                myIntVars["firetime"] -= 1;
            }
            else
            {
                //delete me
            }
        }
    };


    class entity_coffee : public entity {
        public:
        entity_coffee(std::string set_object_index,double set_x,double set_y, float set_dir, double set_spd, bool set_indestructable, int set_insideid)
        : entity( set_object_index, set_x, set_y, set_dir, set_spd, set_indestructable, set_insideid) {
            myIntVars["coffee_hot"] = 15000;
        }
        using entity::entity_set_inventorylimits;
        using entity::entity_securityInit;

        void entity_personal_step() {
            ///personal actions go here
            if(myIntVars["coffee_hot"] > 0) {
                //countdown
                myIntVars["coffee_hot"] -= 1;
            }
            else
            {
                //change into cold coffee
            }
        }
    };


    class entity_powercell : public entity {
        public:
        entity_powercell(std::string set_object_index,double set_x,double set_y, float set_dir, double set_spd, bool set_indestructable, int set_insideid)
        : entity( set_object_index, set_x, set_y, set_dir, set_spd, set_indestructable, set_insideid) {
            myIntVars["charge"] = 0;
        }
        using entity::entity_set_inventorylimits;
        using entity::entity_securityInit;

        void entity_personal_step() {
            ///personal actions go here
            if( myIntVars["charge"] > 0) {
                //countdown
                myIntVars["charge"] -= 1;
            }
            else
            {
                //change into cold coffee
            }
        }
    };


    class entity_securitycard : public entity {
        public:
        entity_securitycard(std::string set_object_index,double set_x,double set_y, float set_dir, double set_spd, bool set_indestructable, int set_insideid)
        : entity( set_object_index, set_x, set_y, set_dir, set_spd, set_indestructable, set_insideid) {
        }
        using entity::entity_set_inventorylimits;
        using entity::entity_securityInit;

        void entity_personal_step() {
            ///personal actions go here
        }
    };



    class entity_machine : public entity {
        public:
        entity_machine(std::string set_object_index,double set_x,double set_y, float set_dir, double set_spd, bool set_indestructable, int set_insideid)
        : entity( set_object_index, set_x, set_y, set_dir, set_spd, set_indestructable, set_insideid) {
            myIntVars["machine_has_power"] = 0;
        }
        using entity::entity_set_inventorylimits;
        using entity::entity_securityInit;

        void entity_personal_step() {
            ///personal actions go here
        }
    };











    ///library creation functions
    /*
        add new entities to BOTH of these! it needs to
        know what kind of class to instantiate as well
        as a bunch of object creation stuff!
    */

    void entity_template_creation() {
        ///living entities
        global.CreateObjectAndAssetIndex("obj_puppet_arrivalshuttle");
        global.CreateObjectAndAssetIndex("obj_puppet_player");
        global.CreateObjectAndAssetIndex("obj_puppet_borb");
        global.CreateObjectAndAssetIndex("obj_puppet_laserpoint");

        ///food
        global.CreateObjectAndAssetIndex("obj_puppet_cup");
        global.CreateObjectAndAssetIndex("obj_puppet_coffeepack");
        global.CreateObjectAndAssetIndex("obj_puppet_coffee_hot");
        global.CreateObjectAndAssetIndex("obj_puppet_coffee_microwaved");
        global.CreateObjectAndAssetIndex("obj_puppet_coffee_cold");

        ///clothing equipment
        global.CreateObjectAndAssetIndex("obj_puppet_toolbelt");
        global.CreateObjectAndAssetIndex("obj_puppet_secbelt");
        global.CreateObjectAndAssetIndex("obj_puppet_medbelt");
        global.CreateObjectAndAssetIndex("obj_puppet_hazardvest");
        global.CreateObjectAndAssetIndex("obj_puppet_hardhat");
        global.CreateObjectAndAssetIndex("obj_puppet_sechelmet");
        global.CreateObjectAndAssetIndex("obj_puppet_firehelmet");
        global.CreateObjectAndAssetIndex("obj_puppet_firesuit");
        global.CreateObjectAndAssetIndex("obj_puppet_secgasmask");
        global.CreateObjectAndAssetIndex("obj_puppet_gasmask");
        global.CreateObjectAndAssetIndex("obj_puppet_secarmor");
        global.CreateObjectAndAssetIndex("obj_puppet_riotarmor");
        global.CreateObjectAndAssetIndex("obj_puppet_bombarmor");
        global.CreateObjectAndAssetIndex("obj_puppet_weldgogs");
        global.CreateObjectAndAssetIndex("obj_puppet_goggles");
        global.CreateObjectAndAssetIndex("obj_puppet_nitrogloves");
        global.CreateObjectAndAssetIndex("obj_puppet_sterilmask");
        global.CreateObjectAndAssetIndex("obj_puppet_cleansuit_helmet");
        global.CreateObjectAndAssetIndex("obj_puppet_cleansuit_body");
        global.CreateObjectAndAssetIndex("obj_puppet_sunglasses");
        global.CreateObjectAndAssetIndex("obj_puppet_glasses_perscrip");
        global.CreateObjectAndAssetIndex("obj_puppet_crowbar");
        global.CreateObjectAndAssetIndex("obj_puppet_wirecutter");
        global.CreateObjectAndAssetIndex("obj_puppet_screwdriver");
        global.CreateObjectAndAssetIndex("obj_puppet_weldtool");
        global.CreateObjectAndAssetIndex("obj_puppet_wrench");
        global.CreateObjectAndAssetIndex("obj_puppet_laserrifle");
        global.CreateObjectAndAssetIndex("obj_puppet_powercell");
        global.CreateObjectAndAssetIndex("obj_puppet_securitycard");
        global.CreateObjectAndAssetIndex("obj_puppet_securitytool");
        global.CreateObjectAndAssetIndex("obj_puppet_flashlight");
        global.CreateObjectAndAssetIndex("obj_puppet_flare");
        global.CreateObjectAndAssetIndex("obj_puppet_radioA");
        global.CreateObjectAndAssetIndex("obj_puppet_umbrella");
        global.CreateObjectAndAssetIndex("obj_puppet_paper");
        global.CreateObjectAndAssetIndex("obj_puppet_pen");
        global.CreateObjectAndAssetIndex("obj_puppet_pencil");
        global.CreateObjectAndAssetIndex("obj_puppet_bucket");
        global.CreateObjectAndAssetIndex("obj_puppet_mop");
        global.CreateObjectAndAssetIndex("obj_puppet_fireex");
        global.CreateObjectAndAssetIndex("obj_puppet_fireaxe");
        global.CreateObjectAndAssetIndex("obj_puppet_stunbaton");
        global.CreateObjectAndAssetIndex("obj_puppet_pepperspray");
        global.CreateObjectAndAssetIndex("obj_puppet_taser");
        global.CreateObjectAndAssetIndex("obj_puppet_flashbang");
        global.CreateObjectAndAssetIndex("obj_puppet_emp");
        global.CreateObjectAndAssetIndex("obj_puppet_handcuffs");
        global.CreateObjectAndAssetIndex("obj_puppet_secflashlight");
        global.CreateObjectAndAssetIndex("obj_puppet_fluidspec");
        global.CreateObjectAndAssetIndex("obj_puppet_stethoscope");
        global.CreateObjectAndAssetIndex("obj_puppet_bandaid_box");
        global.CreateObjectAndAssetIndex("obj_puppet_bandaid");
        global.CreateObjectAndAssetIndex("obj_puppet_burnointment");
        global.CreateObjectAndAssetIndex("obj_puppet_disinfectant");
        global.CreateObjectAndAssetIndex("obj_puppet_antitoxin");
        global.CreateObjectAndAssetIndex("obj_puppet_epinephrine");
        global.CreateObjectAndAssetIndex("obj_puppet_syringe");
        global.CreateObjectAndAssetIndex("obj_puppet_hypoinject");
        global.CreateObjectAndAssetIndex("obj_puppet_beaker");
        global.CreateObjectAndAssetIndex("obj_puppet_pillbottle");
        global.CreateObjectAndAssetIndex("obj_puppet_scalpel");
        global.CreateObjectAndAssetIndex("obj_puppet_hemostat");
        global.CreateObjectAndAssetIndex("obj_puppet_sutures");
        global.CreateObjectAndAssetIndex("obj_puppet_surgerysaw");
        global.CreateObjectAndAssetIndex("obj_puppet_surgerydrill");
        global.CreateObjectAndAssetIndex("obj_puppet_cauterytool");
        global.CreateObjectAndAssetIndex("obj_puppet_cryobeaker");
        global.CreateObjectAndAssetIndex("obj_puppet_gps");

        global.CreateObjectAndAssetIndex("obj_puppet_labeler");
        global.CreateObjectAndAssetIndex("obj_puppet_ducttape");
        global.CreateObjectAndAssetIndex("obj_puppet_cautiontape");
        global.CreateObjectAndAssetIndex("obj_puppet_clipboard");


        //furniture
        global.CreateObjectAndAssetIndex("obj_furniture_stool");
        global.CreateObjectAndAssetIndex("obj_furniture_table");
        global.CreateObjectAndAssetIndex("obj_furniture_locker");
        global.CreateObjectAndAssetIndex("obj_furniture_trashbin");

        global.CreateObjectAndAssetIndex("obj_puppet_janitorcart");

        global.CreateObjectAndAssetIndex("obj_puppet_microwave");
        global.CreateObjectAndAssetIndex("obj_puppet_coffeemaker");

        //constructables and blueprints
        global.CreateObjectAndAssetIndex("obj_puppet_conduit");

        global.CreateObjectAndAssetIndex("obj_machine_STC");

        global.CreateObjectAndAssetIndex("obj_puppet_blueprint");

        global.CreateObjectAndAssetIndex("obj_puppet_blueprint_genorator");
        global.CreateObjectAndAssetIndex("obj_machine_genorator");

        global.CreateObjectAndAssetIndex("obj_puppet_blueprint_outdoorlamp");
        global.CreateObjectAndAssetIndex("obj_machine_outdoorlamp");

        global.CreateObjectAndAssetIndex("obj_machine_indoorlamp");

        global.CreateObjectAndAssetIndex("obj_puppet_blueprint_printer");
        global.CreateObjectAndAssetIndex("obj_machine_blueprinter");

        global.CreateObjectAndAssetIndex("obj_puppet_blueprint_chargingstation");
        global.CreateObjectAndAssetIndex("obj_machine_chargingstation");


        global.CreateObjectAndAssetIndex("obj_puppet_blueprint_fabricator");
        global.CreateObjectAndAssetIndex("obj_machine_fabricator");

        global.CreateObjectAndAssetIndex("obj_puppet_blueprint_elecassem");
        global.CreateObjectAndAssetIndex("obj_machine_elecassem");

        //resources and parts
        global.CreateObjectAndAssetIndex("obj_puppet_plastic_rod");
        global.CreateObjectAndAssetIndex("obj_puppet_metal_ingot");
        global.CreateObjectAndAssetIndex("obj_puppet_metal_plates");
        global.CreateObjectAndAssetIndex("obj_puppet_metal_cable");
        global.CreateObjectAndAssetIndex("obj_puppet_metal_frames");
        global.CreateObjectAndAssetIndex("obj_puppet_parts_fabarray");
        global.CreateObjectAndAssetIndex("obj_puppet_parts_wires");

        ///toolboxes
        global.CreateObjectAndAssetIndex("obj_puppet_assistbox");
        global.CreateObjectAndAssetIndex("obj_puppet_cargobox");
        global.CreateObjectAndAssetIndex("obj_puppet_commsbox");
        global.CreateObjectAndAssetIndex("obj_puppet_weatherbox");
        global.CreateObjectAndAssetIndex("obj_puppet_labbox");
        global.CreateObjectAndAssetIndex("obj_puppet_medicbox");
        global.CreateObjectAndAssetIndex("obj_puppet_toolbox");
        global.CreateObjectAndAssetIndex("obj_puppet_minebox");
        global.CreateObjectAndAssetIndex("obj_puppet_secbox");
        global.CreateObjectAndAssetIndex("obj_puppet_atmobox");
        global.CreateObjectAndAssetIndex("obj_puppet_hydrobox");
        global.CreateObjectAndAssetIndex("obj_puppet_janibox");
    }


    entity* entity_template_library(std::string set_object_index,double set_x,double set_y, float set_dir, double set_spd, bool set_indestructable, int set_insideid) {
        ///this function is largely for GM compatibility
        entity* returnPointer;

        //switches can't handle strings here, soooooooooo.....

        ///living entities
        if(set_object_index == "obj_puppet_arrivalshuttle") {
            returnPointer = new entity_arrivalshuttle( set_object_index,set_x,set_y,set_dir,set_spd,set_indestructable,set_insideid);
            returnPointer->entity_set_inventorylimits(1, itemdata::huge, itemdata::large, false, false, itemdata::ship, itemdata::generic);
        }
        else if(set_object_index == "obj_puppet_player") {
            returnPointer = new entity_player( set_object_index,set_x,set_y,set_dir,set_spd,set_indestructable,set_insideid);
            returnPointer->entity_set_inventorylimits(12, itemdata::large, itemdata::medium, false, false, itemdata::body, itemdata::generic);
            returnPointer->entity_securityInit();
        }
        else if(set_object_index == "obj_puppet_borb") {
            returnPointer = new entity_borb( set_object_index,set_x,set_y,set_dir,set_spd,set_indestructable,set_insideid);
            returnPointer->entity_set_inventorylimits( 0, itemdata::tiny, itemdata::none, true, false, itemdata::body, itemdata::generic);
        }
        else if(set_object_index == "obj_puppet_laserpoint") {
            returnPointer = new entity_laserpoint( set_object_index,set_x,set_y,set_dir,set_spd,set_indestructable,set_insideid);
            returnPointer->entity_set_inventorylimits( 0, itemdata::medium, itemdata::none, false, false, itemdata::generic, itemdata::generic);
        }

        ///food
        else if(set_object_index == "obj_puppet_cup") {
            returnPointer = new entity_generic( set_object_index,set_x,set_y,set_dir,set_spd,set_indestructable,set_insideid);
            returnPointer->entity_set_inventorylimits( 1, itemdata::smal , itemdata::tiny, false, true, itemdata::generic, itemdata::generic );
        }
        else if(set_object_index == "obj_puppet_coffeepack") {
            returnPointer = new entity_generic( set_object_index,set_x,set_y,set_dir,set_spd,set_indestructable,set_insideid);
            returnPointer->entity_set_inventorylimits( 0, itemdata::smal, itemdata::tiny, false, true, itemdata::generic, itemdata::generic);
        }
        else if(set_object_index == "obj_puppet_coffee_hot") {
            returnPointer = new entity_coffee( set_object_index,set_x,set_y,set_dir,set_spd,set_indestructable,set_insideid);
            //returnPointer->coffee_hot = 15000;
            returnPointer->entity_set_inventorylimits(0, itemdata::tiny, itemdata::none, true, false, itemdata::food, itemdata::generic);
        }
        else if(set_object_index == "obj_puppet_coffee_microwaved") {
            returnPointer = new entity_coffee( set_object_index,set_x,set_y,set_dir,set_spd,set_indestructable,set_insideid);
           // returnPointer->coffee_hot = 11000;
            returnPointer->entity_set_inventorylimits(0, itemdata::tiny, itemdata::none, true, false, itemdata::food, itemdata::generic);
        }
        else if(set_object_index == "obj_puppet_coffee_cold") {
            returnPointer = new entity_generic( set_object_index,set_x,set_y,set_dir,set_spd,set_indestructable,set_insideid);
            returnPointer->entity_set_inventorylimits(0, itemdata::tiny, itemdata::none, true, false, itemdata::food, itemdata::generic);
        }

        ///clothing equipment
        else if(set_object_index == "obj_puppet_toolbelt"
        || set_object_index == "obj_puppet_secbelt"
        || set_object_index == "obj_puppet_medbelt") {
            returnPointer = new entity_generic( set_object_index,set_x,set_y,set_dir,set_spd,set_indestructable,set_insideid);
            returnPointer->entity_set_inventorylimits( 5, itemdata::medium, itemdata::smal, false, false, itemdata::generic, itemdata::tools);
        }


        else if(set_object_index == "obj_puppet_hazardvest") {
            returnPointer = new entity_generic( set_object_index,set_x,set_y,set_dir,set_spd,set_indestructable,set_insideid);
            returnPointer->entity_set_inventorylimits( 0, itemdata::medium, itemdata::none, false, false, itemdata::clothing, itemdata::generic);
        }

        else if(set_object_index == "obj_puppet_hardhat") {
            returnPointer = new entity_generic( set_object_index,set_x,set_y,set_dir,set_spd,set_indestructable,set_insideid);
            returnPointer->entity_set_inventorylimits( 0,itemdata::medium, itemdata::smal, false, true, itemdata::clothing, itemdata::generic);
        }

        else if(set_object_index == "obj_puppet_sechelmet") {
            returnPointer = new entity_generic( set_object_index,set_x,set_y,set_dir,set_spd,set_indestructable,set_insideid);
            returnPointer->entity_set_inventorylimits( 0,itemdata::medium, itemdata::smal, false, true, itemdata::clothing, itemdata::generic);
        }

        else if(set_object_index == "obj_puppet_firehelmet") {
            returnPointer = new entity_generic( set_object_index,set_x,set_y,set_dir,set_spd,set_indestructable,set_insideid);
            returnPointer->entity_set_inventorylimits( 0, itemdata::medium, itemdata::none, false, false, itemdata::clothing, itemdata::generic);
        }

        else if(set_object_index == "obj_puppet_firesuit") {
            returnPointer = new entity_generic( set_object_index,set_x,set_y,set_dir,set_spd,set_indestructable,set_insideid);
            returnPointer->entity_set_inventorylimits( 0, itemdata::medium, itemdata::none, false, false, itemdata::clothing, itemdata::generic);
        }

        else if(set_object_index == "obj_puppet_secgasmask") {
            returnPointer = new entity_generic( set_object_index,set_x,set_y,set_dir,set_spd,set_indestructable,set_insideid);
            returnPointer->entity_set_inventorylimits( 0, itemdata::medium, itemdata::none, false, false, itemdata::clothing, itemdata::generic);
        }

        else if(set_object_index == "obj_puppet_gasmask") {
            returnPointer = new entity_generic( set_object_index,set_x,set_y,set_dir,set_spd,set_indestructable,set_insideid);
            returnPointer->entity_set_inventorylimits( 0, itemdata::medium, itemdata::none, false, false, itemdata::clothing, itemdata::generic);
        }

        else if(set_object_index == "obj_puppet_secarmor") {
            returnPointer = new entity_generic( set_object_index,set_x,set_y,set_dir,set_spd,set_indestructable,set_insideid);
            returnPointer->entity_set_inventorylimits( 0, itemdata::medium, itemdata::none, false, false, itemdata::clothing, itemdata::generic);
        }

        else if(set_object_index == "obj_puppet_riotarmor") {
            returnPointer = new entity_generic( set_object_index,set_x,set_y,set_dir,set_spd,set_indestructable,set_insideid);
            returnPointer->entity_set_inventorylimits( 0, itemdata::medium, itemdata::none, false, false, itemdata::clothing, itemdata::generic);
        }

        else if(set_object_index == "obj_puppet_bombarmor") {
            returnPointer = new entity_generic( set_object_index,set_x,set_y,set_dir,set_spd,set_indestructable,set_insideid);
            returnPointer->entity_set_inventorylimits( 0, itemdata::medium, itemdata::none, false, false, itemdata::clothing, itemdata::generic);
        }

        else if(set_object_index == "obj_puppet_weldgogs") {
            returnPointer = new entity_generic( set_object_index,set_x,set_y,set_dir,set_spd,set_indestructable,set_insideid);
            returnPointer->entity_set_inventorylimits( 0, itemdata::medium, itemdata::none, false, false, itemdata::clothing, itemdata::generic);
        }

        else if(set_object_index == "obj_puppet_goggles") {
            returnPointer = new entity_generic( set_object_index,set_x,set_y,set_dir,set_spd,set_indestructable,set_insideid);
            returnPointer->entity_set_inventorylimits( 0, itemdata::medium, itemdata::none, false, false, itemdata::clothing, itemdata::generic);
        }

        else if(set_object_index == "obj_puppet_nitrogloves") {
            returnPointer = new entity_generic( set_object_index,set_x,set_y,set_dir,set_spd,set_indestructable,set_insideid);
            returnPointer->entity_set_inventorylimits( 0, itemdata::smal, itemdata::none, false, false, itemdata::clothing, itemdata::generic);
        }

        else if(set_object_index == "obj_puppet_sterilmask") {
            returnPointer = new entity_generic( set_object_index,set_x,set_y,set_dir,set_spd,set_indestructable,set_insideid);
            returnPointer->entity_set_inventorylimits( 0, itemdata::smal, itemdata::none, false, false, itemdata::clothing, itemdata::generic);
        }

        else if(set_object_index == "obj_puppet_cleansuit_helmet") {
            returnPointer = new entity_generic( set_object_index,set_x,set_y,set_dir,set_spd,set_indestructable,set_insideid);
            returnPointer->entity_set_inventorylimits( 0, itemdata::medium, itemdata::none, false, false, itemdata::clothing, itemdata::generic);
        }

        else if(set_object_index == "obj_puppet_cleansuit_body") {
            returnPointer = new entity_generic( set_object_index,set_x,set_y,set_dir,set_spd,set_indestructable,set_insideid);
            returnPointer->entity_set_inventorylimits( 0, itemdata::medium, itemdata::none, false, false, itemdata::clothing, itemdata::generic);
        }

        else if(set_object_index == "obj_puppet_sunglasses") {
            returnPointer = new entity_generic( set_object_index,set_x,set_y,set_dir,set_spd,set_indestructable,set_insideid);
            returnPointer->entity_set_inventorylimits( 0, itemdata::smal, itemdata::none, false, false, itemdata::clothing, itemdata::generic);
        }

        else if(set_object_index == "obj_puppet_glasses_perscrip") {
            returnPointer = new entity_generic( set_object_index,set_x,set_y,set_dir,set_spd,set_indestructable,set_insideid);
            returnPointer->entity_set_inventorylimits( 0, itemdata::smal, itemdata::none, false, false, itemdata::clothing, itemdata::generic);
        }

        //tools
        else if(set_object_index == "obj_puppet_crowbar") {
            returnPointer = new entity_generic( set_object_index,set_x,set_y,set_dir,set_spd,set_indestructable,set_insideid);
            returnPointer->entity_set_inventorylimits( 0, itemdata::smal, itemdata::none, false, false, itemdata::tools, itemdata::generic);
        }

        else if(set_object_index == "obj_puppet_wirecutter") {
            returnPointer = new entity_generic( set_object_index,set_x,set_y,set_dir,set_spd,set_indestructable,set_insideid);
            returnPointer->entity_set_inventorylimits( 0, itemdata::smal, itemdata::none, false, false, itemdata::tools, itemdata::generic);
        }

        else if(set_object_index == "obj_puppet_screwdriver") {
            returnPointer = new entity_generic( set_object_index,set_x,set_y,set_dir,set_spd,set_indestructable,set_insideid);
            returnPointer->entity_set_inventorylimits( 0, itemdata::smal, itemdata::none, false, false, itemdata::tools, itemdata::generic);
        }

        else if(set_object_index == "obj_puppet_weldtool") {
            returnPointer = new entity_generic( set_object_index,set_x,set_y,set_dir,set_spd,set_indestructable,set_insideid);
            returnPointer->entity_set_inventorylimits( 0, itemdata::smal, itemdata::none, false, false, itemdata::tools, itemdata::generic);
        }

        else if(set_object_index == "obj_puppet_wrench") {
            returnPointer = new entity_generic( set_object_index,set_x,set_y,set_dir,set_spd,set_indestructable,set_insideid);
            returnPointer->entity_set_inventorylimits( 0, itemdata::smal, itemdata::none, false, false, itemdata::tools, itemdata::generic);
        }

        else if(set_object_index == "obj_puppet_laserrifle") {
            returnPointer = new entity_generic( set_object_index,set_x,set_y,set_dir,set_spd,set_indestructable,set_insideid);
            returnPointer->entity_set_inventorylimits( 0,itemdata::medium, itemdata::smal, false, false, itemdata::rifle, itemdata::generic);
        }

        else if(set_object_index == "obj_puppet_powercell") {
            returnPointer = new entity_powercell( set_object_index,set_x,set_y,set_dir,set_spd,set_indestructable,set_insideid);
            returnPointer->entity_set_inventorylimits( 0, itemdata::smal, itemdata::none, false, false, itemdata::generic, itemdata::generic);
            //returnPointer->Charge = 0;
        }

        else if(set_object_index == "obj_puppet_securitycard") {
            returnPointer = new entity_securitycard( set_object_index,set_x,set_y,set_dir,set_spd,set_indestructable,set_insideid);
            returnPointer->entity_set_inventorylimits( 0, itemdata::tiny, itemdata::none, false, false, itemdata::generic, itemdata::generic);
            returnPointer->entity_securityInit();
        }

        else if(set_object_index == "obj_puppet_securitytool") {
            returnPointer = new entity_generic( set_object_index,set_x,set_y,set_dir,set_spd,set_indestructable,set_insideid);
            returnPointer->entity_set_inventorylimits( 0,itemdata::smal, itemdata::tiny, false, false, itemdata::generic, itemdata::generic);
        }

        else if(set_object_index == "obj_puppet_flashlight") {
            returnPointer = new entity_generic( set_object_index,set_x,set_y,set_dir,set_spd,set_indestructable,set_insideid);
            returnPointer->entity_set_inventorylimits( 0,itemdata::smal, itemdata::smal, false, false, itemdata::generic, itemdata::generic);
        }

        else if(set_object_index == "obj_puppet_flare") {
            returnPointer = new entity_generic( set_object_index,set_x,set_y,set_dir,set_spd,set_indestructable,set_insideid);
            returnPointer->entity_set_inventorylimits( 0, itemdata::smal, itemdata::none, false, false, itemdata::generic, itemdata::generic);
        }

        else if(set_object_index == "obj_puppet_radioA") {
            returnPointer = new entity_generic( set_object_index,set_x,set_y,set_dir,set_spd,set_indestructable,set_insideid);
            returnPointer->entity_set_inventorylimits( 0,itemdata::smal, itemdata::smal, false, false, itemdata::generic, itemdata::generic);
        }

        else if(set_object_index == "obj_puppet_umbrella") {
            returnPointer = new entity_generic( set_object_index,set_x,set_y,set_dir,set_spd,set_indestructable,set_insideid);
            returnPointer->entity_set_inventorylimits( 0, itemdata::medium, itemdata::none, false, false, itemdata::generic, itemdata::generic);
        }

        else if(set_object_index == "obj_puppet_paper") {
            returnPointer = new entity_generic( set_object_index,set_x,set_y,set_dir,set_spd,set_indestructable,set_insideid);
            returnPointer->entity_set_inventorylimits( 0, itemdata::tiny, itemdata::none, false, false, itemdata::sheets, itemdata::generic);
        }

        else if(set_object_index == "obj_puppet_pen") {
            returnPointer = new entity_generic( set_object_index,set_x,set_y,set_dir,set_spd,set_indestructable,set_insideid);
            returnPointer->entity_set_inventorylimits( 0, itemdata::tiny, itemdata::none, false, false, itemdata::generic, itemdata::generic);
        }

        else if(set_object_index == "obj_puppet_pencil") {
            returnPointer = new entity_generic( set_object_index,set_x,set_y,set_dir,set_spd,set_indestructable,set_insideid);
            returnPointer->entity_set_inventorylimits( 0, itemdata::tiny, itemdata::none, false, false, itemdata::generic, itemdata::generic);
        }

        else if(set_object_index == "obj_puppet_bucket") {
            returnPointer = new entity_generic( set_object_index,set_x,set_y,set_dir,set_spd,set_indestructable,set_insideid);
            returnPointer->entity_set_inventorylimits( 4, itemdata::medium, itemdata::smal, false, false, itemdata::generic, itemdata::generic);
        }

        else if(set_object_index == "obj_puppet_mop") {
            returnPointer = new entity_generic( set_object_index,set_x,set_y,set_dir,set_spd,set_indestructable,set_insideid);
            returnPointer->entity_set_inventorylimits( 0,itemdata::medium, itemdata::none, false, true, itemdata::generic, itemdata::generic);
        }

        else if(set_object_index == "obj_puppet_fireex") {
            returnPointer = new entity_generic( set_object_index,set_x,set_y,set_dir,set_spd,set_indestructable,set_insideid);
            returnPointer->entity_set_inventorylimits( 0, itemdata::medium, itemdata::none, false, false, itemdata::tools, itemdata::generic);
        }

        else if(set_object_index == "obj_puppet_fireaxe") {
            returnPointer = new entity_generic( set_object_index,set_x,set_y,set_dir,set_spd,set_indestructable,set_insideid);
            returnPointer->entity_set_inventorylimits( 0, itemdata::medium, itemdata::none, false, false, itemdata::tools, itemdata::generic);
        }

        else if(set_object_index == "obj_puppet_stunbaton") {
            returnPointer = new entity_generic( set_object_index,set_x,set_y,set_dir,set_spd,set_indestructable,set_insideid);
            returnPointer->entity_set_inventorylimits( 0, itemdata::smal, itemdata::none, false, false, itemdata::tools, itemdata::generic);
        }

        else if(set_object_index == "obj_puppet_pepperspray") {
            returnPointer = new entity_generic( set_object_index,set_x,set_y,set_dir,set_spd,set_indestructable,set_insideid);
            returnPointer->entity_set_inventorylimits( 0, itemdata::tiny, itemdata::none, false, false, itemdata::generic, itemdata::generic);
        }

        else if(set_object_index == "obj_puppet_taser") {
            returnPointer = new entity_generic( set_object_index,set_x,set_y,set_dir,set_spd,set_indestructable,set_insideid);
            returnPointer->entity_set_inventorylimits( 0, itemdata::smal, itemdata::none, false, false, itemdata::pistol, itemdata::generic);
        }

        else if(set_object_index == "obj_puppet_flashbang") {
            returnPointer = new entity_generic( set_object_index,set_x,set_y,set_dir,set_spd,set_indestructable,set_insideid);
            returnPointer->entity_set_inventorylimits( 0, itemdata::tiny, itemdata::none, false, false, itemdata::generic, itemdata::generic);
        }

        else if(set_object_index == "obj_puppet_emp") {
            returnPointer = new entity_generic( set_object_index,set_x,set_y,set_dir,set_spd,set_indestructable,set_insideid);
            returnPointer->entity_set_inventorylimits( 0, itemdata::tiny, itemdata::none, false, false, itemdata::generic, itemdata::generic);
        }

        else if(set_object_index == "obj_puppet_handcuffs") {
            returnPointer = new entity_generic( set_object_index,set_x,set_y,set_dir,set_spd,set_indestructable,set_insideid);
            returnPointer->entity_set_inventorylimits( 0, itemdata::smal, itemdata::none, false, false, itemdata::generic, itemdata::generic);
        }

        else if(set_object_index == "obj_puppet_secflashlight") {
            returnPointer = new entity_generic( set_object_index,set_x,set_y,set_dir,set_spd,set_indestructable,set_insideid);
            returnPointer->entity_set_inventorylimits( 1,itemdata::smal, itemdata::smal, false, false, itemdata::generic, itemdata::generic);
        }

        else if(set_object_index == "obj_puppet_fluidspec") {
            returnPointer = new entity_generic( set_object_index,set_x,set_y,set_dir,set_spd,set_indestructable,set_insideid);
            returnPointer->entity_set_inventorylimits( 0, itemdata::smal, itemdata::none, false, false, itemdata::generic, itemdata::generic);
        }

        else if(set_object_index == "obj_puppet_stethoscope") {
            returnPointer = new entity_generic( set_object_index,set_x,set_y,set_dir,set_spd,set_indestructable,set_insideid);
            returnPointer->entity_set_inventorylimits( 0, itemdata::smal, itemdata::none, false, false, itemdata::generic, itemdata::generic);
        }

        else if(set_object_index == "obj_puppet_bandaid_box") {
            returnPointer = new entity_generic( set_object_index,set_x,set_y,set_dir,set_spd,set_indestructable,set_insideid);
            returnPointer->entity_set_inventorylimits( 10, itemdata::smal, itemdata::tiny, false, false, itemdata::generic, itemdata::generic);
        }

        else if(set_object_index == "obj_puppet_bandaid") {
            returnPointer = new entity_generic( set_object_index,set_x,set_y,set_dir,set_spd,set_indestructable,set_insideid);
            returnPointer->entity_set_inventorylimits( 0, itemdata::tiny, itemdata::none, false, false, itemdata::generic, itemdata::generic);
        }

        else if(set_object_index == "obj_puppet_burnointment") {
            returnPointer = new entity_generic( set_object_index,set_x,set_y,set_dir,set_spd,set_indestructable,set_insideid);
            returnPointer->entity_set_inventorylimits( 0, itemdata::tiny, itemdata::none, false, false, itemdata::generic, itemdata::generic);
        }

        else if(set_object_index == "obj_puppet_disinfectant") {
            returnPointer = new entity_generic( set_object_index,set_x,set_y,set_dir,set_spd,set_indestructable,set_insideid);
            returnPointer->entity_set_inventorylimits( 0, itemdata::tiny, itemdata::none, false, false, itemdata::generic, itemdata::generic);
        }

        else if(set_object_index == "obj_puppet_antitoxin") {
            returnPointer = new entity_generic( set_object_index,set_x,set_y,set_dir,set_spd,set_indestructable,set_insideid);
            returnPointer->entity_set_inventorylimits( 0, itemdata::tiny, itemdata::none, false, false, itemdata::generic, itemdata::generic);
        }

        else if(set_object_index == "obj_puppet_epinephrine") {
            returnPointer = new entity_generic( set_object_index,set_x,set_y,set_dir,set_spd,set_indestructable,set_insideid);
            returnPointer->entity_set_inventorylimits( 0, itemdata::tiny, itemdata::none, false, false, itemdata::generic, itemdata::generic);
        }

        else if(set_object_index == "obj_puppet_syringe") {
            returnPointer = new entity_generic( set_object_index,set_x,set_y,set_dir,set_spd,set_indestructable,set_insideid);
            returnPointer->entity_set_inventorylimits( 0,itemdata::tiny, itemdata::none, false, true, itemdata::generic, itemdata::generic);
        }

        else if(set_object_index == "obj_puppet_hypoinject") {
            returnPointer = new entity_generic( set_object_index,set_x,set_y,set_dir,set_spd,set_indestructable,set_insideid);
            returnPointer->entity_set_inventorylimits( 0, itemdata::tiny, itemdata::none, false, false, itemdata::generic, itemdata::generic);
        }

        else if(set_object_index == "obj_puppet_beaker") {
            returnPointer = new entity_generic( set_object_index,set_x,set_y,set_dir,set_spd,set_indestructable,set_insideid);
            returnPointer->entity_set_inventorylimits( 2, itemdata::smal, itemdata::none, false, true, itemdata::generic, itemdata::generic);
        }

        else if(set_object_index == "obj_puppet_pillbottle") {
            returnPointer = new entity_generic( set_object_index,set_x,set_y,set_dir,set_spd,set_indestructable,set_insideid);
            returnPointer->entity_set_inventorylimits( 10, itemdata::smal, itemdata::tiny, false, false, itemdata::generic, itemdata::generic);
        }

        else if(set_object_index == "obj_puppet_scalpel") {
            returnPointer = new entity_generic( set_object_index,set_x,set_y,set_dir,set_spd,set_indestructable,set_insideid);
            returnPointer->entity_set_inventorylimits( 0, itemdata::tiny, itemdata::none, false, false, itemdata::generic, itemdata::generic);
        }

        else if(set_object_index == "obj_puppet_hemostat") {
            returnPointer = new entity_generic( set_object_index,set_x,set_y,set_dir,set_spd,set_indestructable,set_insideid);
            returnPointer->entity_set_inventorylimits( 0, itemdata::tiny, itemdata::none, false, false, itemdata::generic, itemdata::generic);
        }

        else if(set_object_index == "obj_puppet_sutures") {
            returnPointer = new entity_generic( set_object_index,set_x,set_y,set_dir,set_spd,set_indestructable,set_insideid);
            returnPointer->entity_set_inventorylimits( 0, itemdata::tiny, itemdata::none, false, false, itemdata::generic, itemdata::generic);
        }

        else if(set_object_index == "obj_puppet_surgerysaw") {
            returnPointer = new entity_generic( set_object_index,set_x,set_y,set_dir,set_spd,set_indestructable,set_insideid);
            returnPointer->entity_set_inventorylimits( 0,itemdata::medium, itemdata::smal, false, false, itemdata::tools, itemdata::generic);
        }

        else if(set_object_index == "obj_puppet_surgerydrill") {
            returnPointer = new entity_generic( set_object_index,set_x,set_y,set_dir,set_spd,set_indestructable,set_insideid);
            returnPointer->entity_set_inventorylimits( 0,itemdata::smal, itemdata::smal, false, false, itemdata::tools, itemdata::generic);
        }

        else if(set_object_index == "obj_puppet_cauterytool") {
            returnPointer = new entity_generic( set_object_index,set_x,set_y,set_dir,set_spd,set_indestructable,set_insideid);
            returnPointer->entity_set_inventorylimits( 0,itemdata::smal, itemdata::smal, false, false, itemdata::generic, itemdata::generic);
        }

        else if(set_object_index == "obj_puppet_cryobeaker") {
            returnPointer = new entity_generic( set_object_index,set_x,set_y,set_dir,set_spd,set_indestructable,set_insideid);
            returnPointer->entity_set_inventorylimits( 2, itemdata::smal, itemdata::none, false, true, itemdata::generic, itemdata::generic);
        }

        else if(set_object_index == "obj_puppet_gps") {
            returnPointer = new entity_generic( set_object_index,set_x,set_y,set_dir,set_spd,set_indestructable,set_insideid);
            returnPointer->entity_set_inventorylimits( 0,itemdata::smal, itemdata::smal, false, false, itemdata::tools, itemdata::generic);
        }

        else if(set_object_index == "obj_puppet_labeler") {
            returnPointer = new entity_generic( set_object_index,set_x,set_y,set_dir,set_spd,set_indestructable,set_insideid);
            returnPointer->entity_set_inventorylimits( 2, itemdata::smal, itemdata::smal, false, false, itemdata::tools, itemdata::generic);
        }

        else if(set_object_index == "obj_puppet_ducttape") {
            returnPointer = new entity_generic( set_object_index,set_x,set_y,set_dir,set_spd,set_indestructable,set_insideid);
            returnPointer->entity_set_inventorylimits( 0, itemdata::smal, itemdata::none, false, false, itemdata::tools, itemdata::generic);
        }

        else if(set_object_index == "obj_puppet_cautiontape") {
            returnPointer = new entity_generic( set_object_index,set_x,set_y,set_dir,set_spd,set_indestructable,set_insideid);
            returnPointer->entity_set_inventorylimits( 0, itemdata::smal, itemdata::none, false, false, itemdata::tools, itemdata::generic);
        }

        else if(set_object_index == "obj_puppet_clipboard") {
            returnPointer = new entity_generic( set_object_index,set_x,set_y,set_dir,set_spd,set_indestructable,set_insideid);
            returnPointer->entity_set_inventorylimits( 5, itemdata::smal, itemdata::tiny, false, false, itemdata::generic, itemdata::sheets);
        }



        //furniture
        else if(set_object_index == "obj_furniture_stool") {
            //pop out generic item...
            returnPointer = new entity_generic( set_object_index,set_x,set_y,set_dir,set_spd,set_indestructable,set_insideid);
            returnPointer->entity_set_inventorylimits( 0, itemdata::medium, itemdata::none, false, false, itemdata::generic, itemdata::generic);
        }

        else if(set_object_index == "obj_furniture_table") {
            //pop out generic item...
            returnPointer = new entity_generic( set_object_index,set_x,set_y,set_dir,set_spd,set_indestructable,set_insideid);
            returnPointer->entity_set_inventorylimits( 1,itemdata::large, itemdata::medium, false, false, itemdata::generic, itemdata::generic);
            returnPointer->contains_display = true;
            returnPointer->contains_display_x = 0;
            returnPointer->contains_display_y = -16;
            returnPointer->contains_display_d = -5;
        }

        else if(set_object_index == "obj_furniture_locker") {
            returnPointer = new entity_generic( set_object_index,set_x,set_y,set_dir,set_spd,set_indestructable,set_insideid);
            //setup a default inventory for the cup! it can store one object!
            returnPointer->entity_set_inventorylimits( 20, itemdata::large, itemdata::large, false, false, itemdata::generic, itemdata::generic);
        }

        else if(set_object_index == "obj_furniture_trashbin") {
            returnPointer = new entity_generic( set_object_index,set_x,set_y,set_dir,set_spd,set_indestructable,set_insideid);
            //setup a default inventory for the cup! it can store one object!
            returnPointer->entity_set_inventorylimits( 20, itemdata::large, itemdata::large, false, false, itemdata::generic, itemdata::generic);
        }

        else if(set_object_index == "obj_puppet_janitorcart") {
            returnPointer = new entity_generic( set_object_index,set_x,set_y,set_dir,set_spd,set_indestructable,set_insideid);
            //setup a default inventory for the cup! it can store one object!
            returnPointer->entity_set_inventorylimits( 8, itemdata::service_cart, itemdata::large, false, false, itemdata::generic, itemdata::generic);
        }

        else if(set_object_index == "obj_puppet_microwave") {
            //pop out generic item...
            returnPointer = new entity_generic( set_object_index,set_x,set_y,set_dir,set_spd,set_indestructable,set_insideid);
            returnPointer->entity_set_inventorylimits( 2, itemdata::medium, itemdata::smal, false, false, itemdata::generic, itemdata::generic);
        }

        else if(set_object_index == "obj_puppet_coffeemaker") {
            //pop out generic item...
            returnPointer = new entity_generic( set_object_index,set_x,set_y,set_dir,set_spd,set_indestructable,set_insideid);
            returnPointer->entity_set_inventorylimits( 3, itemdata::medium, itemdata::smal, false, false, itemdata::generic, itemdata::generic);
        }



        //constructables and blueprints
        else if(set_object_index == "obj_puppet_conduit") {
            //pop out generic item...
            returnPointer = new entity_generic( set_object_index,set_x,set_y,set_dir,set_spd,set_indestructable,set_insideid);
            returnPointer->entity_set_inventorylimits( 0, itemdata::medium, itemdata::none, false, false, itemdata::generic, itemdata::generic);
        }



        else if(set_object_index == "obj_machine_STC") {
            //pop out generic item...
            returnPointer = new entity_generic( set_object_index,set_x,set_y,set_dir,set_spd,set_indestructable,set_insideid);
            returnPointer->entity_set_inventorylimits( 10, itemdata::medium, itemdata::medium, false, false, itemdata::machines, itemdata::machine_parts);
            returnPointer->myIntVars["object_building"] = -1;
        }



        else if(set_object_index == "obj_puppet_blueprint") {
            returnPointer = new entity_generic( set_object_index,set_x,set_y,set_dir,set_spd,set_indestructable,set_insideid);
            //setup a default inventory for the cup! it can store one object!
            returnPointer->entity_set_inventorylimits( 0, itemdata::smal, itemdata::none, false, true, itemdata::machine_parts, itemdata::generic);
        }




        else if(set_object_index == "obj_puppet_blueprint_genorator") {
            returnPointer = new entity_generic( set_object_index,set_x,set_y,set_dir,set_spd,set_indestructable,set_insideid);
            //setup a default inventory for the cup! it can store one object!
            returnPointer->entity_set_inventorylimits( 0, itemdata::smal, itemdata::none, false, true, itemdata::machine_parts, itemdata::generic);
        }
        else if(set_object_index == "obj_machine_genorator") {
            //pop out generic item...
            returnPointer = new entity_machine( set_object_index,set_x,set_y,set_dir,set_spd,set_indestructable,set_insideid);
            returnPointer->entity_set_inventorylimits( 0, itemdata::huge, itemdata::none, false, false, itemdata::machines, itemdata::generic);
            returnPointer->myIntVars["machine_has_power"] = false;
        }



        else if(set_object_index == "obj_puppet_blueprint_outdoorlamp") {
            returnPointer = new entity_generic( set_object_index,set_x,set_y,set_dir,set_spd,set_indestructable,set_insideid);
            //setup a default inventory for the cup! it can store one object!
            returnPointer->entity_set_inventorylimits( 0, itemdata::smal, itemdata::none, false, true, itemdata::machine_parts, itemdata::generic);
        }
        else if(set_object_index == "obj_machine_outdoorlamp") {
            //pop out generic item...
            returnPointer = new entity_machine( set_object_index,set_x,set_y,set_dir,set_spd,set_indestructable,set_insideid);
            returnPointer->entity_set_inventorylimits( 0, itemdata::huge, itemdata::none, false, false, itemdata::machines, itemdata::generic);
            returnPointer->myIntVars["machine_has_power"] = false;
        }



        else if(set_object_index == "obj_machine_indoorlamp") {
            //pop out generic item...
            returnPointer = new entity_machine( set_object_index,set_x,set_y,set_dir,set_spd,set_indestructable,set_insideid);
            returnPointer->entity_set_inventorylimits( 1,itemdata::medium, itemdata::smal, false, false, itemdata::machine_parts, itemdata::generic);
            returnPointer->myIntVars["machine_has_power"] = false;
        }


        else if(set_object_index == "obj_puppet_blueprint_printer") {
            returnPointer = new entity_generic( set_object_index,set_x,set_y,set_dir,set_spd,set_indestructable,set_insideid);
            //setup a default inventory for the cup! it can store one object!
            returnPointer->entity_set_inventorylimits( 0, itemdata::smal, itemdata::none, false, true, itemdata::machine_parts, itemdata::generic);
        }
        else if(set_object_index == "obj_machine_blueprinter") {
            //pop out generic item...
            returnPointer = new entity_machine( set_object_index,set_x,set_y,set_dir,set_spd,set_indestructable,set_insideid);
            returnPointer->entity_set_inventorylimits( 6, itemdata::huge, itemdata::smal, false, false, itemdata::machines, itemdata::generic);
            returnPointer->myIntVars["machine_has_power"] = false;
        }



        else if(set_object_index == "obj_puppet_blueprint_chargingstation") {
            returnPointer = new entity_generic( set_object_index,set_x,set_y,set_dir,set_spd,set_indestructable,set_insideid);
            //setup a default inventory for the cup! it can store one object!
            returnPointer->entity_set_inventorylimits( 0, itemdata::smal, itemdata::none, false, true, itemdata::machine_parts, itemdata::generic);
        }
        else if(set_object_index == "obj_machine_chargingstation") {
            //pop out generic item...
            returnPointer = new entity_machine( set_object_index,set_x,set_y,set_dir,set_spd,set_indestructable,set_insideid);
            returnPointer->entity_set_inventorylimits( 6, itemdata::huge, itemdata::smal, false, false, itemdata::machines, itemdata::generic);
            returnPointer->myIntVars["machine_has_power"] = false;
        }



        else if(set_object_index == "obj_puppet_blueprint_fabricator") {
            returnPointer = new entity_generic( set_object_index,set_x,set_y,set_dir,set_spd,set_indestructable,set_insideid);
            //setup a default inventory for the cup! it can store one object!
            returnPointer->entity_set_inventorylimits( 0, itemdata::smal, itemdata::none, false, true, itemdata::machine_parts, itemdata::generic);
        }
        else if(set_object_index == "obj_machine_fabricator") {
            //pop out generic item...
            returnPointer = new entity_machine( set_object_index,set_x,set_y,set_dir,set_spd,set_indestructable,set_insideid);
            returnPointer->entity_set_inventorylimits( 10, itemdata::huge, itemdata::smal, false, false, itemdata::machines, itemdata::generic);
            returnPointer->myIntVars["machine_has_power"] = false;
        }



        else if(set_object_index == "obj_puppet_blueprint_elecassem") {
            returnPointer = new entity_generic( set_object_index,set_x,set_y,set_dir,set_spd,set_indestructable,set_insideid);
            //setup a default inventory for the cup! it can store one object!
            returnPointer->entity_set_inventorylimits( 0, itemdata::smal, itemdata::none, false, true, itemdata::machine_parts, itemdata::generic);
        }
        else if(set_object_index == "obj_machine_elecassem") {
            //pop out generic item...
            returnPointer = new entity_machine( set_object_index,set_x,set_y,set_dir,set_spd,set_indestructable,set_insideid);
            returnPointer->entity_set_inventorylimits( 10, itemdata::huge, itemdata::smal, false, false, itemdata::machines, itemdata::generic);
            returnPointer->myIntVars["machine_has_power"] = false;
        }


        //resources and parts
        else if(set_object_index == "obj_puppet_plastic_rod") {
            returnPointer = new entity_generic( set_object_index,set_x,set_y,set_dir,set_spd,set_indestructable,set_insideid);
            //setup a default inventory for the cup! it can store one object!
            returnPointer->entity_set_inventorylimits( 0, itemdata::smal, itemdata::none, false, false, itemdata::generic, itemdata::generic);
        }

        else if(set_object_index == "obj_puppet_metal_ingot") {
            returnPointer = new entity_generic( set_object_index,set_x,set_y,set_dir,set_spd,set_indestructable,set_insideid);
            //setup a default inventory for the cup! it can store one object!
            returnPointer->entity_set_inventorylimits( 0, itemdata::smal, itemdata::none, false, false, itemdata::generic, itemdata::generic);
        }

        else if(set_object_index == "obj_puppet_metal_plates") {
            returnPointer = new entity_generic( set_object_index,set_x,set_y,set_dir,set_spd,set_indestructable,set_insideid);
            //setup a default inventory for the cup! it can store one object!
            returnPointer->entity_set_inventorylimits( 0, itemdata::smal, itemdata::none, false, false, itemdata::machine_parts, itemdata::generic);
        }

        else if(set_object_index == "obj_puppet_metal_cable") {
            returnPointer = new entity_generic( set_object_index,set_x,set_y,set_dir,set_spd,set_indestructable,set_insideid);
            //setup a default inventory for the cup! it can store one object!
            returnPointer->entity_set_inventorylimits( 0, itemdata::smal, itemdata::none, false, false, itemdata::machine_parts, itemdata::generic);
        }

        else if(set_object_index == "obj_puppet_metal_frames") {
            returnPointer = new entity_generic( set_object_index,set_x,set_y,set_dir,set_spd,set_indestructable,set_insideid);
            //setup a default inventory for the cup! it can store one object!
            returnPointer->entity_set_inventorylimits( 0, itemdata::smal, itemdata::none, false, false, itemdata::machine_parts, itemdata::generic);
        }


        else if(set_object_index == "obj_puppet_parts_fabarray") {
            returnPointer = new entity_generic( set_object_index,set_x,set_y,set_dir,set_spd,set_indestructable,set_insideid);
            //setup a default inventory for the cup! it can store one object!
            returnPointer->entity_set_inventorylimits( 0, itemdata::smal, itemdata::none, false, false, itemdata::machine_parts, itemdata::generic);
        }

        else if(set_object_index == "obj_puppet_parts_wires") {
            returnPointer = new entity_generic( set_object_index,set_x,set_y,set_dir,set_spd,set_indestructable,set_insideid);
            //setup a default inventory for the cup! it can store one object!
            returnPointer->entity_set_inventorylimits( 0, itemdata::smal, itemdata::none, false, false, itemdata::machine_parts, itemdata::generic);
        }


        ///toolboxes
        else if(set_object_index == "obj_puppet_assistbox"
        || "obj_puppet_cargobox"
        || "obj_puppet_commsbox"
        || "obj_puppet_weatherbox"
        || "obj_puppet_labbox"
        || "obj_puppet_medicbox"
        || "obj_puppet_toolbox"
        || "obj_puppet_minebox"
        || "obj_puppet_secbox"
        || "obj_puppet_atmobox"
        || "obj_puppet_hydrobox"
        || "obj_puppet_janibox") {
            //these kits are setup from another function that spawns the kits and fills them!
            returnPointer = new entity_generic( set_object_index,set_x,set_y,set_dir,set_spd,set_indestructable,set_insideid);
            returnPointer->entity_set_inventorylimits( 10, itemdata::medium, itemdata::smal, false, false, itemdata::generic, itemdata::generic);
        }




        ///backup
        else
        {
            //Backup, object_index missing
            returnPointer = new entity_generic( "obj_puppet_generic",set_x,set_y,set_dir,set_spd,set_indestructable,set_insideid);
        }

        return returnPointer;
    };
};








#endif
