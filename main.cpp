#include <iostream>
#include <vector>
#include <cstdint>
#include "encoder/ObdCommandEncoder.h"
#include "decoder/ObdResponseDecoder.h"
#include "adapters/CanAdapter.h"
#include "transport/IsoTpAdapter.h"
#include "models/CanFrame.h"



int main()
{

    std::cout << "============================="
              << std::endl;

    std::cout << " Diagnostic Engine v0.2 "
              << std::endl;

    std::cout << "============================="
              << std::endl;



    // ==========================
    // Test du modèle CanFrame
    // ==========================

    CanFrame frame(
        0x7E8,
        {0x41,0x0C,0x1A,0xF8},
        1000,
        1
    );


    std::cout << frame.toString()
              << std::endl;




    // ==========================
    // Création CAN Adapter
    // ==========================

    CanAdapter can;



    if(!can.open())
    {
        std::cout << "[MAIN] CAN opening failed"
                  << std::endl;

        return -1;
    }

std::vector<uint8_t> rpmResponse =
    {
        0x41,
        0x0C,
        0x1A,
        0xF8
    };


    DecodedParameter rpm =
        ObdResponseDecoder::decode(rpmResponse);



    std::cout
        << "Parameter : "
        << rpm.parameter
        << std::endl;


    std::cout
        << "Value : "
        << rpm.value
        << " "
        << rpm.unit
        << std::endl;


    std::cout
        << "Status : "
        << rpm.status
        << std::endl;

    // ==========================
    // Couche ISO-TP
    // ==========================

    IsoTpAdapter isotp(can);



    // Requête OBD-II :
    // Service 01 PID 0C (RPM)

    std::vector<uint8_t> request =
    {
        0x02,
        0x01,
        0x0C
    };



    if(isotp.sendMessage(request))
    {
        std::cout 
            << "[MAIN] ISO-TP message sent"
            << std::endl;
    }

std::vector<uint8_t> command =
    ObdCommandEncoder::encode(0x01, 0x0C);

std::cout << "Commande OBD : ";

for (uint8_t byte : command)
{
    printf("%02X ", byte);
}

std::cout << std::endl;

    std::vector<uint8_t> response =
        isotp.receiveMessage();



    std::cout
        << "[MAIN] ECU Response size : "
        << response.size()
        << " bytes"
        << std::endl;



    can.close();



    return 0;
}