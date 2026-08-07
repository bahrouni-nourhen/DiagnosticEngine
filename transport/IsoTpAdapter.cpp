#include "IsoTpAdapter.h"

#include <iostream>


// Constructeur
IsoTpAdapter::IsoTpAdapter(
    CanAdapter& canAdapter
)
:
can(canAdapter)
{

}


// Envoi d'un message ISO-TP
bool IsoTpAdapter::sendMessage(
    const std::vector<uint8_t>& data
)
{

    std::cout
        << "[ISO-TP] Sending message..."
        << std::endl;


    /*
        Pour cette première version :
        on transmet directement les données
        vers la couche CAN.

        La segmentation ISO-TP réelle
        sera ajoutée ensuite.
    */

    return can.send(data);

}


// Réception d'un message ISO-TP
std::vector<uint8_t> IsoTpAdapter::receiveMessage()
{

    std::cout
        << "[ISO-TP] Receiving message..."
        << std::endl;


    /*
        Pour cette première version :
        on récupère directement la trame
        reçue par CAN.

        Plus tard :
        - assemblage des frames
        - gestion First Frame
        - gestion Consecutive Frame
    */


    return can.receive();

}