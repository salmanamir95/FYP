#include <iostream>
#include <array>
#include <ctime>
#include <vector>
#include <chrono>
using namespace std;

class certificate{
    uint16_t nodeID;
    array<uint8_t,32> publicKey;
    array<uint8_t,64> signature;
    time_t notBefore;
    time_t notAfter;
};
