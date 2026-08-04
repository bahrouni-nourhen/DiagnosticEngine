#ifndef CANADAPTER_H
#define CANADAPTER_H

#include "IProtocolAdapter.h"


class CanAdapter : public IProtocolAdapter
{

public:

    CanAdapter();

    ~CanAdapter() override;


    bool connect() override;

    void disconnect() override;

    bool sendRequest(const std::string& request) override;

    std::string receiveResponse() override;

};


#endif