#ifndef OBDCOMMANDENCODER_H
#define OBDCOMMANDENCODER_H

#include <vector>
#include <cstdint>

class ObdCommandEncoder
{
public:

    static std::vector<uint8_t> encode(
        uint8_t mode,
        uint8_t pid
    );
};

#endif