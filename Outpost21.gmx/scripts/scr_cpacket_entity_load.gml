///scr_cpacket_entity_load(connection id, send entity id, send object_index, send x, send y, direction, speed, construct flag , depth modifier);
var send_buffer = buffer_create(1,buffer_grow,1);
buffer_write(send_buffer,buffer_u8,210); //packet-start magic number
buffer_write(send_buffer,buffer_u8,argument0);
buffer_write(send_buffer,buffer_u16, enum_client_packets.entity_load);
buffer_write(send_buffer,buffer_u32, argument1); //entity id
buffer_write(send_buffer,buffer_u16, argument2); //object index
buffer_write(send_buffer,buffer_f32, argument3); //x
buffer_write(send_buffer,buffer_f32, argument4); //y
buffer_write(send_buffer,buffer_u16, floor(((argument5 mod 360) /360)*65534) ); //direction
buffer_write(send_buffer,buffer_u16, argument6); //speed
buffer_write(send_buffer,buffer_u8, argument7); //construct
buffer_write(send_buffer,buffer_s16, argument8); //depth modifier

//show_debug_message("*** ENTITY LOAD SENT TO CLIENT: " + string(argument1) + " obj: " + string(argument2) );
//show_debug_message("Was called from inside object: " + string(object_index));

ds_queue_enqueue(global.packet_batch_queue,send_buffer);

