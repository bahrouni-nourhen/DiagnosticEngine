#include "CanAdapter.h"
#include <iostream>
#include <iomanip>


// Constructeur
CanAdapter::CanAdapter()
{

}


// Destructeur
CanAdapter::~CanAdapter()
{

}


// Ouverture de la communication CAN
bool CanAdapter::open()
{
    std::cout << "[CAN] Communication opened"
              << std::endl;

    return true;
}


// Fermeture de la communication CAN
void CanAdapter::close()
{
    std::cout << "[CAN] Communication closed"
              << std::endl;
}


// Envoi d'une trame CAN
bool CanAdapter::send(
    const std::vector<uint8_t>& data
)
{
    std::cout << "[CAN] Sending frame : ";

    for(uint8_t byte : data)
    {
        std::cout 
            << std::hex
            << std::uppercase
            << std::setw(2)
            << std::setfill('0')
            << static_cast<int>(byte)
            << " ";
    }

    std::cout << std::endl;


    // Simulation d'un envoi réussi
    return true;
}


// Réception d'une trame CAN
std::vector<uint8_t> CanAdapter::receive()
{
    std::cout << "[CAN] Receiving frame..."
              << std::endl;


    // Simulation d'une réponse ECU
    // Réponse OBD-II PID 0C (Engine RPM)

    std::vector<uint8_t> response =
    {
        0x41,
        0x0C,
        0x1A,
        0xF8
    };


    return response;
}