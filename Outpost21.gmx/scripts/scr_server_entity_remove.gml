///scr_server_entity_remove( entity id)
//send to the abyss
var deletemap = list_entities[| argument0];
if scr_ds_map_verify(deletemap) {
    //remove me from storages
    var get_storage_index = deletemap[? "inside_of_id"];
    
    if scr_entityslot_is_valid(get_storage_index) {
        //remove data from entity
        var get_storage_map = list_entities[| get_storage_index]
        
        if scr_ds_map_verify(get_storage_map) {
            //remove from the host storage object
            var get_storage_inventory_map = get_storage_map[? "contains_map"];
            ds_map_delete(get_storage_inventory_map,string(argument0)); //remove from entity
            //update self for completeness sakes
            deletemap[? "inside_of_id"] = -1;
        }
    }
    
    //update all players of this action
    scr_server_storagebox_object_update_all_players(argument0, get_storage_index);

    //delete me
    if deletemap[? "x"] > item_abyss_pos or deletemap[? "y"] > item_abyss_pos {
        deletemap[? "x"] = item_abyss_pos;
        deletemap[? "y"] = item_abyss_pos;
    }
}
