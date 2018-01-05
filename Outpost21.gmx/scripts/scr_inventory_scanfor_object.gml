///scr_inventory_scanfor_object( inventory, object_index)
//extract blueprint!
var return_index = -1;
var inv_size = ds_map_size(argument0);
var current_key = ds_map_find_first(argument0);
for (var i=0; i<inv_size; i+=1)
{
    var item_map = list_entities[| current_key];
    if asset_get_index(item_map[? "object_index"]) == argument1 {
        //store the entity for removal!
        return_index = current_key;
        break;
    }
    
    //try next key
    var current_key = ds_map_find_next(argument0,current_key);
}

return return_index;
