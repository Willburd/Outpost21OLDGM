///scr_cpacket_storagebox_object_update(connection id, entity id, storagebox entity id);
show_debug_message("sent player storage box update to socket: " + string(argument0));
show_debug_message(" -which is player entity: " + string(list_player[| argument0]));
show_debug_message(" -updating entity: " + string(argument1));
show_debug_message(" -inside of entity: " + string(argument2));
var send_buffer = buffer_create(1,buffer_grow,1);
buffer_write(send_buffer,buffer_u8,210); //packet-start magic number
buffer_write(send_buffer,buffer_u8,argument0);
buffer_write(send_buffer,buffer_u16, enum_client_packets.storagebox_object_update);
buffer_write(send_buffer,buffer_u32, argument1);
buffer_write(send_buffer,buffer_u32, argument2);
ds_queue_enqueue(global.packet_batch_queue,send_buffer);
