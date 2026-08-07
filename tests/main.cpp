#include "CanAdapter.h"
#include "IsoTpAdapter.h"
#include "ObdAdapter.h"

#include <iostream>


int main()
{
    // Construction de la chaine complete, couche par couche
    CanAdapter can;
    IsoTpAdapter isotp(can);
    ObdAdapter obd(isotp);

    std::cout << "=== Test de la chaine complete OBD-II ===" << std::endl;
    std::cout << std::endl;

    // Lecture du PID 0x0C (regime moteur)
    // Le CanAdapter simule toujours la reponse 41 0C 1A F8
    DecodedParameter result = obd.readPID(0x0C);

    std::cout << std::endl;
    std::cout << "Resultat final :" << std::endl;
    std::cout << "  parameter : " << result.parameter << std::endl;
    std::cout << "  value     : " << result.value << std::endl;
    std::cout << "  unit      : " << result.unit << std::endl;
    std::cout << "  status    : " << result.status << std::endl;
    std::cout << std::endl;
    std::cout << "Attendu : ENGINE_RPM = 1726 RPM, status SUCCESS" << std::endl;

    return 0;
}