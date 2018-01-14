///scr_spacket_map_object_create( object_index, x, y, hp percent, direction);
var send_buffer = buffer_create(1,buffer_grow,1);
buffer_write(send_buffer,buffer_u8,210); //packet-start magic number
buffer_write( send_buffer, buffer_u16, enum_server_packets.map_object_create); //send login details! Wait for connection back
buffer_write(send_buffer,buffer_u16, argument0);
buffer_write(send_buffer,buffer_f32, argument1);
buffer_write(send_buffer,buffer_f32, argument2);
buffer_write(send_buffer,buffer_u8, argument3);
buffer_write(send_buffer,buffer_u16, floor(((argument4 mod 360) /360)*65534));
network_send_raw( global.client_socket, send_buffer, buffer_get_size(send_buffer));
buffer_delete( send_buffer);
