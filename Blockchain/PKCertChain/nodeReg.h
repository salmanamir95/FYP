#pragma once
#include <iostream>
#include <array>
#include <ctime>
#include <vector>
#include <chrono>
#include "certificate.h"
using namespace std;

class nodeReg{
public:
    array<uint8_t,32> prevHash;
    array<uint8_t,32> nextHash;
    array<uint8_t,32> blockHash;
    
    vector<uint8_t> randomNumber;
    vector<uint8_t> nonce;   // N from PoW
    uint16_t difficulty;          // T
    time_t timestamp;
    
    nodeReg* nextPtr;
    nodeReg* prevPtr;
    certificate cert;
};