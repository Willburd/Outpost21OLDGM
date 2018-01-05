///scr_spacket_security_tool_toggledoorsecurity( map entity, instance id, index);
var send_buffer = buffer_create(1,buffer_grow,1);
buffer_write( send_buffer, buffer_u16, enum_server_packets.security_tool_toggledoorsecurity); //send login details! Wait for connection back
buffer_write(send_buffer,buffer_u16, argument0);
buffer_write(send_buffer,buffer_s32, argument1);
buffer_write(send_buffer,buffer_u8, argument2);
network_send_packet( global.client_socket, send_buffer, buffer_get_size(send_buffer));
buffer_delete( send_buffer);
