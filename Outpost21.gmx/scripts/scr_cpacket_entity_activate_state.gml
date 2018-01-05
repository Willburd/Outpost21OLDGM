///scr_cpacket_entity_activate_state( connection id, send entity id, activation state);
var send_buffer = buffer_create(1,buffer_grow,1);
buffer_write(send_buffer,buffer_u16, enum_client_packets.entity_activate_state);
buffer_write(send_buffer,buffer_u32, argument1); //entity
buffer_write(send_buffer,buffer_u32, argument2); //timer 0 is forever
network_send_packet(argument0, send_buffer, buffer_get_size(send_buffer));
buffer_delete(send_buffer);


