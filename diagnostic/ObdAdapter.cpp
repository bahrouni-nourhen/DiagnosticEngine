#include "ObdAdapter.h"
#include "../encoder/ObdCommandEncoder.h"

#include <iostream>


ObdAdapter::ObdAdapter(
    IsoTpAdapter& isoTpAdapter,
    const ObdResponseDecoder& responseDecoder
)
:
isotp(isoTpAdapter),
decoder(responseDecoder)
{

}


DecodedParameter ObdAdapter::readPID(
    uint8_t pid
)
{
    std::cout
        << "[OBD-II] Reading PID : 0x"
        << std::hex
        << static_cast<int>(pid)
        << std::dec
        << std::endl;

    const uint8_t SERVICE_CURRENT_DATA = 0x01;

    std::vector<uint8_t> request =
        ObdCommandEncoder::encode(SERVICE_CURRENT_DATA, pid);

    isotp.sendMessage(request);

    std::vector<uint8_t> response =
        isotp.receiveMessage();

    // Decodage via le catalogue (formule chargee depuis le JSON)
    DecodedParameter decoded =
        decoder.decode(response);

    return decoded;
}


std::vector<uint8_t> ObdAdapter::readDTC()
{
    std::cout
        << "[OBD-II] Reading DTC..."
        << std::endl;

    const uint8_t SERVICE_STORED_DTC = 0x03;

    std::vector<uint8_t> request =
        ObdCommandEncoder::encode(SERVICE_STORED_DTC, 0x00);

    isotp.sendMessage(request);

    return isotp.receiveMessage();
}