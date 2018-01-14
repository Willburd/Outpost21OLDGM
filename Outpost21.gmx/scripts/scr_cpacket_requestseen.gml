///scr_cpacket_requestseen(connection id);
var send_buffer = buffer_create(1,buffer_grow,1);
buffer_write(send_buffer,buffer_u8,210); //packet-start magic number
buffer_write(send_buffer,buffer_u8,argument0);
buffer_write(send_buffer,buffer_u16, enum_client_packets.request_seen); //write opcode back. connection recognized! Ask for logins...

ds_queue_enqueue(global.packet_batch_queue,send_buffer);
