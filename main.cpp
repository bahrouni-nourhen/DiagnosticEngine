#include <iostream>
#include <vector>
#include <cstdint>
#include "diagnostic/ObdAdapter.h"

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
// Création de la couche OBD-II
ObdAdapter obd(isotp);


// Lecture du PID RPM (0x0C)

std::vector<uint8_t> response =
    obd.readPID(0x0C);


std::cout
    << "[MAIN] ECU Response size : "
    << response.size()
    << " bytes"
    << std::endl;



    std::cout 
        << "[MAIN] ECU Response size : "
        << response.size()
        << " bytes"
        << std::endl;



    // Fermeture CAN

    can.close();



    return 0;
}