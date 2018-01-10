#include <iostream>
#include <cstring>
#include <SFML/Network.hpp>
#include <pthread.h>
#include <chrono>  // for high_resolution_clock
#include <unistd.h> // for usleep

#include "main.h"
#include "inih/cpp/INIReader.h"

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
        std::chrono::system_clock::time_point a = std::chrono::system_clock::now();
        std::chrono::system_clock::time_point b = std::chrono::system_clock::now();

        //process server
        bool server_quit = false;
        while(server_quit == false) {
            // Maintain designated frequency of 5 Hz (200 ms per frame)
            float work_frequency = 1000/global.server_tickrate;
            a = std::chrono::system_clock::now();
            std::chrono::duration<double, std::milli> work_time = a - b;

            if (work_time.count() < work_frequency)
            {
                std::chrono::duration<double, std::milli> delta_ms(work_frequency - work_time.count());
                auto delta_ms_duration = std::chrono::duration_cast<std::chrono::milliseconds>(delta_ms);
                usleep(delta_ms_duration.count() * 1000);
            }

            b = std::chrono::system_clock::now();
            std::chrono::duration<double, std::milli> sleep_time = b - a;

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

                //handle server processing

            }

            //std::cout << "Time: " << (work_time + sleep_time).count() << std::endl;
        }
    }


    return 0;
}
