//
// Created by skyse on 7/19/2025.
//

#include "HomeLights.h"


HomeLights::HomeLights(const std::string &host, int port) : client(host, port){
    myHost = host;
    myPort = port;

    captureLightData();
//    displayAllLights();
    extractLightIDs();
}

bool HomeLights::isConnectionValid() {
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
    if (!lightData.empty()) {
        std::cout << lightData << std::endl;
    }
    else {
        std::cout << "Light Data is not currently captured." << std::endl;
    }
}

void HomeLights::captureLightData() {
    if (isConnectionValid()) {
        auto res = client.Get("/lights");
        lightData = nlohmann::json::parse(res->body);
    }
    else {
        std::cout << "Connection to " << myHost << ":" << myPort << " is invalid." << std::endl;
    }
}

void HomeLights::extractLightIDs() {
    if (!lightData.empty()) {
        for (const auto & light : lightData) {
            lightIDs.push_back(light["id"]);
        }
        for (const auto &id: lightIDs) {
            std::ostringstream builder;
            builder << "/lights/" << id;
            auto lightState = client.Get(builder.str());
            lightData[id] = std::boolalpha(lightState);
        }
    }
    else {
        std::cout << "Light Data is not currently captured." << std::endl;
    }
}
