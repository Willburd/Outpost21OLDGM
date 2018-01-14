///scr_cpacket_map_object_load(connection id, map entity id, send object_index, map buffer size, send x, send y, entity hp, entity direction);
var send_buffer = buffer_create(1,buffer_grow,1);
buffer_write(send_buffer,buffer_u8,210); //packet-start magic number
buffer_write(send_buffer,buffer_u8,argument0);
show_debug_message("===Send map data(loading) to socket: " + string(argument0));
buffer_write(send_buffer,buffer_u16, enum_client_packets.map_object_load);
buffer_write(send_buffer,buffer_u16, argument1); //map entity id map
show_debug_message(" -map entity: " + string(argument1));
buffer_write(send_buffer,buffer_u16, argument2); //object index 
show_debug_message(" -object: " + string(argument2));
buffer_write(send_buffer,buffer_u16, argument3); //max entity count
buffer_write(send_buffer,buffer_f32, argument4); //x
show_debug_message(" -x: " + string(argument4));
buffer_write(send_buffer,buffer_f32, argument5); //y
show_debug_message(" -y: " + string(argument5));
buffer_write(send_buffer,buffer_u8, argument6); //wall hp
buffer_write(send_buffer,buffer_u16, floor(((argument7 mod 360) /360)*65534) ); //direction
ds_queue_enqueue(global.packet_batch_queue,send_buffer);

