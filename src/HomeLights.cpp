//
// Created by Cory Jaramillo on 7/19/2025.
//

#include "HomeLights.h"


HomeLights::HomeLights(const std::string &host, int port) : client(host, port){
#ifdef DEBUG_BUILD
    std::cout << "In Function: HomeLights::HomeLights" << std::endl;
#endif

    myHost = host;
    myPort = port;
}

bool HomeLights::isConnectionValid() {
#ifdef DEBUG_BUILD
    std::cout << "In Function: HomeLights::isConnectionValid" << std::endl;
#endif

    bool returnState = false;
    try {
        returnState = client.is_valid() and server.is_valid();
    }
    catch (const std::exception& ex) {
        std::cerr << "Standard Exception: " << ex.what() << std::endl;
    }
    catch (...) {
        std::cerr << "An unknown exception occurred while trying to check if the client and server are both valid!" << std::endl;
    }

    return returnState;
}

void HomeLights::displayAllLights() {
#ifdef DEBUG_BUILD
    std::cout << "In Function: HomeLights::displayAllLights" << std::endl;
#endif

    if (!lightData.empty()) {
        std::cout << lightData.dump(4) << std::endl;
    }
    else {
        std::cout << "Light Data is not currently captured." << std::endl;
    }
}

void HomeLights::captureLightData() {
#ifdef DEBUG_BUILD
    std::cout << "In Function: HomeLights::captureLightData" << std::endl;
#endif

    if (isConnectionValid()) {
        lightData = queryLightsAPI("/lights");
        extractLightStates();
    }
    else {
        std::cout << "Connection to " << myHost << ":" << myPort << " is invalid." << std::endl;
    }
}

void HomeLights::extractLightStates() {
#ifdef DEBUG_BUILD
    std::cout << "In Function: HomeLights::extractLightStates" << std::endl;
#endif

    if (!lightData.empty()) {
        std::string onKey = "on";
        std::string brightnessKey = "brightness";

        for (auto & currentLight : lightData) {
            std::string id = currentLight["id"];
            std::ostringstream builder;
            builder << "/lights/" << id;
            std::cout << "ON Key in Current Light? " << currentLight.contains(onKey) << std::endl;
            std::cout << "Brightness Key in Current Light? " << currentLight.contains(brightnessKey) << std::endl;

            nlohmann::json light = queryLightsAPI(builder.str());

            if (!light.empty()) {
                // Inspect for existence of "on" key
                if (light.contains(onKey)) {
                    currentLight[onKey] = light[onKey];
//                    currentLight.emplace_back()

#ifdef DEBUG_BUILD
                    std::cout << "\nlight on state: " << light[onKey] << " | type: " << typeid(light[onKey]).name() << std::endl;
                    std::cout << "currentLight on state: " << currentLight[onKey] << " | type: " << typeid(currentLight[onKey]).name() << std::endl;
#endif
                }
                else {
                    std::cerr << "Invalid Key: " << onKey << std::endl;
                }

                // Inspect for existence of "brightness" key
                if (light.contains(brightnessKey)) {
                    currentLight[brightnessKey] = convertValueToFromPercentage(true, light[brightnessKey]);

#ifdef DEBUG_BUILD
                    std::cout << "\nbrightness: " << light[brightnessKey] << " | type: " << typeid(light[brightnessKey]).name() << std::endl;
                    std::cout << "brightness converted: " << currentLight[brightnessKey] << std::endl;
#endif
                }
                else {
                    std::cerr << "Invalid Key: " << brightnessKey << std::endl;
                }
            }
            else {
                std::cerr << "Single Light State Query for Light ID: " << id << " failed..." << std::endl;
            }
        }
    }
    else {
        std::cerr << "Light Data has not been captured yet..." << std::endl;
    }
}

nlohmann::json HomeLights::queryLightsAPI(const std::string& query) {
#ifdef DEBUG_BUILD
    std::cout << "In Function: HomeLights::queryLightsAPI" << std::endl;
#endif

    nlohmann::json returnResult;
    try {
        if(!query.empty()) {
            auto res = client.Get(query);
            if (isConnectionValid() && res->status == 200) {
                returnResult = nlohmann::json::parse(res->body);
            }
            else {
                std::cerr << "HTTP Get Failed; ";
                if (!res) {
                    std::cerr << "Connection Error!" << std::endl;
                }
                else {
                    std::cerr << "HTTP Status Code: " << res->status << std::endl;
                }
            }
        }
        else {
            std::cerr << "Query is empty..." << std::endl;
        }
    }
    catch (const nlohmann::json::exception &e) {
        std::cerr << "JSON Exception: " << e.what() << std::endl;
    }
    catch (const std::exception &ex) {
        std::cerr << "Standard Exception: " << ex.what() << std::endl;
    }
    catch (...) {
        std::cerr << "An unknown exception occurred while trying to check if the client and server are both valid!" << std::endl;
    }

    return returnResult;
}

//true:toPercentage|false:fromPercentage
int HomeLights::convertValueToFromPercentage(bool toFromPercentage, int value) {
    int returnValue = 0;

    if (toFromPercentage) {
        returnValue = static_cast<int>(std::round((static_cast<double>(value) / 255.0) * 100.0));
    }
    else {
        returnValue = static_cast<int>(std::round((static_cast<double>(value) / 100.0) * 255.0));
    }

    return returnValue;
}
