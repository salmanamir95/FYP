#include <iostream>
#include <stdint.h>
#include "../Blockchain/nodeReg.h"
#include "Serialize.h"
#include "Hash.h"
#include "CSPRNG.h"
using namespace std;


typedef struct {
    vector<uint8_t> challenge; //32 bytes fixed
    vector<uint8_t> difficulty; //2 bytes fixed
} PowChallenge;

PowChallenge* GeneratePoWChallenge(nodeReg* prevBlock , uint16_t& id, array<uint8_t,32> publicKey, array<uint8_t, 64> signature);
PoWChallenge* SolvePowChallenge(PowChallenge& challenge);