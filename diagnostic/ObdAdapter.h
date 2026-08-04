#ifndef OBDADAPTER_H
#define OBDADAPTER_H


#include <vector>
#include <cstdint>


#include "../transport/IsoTpAdapter.h"



class ObdAdapter
{

private:

    // Couche transport ISO-TP
    IsoTpAdapter& isotp;



public:

    // Constructeur
    ObdAdapter(
        IsoTpAdapter& isoTpAdapter
    );


    // Lire un PID OBD-II
    std::vector<uint8_t> readPID(
        uint8_t pid
    );


    // Lire les codes défauts DTC
    std::vector<uint8_t> readDTC();



};


#endif