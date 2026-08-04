#ifndef CANADAPTER_H
#define CANADAPTER_H

#include "IProtocolAdapter.h"

#include <vector>
#include <cstdint>


class CanAdapter : public IProtocolAdapter
{

public:

    // Constructeur
    CanAdapter();


    // Destructeur
    ~CanAdapter() override;


    // Ouverture de la communication CAN
    bool open() override;


    // Fermeture de la communication CAN
    void close() override;


    // Envoi d'une trame CAN
    bool send(
        const std::vector<uint8_t>& data
    ) override;


    // Réception d'une trame CAN
    std::vector<uint8_t> receive() override;


};


#endif