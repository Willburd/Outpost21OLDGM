///scr_cpacket_entity_reply(connection id, entity_number, instance_id, reply data, mode flags, force instance or object);
var send_buffer = buffer_create(1,buffer_grow,1);
buffer_write(send_buffer,buffer_u8,210); //packet-start magic number
buffer_write(send_buffer,buffer_u8,argument0);
buffer_write(send_buffer,buffer_u16,  enum_client_packets.entity_reply);
buffer_write(send_buffer,buffer_u32,  argument1);
buffer_write(send_buffer,buffer_s32,  argument2);
buffer_write(send_buffer,buffer_string, argument3);
buffer_write(send_buffer,buffer_u8,   argument4);
buffer_write(send_buffer,buffer_u8,   argument5);
ds_queue_enqueue(global.packet_batch_queue,send_buffer);

