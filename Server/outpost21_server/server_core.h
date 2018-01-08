#ifndef SERVERCORE_H
#define SERVERCORE_H

#include "client_transmit_packets.h"
#include <SFML/Network.hpp>
#include <pthread.h>

struct global_vars {
    sf::TcpListener listener;
    int server_port = 0;
    static const int server_maxplayers = 16;

    //socket threads
    pthread_t* SocketThreads[server_maxplayers];
    bool spawn_new_socket = true;

    const std::string serverdata_file_path = "server_data.ini";
};


#endif
