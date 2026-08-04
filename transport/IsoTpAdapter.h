#ifndef ISOTPADAPTER_H
#define ISOTPADAPTER_H


#include <vector>
#include <cstdint>

#include "../adapters/CanAdapter.h"



class IsoTpAdapter
{

private:

    // Référence vers la couche CAN
    CanAdapter& can;


public:

    // Constructeur
    IsoTpAdapter(
        CanAdapter& canAdapter
    );


    // Envoyer un message ISO-TP
    bool sendMessage(
        const std::vector<uint8_t>& data
    );


    // Recevoir un message ISO-TP
    std::vector<uint8_t> receiveMessage();


};


#endif