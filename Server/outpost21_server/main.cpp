#include <iostream>
#include <cstring>
#include <SFML/Network.hpp>

#include "main.h"
#include "inih/cpp/INIReader.h"
#include <pthread.h>

//just gonna have this so porting the older code will be easy. Mostly just server configs all loaded in one place.
global_vars global;


int main()
{


    // bind the listener to a port
    std::string get_port = "2727";
    std::cout << "Port" << std::endl;
    std::cin >> get_port;
    global.server_port = stoi(get_port);

    //clean out clients
    for (int i = 0; i < global.server_maxplayers; i++)
    {
        global.SocketThreads[i] = nullptr;
    }

    if (global.listener.listen( global.server_port ) != sf::Socket::Done)
        {
            // error...
        }
        else
        {
        bool server_quit = false;
        while(server_quit == false) {
            //handle new clients!
            if(global.spawn_new_socket == true) {

                global.spawn_new_socket = false;

                for (int i = 0; i < global.server_maxplayers+1; i++)
                {
                    if(i < global.server_maxplayers) {
                        if(global.SocketThreads[i] == nullptr) {
                            global.SocketThreads[i] = new pthread_t;
                            pthread_create(global.SocketThreads[i], NULL, &server_recieving_packets::serverProcessLoop, (void *)i);
                            break;
                        }
                    }
                    else
                    {
                        std::cout << "Failed to create new socket, max players reached!" << std::endl;
                    }
                }
            }
        }

        //handle server processing!


    }


    return 0;
}
