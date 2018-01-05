///scr_entity_template_library( object_index,x,y,dir,speed,indestructable,inside of id, optional replacement_map);
//makes an entity based on the object input! RETURNS A DS_MAP OF AN ENTITY
var new_entity = -1;

//hack to refresh entities that require updating to new data
var restoring_entity = -1; //no map
if argument_count == 8 restoring_entity = argument[7];
var keep_inventories = ds_exists(restoring_entity,ds_type_map); //keep the inventories if we are just updating old entities


//entity library
switch argument[0] {
    //living entities
    case obj_puppet_arrivalshuttle:
        new_entity = scr_template_entity(argument[0],argument[1],argument[2],argument[3],argument[4],argument[5],argument[6],restoring_entity);
        scr_template_entity_set_inventorylimits( new_entity, 1, enum_itemsize.huge, enum_itemsize.large, false, false, enum_itemclass.ship, enum_itemclass.generic, keep_inventories);
        new_entity[? "SS_collision_ignores_walls"] = true;
        new_entity[? "dest_x"] = argument[1];
        new_entity[? "dest_y"] = argument[2];
        new_entity[? "dropoff_padid"] = noone;
        new_entity[? "dropoff_x"] = -10;
        new_entity[? "dropoff_y"] = -10;
        new_entity[? "dropoff_flag"] = false;
        new_entity[? "dropoff_waitcounter"] = 300;
        new_entity[? "SS_decelerator"] = 1; //no slowdown!
    break;
    
    case obj_puppet_player:
        //make a new player
        new_entity = scr_template_entity(argument[0],argument[1],argument[2],argument[3],argument[4],argument[5],argument[6],restoring_entity);
        //setup a default inventory for the player!
        scr_template_entity_set_inventorylimits( new_entity, 12, enum_itemsize.large, enum_itemsize.medium, false, false, enum_itemclass.body, enum_itemclass.generic, keep_inventories);
        if keep_inventories == false scr_template_entity_set_playerstats( new_entity);
        if keep_inventories == false ds_map_add_list( new_entity, "security_clearance", ds_list_create());
    break;
    
    case obj_puppet_borb:
        new_entity = scr_template_entity(argument[0],argument[1],argument[2],argument[3],argument[4],argument[5],argument[6],restoring_entity);
        scr_template_entity_set_inventorylimits( new_entity, 0, enum_itemsize.tiny, enum_itemsize.none, true, false, enum_itemclass.body, enum_itemclass.generic, keep_inventories);
        new_entity[? "SS_bouncyness"] = 1.25;
        new_entity[? "SS_decelerator"] = 0.98;
    break;
    
    case obj_puppet_laserpoint:
        //pop out generic item...
        new_entity = scr_template_entity(argument[0],argument[1],argument[2],argument[3],argument[4],argument[5],argument[6],restoring_entity);
        scr_template_entity_set_inventorylimits( new_entity, 0, enum_itemsize.medium, enum_itemsize.none, false, false, enum_itemclass.generic, enum_itemclass.generic, keep_inventories);
        new_entity[? "firetime"] = 5;
    break;
    
    
    
    
    //food
    case obj_puppet_cup:
        new_entity = scr_template_entity(argument[0],argument[1],argument[2],argument[3],argument[4],argument[5],argument[6],restoring_entity);
        //setup a default inventory for the cup! it can store one object!
        scr_template_entity_set_inventorylimits( new_entity, 1, enum_itemsize.small, enum_itemsize.tiny, false, true, enum_itemclass.generic, enum_itemclass.generic, keep_inventories);
    break;
    
    case obj_puppet_coffeepack:
        new_entity = scr_template_entity(argument[0],argument[1],argument[2],argument[3],argument[4],argument[5],argument[6],restoring_entity);
        //setup a default inventory for the cup! it can store one object!
        scr_template_entity_set_inventorylimits( new_entity, 0, enum_itemsize.tiny, enum_itemsize.none, false, false, enum_itemclass.generic, enum_itemclass.generic, keep_inventories);
    break;
    
    case obj_puppet_coffee_hot:
        new_entity = scr_template_entity(argument[0],argument[1],argument[2],argument[3],argument[4],argument[5],argument[6],restoring_entity);
        //setup a default inventory for the cup! it can store one object!
        scr_template_entity_set_inventorylimits( new_entity, 0, enum_itemsize.tiny, enum_itemsize.none, true, false, enum_itemclass.food, enum_itemclass.generic, keep_inventories);
        new_entity[? "coffee_hot"] = 15000;
    break;
    
    case obj_puppet_coffee_microwaved:
        new_entity = scr_template_entity(argument[0],argument[1],argument[2],argument[3],argument[4],argument[5],argument[6],restoring_entity);
        //setup a default inventory for the cup! it can store one object!
        scr_template_entity_set_inventorylimits( new_entity, 0, enum_itemsize.tiny, enum_itemsize.none, true, false, enum_itemclass.food, enum_itemclass.generic, keep_inventories);
        new_entity[? "coffee_hot"] = 11000;
    break;
    
    case obj_puppet_coffee_cold:
        new_entity = scr_template_entity(argument[0],argument[1],argument[2],argument[3],argument[4],argument[5],argument[6],restoring_entity);
        //setup a default inventory for the cup! it can store one object!
        scr_template_entity_set_inventorylimits( new_entity, 0, enum_itemsize.tiny, enum_itemsize.none, true, false, enum_itemclass.food, enum_itemclass.generic, keep_inventories);
        new_entity[? "coffee_hot"] = 0;
    break;
    
    //clothing/equipment
    case obj_puppet_toolbelt:
    case obj_puppet_medbelt:
    case obj_puppet_secbelt:
        new_entity = scr_template_entity(argument[0],argument[1],argument[2],argument[3],argument[4],argument[5],argument[6],restoring_entity);
        scr_template_entity_set_inventorylimits( new_entity, 5, enum_itemsize.medium, enum_itemsize.small, false, false, enum_itemclass.generic, enum_itemclass.tools, keep_inventories);
    break;
    
    case obj_puppet_hazardvest:
        new_entity = scr_template_entity(argument[0],argument[1],argument[2],argument[3],argument[4],argument[5],argument[6],restoring_entity);
        scr_template_entity_set_inventorylimits( new_entity, 0, enum_itemsize.medium, enum_itemsize.none, false, false, enum_itemclass.clothing, enum_itemclass.generic, keep_inventories);
    break;
    
    case obj_puppet_hardhat:
        new_entity = scr_template_entity(argument[0],argument[1],argument[2],argument[3],argument[4],argument[5],argument[6],restoring_entity);
        scr_template_entity_set_inventorylimits( new_entity, 1, enum_itemsize.medium, enum_itemsize.small, false, true, enum_itemclass.clothing, enum_itemclass.generic, keep_inventories);
    break;
    
    case obj_puppet_sechelmet:
        new_entity = scr_template_entity(argument[0],argument[1],argument[2],argument[3],argument[4],argument[5],argument[6],restoring_entity);
        scr_template_entity_set_inventorylimits( new_entity, 1, enum_itemsize.medium, enum_itemsize.small, false, true, enum_itemclass.clothing, enum_itemclass.generic, keep_inventories);
    break;
    
    case obj_puppet_firehelmet:
        new_entity = scr_template_entity(argument[0],argument[1],argument[2],argument[3],argument[4],argument[5],argument[6],restoring_entity);
        scr_template_entity_set_inventorylimits( new_entity, 0, enum_itemsize.medium, enum_itemsize.none, false, false, enum_itemclass.clothing, enum_itemclass.generic, keep_inventories);
    break;
    
    case obj_puppet_firesuit:
        new_entity = scr_template_entity(argument[0],argument[1],argument[2],argument[3],argument[4],argument[5],argument[6],restoring_entity);
        scr_template_entity_set_inventorylimits( new_entity, 0, enum_itemsize.medium, enum_itemsize.none, false, false, enum_itemclass.clothing, enum_itemclass.generic, keep_inventories);
    break;
    
    case obj_puppet_secgasmask:
        new_entity = scr_template_entity(argument[0],argument[1],argument[2],argument[3],argument[4],argument[5],argument[6],restoring_entity);
        scr_template_entity_set_inventorylimits( new_entity, 0, enum_itemsize.medium, enum_itemsize.none, false, false, enum_itemclass.clothing, enum_itemclass.generic, keep_inventories);
    break;
    
    case obj_puppet_gasmask:
        new_entity = scr_template_entity(argument[0],argument[1],argument[2],argument[3],argument[4],argument[5],argument[6],restoring_entity);
        scr_template_entity_set_inventorylimits( new_entity, 0, enum_itemsize.medium, enum_itemsize.none, false, false, enum_itemclass.clothing, enum_itemclass.generic, keep_inventories);
    break;
    
    case obj_puppet_secarmor:
        new_entity = scr_template_entity(argument[0],argument[1],argument[2],argument[3],argument[4],argument[5],argument[6],restoring_entity);
        scr_template_entity_set_inventorylimits( new_entity, 0, enum_itemsize.medium, enum_itemsize.none, false, false, enum_itemclass.clothing, enum_itemclass.generic, keep_inventories);
    break;
    
    case obj_puppet_riotarmor:
        new_entity = scr_template_entity(argument[0],argument[1],argument[2],argument[3],argument[4],argument[5],argument[6],restoring_entity);
        scr_template_entity_set_inventorylimits( new_entity, 0, enum_itemsize.medium, enum_itemsize.none, false, false, enum_itemclass.clothing, enum_itemclass.generic, keep_inventories);
    break;
    
    case obj_puppet_bombarmor:
        new_entity = scr_template_entity(argument[0],argument[1],argument[2],argument[3],argument[4],argument[5],argument[6],restoring_entity);
        scr_template_entity_set_inventorylimits( new_entity, 0, enum_itemsize.medium, enum_itemsize.none, false, false, enum_itemclass.clothing, enum_itemclass.generic, keep_inventories);
    break;
    
    case obj_puppet_weldgogs:
        new_entity = scr_template_entity(argument[0],argument[1],argument[2],argument[3],argument[4],argument[5],argument[6],restoring_entity);
        scr_template_entity_set_inventorylimits( new_entity, 0, enum_itemsize.medium, enum_itemsize.none, false, false, enum_itemclass.clothing, enum_itemclass.generic, keep_inventories);
    break;
    
    case obj_puppet_goggles:
        new_entity = scr_template_entity(argument[0],argument[1],argument[2],argument[3],argument[4],argument[5],argument[6],restoring_entity);
        scr_template_entity_set_inventorylimits( new_entity, 0, enum_itemsize.medium, enum_itemsize.none, false, false, enum_itemclass.clothing, enum_itemclass.generic, keep_inventories);
    break;
    
    case obj_puppet_nitrogloves:
        new_entity = scr_template_entity(argument[0],argument[1],argument[2],argument[3],argument[4],argument[5],argument[6],restoring_entity);
        scr_template_entity_set_inventorylimits( new_entity, 0, enum_itemsize.small, enum_itemsize.none, false, false, enum_itemclass.clothing, enum_itemclass.generic, keep_inventories);
    break;
    
    case obj_puppet_sterilmask:
        new_entity = scr_template_entity(argument[0],argument[1],argument[2],argument[3],argument[4],argument[5],argument[6],restoring_entity);
        scr_template_entity_set_inventorylimits( new_entity, 0, enum_itemsize.small, enum_itemsize.none, false, false, enum_itemclass.clothing, enum_itemclass.generic, keep_inventories);
    break;
    
    case obj_puppet_cleansuit_helmet:
        new_entity = scr_template_entity(argument[0],argument[1],argument[2],argument[3],argument[4],argument[5],argument[6],restoring_entity);
        scr_template_entity_set_inventorylimits( new_entity, 0, enum_itemsize.medium, enum_itemsize.none, false, false, enum_itemclass.clothing, enum_itemclass.generic, keep_inventories);
    break;
    
    case obj_puppet_cleansuit_body:
        new_entity = scr_template_entity(argument[0],argument[1],argument[2],argument[3],argument[4],argument[5],argument[6],restoring_entity);
        scr_template_entity_set_inventorylimits( new_entity, 0, enum_itemsize.medium, enum_itemsize.none, false, false, enum_itemclass.clothing, enum_itemclass.generic, keep_inventories);
    break;
    
    case obj_puppet_sunglasses:
        new_entity = scr_template_entity(argument[0],argument[1],argument[2],argument[3],argument[4],argument[5],argument[6],restoring_entity);
        scr_template_entity_set_inventorylimits( new_entity, 0, enum_itemsize.small, enum_itemsize.none, false, false, enum_itemclass.clothing, enum_itemclass.generic, keep_inventories);
    break;
    
    case obj_puppet_glasses_perscrip:
        new_entity = scr_template_entity(argument[0],argument[1],argument[2],argument[3],argument[4],argument[5],argument[6],restoring_entity);
        scr_template_entity_set_inventorylimits( new_entity, 0, enum_itemsize.small, enum_itemsize.none, false, false, enum_itemclass.clothing, enum_itemclass.generic, keep_inventories);
    break;
    
    //tools
    case obj_puppet_crowbar:
        new_entity = scr_template_entity(argument[0],argument[1],argument[2],argument[3],argument[4],argument[5],argument[6],restoring_entity);
        scr_template_entity_set_inventorylimits( new_entity, 0, enum_itemsize.small, enum_itemsize.none, false, false, enum_itemclass.tools, enum_itemclass.generic, keep_inventories);
    break;
    
    case obj_puppet_wirecutter:
        new_entity = scr_template_entity(argument[0],argument[1],argument[2],argument[3],argument[4],argument[5],argument[6],restoring_entity);
        scr_template_entity_set_inventorylimits( new_entity, 0, enum_itemsize.small, enum_itemsize.none, false, false, enum_itemclass.tools, enum_itemclass.generic, keep_inventories);
    break;
    
    case obj_puppet_screwdriver:
        new_entity = scr_template_entity(argument[0],argument[1],argument[2],argument[3],argument[4],argument[5],argument[6],restoring_entity);
        scr_template_entity_set_inventorylimits( new_entity, 0, enum_itemsize.small, enum_itemsize.none, false, false, enum_itemclass.tools, enum_itemclass.generic, keep_inventories);
    break;
    
    case obj_puppet_weldtool:
        new_entity = scr_template_entity(argument[0],argument[1],argument[2],argument[3],argument[4],argument[5],argument[6],restoring_entity);
        scr_template_entity_set_inventorylimits( new_entity, 0, enum_itemsize.small, enum_itemsize.none, false, false, enum_itemclass.tools, enum_itemclass.generic, keep_inventories);
    break;
    
    case obj_puppet_wrench:
        new_entity = scr_template_entity(argument[0],argument[1],argument[2],argument[3],argument[4],argument[5],argument[6],restoring_entity);
        scr_template_entity_set_inventorylimits( new_entity, 0, enum_itemsize.small, enum_itemsize.none, false, false, enum_itemclass.tools, enum_itemclass.generic, keep_inventories);
    break;
    
    case obj_puppet_laserrifle:
        new_entity = scr_template_entity(argument[0],argument[1],argument[2],argument[3],argument[4],argument[5],argument[6],restoring_entity);
        scr_template_entity_set_inventorylimits( new_entity, 1, enum_itemsize.medium, enum_itemsize.small, false, false, enum_itemclass.rifle, enum_itemclass.generic, keep_inventories);
    break;
    
    case obj_puppet_powercell:
        new_entity = scr_template_entity(argument[0],argument[1],argument[2],argument[3],argument[4],argument[5],argument[6],restoring_entity);
        scr_template_entity_set_inventorylimits( new_entity, 0, enum_itemsize.small, enum_itemsize.none, false, false, enum_itemclass.generic, enum_itemclass.generic, keep_inventories);
        if keep_inventories == false new_entity[? "Charge"] = 0;
    break;
    
    case obj_puppet_securitycard:
        new_entity = scr_template_entity(argument[0],argument[1],argument[2],argument[3],argument[4],argument[5],argument[6],restoring_entity);
        scr_template_entity_set_inventorylimits( new_entity, 0, enum_itemsize.tiny, enum_itemsize.none, false, false, enum_itemclass.generic, enum_itemclass.generic, keep_inventories);
        
        if keep_inventories == false {
            var security_list = ds_list_create();
            security_list[| enum_security_basic.staff] = true; //basic level security
            ds_map_add_list(new_entity, "security_levels", security_list);
        }
    break;
    
    case obj_puppet_securitytool:
        new_entity = scr_template_entity(argument[0],argument[1],argument[2],argument[3],argument[4],argument[5],argument[6],restoring_entity);
        scr_template_entity_set_inventorylimits( new_entity, 1, enum_itemsize.small, enum_itemsize.tiny, false, false, enum_itemclass.generic, enum_itemclass.generic, keep_inventories);
    break;
    
    case obj_puppet_flashlight:
        new_entity = scr_template_entity(argument[0],argument[1],argument[2],argument[3],argument[4],argument[5],argument[6],restoring_entity);
        scr_template_entity_set_inventorylimits( new_entity, 1, enum_itemsize.small, enum_itemsize.small, false, false, enum_itemclass.generic, enum_itemclass.generic, keep_inventories);
    break;
    
    case obj_puppet_flare:
        new_entity = scr_template_entity(argument[0],argument[1],argument[2],argument[3],argument[4],argument[5],argument[6],restoring_entity);
        scr_template_entity_set_inventorylimits( new_entity, 0, enum_itemsize.small, enum_itemsize.none, false, false, enum_itemclass.generic, enum_itemclass.generic, keep_inventories);
    break;
    
    case obj_puppet_radioA:
        new_entity = scr_template_entity(argument[0],argument[1],argument[2],argument[3],argument[4],argument[5],argument[6],restoring_entity);
        scr_template_entity_set_inventorylimits( new_entity, 1, enum_itemsize.small, enum_itemsize.small, false, false, enum_itemclass.generic, enum_itemclass.generic, keep_inventories);
    break;
    
    case obj_puppet_umbrella:
        new_entity = scr_template_entity(argument[0],argument[1],argument[2],argument[3],argument[4],argument[5],argument[6],restoring_entity);
        scr_template_entity_set_inventorylimits( new_entity, 0, enum_itemsize.medium, enum_itemsize.none, false, false, enum_itemclass.generic, enum_itemclass.generic, keep_inventories);
    break;
    
    case obj_puppet_paper:
        new_entity = scr_template_entity(argument[0],argument[1],argument[2],argument[3],argument[4],argument[5],argument[6],restoring_entity);
        scr_template_entity_set_inventorylimits( new_entity, 0, enum_itemsize.tiny, enum_itemsize.none, false, false, enum_itemclass.sheets, enum_itemclass.generic, keep_inventories);
    break;
    
    case obj_puppet_pen:
        new_entity = scr_template_entity(argument[0],argument[1],argument[2],argument[3],argument[4],argument[5],argument[6],restoring_entity);
        scr_template_entity_set_inventorylimits( new_entity, 0, enum_itemsize.tiny, enum_itemsize.none, false, false, enum_itemclass.generic, enum_itemclass.generic, keep_inventories);
    break;
    
    case obj_puppet_pencil:
        new_entity = scr_template_entity(argument[0],argument[1],argument[2],argument[3],argument[4],argument[5],argument[6],restoring_entity);
        scr_template_entity_set_inventorylimits( new_entity, 0, enum_itemsize.tiny, enum_itemsize.none, false, false, enum_itemclass.generic, enum_itemclass.generic, keep_inventories);
    break;
    
    case obj_puppet_bucket:
        new_entity = scr_template_entity(argument[0],argument[1],argument[2],argument[3],argument[4],argument[5],argument[6],restoring_entity);
        scr_template_entity_set_inventorylimits( new_entity, 4, enum_itemsize.medium, enum_itemsize.small, false, false, enum_itemclass.generic, enum_itemclass.generic, keep_inventories);
    break;
    
    case obj_puppet_mop:
        new_entity = scr_template_entity(argument[0],argument[1],argument[2],argument[3],argument[4],argument[5],argument[6],restoring_entity);
        scr_template_entity_set_inventorylimits( new_entity, 1, enum_itemsize.medium, enum_itemsize.none, false, true, enum_itemclass.generic, enum_itemclass.generic, keep_inventories);
    break;
    
    case obj_puppet_fireex:
        new_entity = scr_template_entity(argument[0],argument[1],argument[2],argument[3],argument[4],argument[5],argument[6],restoring_entity);
        scr_template_entity_set_inventorylimits( new_entity, 0, enum_itemsize.medium, enum_itemsize.none, false, false, enum_itemclass.tools, enum_itemclass.generic, keep_inventories);
    break;
    
    case obj_puppet_fireaxe:
        new_entity = scr_template_entity(argument[0],argument[1],argument[2],argument[3],argument[4],argument[5],argument[6],restoring_entity);
        scr_template_entity_set_inventorylimits( new_entity, 0, enum_itemsize.medium, enum_itemsize.none, false, false, enum_itemclass.tools, enum_itemclass.generic, keep_inventories);
    break;
    
    case obj_puppet_stunbaton:
        new_entity = scr_template_entity(argument[0],argument[1],argument[2],argument[3],argument[4],argument[5],argument[6],restoring_entity);
        scr_template_entity_set_inventorylimits( new_entity, 0, enum_itemsize.small, enum_itemsize.none, false, false, enum_itemclass.tools, enum_itemclass.generic, keep_inventories);
    break;
    
    case obj_puppet_pepperspray:
        new_entity = scr_template_entity(argument[0],argument[1],argument[2],argument[3],argument[4],argument[5],argument[6],restoring_entity);
        scr_template_entity_set_inventorylimits( new_entity, 0, enum_itemsize.tiny, enum_itemsize.none, false, false, enum_itemclass.generic, enum_itemclass.generic, keep_inventories);
    break;
    
    case obj_puppet_taser:
        new_entity = scr_template_entity(argument[0],argument[1],argument[2],argument[3],argument[4],argument[5],argument[6],restoring_entity);
        scr_template_entity_set_inventorylimits( new_entity, 0, enum_itemsize.small, enum_itemsize.none, false, false, enum_itemclass.pistol, enum_itemclass.generic, keep_inventories);
    break;
    
    case obj_puppet_flashbang:
        new_entity = scr_template_entity(argument[0],argument[1],argument[2],argument[3],argument[4],argument[5],argument[6],restoring_entity);
        scr_template_entity_set_inventorylimits( new_entity, 0, enum_itemsize.tiny, enum_itemsize.none, false, false, enum_itemclass.generic, enum_itemclass.generic, keep_inventories);
    break;
    
    case obj_puppet_emp:
        new_entity = scr_template_entity(argument[0],argument[1],argument[2],argument[3],argument[4],argument[5],argument[6],restoring_entity);
        scr_template_entity_set_inventorylimits( new_entity, 0, enum_itemsize.tiny, enum_itemsize.none, false, false, enum_itemclass.generic, enum_itemclass.generic, keep_inventories);
    break;
    
    case obj_puppet_handcuffs:
        new_entity = scr_template_entity(argument[0],argument[1],argument[2],argument[3],argument[4],argument[5],argument[6],restoring_entity);
        scr_template_entity_set_inventorylimits( new_entity, 0, enum_itemsize.small, enum_itemsize.none, false, false, enum_itemclass.generic, enum_itemclass.generic, keep_inventories);
    break;
    
    case obj_puppet_secflashlight:
        new_entity = scr_template_entity(argument[0],argument[1],argument[2],argument[3],argument[4],argument[5],argument[6],restoring_entity);
        scr_template_entity_set_inventorylimits( new_entity, 1, enum_itemsize.small, enum_itemsize.small, false, false, enum_itemclass.generic, enum_itemclass.generic, keep_inventories);
    break;
    
    case obj_puppet_fluidspec:
        new_entity = scr_template_entity(argument[0],argument[1],argument[2],argument[3],argument[4],argument[5],argument[6],restoring_entity);
        scr_template_entity_set_inventorylimits( new_entity, 0, enum_itemsize.small, enum_itemsize.none, false, false, enum_itemclass.generic, enum_itemclass.generic, keep_inventories);
    break;
    
    case obj_puppet_stethoscope:
        new_entity = scr_template_entity(argument[0],argument[1],argument[2],argument[3],argument[4],argument[5],argument[6],restoring_entity);
        scr_template_entity_set_inventorylimits( new_entity, 0, enum_itemsize.small, enum_itemsize.none, false, false, enum_itemclass.generic, enum_itemclass.generic, keep_inventories);
    break;
    
    case obj_puppet_bandaid_box:
        new_entity = scr_template_entity(argument[0],argument[1],argument[2],argument[3],argument[4],argument[5],argument[6],restoring_entity);
        scr_template_entity_set_inventorylimits( new_entity, 10, enum_itemsize.small, enum_itemsize.tiny, false, false, enum_itemclass.generic, enum_itemclass.generic, keep_inventories);
    break;
    
    case obj_puppet_bandaid:
        new_entity = scr_template_entity(argument[0],argument[1],argument[2],argument[3],argument[4],argument[5],argument[6],restoring_entity);
        scr_template_entity_set_inventorylimits( new_entity, 0, enum_itemsize.tiny, enum_itemsize.none, false, false, enum_itemclass.generic, enum_itemclass.generic, keep_inventories);
    break;
    
    case obj_puppet_burnointment:
        new_entity = scr_template_entity(argument[0],argument[1],argument[2],argument[3],argument[4],argument[5],argument[6],restoring_entity);
        scr_template_entity_set_inventorylimits( new_entity, 0, enum_itemsize.tiny, enum_itemsize.none, false, false, enum_itemclass.generic, enum_itemclass.generic, keep_inventories);
    break;
    
    case obj_puppet_disinfectant:
        new_entity = scr_template_entity(argument[0],argument[1],argument[2],argument[3],argument[4],argument[5],argument[6],restoring_entity);
        scr_template_entity_set_inventorylimits( new_entity, 0, enum_itemsize.tiny, enum_itemsize.none, false, false, enum_itemclass.generic, enum_itemclass.generic, keep_inventories);
    break;
    
    case obj_puppet_antitoxin:
        new_entity = scr_template_entity(argument[0],argument[1],argument[2],argument[3],argument[4],argument[5],argument[6],restoring_entity);
        scr_template_entity_set_inventorylimits( new_entity, 0, enum_itemsize.tiny, enum_itemsize.none, false, false, enum_itemclass.generic, enum_itemclass.generic, keep_inventories);
    break;
    
    case obj_puppet_epinephrine:
        new_entity = scr_template_entity(argument[0],argument[1],argument[2],argument[3],argument[4],argument[5],argument[6],restoring_entity);
        scr_template_entity_set_inventorylimits( new_entity, 0, enum_itemsize.tiny, enum_itemsize.none, false, false, enum_itemclass.generic, enum_itemclass.generic, keep_inventories);
    break;
    
    case obj_puppet_syringe:
        new_entity = scr_template_entity(argument[0],argument[1],argument[2],argument[3],argument[4],argument[5],argument[6],restoring_entity);
        scr_template_entity_set_inventorylimits( new_entity, 1, enum_itemsize.tiny, enum_itemsize.none, false, true, enum_itemclass.generic, enum_itemclass.generic, keep_inventories);
    break;
    
    case obj_puppet_hypoinject:
        new_entity = scr_template_entity(argument[0],argument[1],argument[2],argument[3],argument[4],argument[5],argument[6],restoring_entity);
        scr_template_entity_set_inventorylimits( new_entity, 0, enum_itemsize.tiny, enum_itemsize.none, false, false, enum_itemclass.generic, enum_itemclass.generic, keep_inventories);
    break;
    
    case obj_puppet_beaker:
        new_entity = scr_template_entity(argument[0],argument[1],argument[2],argument[3],argument[4],argument[5],argument[6],restoring_entity);
        scr_template_entity_set_inventorylimits( new_entity, 2, enum_itemsize.small, enum_itemsize.none, false, true, enum_itemclass.generic, enum_itemclass.generic, keep_inventories);
    break;
    
    case obj_puppet_pillbottle:
        new_entity = scr_template_entity(argument[0],argument[1],argument[2],argument[3],argument[4],argument[5],argument[6],restoring_entity);
        scr_template_entity_set_inventorylimits( new_entity, 10, enum_itemsize.small, enum_itemsize.tiny, false, false, enum_itemclass.generic, enum_itemclass.generic, keep_inventories);
    break;
    
    case obj_puppet_scalpel:
        new_entity = scr_template_entity(argument[0],argument[1],argument[2],argument[3],argument[4],argument[5],argument[6],restoring_entity);
        scr_template_entity_set_inventorylimits( new_entity, 0, enum_itemsize.tiny, enum_itemsize.none, false, false, enum_itemclass.generic, enum_itemclass.generic, keep_inventories);
    break;
    
    case obj_puppet_hemostat:
        new_entity = scr_template_entity(argument[0],argument[1],argument[2],argument[3],argument[4],argument[5],argument[6],restoring_entity);
        scr_template_entity_set_inventorylimits( new_entity, 0, enum_itemsize.tiny, enum_itemsize.none, false, false, enum_itemclass.generic, enum_itemclass.generic, keep_inventories);
    break;
    
    case obj_puppet_sutures:
        new_entity = scr_template_entity(argument[0],argument[1],argument[2],argument[3],argument[4],argument[5],argument[6],restoring_entity);
        scr_template_entity_set_inventorylimits( new_entity, 0, enum_itemsize.tiny, enum_itemsize.none, false, false, enum_itemclass.generic, enum_itemclass.generic, keep_inventories);
    break;
    
    case obj_puppet_surgerysaw:
        new_entity = scr_template_entity(argument[0],argument[1],argument[2],argument[3],argument[4],argument[5],argument[6],restoring_entity);
        scr_template_entity_set_inventorylimits( new_entity, 1, enum_itemsize.medium, enum_itemsize.small, false, false, enum_itemclass.tools, enum_itemclass.generic, keep_inventories);
    break;
   
    case obj_puppet_surgerydrill:
        new_entity = scr_template_entity(argument[0],argument[1],argument[2],argument[3],argument[4],argument[5],argument[6],restoring_entity);
        scr_template_entity_set_inventorylimits( new_entity, 1, enum_itemsize.small, enum_itemsize.small, false, false, enum_itemclass.tools, enum_itemclass.generic, keep_inventories);
    break; 
    
    case obj_puppet_cauterytool:
        new_entity = scr_template_entity(argument[0],argument[1],argument[2],argument[3],argument[4],argument[5],argument[6],restoring_entity);
        scr_template_entity_set_inventorylimits( new_entity, 1, enum_itemsize.small, enum_itemsize.small, false, false, enum_itemclass.generic, enum_itemclass.generic, keep_inventories);
    break; 
    
    case obj_puppet_cryobeaker:
        new_entity = scr_template_entity(argument[0],argument[1],argument[2],argument[3],argument[4],argument[5],argument[6],restoring_entity);
        scr_template_entity_set_inventorylimits( new_entity, 2, enum_itemsize.small, enum_itemsize.none, false, true, enum_itemclass.generic, enum_itemclass.generic, keep_inventories);
    break;
    
    case obj_puppet_gps:
        new_entity = scr_template_entity(argument[0],argument[1],argument[2],argument[3],argument[4],argument[5],argument[6],restoring_entity);
        scr_template_entity_set_inventorylimits( new_entity, 1, enum_itemsize.small, enum_itemsize.small, false, false, enum_itemclass.tools, enum_itemclass.generic, keep_inventories);
    break;
    
    case obj_puppet_labeler:
        new_entity = scr_template_entity(argument[0],argument[1],argument[2],argument[3],argument[4],argument[5],argument[6],restoring_entity);
        scr_template_entity_set_inventorylimits( new_entity, 2, enum_itemsize.small, enum_itemsize.small, false, false, enum_itemclass.tools, enum_itemclass.generic, keep_inventories);
    break;
    
    case obj_puppet_ducttape:
        new_entity = scr_template_entity(argument[0],argument[1],argument[2],argument[3],argument[4],argument[5],argument[6],restoring_entity);
        scr_template_entity_set_inventorylimits( new_entity, 0, enum_itemsize.small, enum_itemsize.none, false, false, enum_itemclass.tools, enum_itemclass.generic, keep_inventories);
    break;
    
    case obj_puppet_cautiontape:
        new_entity = scr_template_entity(argument[0],argument[1],argument[2],argument[3],argument[4],argument[5],argument[6],restoring_entity);
        scr_template_entity_set_inventorylimits( new_entity, 0, enum_itemsize.small, enum_itemsize.none, false, false, enum_itemclass.tools, enum_itemclass.generic, keep_inventories);
    break;
    
    case obj_puppet_clipboard:
        new_entity = scr_template_entity(argument[0],argument[1],argument[2],argument[3],argument[4],argument[5],argument[6],restoring_entity);
        scr_template_entity_set_inventorylimits( new_entity, 5, enum_itemsize.small, enum_itemsize.tiny, false, false, enum_itemclass.generic, enum_itemclass.sheets, keep_inventories);
    break;
    
    
    
    //furniture
    case obj_furniture_stool:
        //pop out generic item...
        new_entity = scr_template_entity(argument[0],argument[1],argument[2],argument[3],argument[4],argument[5],argument[6],restoring_entity);
        scr_template_entity_set_inventorylimits( new_entity, 0, enum_itemsize.medium, enum_itemsize.none, false, false, enum_itemclass.generic, enum_itemclass.generic, keep_inventories);
    break;
    
    case obj_furniture_table:
        //pop out generic item...
        new_entity = scr_template_entity(argument[0],argument[1],argument[2],argument[3],argument[4],argument[5],argument[6],restoring_entity);
        scr_template_entity_set_inventorylimits( new_entity, 1, enum_itemsize.large, enum_itemsize.medium, false, false, enum_itemclass.generic, enum_itemclass.generic, keep_inventories);
        new_entity[? "contains_display"] = true;
        new_entity[? "contains_display_x"] = 0;
        new_entity[? "contains_display_y"] = -16;
        new_entity[? "contains_display_d"] = -5;
    break;
    
    case obj_furniture_locker:
        new_entity = scr_template_entity(argument[0],argument[1],argument[2],argument[3],argument[4],argument[5],argument[6],restoring_entity);
        //setup a default inventory for the cup! it can store one object!
        scr_template_entity_set_inventorylimits( new_entity, 20, enum_itemsize.large, enum_itemsize.large, false, false, enum_itemclass.generic, enum_itemclass.generic, keep_inventories);
    break;
    
    case obj_furniture_trashbin:
        new_entity = scr_template_entity(argument[0],argument[1],argument[2],argument[3],argument[4],argument[5],argument[6],restoring_entity);
        //setup a default inventory for the cup! it can store one object!
        scr_template_entity_set_inventorylimits( new_entity, 20, enum_itemsize.large, enum_itemsize.large, false, false, enum_itemclass.generic, enum_itemclass.generic, keep_inventories);
    break;
    
    case obj_puppet_janitorcart:
        new_entity = scr_template_entity(argument[0],argument[1],argument[2],argument[3],argument[4],argument[5],argument[6],restoring_entity);
        //setup a default inventory for the cup! it can store one object!
        scr_template_entity_set_inventorylimits( new_entity, 8, enum_itemsize.service_cart, enum_itemsize.large, false, false, enum_itemclass.generic, enum_itemclass.generic, keep_inventories);
    break;
    
    case obj_puppet_microwave:
        //pop out generic item...
        new_entity = scr_template_entity(argument[0],argument[1],argument[2],argument[3],argument[4],argument[5],argument[6],restoring_entity);
        scr_template_entity_set_inventorylimits( new_entity, 2, enum_itemsize.medium, enum_itemsize.small, false, false, enum_itemclass.generic, enum_itemclass.generic, keep_inventories);
    break;
    
    case obj_puppet_coffeemaker:
        //pop out generic item...
        new_entity = scr_template_entity(argument[0],argument[1],argument[2],argument[3],argument[4],argument[5],argument[6],restoring_entity);
        scr_template_entity_set_inventorylimits( new_entity, 3, enum_itemsize.medium, enum_itemsize.small, false, false, enum_itemclass.generic, enum_itemclass.generic, keep_inventories);
    break;
    
    
    
    //constructables and blueprints
    case obj_puppet_conduit:
        //pop out generic item...
        new_entity = scr_template_entity(argument[0],argument[1],argument[2],argument[3],argument[4],argument[5],argument[6],restoring_entity);
        scr_template_entity_set_inventorylimits( new_entity, 0, enum_itemsize.medium, enum_itemsize.none, false, false, enum_itemclass.generic, enum_itemclass.generic, keep_inventories);
    break;
    
    
    
    case obj_machine_STC:
        //pop out generic item...
        new_entity = scr_template_entity(argument[0],argument[1],argument[2],argument[3],argument[4],argument[5],argument[6],restoring_entity);
        scr_template_entity_set_inventorylimits( new_entity, 10, enum_itemsize.medium, enum_itemsize.medium, false, false, enum_itemclass.machines, enum_itemclass.machine_parts, keep_inventories);
        new_entity[? "object_building"] = -1;
    break;
    
    
    
    case obj_puppet_blueprint:
        new_entity = scr_template_entity(argument[0],argument[1],argument[2],argument[3],argument[4],argument[5],argument[6],restoring_entity);
        //setup a default inventory for the cup! it can store one object!
        scr_template_entity_set_inventorylimits( new_entity, 0, enum_itemsize.small, enum_itemsize.none, false, true, enum_itemclass.machine_parts, enum_itemclass.generic, keep_inventories);
    break;
    
    
    
    
    case obj_puppet_blueprint_genorator:
        new_entity = scr_template_entity(argument[0],argument[1],argument[2],argument[3],argument[4],argument[5],argument[6],restoring_entity);
        //setup a default inventory for the cup! it can store one object!
        scr_template_entity_set_inventorylimits( new_entity, 0, enum_itemsize.small, enum_itemsize.none, false, true, enum_itemclass.machine_parts, enum_itemclass.generic, keep_inventories);
    break;
    case obj_machine_genorator:
        //pop out generic item...
        new_entity = scr_template_entity(argument[0],argument[1],argument[2],argument[3],argument[4],argument[5],argument[6],restoring_entity);
        scr_template_entity_set_inventorylimits( new_entity, 0, enum_itemsize.huge, enum_itemsize.none, false, false, enum_itemclass.machines, enum_itemclass.generic, keep_inventories);
        new_entity[? "machine_has_power"] = true;
    break;
    
    
    
    case obj_puppet_blueprint_outdoorlamp:
        new_entity = scr_template_entity(argument[0],argument[1],argument[2],argument[3],argument[4],argument[5],argument[6],restoring_entity);
        //setup a default inventory for the cup! it can store one object!
        scr_template_entity_set_inventorylimits( new_entity, 0, enum_itemsize.small, enum_itemsize.none, false, true, enum_itemclass.machine_parts, enum_itemclass.generic, keep_inventories);
    break;
    case obj_machine_outdoorlamp:
        //pop out generic item...
        new_entity = scr_template_entity(argument[0],argument[1],argument[2],argument[3],argument[4],argument[5],argument[6],restoring_entity);
        scr_template_entity_set_inventorylimits( new_entity, 0, enum_itemsize.huge, enum_itemsize.none, false, false, enum_itemclass.machines, enum_itemclass.generic, keep_inventories);
        new_entity[? "machine_has_power"] = false;
    break;
    
    
    
    case obj_machine_indoorlamp:
        //pop out generic item...
        new_entity = scr_template_entity(argument[0],argument[1],argument[2],argument[3],argument[4],argument[5],argument[6],restoring_entity);
        scr_template_entity_set_inventorylimits( new_entity, 1, enum_itemsize.medium, enum_itemsize.small, false, false, enum_itemclass.machine_parts, enum_itemclass.generic, keep_inventories);
        new_entity[? "light_charge"] = 0;
        new_entity[? "machine_has_power"] = false; //was previously powered by a battery
    break;
    
    
    case obj_puppet_blueprint_printer:
        new_entity = scr_template_entity(argument[0],argument[1],argument[2],argument[3],argument[4],argument[5],argument[6],restoring_entity);
        //setup a default inventory for the cup! it can store one object!
        scr_template_entity_set_inventorylimits( new_entity, 0, enum_itemsize.small, enum_itemsize.none, false, true, enum_itemclass.machine_parts, enum_itemclass.generic, keep_inventories);
    break;
    case obj_machine_blueprinter:
        //pop out generic item...
        new_entity = scr_template_entity(argument[0],argument[1],argument[2],argument[3],argument[4],argument[5],argument[6],restoring_entity);
        scr_template_entity_set_inventorylimits( new_entity, 6, enum_itemsize.huge, enum_itemsize.small, false, false, enum_itemclass.machines, enum_itemclass.generic, keep_inventories);
        new_entity[? "machine_has_power"] = false;
    break;
    
    
    
    case obj_puppet_blueprint_chargingstation:
        new_entity = scr_template_entity(argument[0],argument[1],argument[2],argument[3],argument[4],argument[5],argument[6],restoring_entity);
        //setup a default inventory for the cup! it can store one object!
        scr_template_entity_set_inventorylimits( new_entity, 0, enum_itemsize.small, enum_itemsize.none, false, true, enum_itemclass.machine_parts, enum_itemclass.generic, keep_inventories);
    break;
    case obj_machine_chargingstation:
        //pop out generic item...
        new_entity = scr_template_entity(argument[0],argument[1],argument[2],argument[3],argument[4],argument[5],argument[6],restoring_entity);
        scr_template_entity_set_inventorylimits( new_entity, 6, enum_itemsize.huge, enum_itemsize.small, false, false, enum_itemclass.machines, enum_itemclass.generic, keep_inventories);
        new_entity[? "machine_has_power"] = false;
    break;
    
    
    
    case obj_puppet_blueprint_fabricator:
        new_entity = scr_template_entity(argument[0],argument[1],argument[2],argument[3],argument[4],argument[5],argument[6],restoring_entity);
        //setup a default inventory for the cup! it can store one object!
        scr_template_entity_set_inventorylimits( new_entity, 0, enum_itemsize.small, enum_itemsize.none, false, true, enum_itemclass.machine_parts, enum_itemclass.generic, keep_inventories);
    break;
    case obj_machine_fabricator:
        //pop out generic item...
        new_entity = scr_template_entity(argument[0],argument[1],argument[2],argument[3],argument[4],argument[5],argument[6],restoring_entity);
        scr_template_entity_set_inventorylimits( new_entity, 10, enum_itemsize.huge, enum_itemsize.small, false, false, enum_itemclass.machines, enum_itemclass.generic, keep_inventories);
        new_entity[? "machine_has_power"] = false;
    break;
    
    
    
    case obj_puppet_blueprint_elecassem:
        new_entity = scr_template_entity(argument[0],argument[1],argument[2],argument[3],argument[4],argument[5],argument[6],restoring_entity);
        //setup a default inventory for the cup! it can store one object!
        scr_template_entity_set_inventorylimits( new_entity, 0, enum_itemsize.small, enum_itemsize.none, false, true, enum_itemclass.machine_parts, enum_itemclass.generic, keep_inventories);
    break;
    case obj_machine_elecassem:
        //pop out generic item...
        new_entity = scr_template_entity(argument[0],argument[1],argument[2],argument[3],argument[4],argument[5],argument[6],restoring_entity);
        scr_template_entity_set_inventorylimits( new_entity, 10, enum_itemsize.huge, enum_itemsize.small, false, false, enum_itemclass.machines, enum_itemclass.generic, keep_inventories);
        new_entity[? "machine_has_power"] = false;
    break;
    
    
    //resources and parts
    case obj_puppet_plastic_rod:
        new_entity = scr_template_entity(argument[0],argument[1],argument[2],argument[3],argument[4],argument[5],argument[6],restoring_entity);
        //setup a default inventory for the cup! it can store one object!
        scr_template_entity_set_inventorylimits( new_entity, 0, enum_itemsize.small, enum_itemsize.none, false, false, enum_itemclass.generic, enum_itemclass.generic, keep_inventories);
    break;
    
    case obj_puppet_metal_ingot:
        new_entity = scr_template_entity(argument[0],argument[1],argument[2],argument[3],argument[4],argument[5],argument[6],restoring_entity);
        //setup a default inventory for the cup! it can store one object!
        scr_template_entity_set_inventorylimits( new_entity, 0, enum_itemsize.small, enum_itemsize.none, false, false, enum_itemclass.generic, enum_itemclass.generic, keep_inventories);
    break;
    
    case obj_puppet_metal_plates:
        new_entity = scr_template_entity(argument[0],argument[1],argument[2],argument[3],argument[4],argument[5],argument[6],restoring_entity);
        //setup a default inventory for the cup! it can store one object!
        scr_template_entity_set_inventorylimits( new_entity, 0, enum_itemsize.small, enum_itemsize.none, false, false, enum_itemclass.machine_parts, enum_itemclass.generic, keep_inventories);
    break;
    
    case obj_puppet_metal_cable:
        new_entity = scr_template_entity(argument[0],argument[1],argument[2],argument[3],argument[4],argument[5],argument[6],restoring_entity);
        //setup a default inventory for the cup! it can store one object!
        scr_template_entity_set_inventorylimits( new_entity, 0, enum_itemsize.small, enum_itemsize.none, false, false, enum_itemclass.machine_parts, enum_itemclass.generic, keep_inventories);
    break;
    
    case obj_puppet_metal_frames:
        new_entity = scr_template_entity(argument[0],argument[1],argument[2],argument[3],argument[4],argument[5],argument[6],restoring_entity);
        //setup a default inventory for the cup! it can store one object!
        scr_template_entity_set_inventorylimits( new_entity, 0, enum_itemsize.small, enum_itemsize.none, false, false, enum_itemclass.machine_parts, enum_itemclass.generic, keep_inventories);
    break;
    
    
    case obj_puppet_parts_fabarray:
        new_entity = scr_template_entity(argument[0],argument[1],argument[2],argument[3],argument[4],argument[5],argument[6],restoring_entity);
        //setup a default inventory for the cup! it can store one object!
        scr_template_entity_set_inventorylimits( new_entity, 0, enum_itemsize.small, enum_itemsize.none, false, false, enum_itemclass.machine_parts, enum_itemclass.generic, keep_inventories);
    break;
    
    case obj_puppet_parts_wires:
        new_entity = scr_template_entity(argument[0],argument[1],argument[2],argument[3],argument[4],argument[5],argument[6],restoring_entity);
        //setup a default inventory for the cup! it can store one object!
        scr_template_entity_set_inventorylimits( new_entity, 0, enum_itemsize.small, enum_itemsize.none, false, false, enum_itemclass.machine_parts, enum_itemclass.generic, keep_inventories);
    break;
    
    
    
    default:
        //pop out generic item...
        new_entity = scr_template_entity(obj_puppet_genericitem,argument[1],argument[2],argument[3],argument[4],argument[5],argument[6],restoring_entity);
        scr_template_entity_set_inventorylimits( new_entity, 0, enum_itemsize.small, enum_itemsize.none, false, false, enum_itemclass.generic, enum_itemclass.generic, keep_inventories);
    break;
    
    
    
    
    //toolkits
    case obj_puppet_assistbox:
    case obj_puppet_cargobox:
    case obj_puppet_commsbox:
    case obj_puppet_weatherbox:
    case obj_puppet_labbox:
    case obj_puppet_medicbox:
    case obj_puppet_toolbox:
    case obj_puppet_minebox:
    case obj_puppet_secbox:
    case obj_puppet_atmobox:
    case obj_puppet_hydrobox:
    case obj_puppet_janibox:
        //these kits are setup from another function that spawns the kits and fills them!
        new_entity = scr_template_entity(argument[0],argument[1],argument[2],argument[3],argument[4],argument[5],argument[6],restoring_entity);
        scr_template_entity_set_inventorylimits( new_entity, 10, enum_itemsize.medium, enum_itemsize.small, false, false, enum_itemclass.generic, enum_itemclass.generic, keep_inventories);
    break;
    
    
    
}



return new_entity;
