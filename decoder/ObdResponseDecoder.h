#ifndef OBD_RESPONSE_DECODER_H
#define OBD_RESPONSE_DECODER_H


#include <vector>
#include <cstdint>
#include <string>

#include "PidCatalog.h"


struct DecodedParameter
{
    uint8_t     pid;
    std::string parameter;
    double      value;
    std::string unit;
    std::string status;
};


// ObdResponseDecoder = decode une reponse brute en utilisant
// le catalogue PID (formules chargees depuis le JSON),
// au lieu d'un switch code en dur.
class ObdResponseDecoder
{

public:

    // Le decoder a besoin du catalogue pour savoir comment
    // interpreter chaque PID.
    explicit ObdResponseDecoder(
        const PidCatalog& catalog
    );


    DecodedParameter decode(
        const std::vector<uint8_t>& response
    ) const;


private:

    const PidCatalog& m_catalog;

};


#endif