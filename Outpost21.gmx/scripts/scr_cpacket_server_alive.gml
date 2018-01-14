///scr_cpacket_server_alive(connection id);
var send_buffer = buffer_create(1,buffer_grow,1);
buffer_write(send_buffer,buffer_u8,210); //packet-start magic number
buffer_write(send_buffer,buffer_u8,argument0);
buffer_write(send_buffer,buffer_u16, enum_client_packets.server_alive); //write back to the client that they have logged in! 5 is failed 6 is success!
ds_queue_enqueue(global.packet_batch_queue,send_buffer);
