///scr_spacket_map_object_destroy( map entity id);
var send_buffer = buffer_create(1,buffer_grow,1);
buffer_write(send_buffer,buffer_u8,210); //packet-start magic number
buffer_write( send_buffer, buffer_u16, enum_server_packets.map_object_destroy); //send login details! Wait for connection back
buffer_write(send_buffer,buffer_u16, argument0); //map entity id,
network_send_raw( global.client_socket, send_buffer, buffer_get_size(send_buffer));
buffer_delete( send_buffer);
