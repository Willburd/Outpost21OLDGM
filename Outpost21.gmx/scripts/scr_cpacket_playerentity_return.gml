///scr_cpacket_playerentity_return(connection id, entity number, object_index, x, y, hide_entity);
var send_buffer = buffer_create(1,buffer_grow,1);
buffer_write(send_buffer,buffer_u8,210); //packet-start magic number
buffer_write(send_buffer,buffer_u8,argument0);
buffer_write(send_buffer,buffer_u16, enum_client_packets.player_entity_return);
buffer_write(send_buffer,buffer_u32, argument1);
buffer_write(send_buffer,buffer_u16, argument2);
buffer_write(send_buffer,buffer_f32, argument3);
buffer_write(send_buffer,buffer_f32, argument4);
buffer_write(send_buffer,buffer_u8, argument5);
ds_queue_enqueue(global.packet_batch_queue,send_buffer);
