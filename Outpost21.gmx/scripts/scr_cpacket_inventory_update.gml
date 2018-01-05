///scr_cpacket_inventory_update(connection id, object_id_request_is_from, entity id of inventory to send);
var get_map = list_entities[| string(argument2)];
show_debug_message("attempting to transmit inventory of entity: " + string(list_entities[| argument2]) + " using instance: " + string(argument1) + " to socket: " + string(argument0));
if is_undefined(get_map) == false and ds_exists(get_map,ds_type_map) {
    //compile data
    var get_inventory_map = get_map[? "contains_map"];
    
    var transmit_list = ds_list_create();
    var size, key, i;
    size = ds_map_size(get_inventory_map);
    current_key = ds_map_find_first(get_inventory_map);
    for (var i = 0; i < size; i++;) {
    
        var get_slot_data = list_entities[| current_key ]; //pull the entity from from the list, the key popped off the map is just the entity id
        
        if is_undefined(get_slot_data) == false and ds_exists(get_slot_data,ds_type_map) {
            transmit_list[| (i*2)] = current_key; //store entity number
            transmit_list[| (i*2)+1] = asset_get_index(get_slot_data[? "object_index"]); //store object index
        }
    
        //next
        current_key = ds_map_find_next(get_inventory_map, current_key);
    }
    
    //encode the transmitting list for packetting
    var inventory_string = ds_list_write(transmit_list);
    var base64_inventory = base64_encode(inventory_string);
    ds_list_destroy(transmit_list); //cleanup
    
    //send inventory data!
    var send_buffer = buffer_create(1,buffer_grow,1);
    buffer_write(send_buffer,buffer_u8,argument0);
    buffer_write(send_buffer,buffer_u16, enum_client_packets.inventory_update);
    buffer_write(send_buffer,buffer_s32, argument1); //instance id of object to set the inventory in, signed because noone is a -
    buffer_write(send_buffer,buffer_u8, get_map[? "contains_max"])
    buffer_write(send_buffer,buffer_string, base64_inventory);
    ds_queue_enqueue(global.packet_batch_queue,send_buffer);
    
    show_debug_message("Inventory sent, size: " + string(size) );
}
