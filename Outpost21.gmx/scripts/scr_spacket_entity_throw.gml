///scr_spacket_entity_throw( entity to store, storage box entity,x,y,dir,spd);
var send_buffer = buffer_create(1,buffer_grow,1);
buffer_write(send_buffer,buffer_u16, enum_server_packets.entity_throw); //send login details! Wait for connection back
buffer_write(send_buffer,buffer_u16, floor(((argument4 mod 360) /360)*65534)); //dir these first so i can use some switch statement tricks to turn a throw into a place with velocity!
buffer_write(send_buffer,buffer_u16, argument5); //spd
buffer_write(send_buffer,buffer_u32, argument0); //entity
buffer_write(send_buffer,buffer_u32, argument1); //storage entity
buffer_write(send_buffer,buffer_f32, argument2); //x
buffer_write(send_buffer,buffer_f32, argument3); //y
network_send_raw(global.client_socket, send_buffer, buffer_get_size(send_buffer));
buffer_delete(send_buffer);
