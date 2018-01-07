///scr_cpacket_character_notfound(connection id, attempted name);
var send_buffer = buffer_create(1,buffer_grow,1);
buffer_write(send_buffer,buffer_u16, enum_client_packets.character_not_found);
buffer_write(send_buffer,buffer_string, argument1);
network_send_raw(argument0, send_buffer, buffer_get_size(send_buffer));
buffer_delete(send_buffer);
