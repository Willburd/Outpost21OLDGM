#include "client_transmit_packets.h"
#include "client_structure.h"

int client_transmission_packets::cPacket_request_seen(client_struct& inputClient) {
    //construct buffer to send data
    byte_buffer send_buffer;
    send_buffer.buffer_write_u8( 210); //packetstart magic number
    send_buffer.buffer_write_u8( inputClient.myNumber); //client number

    send_buffer.buffer_write_u16( client_transmission_packets::request_seen); //opcode

    //transmit
    return inputClient.mySocket.send(send_buffer.data, send_buffer.buffer_get_pos());
}

int client_transmission_packets::cpacket_login_newuser(client_struct& inputClient, std::string nameUsed, std::string hashUsed) {
    //construct buffer to send data
    byte_buffer send_buffer;
    send_buffer.buffer_write_u8( 210); //packetstart magic number
    send_buffer.buffer_write_u8( inputClient.myNumber); //client number

    send_buffer.buffer_write_u16( client_transmission_packets::login_newuser); //opcode
    send_buffer.buffer_write_string( nameUsed);
    send_buffer.buffer_write_string( hashUsed);

    //transmit
    return inputClient.mySocket.send(send_buffer.data, send_buffer.buffer_get_pos());
}

int client_transmission_packets::cPacket_login_failed(client_struct& inputClient, std::string nameUsed) {
    //construct buffer to send data
    byte_buffer send_buffer;
    send_buffer.buffer_write_u8( 210); //packetstart magic number
    send_buffer.buffer_write_u8( inputClient.myNumber); //client number

    send_buffer.buffer_write_u16( client_transmission_packets::login_failed); //opcode
    send_buffer.buffer_write_string( nameUsed);

    //transmit
    return inputClient.mySocket.send(send_buffer.data, send_buffer.buffer_get_pos());
};

int client_transmission_packets::cPacket_login_success(client_struct& inputClient, std::string nameUsed) {
    //construct buffer to send data
    byte_buffer send_buffer;
    send_buffer.buffer_write_u8( 210); //packetstart magic number
    send_buffer.buffer_write_u8( inputClient.myNumber); //client number

    send_buffer.buffer_write_u16( client_transmission_packets::login_success); //opcode
    send_buffer.buffer_write_string( nameUsed);

    //transmit
    return inputClient.mySocket.send(send_buffer.data, send_buffer.buffer_get_pos());
};

int client_transmission_packets::cpacket_character_transmit_data(client_struct& inputClient, std::string jsonStringOfEntity) {
    //construct buffer to send data
    byte_buffer send_buffer;
    send_buffer.buffer_write_u8( 210); //packetstart magic number
    send_buffer.buffer_write_u8( inputClient.myNumber); //client number

    send_buffer.buffer_write_u16( client_transmission_packets::character_transmit_data); //opcode
    send_buffer.buffer_write_string( jsonStringOfEntity);

    //transmit
    return inputClient.mySocket.send(send_buffer.data, send_buffer.buffer_get_pos());
}

//map_object_load,
//map_object_drop,
//map_security_reply,
//map_door_open,
//map_door_security_reply,
///character locking
int client_transmission_packets::cpacket_character_lock(client_struct& inputClient, int input_EntityNumber) {
    //construct buffer to send data
    byte_buffer send_buffer;
    send_buffer.buffer_write_u8( 210); //packetstart magic number
    send_buffer.buffer_write_u8( inputClient.myNumber); //client number

    send_buffer.buffer_write_u16( client_transmission_packets::character_locked);
    send_buffer.buffer_write_u32( input_EntityNumber);

    //transmit
    return inputClient.mySocket.send(send_buffer.data, send_buffer.buffer_get_pos());
}

int client_transmission_packets::cpacket_playerentity_return( client_struct& inputClient, int input_EntityNumber, int get_object_index, double get_x, double get_y, bool get_hide) {
    byte_buffer send_buffer;
    send_buffer.buffer_write_u8( 210); //packetstart magic number
    send_buffer.buffer_write_u8( inputClient.myNumber); //client number

    send_buffer.buffer_write_u16( client_transmission_packets::player_entity_return);
    send_buffer.buffer_write_u32( input_EntityNumber);
    send_buffer.buffer_write_u16( get_object_index);
    send_buffer.buffer_write_f32( get_x);
    send_buffer.buffer_write_f32( get_y);
    send_buffer.buffer_write_u8( get_hide);

    //transmit
    return inputClient.mySocket.send(send_buffer.data, send_buffer.buffer_get_pos());
}

//player_security_reply,
//movement_location_sync,
///entities
//entity_load,

int client_transmission_packets::cpacket_entity_drop(client_struct& inputClient, int input_EntityNumber) {
    //construct buffer to send data
    byte_buffer send_buffer;
    send_buffer.buffer_write_u8( 210); //packetstart magic number
    send_buffer.buffer_write_u8( inputClient.myNumber );

    send_buffer.buffer_write_u16( client_transmission_packets::entity_drop);
    send_buffer.buffer_write_u32( input_EntityNumber );

    //transmit
    return inputClient.mySocket.send(send_buffer.data, send_buffer.buffer_get_pos());
}

//entity_reply,
//entity_activate,
int client_transmission_packets::cpacket_entity_grab_update(client_struct& inputClient, int input_EntityNumber) {
    //construct buffer to send data
    byte_buffer send_buffer;
    send_buffer.buffer_write_u8( 210); //packetstart magic number
    send_buffer.buffer_write_u8( inputClient.myNumber );

    send_buffer.buffer_write_u16( client_transmission_packets::entity_grab_update);
    send_buffer.buffer_write_u32( input_EntityNumber );

    //transmit
    return inputClient.mySocket.send(send_buffer.data, send_buffer.buffer_get_pos());
}

///misc
int client_transmission_packets::cpacket_force_reset( client_struct& inputClient, std::string errorString) {
    byte_buffer send_buffer;
    send_buffer.buffer_write_u8( 210); //packetstart magic number
    send_buffer.buffer_write_u8( inputClient.myNumber );

    send_buffer.buffer_write_u16( client_transmission_packets::force_reset);
    send_buffer.buffer_write_string( errorString);

    //transmit
    return inputClient.mySocket.send(send_buffer.data, send_buffer.buffer_get_pos());
}

int client_transmission_packets::cpacket_failed_action( client_struct& inputClient, std::string errorString) { //just when normal things like being unable to fill a cup because it is full!
    byte_buffer send_buffer;
    send_buffer.buffer_write_u8( 210); //packetstart magic number
    send_buffer.buffer_write_u8( inputClient.myNumber );

    send_buffer.buffer_write_u16( client_transmission_packets::failed_action);
    send_buffer.buffer_write_string( errorString);

    //transmit
    return inputClient.mySocket.send(send_buffer.data, send_buffer.buffer_get_pos());
}

int client_transmission_packets::cpacket_server_alive(client_struct& inputClient) {
    std::cout << "-Heartbeat" << std::endl;
    //construct buffer to send data
    byte_buffer send_buffer;
    send_buffer.buffer_write_u8( 210); //packetstart magic number
    send_buffer.buffer_write_u8( inputClient.myNumber ); //client number

    send_buffer.buffer_write_u16( client_transmission_packets::server_alive); //opcode

    //transmit
    return inputClient.mySocket.send(send_buffer.data, send_buffer.buffer_get_pos());
};

///inventory
//inventory_update,
//storagebox_object_update,
