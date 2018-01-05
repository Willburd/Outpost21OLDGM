///scr_spacket_entity_inventory_request( entity id of inventory, instance id requesting);
scr_consoleout("Requested inventory of entity: " + string(argument0) + " using instance id" + string(argument1));

var send_buffer = buffer_create(1,buffer_grow,1);
buffer_write(send_buffer,buffer_u16, enum_server_packets.entity_inventory_request); //send login details! Wait for connection back
buffer_write(send_buffer,buffer_u32,argument0);
buffer_write(send_buffer,buffer_s32,argument1);
network_send_packet(global.client_socket, send_buffer, buffer_get_size(send_buffer));
buffer_delete(send_buffer);
