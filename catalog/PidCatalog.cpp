#include "PidCatalog.h"
#include "json.hpp"

#include <fstream>
#include <iostream>


using json = nlohmann::json;


// Convertit une chaine hexadecimale ("0C") en entier (0x0C)
static uint8_t hexStringToByte(const std::string& hex)
{
    return static_cast<uint8_t>(std::stoi(hex, nullptr, 16));
}


bool PidCatalog::loadFromFile(
    const std::string& filepath
)
{
    std::ifstream file(filepath);

    if (!file.is_open())
    {
        std::cout << "[PidCatalog] Impossible d'ouvrir : "
                  << filepath
                  << std::endl;

        return false;
    }

    json data;

    try
    {
        file >> data;
    }
    catch (const std::exception& e)
    {
        std::cout << "[PidCatalog] Erreur de parsing JSON : "
                  << e.what()
                  << std::endl;

        return false;
    }

    m_entries.clear();

    for (const auto& item : data["pids"])
    {
        PidCatalogEntry entry;

        entry.name        = item.at("name").get<std::string>();
        entry.pid          = hexStringToByte(item.at("pid").get<std::string>());
        entry.service       = hexStringToByte(item.at("service").get<std::string>());
        entry.unit           = item.at("unit").get<std::string>();
        entry.bytesNeeded  = item.at("bytes").get<int>();
        entry.formula       = item.at("formula").get<std::string>();

        m_entries.push_back(entry);
    }

    std::cout << "[PidCatalog] "
              << m_entries.size()
              << " parametres charges depuis "
              << filepath
              << std::endl;

    return true;
}


PidCatalogEntry PidCatalog::findByPid(
    uint8_t pid,
    bool& found
) const
{
    for (const auto& entry : m_entries)
    {
        if (entry.pid == pid)
        {
            found = true;
            return entry;
        }
    }

    found = false;
    return PidCatalogEntry{};
}