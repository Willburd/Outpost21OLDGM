///scr_spacket_map_request_whole();
instance_activate_object(obj_construction)
with obj_construction instance_destroy(); //cleanout all and get data!

global.current_map_load_entities = 0;

var send_buffer = buffer_create(1,buffer_grow,1);
buffer_write(send_buffer,buffer_u8,210); //packet-start magic number
buffer_write( send_buffer, buffer_u16, enum_server_packets.map_request_whole); //send login details! Wait for connection back
network_send_raw( global.client_socket, send_buffer, buffer_get_size(send_buffer));
buffer_delete( send_buffer);
