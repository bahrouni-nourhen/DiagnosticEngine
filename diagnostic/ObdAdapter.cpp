#include "ObdAdapter.h"

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
std::vector<uint8_t> ObdAdapter::readPID(
    uint8_t pid
)
{

    std::cout 
        << "[OBD-II] Reading PID : 0x"
        << std::hex
        << static_cast<int>(pid)
        << std::endl;



    /*
        Construction d'une requête OBD-II

        Service 01 :
        Current data

        Exemple :
        01 0C  --> Engine RPM
    */


    std::vector<uint8_t> request =
    {
        0x02,   // longueur ISO-TP (2 octets)
        0x01,   // Service Mode 01
        pid
    };



    // Envoi vers ISO-TP

    isotp.sendMessage(request);



    // Réception de la réponse ECU

    std::vector<uint8_t> response =
        isotp.receiveMessage();



    return response;

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
    */


    std::vector<uint8_t> request =
    {
        0x01,  // longueur
        0x03   // Service 03
    };



    isotp.sendMessage(request);



    return isotp.receiveMessage();

}