///scr_server_entity_dumpinventory( entity);
var get_map = list_entities[| string(argument0)];
var get_inventory_map = get_map[? "contains_map"];

var inv_size = ds_map_size(get_inventory_map);
var current_key = ds_map_find_first(get_inventory_map);

for (var i=0; i<inv_size; i+=1)
{
    //release me
    var item_map = list_entities[| current_key];

    item_map[? "inside_of_id"] = -1;
    item_map[? "dir"] = irandom(360);
    item_map[? "spd"] = choose(1,2,3);
    item_map[? "x"] = get_map[? "x"];
    item_map[? "y"] = get_map[? "y"];
    
    //cleanout help
    ds_map_delete(argument0,string(current_key));
    
    //forces update, mark all player flags as update forced!
    scr_item_updateflag_allplayers(current_key,true);
    
    //update all players of this action
    scr_server_storagebox_object_update_all_players(current_key,argument0); //update storage box
        
    //next entry
    var current_key = ds_map_find_first(get_inventory_map); //repeatedly itterating till empty
}


