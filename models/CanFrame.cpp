#include "CanFrame.h"
#include <sstream>
#include <iomanip>


CanFrame::CanFrame(
    uint32_t id,
    const std::vector<uint8_t>& data,
    uint64_t timestamp,
    uint8_t channel
)
{
    this->id = id;
    this->data = data;
    this->timestamp = timestamp;
    this->channel = channel;
}



uint32_t CanFrame::getId() const
{
    return id;
}



const std::vector<uint8_t>& CanFrame::getData() const
{
    return data;
}



uint64_t CanFrame::getTimestamp() const
{
    return timestamp;
}



uint8_t CanFrame::getChannel() const
{
    return channel;
}



std::string CanFrame::toString() const
{

    std::stringstream ss;


    ss << "CAN ID: 0x"
       << std::hex
       << id
       << " DATA: ";


    for(uint8_t byte : data)
    {
        ss << std::setw(2)
           << std::setfill('0')
           << static_cast<int>(byte)
           << " ";
    }


    ss << "CHANNEL: "
       << std::dec
       << static_cast<int>(channel);


    return ss.str();
}