#ifndef CANFRAME_H
#define CANFRAME_H

#include <cstdint>
#include <vector>
#include <string>


class CanFrame
{

private:

    uint32_t id;                 // Identifiant CAN
    std::vector<uint8_t> data;   // Données CAN (0 à 8 octets)
    uint64_t timestamp;          // Temps de réception
    uint8_t channel;             // Canal CAN utilisé


public:

    // Constructeur
    CanFrame(
        uint32_t id,
        const std::vector<uint8_t>& data,
        uint64_t timestamp,
        uint8_t channel
    );


    // Accesseurs

    uint32_t getId() const;


    const std::vector<uint8_t>& getData() const;


    uint64_t getTimestamp() const;


    uint8_t getChannel() const;


    // Informations affichage/debug

    std::string toString() const;


};

#endif