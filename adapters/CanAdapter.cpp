#include "CanAdapter.h"
#include <iostream>


// Constructeur
CanAdapter::CanAdapter()
{

}


// Destructeur
CanAdapter::~CanAdapter()
{

}


// Fonction de connexion au réseau CAN
bool CanAdapter::connect()
{
    std::cout << "[CAN] Connection established" << std::endl;

    return true;
}


// Fonction de déconnexion
void CanAdapter::disconnect()
{
    std::cout << "[CAN] Connection closed" << std::endl;
}


// Envoi d'une requête CAN
bool CanAdapter::sendRequest(const std::string& request)
{
    std::cout << "[CAN] Sending request : "
              << request
              << std::endl;


    // Simulation d'un envoi réussi
    return true;
}


// Réception d'une réponse CAN
std::string CanAdapter::receiveResponse()
{
    std::cout << "[CAN] Receiving response..." 
              << std::endl;


    // Simulation d'une réponse ECU
    // Exemple : réponse PID 0C (Engine RPM)
    return "41 0C 1A F8";
}