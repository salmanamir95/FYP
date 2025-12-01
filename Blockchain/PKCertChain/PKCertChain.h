#pragma once
#include <Blockchain/PKCertChain/nodeReg.h>

class PKCertChain{
public:
    nodeReg* head;
    nodeReg* tail;

    PKCertChain();
    ~PKCertChain();
};
