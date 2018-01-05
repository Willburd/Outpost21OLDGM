///scr_server_entity_securityupdate( entity);
var entity_number = argument0;
var found_map = list_entities[| entity_number];
if scr_ds_map_verify(found_map) {
    var get_inventory_map = found_map[? "contains_map"];
    var inv_size = ds_map_size(get_inventory_map);
    
    
    //get security data from player
    var clearance_list = found_map[? "security_clearance"];
    
    if is_undefined( clearance_list) {
        ds_map_add_list(found_map, "security_clearance", ds_list_create());
    }
    
    //cleanout as needed
    ds_list_clear( clearance_list);

    //populate list, if it was removed then the cached one is already cleared anyway!
    if scr_ds_map_verify(clearance_list) {
        if is_undefined(found_map[? "player_socket"]) == false and found_map[? "player_socket"] != -1 {
            //clear out current data for a reload!
            ds_list_clear(clearance_list);
        
            //look for security cards!
            var current_key = ds_map_find_first(get_inventory_map);
            for (var i=0; i<inv_size; i+=1)
            {
                var item_map = list_entities[| current_key];
                if asset_get_index(item_map[? "object_index"]) == obj_puppet_securitycard {
                    var get_card_sec = item_map[? "security_levels"];
                
                    for (sec = 0; sec < ds_list_size(global.list_security_levels); sec+=1)
                    {
                        if is_undefined(get_card_sec[| sec]) == false and get_card_sec[| sec] != 0 clearance_list[| sec] = 1; //undefined is no clearance, otherwise allow! cards stack!
                    }
                }
                //next index
                current_key = ds_map_find_next(get_inventory_map, current_key);
            }
            
            //transmit data
            var TXstring = ds_list_write(clearance_list);
            var TXbase64 = base64_encode(TXstring);
            scr_cpacket_player_security_reply( found_map[? "player_socket"], TXbase64);
        }
    }
}
