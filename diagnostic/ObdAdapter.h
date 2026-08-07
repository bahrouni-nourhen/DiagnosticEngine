#ifndef OBDADAPTER_H
#define OBDADAPTER_H


#include <vector>
#include <cstdint>


#include "../transport/IsoTpAdapter.h"
#include "../decoder/ObdResponseDecoder.h"



class ObdAdapter
{

private:

    IsoTpAdapter& isotp;
    const ObdResponseDecoder& decoder;


public:

    ObdAdapter(
        IsoTpAdapter& isoTpAdapter,
        const ObdResponseDecoder& responseDecoder
    );


    DecodedParameter readPID(
        uint8_t pid
    );


    std::vector<uint8_t> readDTC();


};


#endif