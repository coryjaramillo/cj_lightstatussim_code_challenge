//
// Created by Cory Jaramillo on 7/19/2025.
//

#ifndef CJ_LIGHTSIMSTATUS_CODE_CHAL_HOMELIGHTS_H
#define CJ_LIGHTSIMSTATUS_CODE_CHAL_HOMELIGHTS_H

// Standard Libraries
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <sstream>
#include <cmath>

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
    void extractLightStates();

private:
    std::string myHost;
    int myPort;
    nlohmann::ordered_json lightData;

    // API HTTP Connection
    httplib::Client client;
    httplib::Server server;

    nlohmann::json queryLightsAPI(const std::string& query);
    static int convertValueToFromPercentage(bool toFromPercentage, int value); //true:toPercentage;false:fromPercentage
};


#endif //CJ_LIGHTSIMSTATUS_CODE_CHAL_HOMELIGHTS_H
