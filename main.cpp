#include <iostream>
#include <vector>
#include <cstdint>


#include "adapters/CanAdapter.h"
#include "transport/IsoTpAdapter.h"



int main()
{

    std::cout << "============================="
              << std::endl;

    std::cout << " Diagnostic Engine v0.2 "
              << std::endl;

    std::cout << "============================="
              << std::endl;



    // Création de l'adaptateur CAN
    CanAdapter can;



    // Ouverture communication CAN
    if(!can.open())
    {
        std::cout << "[MAIN] CAN opening failed"
                  << std::endl;

        return -1;
    }



    // Création de la couche ISO-TP
    IsoTpAdapter isotp(can);



    // Exemple de requête OBD-II
    // Service 01 - PID 0C (Engine RPM)

    std::vector<uint8_t> request =
    {
        0x02,
        0x01,
        0x0C
    };



    // Envoi via ISO-TP

    if(isotp.sendMessage(request))
    {
        std::cout 
            << "[MAIN] ISO-TP message sent"
            << std::endl;
    }



    // Réception réponse ECU

    std::vector<uint8_t> response =
        isotp.receiveMessage();



    std::cout 
        << "[MAIN] ECU Response size : "
        << response.size()
        << " bytes"
        << std::endl;



    // Fermeture CAN

    can.close();



    return 0;
}