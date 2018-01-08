#ifndef CLIENTSTRUCT_H
#define CLIENTSTRUCT_H

#include <SFML/Network.hpp>

struct client_struct {
    sf::TcpSocket mySocket;
    int myNumber = -1;
};

#endif
