///scr_cpacket_location_sync(connection id, send x, send y, send dir, send spd);
var send_buffer = buffer_create(1,buffer_grow,1);
buffer_write(send_buffer,buffer_u8,210); //packet-start magic number
buffer_write(send_buffer,buffer_u8,argument0);
buffer_write(send_buffer,buffer_u16, enum_client_packets.movement_location_sync);
buffer_write(send_buffer,buffer_f32, argument1);
buffer_write(send_buffer,buffer_f32, argument2);
buffer_write(send_buffer,buffer_u16, floor(((argument3 mod 360) /360)*65534) ); //direction
buffer_write(send_buffer,buffer_u16, argument4); //speed
ds_queue_enqueue(global.packet_batch_queue,send_buffer);
