#ifndef MAIN_H
#define MAIN_H
//=================================
// forward declared dependencies

//=================================
// included dependencies
#include <iostream>
#include <cstring>
#include <SFML/Network.hpp>
#include <pthread.h>
#include <chrono>  // for high_resolution_clock
#include <ctime> // for nanosleep

#define NANO_SECOND_MULTIPLIER  1000000  // 1 millisecond = 1,000,000 Nanoseconds

int main();


#endif
