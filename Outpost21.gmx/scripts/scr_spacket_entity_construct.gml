///scr_spacket_entity_construct( entity to place, storage box entity,x,y);
var send_buffer = buffer_create(1,buffer_grow,1);
buffer_write(send_buffer,buffer_u8,210); //packet-start magic number
buffer_write(send_buffer,buffer_u16, enum_server_packets.entity_construct); 
buffer_write(send_buffer,buffer_u32, argument0);
buffer_write(send_buffer,buffer_u32, argument1);
buffer_write(send_buffer,buffer_f32, argument2);
buffer_write(send_buffer,buffer_f32, argument3);
network_send_raw(global.client_socket, send_buffer, buffer_get_size(send_buffer));
buffer_delete(send_buffer);
