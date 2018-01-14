///scr_spacket_login_newuser(username,passwordhash);
var send_buffer = buffer_create(1,buffer_grow,1);
buffer_write(send_buffer,buffer_u8,210); //packet-start magic number
buffer_write(send_buffer,buffer_u16, enum_server_packets.login_newuser); //send login details! Wait for connection back
buffer_write(send_buffer,buffer_string,argument0);
buffer_write(send_buffer,buffer_string,argument1);
network_send_raw(global.client_socket, send_buffer, buffer_get_size(send_buffer));
buffer_delete(send_buffer);
