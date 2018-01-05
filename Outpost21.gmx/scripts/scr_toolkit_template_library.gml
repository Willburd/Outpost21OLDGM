///scr_toolkit_template_library( object_index,x,y,dir,speed,indestructable,inside of id);
//makes an entity based on the object input! RETURNS AN ACTUAL ENTITY
var new_entity = -1;

switch argument0 {
    case obj_puppet_assistbox:
        //these kits are setup from another function that spawns the kits and fills them!
        var get_map = scr_entity_template_library(argument0,argument1,argument2,argument3,argument4,argument5,argument6);
        new_entity = scr_server_entity_add(get_map);
        
        //add items!
        
        var sub_entity = scr_toolkit_template_library( obj_puppet_flashlight, item_storage_pos, item_storage_pos, 0, 0, false, new_entity);
        ds_map_add(get_map[? "contains_map"], string(sub_entity), sub_entity);
        
        var sub_map = scr_entity_template_library( obj_puppet_gasmask, item_storage_pos, item_storage_pos, 0, 0, false, new_entity);
        var sub_entity = scr_server_entity_add(sub_map);
        ds_map_add(get_map[? "contains_map"], string(sub_entity), sub_entity);
        
        var sub_map = scr_entity_template_library( obj_puppet_powercell, item_storage_pos, item_storage_pos, 0, 0, false, new_entity);
        var sub_entity = scr_server_entity_add(sub_map);
        sub_map[? "Charge"] = 100;
        ds_map_add(get_map[? "contains_map"], string(sub_entity), sub_entity);
        
        
        var sub_entity = scr_toolkit_template_library( obj_puppet_clipboard, item_storage_pos, item_storage_pos, 0, 0, false, new_entity);
        ds_map_add(get_map[? "contains_map"], string(sub_entity), sub_entity);
        
        var sub_map = scr_entity_template_library( obj_puppet_pen, item_storage_pos, item_storage_pos, 0, 0, false, new_entity);
        var sub_entity = scr_server_entity_add(sub_map);
        ds_map_add(get_map[? "contains_map"], string(sub_entity), sub_entity);
    break;

    
    
    case obj_puppet_cargobox:
        //these kits are setup from another function that spawns the kits and fills them!
        var get_map = scr_entity_template_library(argument0,argument1,argument2,argument3,argument4,argument5,argument6);
        new_entity = scr_server_entity_add(get_map);
        
        //add items!
        
        var sub_entity = scr_toolkit_template_library( obj_puppet_flashlight, item_storage_pos, item_storage_pos, 0, 0, false, new_entity);
        ds_map_add(get_map[? "contains_map"], string(sub_entity), sub_entity);
        
        var sub_map = scr_entity_template_library( obj_puppet_gasmask, item_storage_pos, item_storage_pos, 0, 0, false, new_entity);
        var sub_entity = scr_server_entity_add(sub_map);
        ds_map_add(get_map[? "contains_map"], string(sub_entity), sub_entity);
    break;
    
    
    
    case obj_puppet_commsbox:
        //these kits are setup from another function that spawns the kits and fills them!
        var get_map = scr_entity_template_library(argument0,argument1,argument2,argument3,argument4,argument5,argument6);
        new_entity = scr_server_entity_add(get_map);
        
        //add items!
        
        var sub_entity = scr_toolkit_template_library( obj_puppet_flashlight, item_storage_pos, item_storage_pos, 0, 0, false, new_entity);
        ds_map_add(get_map[? "contains_map"], string(sub_entity), sub_entity);
        
        var sub_map = scr_entity_template_library( obj_puppet_gasmask, item_storage_pos, item_storage_pos, 0, 0, false, new_entity);
        var sub_entity = scr_server_entity_add(sub_map);
        ds_map_add(get_map[? "contains_map"], string(sub_entity), sub_entity);
    break;
    
    
    
    case obj_puppet_weatherbox:
        //these kits are setup from another function that spawns the kits and fills them!
        var get_map = scr_entity_template_library(argument0,argument1,argument2,argument3,argument4,argument5,argument6);
        new_entity = scr_server_entity_add(get_map);
        
        //add items!
        
        var sub_entity = scr_toolkit_template_library( obj_puppet_flashlight, item_storage_pos, item_storage_pos, 0, 0, false, new_entity);
        ds_map_add(get_map[? "contains_map"], string(sub_entity), sub_entity);
        
        var sub_map = scr_entity_template_library( obj_puppet_gasmask, item_storage_pos, item_storage_pos, 0, 0, false, new_entity);
        var sub_entity = scr_server_entity_add(sub_map);
        ds_map_add(get_map[? "contains_map"], string(sub_entity), sub_entity);
    break;
    
    
    
    case obj_puppet_labbox:
        //these kits are setup from another function that spawns the kits and fills them!
        var get_map = scr_entity_template_library(argument0,argument1,argument2,argument3,argument4,argument5,argument6);
        new_entity = scr_server_entity_add(get_map);
        
        //add items!
        
        var sub_entity = scr_toolkit_template_library( obj_puppet_flashlight, item_storage_pos, item_storage_pos, 0, 0, false, new_entity);
        ds_map_add(get_map[? "contains_map"], string(sub_entity), sub_entity);
        
        var sub_map = scr_entity_template_library( obj_puppet_gasmask, item_storage_pos, item_storage_pos, 0, 0, false, new_entity);
        var sub_entity = scr_server_entity_add(sub_map);
        ds_map_add(get_map[? "contains_map"], string(sub_entity), sub_entity);
    break;
    
    
    
    case obj_puppet_medicbox:
        //these kits are setup from another function that spawns the kits and fills them!
        var get_map = scr_entity_template_library(argument0,argument1,argument2,argument3,argument4,argument5,argument6);
        new_entity = scr_server_entity_add(get_map);
        
        //add items!
        
        var sub_entity = scr_toolkit_template_library( obj_puppet_flashlight, item_storage_pos, item_storage_pos, 0, 0, false, new_entity);
        ds_map_add(get_map[? "contains_map"], string(sub_entity), sub_entity);
        
        var sub_map = scr_entity_template_library( obj_puppet_gasmask, item_storage_pos, item_storage_pos, 0, 0, false, new_entity);
        var sub_entity = scr_server_entity_add(sub_map);
        ds_map_add(get_map[? "contains_map"], string(sub_entity), sub_entity);
        
        
        var sub_entity = scr_toolkit_template_library( obj_puppet_bandaid_box, item_storage_pos, item_storage_pos, 0, 0, false, new_entity);
        ds_map_add(get_map[? "contains_map"], string(sub_entity), sub_entity);
    break;
    
    
    
    case obj_puppet_toolbox:
        //these kits are setup from another function that spawns the kits and fills them!
        var get_map = scr_entity_template_library(argument0,argument1,argument2,argument3,argument4,argument5,argument6);
        new_entity = scr_server_entity_add(get_map);
        
        //add items!
        
        var sub_entity = scr_toolkit_template_library( obj_puppet_flashlight, item_storage_pos, item_storage_pos, 0, 0, false, new_entity);
        ds_map_add(get_map[? "contains_map"], string(sub_entity), sub_entity);
        
        var sub_map = scr_entity_template_library( obj_puppet_gasmask, item_storage_pos, item_storage_pos, 0, 0, false, new_entity);
        var sub_entity = scr_server_entity_add(sub_map);
        ds_map_add(get_map[? "contains_map"], string(sub_entity), sub_entity);
        
        var sub_map = scr_entity_template_library( obj_puppet_wrench, item_storage_pos, item_storage_pos, 0, 0, false, new_entity);
        var sub_entity = scr_server_entity_add(sub_map);
        ds_map_add(get_map[? "contains_map"], string(sub_entity), sub_entity);
        
        var sub_map = scr_entity_template_library( obj_puppet_crowbar, item_storage_pos, item_storage_pos, 0, 0, false, new_entity);
        var sub_entity = scr_server_entity_add(sub_map);
        ds_map_add(get_map[? "contains_map"], string(sub_entity), sub_entity);
        
        var sub_map = scr_entity_template_library( obj_puppet_screwdriver, item_storage_pos, item_storage_pos, 0, 0, false, new_entity);
        var sub_entity = scr_server_entity_add(sub_map);
        ds_map_add(get_map[? "contains_map"], string(sub_entity), sub_entity);
    break;
    
    
    
    case obj_puppet_minebox:
        //these kits are setup from another function that spawns the kits and fills them!
        var get_map = scr_entity_template_library(argument0,argument1,argument2,argument3,argument4,argument5,argument6);
        new_entity = scr_server_entity_add(get_map);
        
        //add items!
        
        var sub_entity = scr_toolkit_template_library( obj_puppet_flashlight, item_storage_pos, item_storage_pos, 0, 0, false, new_entity);
        ds_map_add(get_map[? "contains_map"], string(sub_entity), sub_entity);
        
        var sub_map = scr_entity_template_library( obj_puppet_gasmask, item_storage_pos, item_storage_pos, 0, 0, false, new_entity);
        var sub_entity = scr_server_entity_add(sub_map);
        ds_map_add(get_map[? "contains_map"], string(sub_entity), sub_entity);
        
        var sub_map = scr_entity_template_library( obj_puppet_wrench, item_storage_pos, item_storage_pos, 0, 0, false, new_entity);
        var sub_entity = scr_server_entity_add(sub_map);
        ds_map_add(get_map[? "contains_map"], string(sub_entity), sub_entity);
        
        var sub_map = scr_entity_template_library( obj_puppet_crowbar, item_storage_pos, item_storage_pos, 0, 0, false, new_entity);
        var sub_entity = scr_server_entity_add(sub_map);
        ds_map_add(get_map[? "contains_map"], string(sub_entity), sub_entity);
        
        var sub_map = scr_entity_template_library( obj_puppet_screwdriver, item_storage_pos, item_storage_pos, 0, 0, false, new_entity);
        var sub_entity = scr_server_entity_add(sub_map);
        ds_map_add(get_map[? "contains_map"], string(sub_entity), sub_entity);
    break;
    
    
    
    case obj_puppet_secbox:
        //these kits are setup from another function that spawns the kits and fills them!
        var get_map = scr_entity_template_library(argument0,argument1,argument2,argument3,argument4,argument5,argument6);
        new_entity = scr_server_entity_add(get_map);
        
        //add items!
        
        var sub_entity = scr_toolkit_template_library( obj_puppet_secflashlight, item_storage_pos, item_storage_pos, 0, 0, false, new_entity);
        ds_map_add(get_map[? "contains_map"], string(sub_entity), sub_entity);
        
        var sub_map = scr_entity_template_library( obj_puppet_gasmask, item_storage_pos, item_storage_pos, 0, 0, false, new_entity);
        var sub_entity = scr_server_entity_add(sub_map);
        ds_map_add(get_map[? "contains_map"], string(sub_entity), sub_entity);
    break;
    
    
    
    case obj_puppet_atmobox:
        //these kits are setup from another function that spawns the kits and fills them!
        var get_map = scr_entity_template_library(argument0,argument1,argument2,argument3,argument4,argument5,argument6);
        new_entity = scr_server_entity_add(get_map);
        
        //add items!
        
        var sub_entity = scr_toolkit_template_library( obj_puppet_flashlight, item_storage_pos, item_storage_pos, 0, 0, false, new_entity);
        ds_map_add(get_map[? "contains_map"], string(sub_entity), sub_entity);
        
        var sub_map = scr_entity_template_library( obj_puppet_gasmask, item_storage_pos, item_storage_pos, 0, 0, false, new_entity);
        var sub_entity = scr_server_entity_add(sub_map);
        ds_map_add(get_map[? "contains_map"], string(sub_entity), sub_entity);
    break;
    
    
    
    case obj_puppet_hydrobox:
        //these kits are setup from another function that spawns the kits and fills them!
        var get_map = scr_entity_template_library(argument0,argument1,argument2,argument3,argument4,argument5,argument6);
        new_entity = scr_server_entity_add(get_map);
        
        //add items!
        
        var sub_entity = scr_toolkit_template_library( obj_puppet_flashlight, item_storage_pos, item_storage_pos, 0, 0, false, new_entity);
        ds_map_add(get_map[? "contains_map"], string(sub_entity), sub_entity);
        
        var sub_map = scr_entity_template_library( obj_puppet_gasmask, item_storage_pos, item_storage_pos, 0, 0, false, new_entity);
        var sub_entity = scr_server_entity_add(sub_map);
        ds_map_add(get_map[? "contains_map"], string(sub_entity), sub_entity);
    break;
    
    
    
    case obj_puppet_janibox:
        //these kits are setup from another function that spawns the kits and fills them!
        var get_map = scr_entity_template_library(argument0,argument1,argument2,argument3,argument4,argument5,argument6);
        new_entity = scr_server_entity_add(get_map);
        
        //add items!
        
        var sub_entity = scr_toolkit_template_library( obj_puppet_flashlight, item_storage_pos, item_storage_pos, 0, 0, false, new_entity);
        ds_map_add(get_map[? "contains_map"], string(sub_entity), sub_entity);
        
        var sub_map = scr_entity_template_library( obj_puppet_gasmask, item_storage_pos, item_storage_pos, 0, 0, false, new_entity);
        var sub_entity = scr_server_entity_add(sub_map);
        ds_map_add(get_map[? "contains_map"], string(sub_entity), sub_entity);
    break;
    
    
    
    //NONE TOOLKIT BOXES
    
    case obj_puppet_bandaid_box:
        //these kits are setup from another function that spawns the kits and fills them!
        var get_map = scr_entity_template_library(argument0,argument1,argument2,argument3,argument4,argument5,argument6);
        new_entity = scr_server_entity_add(get_map);
        
        //add items!
        repeat(get_map[? "contains_max"] - 2) { //fill inventory!
            var sub_map = scr_entity_template_library( obj_puppet_bandaid, item_storage_pos, item_storage_pos, 0, 0, false, new_entity);
            var sub_entity = scr_server_entity_add(sub_map);
            ds_map_add(get_map[? "contains_map"], string(sub_entity), sub_entity);
        }
        
        var sub_map = scr_entity_template_library( obj_puppet_burnointment, item_storage_pos, item_storage_pos, 0, 0, false, new_entity);
        var sub_entity = scr_server_entity_add(sub_map);
        ds_map_add(get_map[? "contains_map"], string(sub_entity), sub_entity);
        
        var sub_map = scr_entity_template_library( obj_puppet_disinfectant, item_storage_pos, item_storage_pos, 0, 0, false, new_entity);
        var sub_entity = scr_server_entity_add(sub_map);
        ds_map_add(get_map[? "contains_map"], string(sub_entity), sub_entity);
    break;
    
    
    
    case obj_puppet_flashlight:
    case obj_puppet_secflashlight:
        //these kits are setup from another function that spawns the kits and fills them!
        var get_map = scr_entity_template_library(argument0,argument1,argument2,argument3,argument4,argument5,argument6);
        new_entity = scr_server_entity_add(get_map);
        
        //add items!
        var sub_map = scr_entity_template_library( obj_puppet_powercell, item_storage_pos, item_storage_pos, 0, 0, false, new_entity);
        sub_map[? "Charge"] = 100;
        var sub_entity = scr_server_entity_add(sub_map);
        ds_map_add(get_map[? "contains_map"], string(sub_entity), sub_entity);
    break;
    
    
    
    case obj_puppet_clipboard:
        //these kits are setup from another function that spawns the kits and fills them!
        var get_map = scr_entity_template_library(argument0,argument1,argument2,argument3,argument4,argument5,argument6);
        new_entity = scr_server_entity_add(get_map);
        
        //add items!
        repeat(get_map[? "contains_max"]) { //fill inventory!
            var sub_map = scr_entity_template_library( obj_puppet_paper, item_storage_pos, item_storage_pos, 0, 0, false, new_entity);
            var sub_entity = scr_server_entity_add(sub_map);
            ds_map_add(get_map[? "contains_map"], string(sub_entity), sub_entity);
        }
    break;
    
}
    
return new_entity;
