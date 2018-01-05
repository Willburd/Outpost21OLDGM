///scr_cpacket_character_wasfound_inuse(connection id);
var send_buffer = buffer_create(1,buffer_grow,1);
buffer_write(send_buffer,buffer_u16, enum_client_packets.character_was_found_inuse);
network_send_packet(argument0, send_buffer, buffer_get_size(send_buffer));
buffer_delete(send_buffer);
