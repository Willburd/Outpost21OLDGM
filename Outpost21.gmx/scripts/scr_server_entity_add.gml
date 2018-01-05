///scr_server_entity_add(ds_map to add);
//returns the slot used!
var found_slot = false;
var slotid = 0;
while found_slot == false {
    if slotid > ds_list_size(list_entities) or scr_ds_map_verify(list_entities[| slotid]) == false { //end of list, or no ds_map in this entity slot!
        //add to the main entity list
        list_entities[| slotid] = argument0;
        argument0[? "entity_number"] = slotid;
        ds_list_mark_as_map(list_entities,slotid);
        found_slot = true;
        //say the entity is ready to be updated to the client
        scr_item_updateflag_allplayers( slotid, true);
        break;
    }
    else
    {
        slotid++;
    }
}

return slotid;
