#include "certificate.h"
#include "nodeReg.h"
#include "../Consensus/PoW.h"
using namespace std;

class nodeReg{
public:
    array<uint8_t,32> prevHash;
    array<uint8_t,32> nextHash;
    array<uint8_t,32> blockHash;
    
    vector<uint8_t> nonce;   // N from PoW
    uint16_t difficulty;          // T
    time_t timestamp;
    
    nodeReg* nextPtr;
    nodeReg* prevPtr;
    certificate cert;
};

class PKCertChain{
public:
    nodeReg* head;
    nodeReg* tail;

    


    PKCertChain();



    ~PKCertChain();
};

