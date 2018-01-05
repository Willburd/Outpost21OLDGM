///scr_blueprint_build_entity( blueprint object, stc entity, client socket, true);
// if deconstructing scr_blueprint_build_entity( building entity, -1, client socket, false);
if argument3 == true {
    /**************************************
        CONSTRUCTING BUILDING!
    **************************************/  
    var get_map = list_entities[| string(argument1)];
    var get_object = asset_get_index( get_map[? "object_index"] );  //the object of the building doing the construction action!
    
    var get_inventory_map = get_map[? "contains_map"];
    var object_spawn = -1;
    var ignore_inv_clearing = false;

    //loop through all slots 
    var inv_size = ds_map_size(get_inventory_map);
    
    //store a list of requireparts to be erased when constructed
    var entity_consume_list = ds_list_create();
    
    
    
    switch argument0 {
        
        case obj_puppet_blueprint:
            var get_object = asset_get_index( get_map[? "object_index"] );
            
            if get_object == obj_machine_STC {
                //attempting to build a blank blueprint
                scr_cpacket_failed_action( argument2, "Blueprint requires programming at Blueprinter")
                break; //early escape!
            }
    
        default:
            if get_object == obj_machine_blueprinter {
                //creating a new blueprint
                var foundbp = scr_inventory_scanfor_object(get_inventory_map,obj_puppet_blueprint);
                
                if foundbp != -1 {
                    scr_server_entity_remove(foundbp); //BP
                    
                    //allow a spawn!
                    ignore_inv_clearing = true;
                    object_spawn = argument0;
                }
                else
                {
                    scr_cpacket_failed_action( argument2, "A blank blueprint is required")
                }
            }
            
            
            else if get_object == obj_machine_fabricator {
                //extract blueprint!
                var part_peak_list = global.crafting_req[| argument0]; //NOTE TO SELF! the STC build function passes in the BP!
                for (i=0; i<ds_list_size(part_peak_list); i+=1)
                {
                    entity_consume_list[| i] = scr_inventory_scanfor_object(get_inventory_map,part_peak_list[| i]);
                }
                
                //final confirmation
                var confirm_build = true;
                for (i=0; i<ds_list_size(entity_consume_list); i+=1)
                {
                    if entity_consume_list[| i] == -1 confirm_build = false;
                };
                
                
                if confirm_build == true {
                    //remove consumed objects,some objects can just be a catalyst too! if they are not removed here the next bit will spit them out!
                    for (i=0; i<ds_list_size(entity_consume_list); i+=1)
                    {
                        scr_server_entity_remove(entity_consume_list[| i]); //BP
                    }
                
                    //allow a spawn!
                    ignore_inv_clearing = true;
                    object_spawn = argument0;
                }
                else
                {
                    for (i=0; i<ds_list_size(entity_consume_list); i+=1)
                    {
                        //provide errors to the client!
                        if entity_consume_list[| i] == -1 {
                            scr_cpacket_failed_action( argument2, "Missing: " + string( global.obj_names[|  part_peak_list[| i] ] ));
                            break;
                        }
                    }
                }
            }
            
            
            else
            {
                //extract blueprint!
                var part_peak_list = global.crafting_req[| argument0]; //NOTE TO SELF! the STC build function passes in the BP!
                for (i=0; i<ds_list_size(part_peak_list); i+=1)
                {
                    entity_consume_list[| i] = scr_inventory_scanfor_object(get_inventory_map,part_peak_list[| i]);
                }
                
                //final confirmation
                var confirm_build = true;
                for (i=0; i<ds_list_size(entity_consume_list); i+=1)
                {
                    if entity_consume_list[| i] == -1 confirm_build = false;
                }
                
                
                if confirm_build == true {
                    //remove consumed objects,some objects can just be a catalyst too! if they are not removed here the next bit will spit them out!
                    for (i=0; i<ds_list_size(entity_consume_list); i+=1)
                    {
                        scr_server_entity_remove(entity_consume_list[| i]); //BP
                    }
                    
                    //allow a spawn!
                    object_spawn = global.crafting_result[| argument0] ;
                }
                else
                {
                    for (i=0; i<ds_list_size(entity_consume_list); i+=1)
                    {
                        //provide errors to the client!
                        if entity_consume_list[| i] == -1 {
                            scr_cpacket_failed_action( argument2, "Missing: " + string( global.obj_names[|  part_peak_list[| i] ] ));
                            break;
                        }
                    }
                }
            }
        break;
    }
    
    
    //cleanlist 
    ds_list_destroy(entity_consume_list);
    
    
    //release contents of inventory, anything not already grabbed is just gonna get lost inside of it if we don't.
    if object_spawn != -1 and ignore_inv_clearing == false {
        //dump all excess items out
        scr_server_entity_dumpinventory( argument1);
        if get_object == obj_machine_STC scr_server_storagebox_object_update_all_players( argument1, argument1); //close inventory on STCs
    }
    
    
    return object_spawn;
}
else
{
    /**************************************
        DECONSTRUCTING BUILDING!
    **************************************/
    var get_map = list_entities[| string(argument0)];
    var get_object = asset_get_index( get_map[? "object_index"] );
    var xx = get_map[? "x"];
    var yy = get_map[? "y"];
    
    var get_inventory_map = get_map[? "contains_map"];
    
    //loop through all slots 
    var inv_size = ds_map_size(get_inventory_map);
    
    //spew all inventory items out!
    scr_server_entity_dumpinventory( argument0);
    
    
    //a stc is always used anyway
    var new_item = scr_entity_template_library(obj_machine_STC,xx,yy,irandom(360),choose(1,2,3),false,-1);
    scr_server_entity_add(new_item);
    
    
    //changes based on machine!
    switch get_object {
    
        default:
            var part_peak_list = global.crafting_req[| get_object]; //NOTE TO SELF! the STC build function passes in the BP!
            for (i=0; i<ds_list_size(part_peak_list); i+=1)
            {
                var new_item = scr_entity_template_library(part_peak_list[| i],xx,yy,irandom(360),choose(1,2,3),false,-1);
                scr_server_entity_add(new_item);
            }
        break;
    }
}
