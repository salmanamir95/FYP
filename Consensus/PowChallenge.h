#pragma once
#include <vector>
#include <cstdint>


typedef struct {
    vector<uint8_t> challenge; //32 bytes fixed
    vector<uint8_t> difficulty; //2 bytes fixed
} PowChallenge;
