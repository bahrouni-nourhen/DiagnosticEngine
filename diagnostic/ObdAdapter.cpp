#include "ObdAdapter.h"
#include "ObdCommandEncoder.h"

#include <iostream>


// Constructeur
ObdAdapter::ObdAdapter(
    IsoTpAdapter& isoTpAdapter
)
:
isotp(isoTpAdapter)
{

}



// Lecture d'un PID OBD-II
DecodedParameter ObdAdapter::readPID(
    uint8_t pid
)
{

    std::cout
        << "[OBD-II] Reading PID : 0x"
        << std::hex
        << static_cast<int>(pid)
        << std::dec
        << std::endl;


    /*
        Construction de la requete via l'encoder,
        au lieu de construire les octets a la main.

        Service 01 : Current data
    */

    const uint8_t SERVICE_CURRENT_DATA = 0x01;

    std::vector<uint8_t> request =
        ObdCommandEncoder::encode(SERVICE_CURRENT_DATA, pid);


    // Envoi vers ISO-TP
    isotp.sendMessage(request);


    // Réception de la réponse ECU (octets bruts)
    std::vector<uint8_t> response =
        isotp.receiveMessage();


    // Decodage de la reponse en valeur exploitable
    DecodedParameter decoded =
        ObdResponseDecoder::decode(response);


    return decoded;

}




// Lecture des codes défauts DTC
std::vector<uint8_t> ObdAdapter::readDTC()
{

    std::cout
        << "[OBD-II] Reading DTC..."
        << std::endl;


    /*
        Service OBD-II 03 :
        Request stored trouble codes

        Note : ObdCommandEncoder::encode() attend un PID,
        mais le service 03 n'a pas de PID a proprement parler.
        On utilise 0x00 par convention ici ; le catalogue DTC
        (a venir) fournira un encodage dedie pour ce service.
    */

    const uint8_t SERVICE_STORED_DTC = 0x03;

    std::vector<uint8_t> request =
        ObdCommandEncoder::encode(SERVICE_STORED_DTC, 0x00);


    isotp.sendMessage(request);


    return isotp.receiveMessage();

}