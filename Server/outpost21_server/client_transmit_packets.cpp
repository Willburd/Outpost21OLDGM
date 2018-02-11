#include "server_core.h"
#include "byte_buffer.h"
#include "client_transmit_packets.h"
#include <math.h>

//mostly debugging tool
void queueCurrentPacket(client_struct& inputClient, byte_buffer* inputbuff) {
    inputClient.packetQueue.push_back(inputbuff);
}


byte_buffer* client_transmission_packets::cPacket_request_seen(client_struct& inputClient) {
    //construct buffer to send data
    byte_buffer* send_buffer = new byte_buffer;
    send_buffer->buffer_write_u8( 210); //packetstart magic number
    send_buffer->buffer_write_u8( inputClient.myNumber); //client number

    send_buffer->buffer_write_u16( client_transmission_packets::request_seen); //opcode

    //transmit
    std::cout << "Pushed packet type: request seen" << std::endl;
    queueCurrentPacket( inputClient, send_buffer);
    return send_buffer;
}

byte_buffer* client_transmission_packets::cpacket_login_newuser(client_struct& inputClient, std::string nameUsed, std::string hashUsed) {
    //construct buffer to send data
    byte_buffer* send_buffer = new byte_buffer;
    send_buffer->buffer_write_u8( 210); //packetstart magic number
    send_buffer->buffer_write_u8( inputClient.myNumber); //client number

    send_buffer->buffer_write_u16( client_transmission_packets::login_newuser); //opcode
    send_buffer->buffer_write_string( nameUsed);
    send_buffer->buffer_write_string( hashUsed);

    //transmit
    std::cout << "Pushed packet type: login new" << std::endl;
    queueCurrentPacket( inputClient, send_buffer);
    return send_buffer;
}

byte_buffer* client_transmission_packets::cPacket_login_failed(client_struct& inputClient, std::string nameUsed) {
    //construct buffer to send data
    byte_buffer* send_buffer = new byte_buffer;
    send_buffer->buffer_write_u8( 210); //packetstart magic number
    send_buffer->buffer_write_u8( inputClient.myNumber); //client number

    send_buffer->buffer_write_u16( client_transmission_packets::login_failed); //opcode
    send_buffer->buffer_write_string( nameUsed);

    //transmit
    std::cout << "Pushed packet type: login fail" << std::endl;
    queueCurrentPacket( inputClient, send_buffer);
    return send_buffer;
}

byte_buffer* client_transmission_packets::cPacket_login_success(client_struct& inputClient, std::string nameUsed) {
    //construct buffer to send data
    byte_buffer* send_buffer = new byte_buffer;
    send_buffer->buffer_write_u8( 210); //packetstart magic number
    send_buffer->buffer_write_u8( inputClient.myNumber); //client number

    send_buffer->buffer_write_u16( client_transmission_packets::login_success); //opcode
    send_buffer->buffer_write_string( nameUsed);

    //transmit
    std::cout << "Pushed packet type: login success" << std::endl;
    queueCurrentPacket( inputClient, send_buffer);
    return send_buffer;
}

byte_buffer* client_transmission_packets::cpacket_character_transmit_data(client_struct& inputClient, std::string jsonStringOfEntity) {
    //construct buffer to send data
    byte_buffer* send_buffer = new byte_buffer;
    send_buffer->buffer_write_u8( 210); //packetstart magic number
    send_buffer->buffer_write_u8( inputClient.myNumber); //client number

    send_buffer->buffer_write_u16( client_transmission_packets::character_transmit_data); //opcode
    send_buffer->buffer_write_string( jsonStringOfEntity);

    //transmit
    std::cout << "Pushed packet type: char TX" << std::endl;
    queueCurrentPacket( inputClient, send_buffer);
    return send_buffer;
}

byte_buffer* client_transmission_packets::cpacket_map_object_load(client_struct& inputClient,mapConstruction* inputConstruction){
    //construct buffer to send data
    byte_buffer* send_buffer = new byte_buffer;
    send_buffer->buffer_write_u8( 210); //packetstart magic number
    send_buffer->buffer_write_u8( inputClient.myNumber); //client number

    send_buffer->buffer_write_u16( client_transmission_packets::map_object_load); //opcode
    send_buffer->buffer_write_u16( inputConstruction->map_entity); //map entity id map
    send_buffer->buffer_write_u16( serverObj.getIndexOfAsset( inputConstruction->obj)); //object index
    send_buffer->buffer_write_u16( inputClient.mapDownloadQueue.size() ); //current size of buffer being sent
    send_buffer->buffer_write_f32( inputConstruction->x); //x
    send_buffer->buffer_write_f32( inputConstruction->y); //y
    send_buffer->buffer_write_u8 ( inputConstruction->health); //wall hp
    send_buffer->buffer_write_u16( (int)floor((fmod(inputConstruction->angle,360) /360)*65534) ); //direction

    //transmit
    std::cout << "Pushed packet type: map object load" << std::endl;
    queueCurrentPacket( inputClient, send_buffer);
    return send_buffer;
}

byte_buffer* client_transmission_packets::cpacket_map_object_drop(client_struct& inputClient,mapConstruction* inputConstruction){
    //construct buffer to send data
    byte_buffer* send_buffer = new byte_buffer;
    send_buffer->buffer_write_u8( 210); //packetstart magic number
    send_buffer->buffer_write_u8( inputClient.myNumber); //client number

    send_buffer->buffer_write_u16( client_transmission_packets::map_object_drop); //opcode
    send_buffer->buffer_write_u16( inputConstruction->map_entity); //map entity id
    send_buffer->buffer_write_f32( inputConstruction->x); //x
    send_buffer->buffer_write_f32( inputConstruction->y); //y

    //transmit
    std::cout << "Pushed packet type: map object drop" << std::endl;
    queueCurrentPacket( inputClient, send_buffer);
    return send_buffer;
}

//map_security_reply,
//map_door_open,
//map_door_security_reply,
///character locking
byte_buffer* client_transmission_packets::cpacket_character_lock(client_struct& inputClient, int input_EntityNumber) {
    //construct buffer to send data
    byte_buffer* send_buffer = new byte_buffer;
    send_buffer->buffer_write_u8( 210); //packetstart magic number
    send_buffer->buffer_write_u8( inputClient.myNumber); //client number

    send_buffer->buffer_write_u16( client_transmission_packets::character_locked);
    send_buffer->buffer_write_u32( input_EntityNumber);

    //transmit
    std::cout << "Pushed packet type: char lock" << std::endl;
    queueCurrentPacket( inputClient, send_buffer);
    return send_buffer;
}

byte_buffer* client_transmission_packets::cpacket_playerentity_return( client_struct& inputClient, int input_EntityNumber, int get_object_index, double get_x, double get_y, bool get_hide) {
    byte_buffer* send_buffer = new byte_buffer;
    send_buffer->buffer_write_u8( 210); //packetstart magic number
    send_buffer->buffer_write_u8( inputClient.myNumber); //client number

    send_buffer->buffer_write_u16( client_transmission_packets::player_entity_return);
    send_buffer->buffer_write_u32( input_EntityNumber);
    send_buffer->buffer_write_u16( get_object_index);
    send_buffer->buffer_write_f32( get_x);
    send_buffer->buffer_write_f32( get_y);
    send_buffer->buffer_write_u8( get_hide);

    //transmit
    std::cout << "Pushed packet type: player ent return" << std::endl;
    queueCurrentPacket( inputClient, send_buffer);
    return send_buffer;
}

//player_security_reply,
//movement_location_sync,
///entities
byte_buffer* client_transmission_packets::cpacket_entity_load(client_struct& inputClient, int input_EntityNumber, int send_object_index, double send_x, double send_y, float send_direction, double send_speed, bool send_constructflag , int send_depth_modifier) {
    //construct buffer to send data
    byte_buffer* send_buffer = new byte_buffer;
    send_buffer->buffer_write_u8( 210); //packetstart magic number
    send_buffer->buffer_write_u8( inputClient.myNumber );

    send_buffer->buffer_write_u16( client_transmission_packets::entity_load);
    send_buffer->buffer_write_u32( input_EntityNumber); //entity id
    send_buffer->buffer_write_u16( send_object_index); //object index
    send_buffer->buffer_write_f32( send_x); //x
    send_buffer->buffer_write_f32( send_y); //y
    send_buffer->buffer_write_u16( floor((((int)send_direction % 360) /360)*65534) ); //direction
    send_buffer->buffer_write_u16( send_speed); //speed
    send_buffer->buffer_write_u8( send_constructflag); //construct
    send_buffer->buffer_write_s16( send_depth_modifier); //depth modifier, used by stuff like tables to do unique draw depths

    //transmit
    std::cout << "Pushed packet type: entity load" << std::endl;
    queueCurrentPacket( inputClient, send_buffer);
    return send_buffer;
}

byte_buffer* client_transmission_packets::cpacket_entity_drop(client_struct& inputClient, int input_EntityNumber) {
    //construct buffer to send data
    byte_buffer* send_buffer = new byte_buffer;
    send_buffer->buffer_write_u8( 210); //packetstart magic number
    send_buffer->buffer_write_u8( inputClient.myNumber );

    send_buffer->buffer_write_u16( client_transmission_packets::entity_drop);
    send_buffer->buffer_write_u32( input_EntityNumber );

    //transmit
    std::cout << "Pushed packet type: entity drop" << std::endl;
    queueCurrentPacket( inputClient, send_buffer);
    return send_buffer;
}

byte_buffer* client_transmission_packets::cpacket_entity_reply(client_struct& inputClient, int input_EntityNumber, int resend_instance_id, std::string replyDataString, unsigned int mode_flag, bool is_object_else_is_index) {
    //construct buffer to send data
    byte_buffer* send_buffer = new byte_buffer;
    send_buffer->buffer_write_u8( 210); //packetstart magic number
    send_buffer->buffer_write_u8( inputClient.myNumber );

    send_buffer->buffer_write_u16( client_transmission_packets::entity_reply);
    send_buffer->buffer_write_u32( input_EntityNumber);
    send_buffer->buffer_write_s32( resend_instance_id);
    send_buffer->buffer_write_string( replyDataString);
    send_buffer->buffer_write_u8( mode_flag);
    send_buffer->buffer_write_u8( is_object_else_is_index);

    //transmit
    std::cout << "Pushed packet type: entity reply" << std::endl;
    queueCurrentPacket( inputClient, send_buffer);
    return send_buffer;
}

//entity_activate,
byte_buffer* client_transmission_packets::cpacket_entity_grab_update(client_struct& inputClient, int input_EntityNumber) {
    //construct buffer to send data
    byte_buffer* send_buffer = new byte_buffer;
    send_buffer->buffer_write_u8( 210); //packetstart magic number
    send_buffer->buffer_write_u8( inputClient.myNumber );

    send_buffer->buffer_write_u16( client_transmission_packets::entity_grab_update);
    send_buffer->buffer_write_u32( input_EntityNumber );

    //transmit
    std::cout << "Pushed packet type: entity grab update" << std::endl;
    queueCurrentPacket( inputClient, send_buffer);
    return send_buffer;
}

///misc
byte_buffer* client_transmission_packets::cpacket_force_reset( client_struct& inputClient, std::string errorString) {
    byte_buffer* send_buffer = new byte_buffer;
    send_buffer->buffer_write_u8( 210); //packetstart magic number
    send_buffer->buffer_write_u8( inputClient.myNumber );

    send_buffer->buffer_write_u16( client_transmission_packets::force_reset);
    send_buffer->buffer_write_string( errorString);

    //transmit
    std::cout << "Pushed packet type: force reset" << std::endl;
    queueCurrentPacket( inputClient, send_buffer);
    return send_buffer;
}

byte_buffer* client_transmission_packets::cpacket_failed_action( client_struct& inputClient, std::string errorString) { //just when normal things like being unable to fill a cup because it is full!
    byte_buffer* send_buffer = new byte_buffer;
    send_buffer->buffer_write_u8( 210); //packetstart magic number
    send_buffer->buffer_write_u8( inputClient.myNumber );

    send_buffer->buffer_write_u16( client_transmission_packets::failed_action);
    send_buffer->buffer_write_string( errorString);

    //transmit
    std::cout << "Pushed packet type: failed action" << std::endl;
    queueCurrentPacket( inputClient, send_buffer);
    return send_buffer;
}

byte_buffer* client_transmission_packets::cpacket_server_alive(client_struct& inputClient) {
    std::cout << "-Heartbeat" << std::endl;
    //construct buffer to send data
    byte_buffer* send_buffer = new byte_buffer;
    send_buffer->buffer_write_u8( 210); //packetstart magic number
    send_buffer->buffer_write_u8( inputClient.myNumber ); //client number

    send_buffer->buffer_write_u16( client_transmission_packets::server_alive); //opcode

    //transmit
    queueCurrentPacket( inputClient, send_buffer);
    return send_buffer;
}

///inventory
//inventory_update,
//storagebox_object_update,
