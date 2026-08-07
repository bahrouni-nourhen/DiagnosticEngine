#ifndef CANADAPTER_H
#define CANADAPTER_H

#include <vector>
#include <cstdint>


// CanAdapter = couche transport CAN "brute".
// Il ne connait AUCUN PID, AUCUNE formule.
// Il envoie et recoit des octets, c'est tout.
// (Il joue ici le role d'un connecteur simule, en attendant
// le vrai VehicleConnector du developpeur 1.)
class CanAdapter
{

public:

    // Constructeur
    CanAdapter();


    // Destructeur
    ~CanAdapter();


    // Envoi d'une trame brute (octets purs, sans interpretation)
    bool send(
        const std::vector<uint8_t>& data
    );


    // Reception d'une trame brute (octets purs, sans interpretation)
    std::vector<uint8_t> receive();


};


#endif