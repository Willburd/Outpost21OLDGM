///scr_spacket_map_request_securitydata();
var send_buffer = buffer_create(1,buffer_grow,1);
buffer_write( send_buffer, buffer_u16, enum_server_packets.map_request_securitydata); //send login details! Wait for connection back
network_send_packet( global.client_socket, send_buffer, buffer_get_size(send_buffer));
buffer_delete( send_buffer);
