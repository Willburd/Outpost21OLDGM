///scr_cpacket_map_door_open( map entity);
for (var i=0; i<global.max_server_players; i+=1)
{
    if scr_socket_verify(obj_server.list_sockets[| i]) {
        var send_buffer = buffer_create(1,buffer_grow,1);
        buffer_write(send_buffer,buffer_u8,i);
        show_debug_message("Send map door: " + string(argument0) + " opening to socket");
        buffer_write(send_buffer,buffer_u16, enum_client_packets.map_door_open);
        buffer_write(send_buffer,buffer_u16, argument0);
        ds_queue_enqueue(global.packet_batch_queue,send_buffer);
    }
}
