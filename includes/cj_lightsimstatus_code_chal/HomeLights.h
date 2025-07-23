//
// Created by skyse on 7/19/2025.
//

#ifndef CJ_LIGHTSIMSTATUS_CODE_CHAL_HOMELIGHTS_H
#define CJ_LIGHTSIMSTATUS_CODE_CHAL_HOMELIGHTS_H

// Standard Libraries
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <sstream>

// Local Libraries

// Third Party Libraries
#include "json_fwd.hpp"
#include "json.hpp"
#include "httplib.h"


class HomeLights {

public:
    // Constructor
    HomeLights(const std::string &host, int port);

    // Destructor
    ~HomeLights() = default;

    // Getters

    // Setters

    // Utility Methods
    bool isConnectionValid();
    void displayAllLights();
    void captureLightData();


protected:
    void extractLightIDs();

private:
    std::string myHost;
    int myPort;
    nlohmann::json lightData;
    std::vector<std::string> lightIDs;

    // API HTTP Connection
    httplib::Client client;
    httplib::Server server;
};


#endif //CJ_LIGHTSIMSTATUS_CODE_CHAL_HOMELIGHTS_H
