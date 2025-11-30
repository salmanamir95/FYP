#include "PKCertChain.h"


PKCertChain::PKCertChain()
{
    head = NULL;
    tail = NULL;
}

PKCertChain::~PKCertChain()
{
    nodeReg* temp = head;
    while(head != NULL)
    {
        head = head->nextPtr;
        delete temp;
        temp = head;
    }
}

