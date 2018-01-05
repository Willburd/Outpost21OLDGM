///scr_inventory_scanfor_updated_item( entity id, storagebox entity id);
//calls an inventory update if the on screen inventory object has this entity!
var get_item_entity = argument0;
var return_value = false;
scr_consoleout(" -scanning for entity in an open inventory!");

with obj_inventory_parent {
    if string(my_entity) == string(argument1) {
        scr_consoleout(" -found entity inside instance: " + string(id) );
        scr_consoleout(" -hosting entity inventory of: " + string( my_entity));
        
        return_value = true; //found it!
        
        //temporarily lock inventory out so we can updoot it!
        inventory_sized = 0;
        scr_spacket_entity_inventory_request( real(my_entity), id);
    }
    else
    {
        //needed for removal from inventories it is no longer inside!
        for (var i=0; i<inventory_sized; i+=1)
        {
            if string(array_inventory[i,0]) == string(argument0) {
                scr_consoleout(" -found entity inside instance: " + string(id) );
                scr_consoleout(" -hosting entity inventory of: " + string( my_entity));
            
                return_value = true; //found it!
                
                //temporarily lock inventory out so we can updoot it!
                inventory_sized = 0;
                scr_spacket_entity_inventory_request( real(my_entity), id);
                break;
            }
        }
    }
    
    //extra dangerous! an active inventory window for the item being placed!
    if string(my_entity) == string(argument0) {
        scr_consoleout(" -found open inventory of entity, inside instance: " + string(id) );
        //drop equiped entity
        if string(argument0) == global.equiped_entity {
            global.equiped_entity = -1;
            global.equiped_object = noone;
        }
        //remove inventory
        instance_destroy();
    }
}



//drop equiped entity, for safety this always happens, because you are not meant to put it inside items anyway.
if string(argument0) == global.equiped_entity {
    global.equiped_entity = -1;
    global.equiped_object = noone;
}
//update tooltip if this is the same entity!
with obj_tooltip {
    if last_used_index == get_item_entity instance_destroy();
}
//just in case a context menu was open, with the entity trying to interact with it!
with obj_contextmenu {
    if my_entity == string(argument1) {
        //close all child menus!
        delete_child_onclose = true;
        //drop equiped entity
        if string(argument0) == string(global.equiped_entity) {
            global.equiped_entity = -1;
            global.equiped_object = noone;
        }
        instance_destroy(); //if the menu was using it, kill it because we don't want fuckery!
    }
}

return return_value;
