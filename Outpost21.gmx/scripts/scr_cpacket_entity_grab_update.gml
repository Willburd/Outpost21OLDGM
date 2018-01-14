///scr_cpacket_entity_grab_update(connection id, entity_number);
var send_buffer = buffer_create(1,buffer_grow,1);
buffer_write(send_buffer,buffer_u8,210); //packet-start magic number
buffer_write(send_buffer,buffer_u8,argument0);
buffer_write(send_buffer,buffer_u16,  enum_client_packets.entity_grab_update);
buffer_write(send_buffer,buffer_u32,  argument1);
ds_queue_enqueue(global.packet_batch_queue,send_buffer);

