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


// Envoi d'une trame brute.
// Le CanAdapter ne sait pas ce que contiennent les octets,
// il les affiche juste pour debug et simule un envoi reussi.
bool CanAdapter::send(
    const std::vector<uint8_t>& data
)
{
    std::cout << "[CAN] Sending frame : ";

    for (uint8_t byte : data)
    {
        std::cout
            << std::hex
            << std::uppercase
            << std::setw(2)
            << std::setfill('0')
            << static_cast<int>(byte)
            << " ";
    }

    std::cout << std::dec << std::endl;

    return true;
}


// Reception d'une trame brute.
// Pour l'instant, on simule TOUJOURS la meme reponse
// (regime moteur), en attendant le vrai simulateur du developpeur 4.
std::vector<uint8_t> CanAdapter::receive()
{
    std::cout << "[CAN] Receiving frame..." << std::endl;

    // Reponse simulee : 41 0C 1A F8 (PID 0C, regime moteur)
    std::vector<uint8_t> response =
    {
        0x41,
        0x0C,
        0x1A,
        0xF8
    };

    return response;
}