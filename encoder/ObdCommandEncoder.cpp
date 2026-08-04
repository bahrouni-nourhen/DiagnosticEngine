#include "ObdCommandEncoder.h"

std::vector<uint8_t> ObdCommandEncoder::encode(
    uint8_t mode,
    uint8_t pid
)
{
    return
    {
        mode,
        pid
    };
}