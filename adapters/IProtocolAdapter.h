#ifndef IPROTOCOLADAPTER_H
#define IPROTOCOLADAPTER_H

#include <vector>
#include <cstdint>


class IProtocolAdapter
{

public:

    virtual ~IProtocolAdapter() = default;


    // Ouverture de la communication
    virtual bool open() = 0;


    // Fermeture de la communication
    virtual void close() = 0;


    // Envoi d'une trame brute
    virtual bool send(
        const std::vector<uint8_t>& data
    ) = 0;


    // Réception d'une trame brute
    virtual std::vector<uint8_t> receive() = 0;


};


#endif