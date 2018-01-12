#include "entity_library.h"


entityLibrary::entity_generic::entity_generic(std::string set_object_index,double set_x,double set_y, float set_dir, double set_spd, bool set_indestructable, int set_insideid)
: entity( set_object_index, set_x, set_y, set_dir, set_spd, set_indestructable, set_insideid) {
}
void entityLibrary::entity_generic::entity_personal_step() {
    ///personal actions go here
}



entityLibrary::entity_arrivalshuttle::entity_arrivalshuttle(std::string set_object_index,double set_x,double set_y, float set_dir, double set_spd, bool set_indestructable, int set_insideid)
: entity( set_object_index, set_x, set_y, set_dir, set_spd, set_indestructable, set_insideid) {
    myIntVars["dest_x"] = set_x;
    myIntVars["dest_y"] = set_y;
    myIntVars["dropoff_padEntityId"] = -1;
    myIntVars["dropoff_x"] = -10;
    myIntVars["dropoff_y"] = -10;
    myIntVars["dropoff_flag"] = 0;
    myIntVars["dropoff_waitcounter"] = 300;
}
void entityLibrary::entity_arrivalshuttle::entity_personal_step() {
    ///personal actions go here
}




entityLibrary::entity_player::entity_player(std::string set_object_index,double set_x,double set_y, float set_dir, double set_spd, bool set_indestructable, int set_insideid)
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

    myIntVars["stasis"] = true;

}
void entityLibrary::entity_player::entity_personal_step() {
    ///personal actions go here
}



entityLibrary::entity_borb::entity_borb(std::string set_object_index,double set_x,double set_y, float set_dir, double set_spd, bool set_indestructable, int set_insideid)
: entity( set_object_index, set_x, set_y, set_dir, set_spd, set_indestructable, set_insideid) {
}
void entityLibrary::entity_borb::entity_personal_step() {
    ///personal actions go here
}




entityLibrary::entity_laserpoint::entity_laserpoint(std::string set_object_index,double set_x,double set_y, float set_dir, double set_spd, bool set_indestructable, int set_insideid)
: entity( set_object_index, set_x, set_y, set_dir, set_spd, set_indestructable, set_insideid) {
    myIntVars["firetime"] = 5;
}
void entityLibrary::entity_laserpoint::entity_personal_step() {
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


entityLibrary::entity_coffee::entity_coffee(std::string set_object_index,double set_x,double set_y, float set_dir, double set_spd, bool set_indestructable, int set_insideid)
: entity( set_object_index, set_x, set_y, set_dir, set_spd, set_indestructable, set_insideid) {
    myIntVars["coffee_hot"] = 15000;
}
void entityLibrary::entity_coffee::entity_personal_step() {
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



entityLibrary::entity_powercell::entity_powercell(std::string set_object_index,double set_x,double set_y, float set_dir, double set_spd, bool set_indestructable, int set_insideid)
: entity( set_object_index, set_x, set_y, set_dir, set_spd, set_indestructable, set_insideid) {
    myIntVars["charge"] = 0;
}
void entityLibrary::entity_powercell::entity_personal_step() {
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



entityLibrary::entity_securitycard::entity_securitycard(std::string set_object_index,double set_x,double set_y, float set_dir, double set_spd, bool set_indestructable, int set_insideid)
: entity( set_object_index, set_x, set_y, set_dir, set_spd, set_indestructable, set_insideid) {
}
void entityLibrary::entity_securitycard::entity_personal_step() {
    ///personal actions go here
}




entityLibrary::entity_machine::entity_machine(std::string set_object_index,double set_x,double set_y, float set_dir, double set_spd, bool set_indestructable, int set_insideid)
: entity( set_object_index, set_x, set_y, set_dir, set_spd, set_indestructable, set_insideid) {
    myIntVars["machine_has_power"] = 0;
}
void entityLibrary::entity_machine::entity_personal_step() {
    ///personal actions go here
}










///library creation functions
/*
    add new entities to BOTH of these! it needs to
    know what kind of class to instantiate as well
    as a bunch of object creation stuff!
*/

void entityLibrary::entity_template_creation() {
    ///living entities
    serverObj.CreateObjectAndAssetIndex("obj_puppet_arrivalshuttle");
    serverObj.CreateObjectAndAssetIndex("obj_puppet_player");
    serverObj.CreateObjectAndAssetIndex("obj_puppet_borb");
    serverObj.CreateObjectAndAssetIndex("obj_puppet_laserpoint");

    ///food
    serverObj.CreateObjectAndAssetIndex("obj_puppet_cup");
    serverObj.CreateObjectAndAssetIndex("obj_puppet_coffeepack");
    serverObj.CreateObjectAndAssetIndex("obj_puppet_coffee_hot");
    serverObj.CreateObjectAndAssetIndex("obj_puppet_coffee_microwaved");
    serverObj.CreateObjectAndAssetIndex("obj_puppet_coffee_cold");

    ///clothing equipment
    serverObj.CreateObjectAndAssetIndex("obj_puppet_toolbelt");
    serverObj.CreateObjectAndAssetIndex("obj_puppet_secbelt");
    serverObj.CreateObjectAndAssetIndex("obj_puppet_medbelt");
    serverObj.CreateObjectAndAssetIndex("obj_puppet_hazardvest");
    serverObj.CreateObjectAndAssetIndex("obj_puppet_hardhat");
    serverObj.CreateObjectAndAssetIndex("obj_puppet_sechelmet");
    serverObj.CreateObjectAndAssetIndex("obj_puppet_firehelmet");
    serverObj.CreateObjectAndAssetIndex("obj_puppet_firesuit");
    serverObj.CreateObjectAndAssetIndex("obj_puppet_secgasmask");
    serverObj.CreateObjectAndAssetIndex("obj_puppet_gasmask");
    serverObj.CreateObjectAndAssetIndex("obj_puppet_secarmor");
    serverObj.CreateObjectAndAssetIndex("obj_puppet_riotarmor");
    serverObj.CreateObjectAndAssetIndex("obj_puppet_bombarmor");
    serverObj.CreateObjectAndAssetIndex("obj_puppet_weldgogs");
    serverObj.CreateObjectAndAssetIndex("obj_puppet_goggles");
    serverObj.CreateObjectAndAssetIndex("obj_puppet_nitrogloves");
    serverObj.CreateObjectAndAssetIndex("obj_puppet_sterilmask");
    serverObj.CreateObjectAndAssetIndex("obj_puppet_cleansuit_helmet");
    serverObj.CreateObjectAndAssetIndex("obj_puppet_cleansuit_body");
    serverObj.CreateObjectAndAssetIndex("obj_puppet_sunglasses");
    serverObj.CreateObjectAndAssetIndex("obj_puppet_glasses_perscrip");
    serverObj.CreateObjectAndAssetIndex("obj_puppet_crowbar");
    serverObj.CreateObjectAndAssetIndex("obj_puppet_wirecutter");
    serverObj.CreateObjectAndAssetIndex("obj_puppet_screwdriver");
    serverObj.CreateObjectAndAssetIndex("obj_puppet_weldtool");
    serverObj.CreateObjectAndAssetIndex("obj_puppet_wrench");
    serverObj.CreateObjectAndAssetIndex("obj_puppet_laserrifle");
    serverObj.CreateObjectAndAssetIndex("obj_puppet_powercell");
    serverObj.CreateObjectAndAssetIndex("obj_puppet_securitycard");
    serverObj.CreateObjectAndAssetIndex("obj_puppet_securitytool");
    serverObj.CreateObjectAndAssetIndex("obj_puppet_flashlight");
    serverObj.CreateObjectAndAssetIndex("obj_puppet_flare");
    serverObj.CreateObjectAndAssetIndex("obj_puppet_radioA");
    serverObj.CreateObjectAndAssetIndex("obj_puppet_umbrella");
    serverObj.CreateObjectAndAssetIndex("obj_puppet_paper");
    serverObj.CreateObjectAndAssetIndex("obj_puppet_pen");
    serverObj.CreateObjectAndAssetIndex("obj_puppet_pencil");
    serverObj.CreateObjectAndAssetIndex("obj_puppet_bucket");
    serverObj.CreateObjectAndAssetIndex("obj_puppet_mop");
    serverObj.CreateObjectAndAssetIndex("obj_puppet_fireex");
    serverObj.CreateObjectAndAssetIndex("obj_puppet_fireaxe");
    serverObj.CreateObjectAndAssetIndex("obj_puppet_stunbaton");
    serverObj.CreateObjectAndAssetIndex("obj_puppet_pepperspray");
    serverObj.CreateObjectAndAssetIndex("obj_puppet_taser");
    serverObj.CreateObjectAndAssetIndex("obj_puppet_flashbang");
    serverObj.CreateObjectAndAssetIndex("obj_puppet_emp");
    serverObj.CreateObjectAndAssetIndex("obj_puppet_handcuffs");
    serverObj.CreateObjectAndAssetIndex("obj_puppet_secflashlight");
    serverObj.CreateObjectAndAssetIndex("obj_puppet_fluidspec");
    serverObj.CreateObjectAndAssetIndex("obj_puppet_stethoscope");
    serverObj.CreateObjectAndAssetIndex("obj_puppet_bandaid_box");
    serverObj.CreateObjectAndAssetIndex("obj_puppet_bandaid");
    serverObj.CreateObjectAndAssetIndex("obj_puppet_burnointment");
    serverObj.CreateObjectAndAssetIndex("obj_puppet_disinfectant");
    serverObj.CreateObjectAndAssetIndex("obj_puppet_antitoxin");
    serverObj.CreateObjectAndAssetIndex("obj_puppet_epinephrine");
    serverObj.CreateObjectAndAssetIndex("obj_puppet_syringe");
    serverObj.CreateObjectAndAssetIndex("obj_puppet_hypoinject");
    serverObj.CreateObjectAndAssetIndex("obj_puppet_beaker");
    serverObj.CreateObjectAndAssetIndex("obj_puppet_pillbottle");
    serverObj.CreateObjectAndAssetIndex("obj_puppet_scalpel");
    serverObj.CreateObjectAndAssetIndex("obj_puppet_hemostat");
    serverObj.CreateObjectAndAssetIndex("obj_puppet_sutures");
    serverObj.CreateObjectAndAssetIndex("obj_puppet_surgerysaw");
    serverObj.CreateObjectAndAssetIndex("obj_puppet_surgerydrill");
    serverObj.CreateObjectAndAssetIndex("obj_puppet_cauterytool");
    serverObj.CreateObjectAndAssetIndex("obj_puppet_cryobeaker");
    serverObj.CreateObjectAndAssetIndex("obj_puppet_gps");

    serverObj.CreateObjectAndAssetIndex("obj_puppet_labeler");
    serverObj.CreateObjectAndAssetIndex("obj_puppet_ducttape");
    serverObj.CreateObjectAndAssetIndex("obj_puppet_cautiontape");
    serverObj.CreateObjectAndAssetIndex("obj_puppet_clipboard");


    //furniture
    serverObj.CreateObjectAndAssetIndex("obj_furniture_stool");
    serverObj.CreateObjectAndAssetIndex("obj_furniture_table");
    serverObj.CreateObjectAndAssetIndex("obj_furniture_locker");
    serverObj.CreateObjectAndAssetIndex("obj_furniture_trashbin");

    serverObj.CreateObjectAndAssetIndex("obj_puppet_janitorcart");

    serverObj.CreateObjectAndAssetIndex("obj_puppet_microwave");
    serverObj.CreateObjectAndAssetIndex("obj_puppet_coffeemaker");

    //constructables and blueprints
    serverObj.CreateObjectAndAssetIndex("obj_puppet_conduit");

    serverObj.CreateObjectAndAssetIndex("obj_machine_STC");

    serverObj.CreateObjectAndAssetIndex("obj_puppet_blueprint");

    serverObj.CreateObjectAndAssetIndex("obj_puppet_blueprint_genorator");
    serverObj.CreateObjectAndAssetIndex("obj_machine_genorator");

    serverObj.CreateObjectAndAssetIndex("obj_puppet_blueprint_outdoorlamp");
    serverObj.CreateObjectAndAssetIndex("obj_machine_outdoorlamp");

    serverObj.CreateObjectAndAssetIndex("obj_machine_indoorlamp");

    serverObj.CreateObjectAndAssetIndex("obj_puppet_blueprint_printer");
    serverObj.CreateObjectAndAssetIndex("obj_machine_blueprinter");

    serverObj.CreateObjectAndAssetIndex("obj_puppet_blueprint_chargingstation");
    serverObj.CreateObjectAndAssetIndex("obj_machine_chargingstation");


    serverObj.CreateObjectAndAssetIndex("obj_puppet_blueprint_fabricator");
    serverObj.CreateObjectAndAssetIndex("obj_machine_fabricator");

    serverObj.CreateObjectAndAssetIndex("obj_puppet_blueprint_elecassem");
    serverObj.CreateObjectAndAssetIndex("obj_machine_elecassem");

    //resources and parts
    serverObj.CreateObjectAndAssetIndex("obj_puppet_plastic_rod");
    serverObj.CreateObjectAndAssetIndex("obj_puppet_metal_ingot");
    serverObj.CreateObjectAndAssetIndex("obj_puppet_metal_plates");
    serverObj.CreateObjectAndAssetIndex("obj_puppet_metal_cable");
    serverObj.CreateObjectAndAssetIndex("obj_puppet_metal_frames");
    serverObj.CreateObjectAndAssetIndex("obj_puppet_parts_fabarray");
    serverObj.CreateObjectAndAssetIndex("obj_puppet_parts_wires");

    ///toolboxes
    serverObj.CreateObjectAndAssetIndex("obj_puppet_assistbox");
    serverObj.CreateObjectAndAssetIndex("obj_puppet_cargobox");
    serverObj.CreateObjectAndAssetIndex("obj_puppet_commsbox");
    serverObj.CreateObjectAndAssetIndex("obj_puppet_weatherbox");
    serverObj.CreateObjectAndAssetIndex("obj_puppet_labbox");
    serverObj.CreateObjectAndAssetIndex("obj_puppet_medicbox");
    serverObj.CreateObjectAndAssetIndex("obj_puppet_toolbox");
    serverObj.CreateObjectAndAssetIndex("obj_puppet_minebox");
    serverObj.CreateObjectAndAssetIndex("obj_puppet_secbox");
    serverObj.CreateObjectAndAssetIndex("obj_puppet_atmobox");
    serverObj.CreateObjectAndAssetIndex("obj_puppet_hydrobox");
    serverObj.CreateObjectAndAssetIndex("obj_puppet_janibox");
}


entity* entityLibrary::entity_template_library(std::string set_object_index,double set_x,double set_y, float set_dir, double set_spd, bool set_indestructable, int set_insideid) {
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
