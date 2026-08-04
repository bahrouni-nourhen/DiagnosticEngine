#ifndef IPROTOCOLADAPTER_H
#define IPROTOCOLADAPTER_H

#include <string>


class IProtocolAdapter
{

public:

    virtual ~IProtocolAdapter() = default;


    // Établir la connexion avec le réseau/protocole
    virtual bool connect() = 0;


    // Fermer la connexion
    virtual void disconnect() = 0;


    // Envoyer une requête de diagnostic
    virtual bool sendRequest(const std::string& request) = 0;


    // Recevoir la réponse du véhicule
    virtual std::string receiveResponse() = 0;


};


#endif