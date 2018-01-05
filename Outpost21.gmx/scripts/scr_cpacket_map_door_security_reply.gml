///scr_cpacket_map_door_security_reply(connection id, map entity, return door color);
var send_buffer = buffer_create(1,buffer_grow,1);
buffer_write(send_buffer,buffer_u8,argument0);
buffer_write(send_buffer,buffer_u16, enum_client_packets.map_door_security_reply);
buffer_write(send_buffer,buffer_u16, argument1); //map entity id map
buffer_write(send_buffer,buffer_s32, argument2); //color to set it to!
ds_queue_enqueue(global.packet_batch_queue,send_buffer);

