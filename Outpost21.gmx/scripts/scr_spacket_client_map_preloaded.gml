///scr_spacket_client_map_preloaded();
var send_buffer = buffer_create(1,buffer_grow,1);
buffer_write( send_buffer, buffer_u16, enum_server_packets.client_map_preloaded); //send login details! Wait for connection back
var connect_transmit = 0;
while (connect_transmit == 0) { //FORCE RESEND
    connect_transmit = network_send_packet( global.client_socket, send_buffer, buffer_get_size(send_buffer));
}; 
buffer_delete( send_buffer);
