///scr_cpacket_map_object_drop(connection id, map entity id, send x, send y);
var send_buffer = buffer_create(1,buffer_grow,1);
buffer_write(send_buffer,buffer_u8,argument0);
show_debug_message("Send map data(dropping) to socket: " + string(argument0));
buffer_write(send_buffer,buffer_u16, enum_client_packets.map_object_drop);
buffer_write(send_buffer,buffer_u16, argument1); //map entity id 
show_debug_message(" -map entity: " + string(argument1));
buffer_write(send_buffer,buffer_f32, argument2); //x
show_debug_message(" -x: " + string(argument2));
buffer_write(send_buffer,buffer_f32, argument3); //y
show_debug_message(" -y: " + string(argument3));
ds_queue_enqueue(global.packet_batch_queue,send_buffer);
