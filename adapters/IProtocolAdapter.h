#ifndef IPROTOCOLADAPTER_H
#define IPROTOCOLADAPTER_H

#include <vector>
#include <cstdint>
#include <string>


// Une trame prête à être transmise.
// Le développeur 1 (connecteur) s'occupera de l'envoi physique réel.
struct ProtocolRequest
{
    std::vector<uint8_t> rawData;
};


// Résultat du décodage d'une réponse brute reçue du véhicule.
struct DecodedValue
{
    std::string parameterId;   // ex: "ENGINE_RPM"
    double      value = 0.0;
    std::string unit;          // ex: "RPM", "CELSIUS"
    std::string status;        // ex: "SUCCESS", "UNSUPPORTED_PARAMETER", "ERROR"
};


class IProtocolAdapter
{

public:

    virtual ~IProtocolAdapter() = default;


    // Construit une trame brute à partir d'un identifiant de paramètre lisible.
    // Exemple : "ENGINE_RPM" -> { 0x01, 0x0C }
    virtual ProtocolRequest encodeRequest(
        const std::string& parameterId
    ) = 0;


    // Décode une trame brute déjà reçue par le connecteur (développeur 1)
    // et retourne une valeur exploitable.
    // Exemple : { 0x41, 0x0C, 0x1A, 0xF8 } -> ENGINE_RPM = 1726 RPM
    virtual DecodedValue decodeResponse(
        const std::vector<uint8_t>& rawResponse
    ) = 0;


    // Nom du protocole, utile pour les logs et le debug.
    // Exemple : "OBD-II", "CAN", "ISO-TP"
    virtual std::string protocolName() const = 0;

};


#endif