///scr_spacket_character_create(character name,username,race,home,body,jobprev,job,guild,langM,langA,age);
var send_buffer = buffer_create(1,buffer_grow,1);
buffer_write(send_buffer,buffer_u16, enum_server_packets.character_created); //make new char
buffer_write(send_buffer,buffer_string, argument[0]); //name
buffer_write(send_buffer,buffer_string, argument[1]); //user name
buffer_write(send_buffer,buffer_u8, argument[2]); //race
buffer_write(send_buffer,buffer_u8, argument[3]); //homeworld
buffer_write(send_buffer,buffer_u8, argument[4]); //body type
buffer_write(send_buffer,buffer_u8, argument[5]); //job
buffer_write(send_buffer,buffer_u8, argument[6]); //jobprev
buffer_write(send_buffer,buffer_u8, argument[7]); //guild
buffer_write(send_buffer,buffer_u8, argument[8]); //lang main
buffer_write(send_buffer,buffer_u8, argument[9]); //lang alt
buffer_write(send_buffer,buffer_u16, argument[10]); //age
network_send_raw(global.client_socket, send_buffer, buffer_get_size(send_buffer));
buffer_delete(send_buffer);
