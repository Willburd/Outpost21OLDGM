#include "client_transmit_packets.h"
#include "client_structure.h"

int client_transmission_packets::cPacket_request_seen(client_struct& inputClient) {
    //construct buffer to send data
    byte_buffer send_buffer;
    send_buffer.buffer_write_u8( inputClient.myNumber); //client number
    send_buffer.buffer_write_u16( client_transmission_packets::request_seen); //opcode

    //transmit
    return inputClient.mySocket.send(send_buffer.data, send_buffer.buffer_get_pos());
}


int client_transmission_packets::cPacket_login_failed(client_struct& inputClient, std::string nameUsed) {
    //construct buffer to send data
    byte_buffer send_buffer;
    send_buffer.buffer_write_u8( inputClient.myNumber); //client number
    send_buffer.buffer_write_u16( client_transmission_packets::login_failed); //opcode

    //transmit
    send_buffer.buffer_debug();
    return inputClient.mySocket.send(send_buffer.data, send_buffer.buffer_get_pos());
};


int client_transmission_packets::cPacket_login_success(client_struct& inputClient, std::string nameUsed) {
    //construct buffer to send data
    byte_buffer send_buffer;
    send_buffer.buffer_write_u8( inputClient.myNumber); //client number
    send_buffer.buffer_write_u16( client_transmission_packets::login_success); //opcode
    send_buffer.buffer_write_string( nameUsed);

    //transmit
    send_buffer.buffer_debug();
    return inputClient.mySocket.send(send_buffer.data, send_buffer.buffer_get_pos());
};
