#ifndef OBDADAPTER_H
#define OBDADAPTER_H


#include <vector>
#include <cstdint>


#include "IsoTpAdapter.h"
#include "ObdResponseDecoder.h"



// ObdAdapter = le chef d'orchestre.
// Il utilise l'encoder pour construire la requete,
// l'ISO-TP pour la transmettre/recevoir,
// et le decoder pour interpreter la reponse.
class ObdAdapter
{

private:

    // Couche transport ISO-TP
    IsoTpAdapter& isotp;



public:

    // Constructeur
    ObdAdapter(
        IsoTpAdapter& isoTpAdapter
    );


    // Lire un PID OBD-II et retourner la valeur DEJA DECODEE
    DecodedParameter readPID(
        uint8_t pid
    );


    // Lire les codes défauts DTC (reponse brute pour l'instant,
    // le decodage DTC viendra avec le catalogue DTC)
    std::vector<uint8_t> readDTC();



};


#endif