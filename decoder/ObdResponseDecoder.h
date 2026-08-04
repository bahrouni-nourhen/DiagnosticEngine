#ifndef OBD_RESPONSE_DECODER_H
#define OBD_RESPONSE_DECODER_H


#include <vector>
#include <cstdint>
#include <string>



struct DecodedParameter
{

    // Identifiant PID
    uint8_t pid;


    // Nom du paramètre
    std::string parameter;


    // Valeur décodée
    double value;


    // Unité
    std::string unit;


    // Etat du décodage
    std::string status;

};



class ObdResponseDecoder
{

public:


    static DecodedParameter decode(
        const std::vector<uint8_t>& response
    );



private:


    static DecodedParameter decodeRPM(
        uint8_t A,
        uint8_t B
    );


    static DecodedParameter decodeSpeed(
        uint8_t A
    );


    static DecodedParameter decodeTemperature(
        uint8_t A
    );


};


#endif