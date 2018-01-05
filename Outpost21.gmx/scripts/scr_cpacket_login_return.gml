///scr_cpacket_login_return(connection id, login success?, username used);
var send_buffer = buffer_create(1,buffer_grow,1);
buffer_write(send_buffer,buffer_u8,argument0);
buffer_write(send_buffer,buffer_u16, enum_client_packets.login_failed + argument1); //write back to the client that they have logged in! 5 is failed 6 is success!
buffer_write(send_buffer,buffer_string, argument2); 
ds_queue_enqueue(global.packet_batch_queue,send_buffer);
