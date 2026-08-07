#include "ObdResponseDecoder.h"
#include "FormulaEvaluator.h"

#include <iostream>


ObdResponseDecoder::ObdResponseDecoder(
    const PidCatalog& catalog
)
:
m_catalog(catalog)
{

}


DecodedParameter ObdResponseDecoder::decode(
    const std::vector<uint8_t>& response
) const
{
    DecodedParameter result;

    // Verification taille minimale (mode + pid)
    if (response.size() < 3)
    {
        result.status = "INVALID_RESPONSE";
        return result;
    }

    /*
        Format reponse OBD-II :
        [0] = 41  -> reponse positive Mode 01
        [1] = PID
        [2...] = Data bytes
    */

    uint8_t pid = response[1];
    result.pid = pid;

    // On cherche ce PID dans le catalogue
    bool found = false;

    PidCatalogEntry entry = m_catalog.findByPid(pid, found);

    if (!found)
    {
        result.parameter = "UNKNOWN_PID";
        result.value       = 0;
        result.unit         = "";
        result.status        = "UNSUPPORTED_PARAMETER";
        return result;
    }

    // Verification qu'on a assez d'octets de donnees
    // (2 octets d'en-tete + le nombre d'octets requis par ce PID)
    size_t requiredSize = 2 + entry.bytesNeeded;

    if (response.size() < requiredSize)
    {
        result.status = "INVALID_DATA";
        return result;
    }

    // Recuperation de A (et B si necessaire)
    double A = response[2];
    double B = (entry.bytesNeeded >= 2) ? response[3] : 0.0;

    // Application de la formule du catalogue
    double value = 0.0;

    try
    {
        value = FormulaEvaluator::evaluate(entry.formula, A, B);
    }
    catch (const std::exception& e)
    {
        std::cout << "[ObdResponseDecoder] Erreur formule : "
                  << e.what()
                  << std::endl;

        result.status = "FORMULA_ERROR";
        return result;
    }

    result.parameter = entry.name;
    result.value       = value;
    result.unit         = entry.unit;
    result.status        = "SUCCESS";

    return result;
}