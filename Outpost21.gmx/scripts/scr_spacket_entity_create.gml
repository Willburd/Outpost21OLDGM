///scr_spacket_entity_create( x, y, object_index);
var send_buffer = buffer_create(1,buffer_grow,1);
buffer_write( send_buffer, buffer_u16, enum_server_packets.entity_create); //send login details! Wait for connection back
buffer_write(send_buffer,buffer_f32, argument0);
buffer_write(send_buffer,buffer_f32, argument1);
buffer_write(send_buffer,buffer_u16, argument2);
network_send_raw( global.client_socket, send_buffer, buffer_get_size(send_buffer));
buffer_delete( send_buffer);
