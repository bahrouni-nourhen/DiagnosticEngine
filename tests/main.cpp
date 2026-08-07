#include <iostream>
#include <vector>

#include "adapters/CanAdapter.h"
#include "transport/IsoTpAdapter.h"
#include "diagnostic/ObdAdapter.h"
#include "decoder/ObdResponseDecoder.h"
#include "catalog/PidCatalog.h"


int main()
{
    // 1) Chargement du catalogue PID depuis le fichier JSON
    PidCatalog catalog;

if (!catalog.loadFromFile("catalog/pid_catalog.json"))    {
        std::cout << "Impossible de charger le catalogue, arret." << std::endl;
        return 1;
    }

    // 2) Construction de la chaine complete
    CanAdapter can;
    IsoTpAdapter isotp(can);
    ObdResponseDecoder decoder(catalog);
    ObdAdapter obd(isotp, decoder);

    std::cout << std::endl;
    std::cout << "=== Test avec catalogue PID (regime moteur) ===" << std::endl;

    // Le CanAdapter simule toujours la reponse 41 0C 1A F8 (PID 0C)
    DecodedParameter result = obd.readPID(0x0C);

    std::cout << std::endl;
    std::cout << "Resultat :" << std::endl;
    std::cout << "  parameter : " << result.parameter << std::endl;
    std::cout << "  value     : " << result.value << std::endl;
    std::cout << "  unit      : " << result.unit << std::endl;
    std::cout << "  status    : " << result.status << std::endl;
    std::cout << "Attendu : ENGINE_RPM = 1726 RPM, status SUCCESS" << std::endl;

    // 3) Test direct du decoder (sans passer par le transport)
    //    pour verifier d'autres PID du catalogue, avec des octets ecrits a la main
    std::cout << std::endl;
    std::cout << "=== Tests directs du decoder (autres PID) ===" << std::endl;

    std::vector<uint8_t> tempResponse   = { 0x41, 0x05, 0x5A };       // 90 -> 50 C
    std::vector<uint8_t> speedResponse  = { 0x41, 0x0D, 0x48 };       // 72 km/h
    std::vector<uint8_t> loadResponse   = { 0x41, 0x04, 0x75 };       // 117 -> ~45.88 %
    std::vector<uint8_t> unknownResponse = { 0x41, 0x99, 0x00 };      // PID inconnu

    for (auto& r : { tempResponse, speedResponse, loadResponse, unknownResponse })
    {
        DecodedParameter d = decoder.decode(r);

        std::cout << "  " << d.parameter
                   << " = " << d.value
                   << " " << d.unit
                   << " (" << d.status << ")"
                   << std::endl;
    }

    return 0;
}