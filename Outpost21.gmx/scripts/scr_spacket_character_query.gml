///scr_spacket_character_query(character name);
var send_buffer = buffer_create(1,buffer_grow,1);
buffer_write(send_buffer,buffer_u16, enum_server_packets.character_query); //send login details! Wait for connection back
buffer_write(send_buffer,buffer_string,argument0);
network_send_packet(global.client_socket, send_buffer, buffer_get_size(send_buffer));
buffer_delete(send_buffer);
