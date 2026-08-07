#include "ObdResponseDecoder.h"

#include <iostream>



DecodedParameter ObdResponseDecoder::decode(
    const std::vector<uint8_t>& response
)
{

    DecodedParameter result;


    // Vérification taille minimale (mode + pid)
    if(response.size() < 3)
    {
        result.status = "INVALID_RESPONSE";
        return result;
    }


    /*
        Format réponse OBD-II :

        [0] = 41  -> réponse positive Mode 01
        [1] = PID
        [2...] = Data bytes

    */


    uint8_t pid = response[1];


    result.pid = pid;



    switch(pid)
    {

        // ==========================
        // PID 0C : Engine RPM
        // Formule :
        // ((256*A)+B)/4
        // ==========================

        case 0x0C:
        {
            // Besoin de 2 octets de donnees (A et B)
            if(response.size() < 4)
            {
                result.status = "INVALID_DATA";
                break;
            }


            uint8_t A = response[2];
            uint8_t B = response[3];


            return decodeRPM(A,B);
        }



        // ==========================
        // PID 0D : Vehicle Speed
        // Formule :
        // A km/h
        // ==========================

        case 0x0D:
        {
            // Besoin d'1 octet de donnee (A)
            if(response.size() < 3)
            {
                result.status = "INVALID_DATA";
                break;
            }

            uint8_t A = response[2];


            return decodeSpeed(A);

        }



        // ==========================
        // PID 05 :
        // Coolant temperature
        //
        // Formula :
        // A - 40
        // ==========================

        case 0x05:
        {
            // Besoin d'1 octet de donnee (A)
            if(response.size() < 3)
            {
                result.status = "INVALID_DATA";
                break;
            }

            uint8_t A = response[2];


            return decodeTemperature(A);

        }



        default:
        {

            result.parameter = "UNKNOWN_PID";
            result.value = 0;
            result.unit = "";
            result.status = "UNSUPPORTED_PARAMETER";

            break;
        }

    }


    return result;

}





DecodedParameter ObdResponseDecoder::decodeRPM(
    uint8_t A,
    uint8_t B
)
{

    DecodedParameter result;


    result.pid = 0x0C;

    result.parameter = "ENGINE_RPM";


    result.value =
        ((256 * A) + B) / 4.0;


    result.unit = "RPM";


    result.status = "SUCCESS";


    return result;

}





DecodedParameter ObdResponseDecoder::decodeSpeed(
    uint8_t A
)
{

    DecodedParameter result;


    result.pid = 0x0D;


    result.parameter = "VEHICLE_SPEED";


    result.value = A;


    result.unit = "km/h";


    result.status = "SUCCESS";


    return result;

}





DecodedParameter ObdResponseDecoder::decodeTemperature(
    uint8_t A
)
{

    DecodedParameter result;


    result.pid = 0x05;


    result.parameter =
        "ENGINE_COOLANT_TEMPERATURE";


    result.value =
        A - 40;


    result.unit = "CELSIUS";


    result.status = "SUCCESS";


    return result;

}