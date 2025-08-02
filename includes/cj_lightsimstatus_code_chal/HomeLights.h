//
// Created by Cory Jaramillo on 7/19/2025.
//

#ifndef CJ_LIGHTSIMSTATUS_CODE_CHAL_HOMELIGHTS_H
#define CJ_LIGHTSIMSTATUS_CODE_CHAL_HOMELIGHTS_H

// Standard Libraries
#include <iostream>
#include <iomanip>
#include <string>
//#include <vector>
#include <sstream>
#include <cmath>
#include <queue>

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
    void captureLightData(bool checkForNewData = false);
    nlohmann::ordered_json getLightStateChange();

    // Setters


    // Utility Methods
    bool isConnectionValid();
    bool areAnyChangesInQueue();
    void displayAllLights();


protected:
    void extractLightStates(bool checkForNewData);

private:
    std::string myHost;
    int myPort;
    std::vector<std::string> lightKeys;
    nlohmann::ordered_json currentLightData;
    nlohmann::ordered_json newLightData;
    std::queue<nlohmann::ordered_json> changesToLightState;


    // API HTTP Connection
    httplib::Client client;
    httplib::Server server;

    nlohmann::json queryLightsAPI(const std::string& query = "");
    void inspectDataForChanges(bool checkForNewData = false);
    void captureChangeToQueue(const std::string &changeId, const std::string &changeKey, const std::string &statusChange);
    void captureChangeToQueue(const nlohmann::json &lightChange);
    static int convertValueToFromPercentage(bool toFromPercentage, int value); //true:toPercentage;false:fromPercentage
};


#endif //CJ_LIGHTSIMSTATUS_CODE_CHAL_HOMELIGHTS_H
