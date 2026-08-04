#include <iostream>
#include <string>

#include "adapters/CanAdapter.h"


int main()
{
    std::cout << "=============================" << std::endl;
    std::cout << "   Diagnostic Engine v0.1     " << std::endl;
    std::cout << "=============================" << std::endl;


    // Création de l'adaptateur CAN
    CanAdapter canAdapter;


    // Connexion au réseau CAN
    if (canAdapter.connect())
    {
        std::cout << "[MAIN] CAN adapter connected successfully"
                  << std::endl;


        // Exemple de requête OBD-II
        // PID 0C = Engine RPM
        std::string request = "01 0C";


        // Envoi de la requête au véhicule
        if (canAdapter.sendRequest(request))
        {
            std::cout << "[MAIN] Request sent successfully"
                      << std::endl;


            // Réception de la réponse ECU
            std::string response = canAdapter.receiveResponse();


            std::cout << "[MAIN] ECU Response : "
                      << response
                      << std::endl;
        }
        else
        {
            std::cout << "[MAIN] Failed to send request"
                      << std::endl;
        }


        // Fermeture de la communication CAN
        canAdapter.disconnect();
    }
    else
    {
        std::cout << "[MAIN] CAN connection failed"
                  << std::endl;
    }


    return 0;
}