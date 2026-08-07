#ifndef PID_CATALOG_H
#define PID_CATALOG_H

#include <string>
#include <vector>
#include <cstdint>


// Une entree du catalogue = un paramètre OBD-II connu
// (correspond a un objet du fichier pid_catalog.json)
struct PidCatalogEntry
{
    std::string name;      // ex: "ENGINE_RPM"
    uint8_t     pid;        // ex: 0x0C
    uint8_t     service;    // ex: 0x01
    std::string unit;       // ex: "RPM"
    int         bytesNeeded; // combien d'octets de donnees sont necessaires
    std::string formula;    // ex: "(256*A+B)/4"
};


// PidCatalog = le "menu" des paramètres connus.
// Il charge le fichier JSON une seule fois, puis permet
// de chercher un paramètre par son PID.
class PidCatalog
{

public:

    // Charge le catalogue depuis un fichier JSON.
    // Retourne false si le fichier est introuvable ou invalide.
    bool loadFromFile(
        const std::string& filepath
    );


    // Cherche un paramètre par son PID (ex: 0x0C).
    // found = true si trouve, false sinon.
    PidCatalogEntry findByPid(
        uint8_t pid,
        bool& found
    ) const;


private:

    std::vector<PidCatalogEntry> m_entries;

};


#endif