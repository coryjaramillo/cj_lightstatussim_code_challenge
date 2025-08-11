//
// Created by Cory Jaramillo on 7/19/2025.
//

#include "HomeLights.h"


HomeLights::HomeLights(const std::string &host, int port) : client(host, port){

#ifdef DEBUG_BUILD_VERBOSE
    std::cout << "In Function: HomeLights::HomeLights" << std::endl;
    std::cout << "\tFunction Arguments:-->host: " << host << ", port: " << port << std::endl;
#endif

    myHost = host;
    myPort = port;
    lightKeys = {"id", "name", "room", "on", "brightness"};
}

bool HomeLights::isConnectionValid() {

#ifdef DEBUG_BUILD_VERBOSE
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

#ifdef DEBUG_BUILD_VERBOSE
    std::cout << "In Function: HomeLights::displayAllLights" << std::endl;
#endif
    // if currentLightdata is not empty, then print to output
    if (!currentLightData.empty()) {
        std::cout << currentLightData.dump(4) << std::endl;
    }
    else {
        std::cout << "Light Data is not currently captured." << std::endl;
    }
}


void HomeLights::captureLightData(bool checkForNewData) {

#ifdef DEBUG_BUILD_VERBOSE
    std::cout << "In Function: HomeLights::captureLightData" << std::endl;
    std::cout << std::boolalpha << "\tFunction Argument:-->checkForNewData: " << checkForNewData << std::noboolalpha << std::endl;
#endif
    // check if the connection is valid
    if (isConnectionValid()) {
        if (checkForNewData) {
            // if checkForNewData is true, then get a new copy of the API light data
#ifdef DEBUG_BUILD_SIMPLE
            std::cout << "Checking for New Data..." << std::endl;
#endif

            newLightData = queryLightsAPI();
        }
        else {
            // if checkForNewData is false, then the API light data is the first capture
#ifdef DEBUG_BUILD_SIMPLE
            std::cout << "Populating Current Data..." << std::endl;
#endif

            currentLightData = queryLightsAPI();
        }
        // extract light states for all lights in the found data
        extractLightStates(checkForNewData);

        if(checkForNewData) {
            // Check the data for any changes
#ifdef DEBUG_BUILD_SIMPLE
            std::cout << "Inspecting Data for changes..." << std::endl;
#endif

            inspectDataForChanges(checkForNewData);
        }
    }
    else {
        std::cerr << "Connection to " << myHost << ":" << myPort << " is invalid." << std::endl;
    }
}

void HomeLights::extractLightStates(bool checkForNewData) {

#ifdef DEBUG_BUILD_VERBOSE
    std::cout << "In Function: HomeLights::extractLightStates" << std::endl;
    std::cout << std::boolalpha << "\tFunction Argument:-->checkForNewData: " << checkForNewData << std::noboolalpha << std::endl;
#endif
    // extract the light states and store them to newLightData or currentLightData based on whether there is a new
    // capture being performed or first capture being performed
    nlohmann::ordered_json *targetContainer = checkForNewData ? &newLightData : &currentLightData;

#ifdef DEBUG_BUILD_VERBOSE
    std::cout << "newLightData Container: " << newLightData << std::endl;
    std::cout << "currentLightData Container: " << currentLightData << std::endl;
    std::cout << "Target Container: " << *targetContainer << std::endl;
#endif
    // make sure the container is not empty
    if (!targetContainer->empty()) {
        // iterate through the lightData in target
        for (auto & currentLight : *targetContainer) {
            // obtain the light ID
            std::string id = currentLight[lightKeys[0]];

#ifdef DEBUG_BUILD_VERBOSE
            std::cout << "ON Key in Current Light? " << currentLight.contains(lightKeys[3]) << std::endl;
            std::cout << "Brightness Key in Current Light? " << currentLight.contains(lightKeys[4]) << std::endl;
#endif
            // get the light state of the target light ID
            nlohmann::json light = queryLightsAPI(id);

            if (!light.empty()) {
                // Inspect for existence of "on" key
                if (light.contains(lightKeys[3])) {
                    // if found, capture the state
                    currentLight[lightKeys[3]] = light[lightKeys[3]];

#ifdef DEBUG_BUILD_VERBOSE
                    std::cout << "\nlight on state: " << light[lightKeys[3]] << " | type: " << typeid(light[lightKeys[3]]).name() << std::endl;
                    std::cout << "currentLight on state: " << currentLight[lightKeys[3]] << " | type: " << typeid(currentLight[lightKeys[3]]).name() << std::endl;
#endif

                }
                else {
                    // otherwise flag for invalid key. this should never be reached
                    std::cerr << "Invalid Key: " << lightKeys[3] << std::endl;
                }

                // Inspect for existence of "brightness" key
                if (light.contains(lightKeys[4])) {
                    // if found, capture the state
                    currentLight[lightKeys[4]] = convertValueToFromPercentage(true, light[lightKeys[4]]);

#ifdef DEBUG_BUILD_VERBOSE
                    std::cout << "\nbrightness: " << light[lightKeys[4]] << " | type: " << typeid(light[lightKeys[4]]).name() << std::endl;
                    std::cout << "brightness converted: " << currentLight[lightKeys[4]] << std::endl;
#endif

                }
                else {
                    // otherwise flag for invalid key. this should never be reached
                    std::cerr << "Invalid Key: " << lightKeys[4] << std::endl;
                }
            }
            else {
                // indicate when getting the light state query fails
                std::cerr << "Single Light State Query for Light ID: " << id << " failed..." << std::endl;
            }
        }
    }
    else {
        std::cerr << "Light Data has not been captured yet..." << std::endl;
    }
}

nlohmann::json HomeLights::queryLightsAPI(const std::string &query) {

#ifdef DEBUG_BUILD_VERBOSE
    std::cout << "In Function: HomeLights::queryLightsAPI" << std::endl;
    std::cout << "\tFunction Argument:-->query: " << query << std::endl;
#endif
    // build the query into a string
    nlohmann::json returnResult;
    try {
        std::ostringstream builder;
        builder << "/lights";
        if (!query.empty()) {
            builder << "/" << query;
        }
        std::string queryString = builder.str();

#ifdef DEBUG_BUILD_SIMPLE
        std::cout << "Query String Builder: " << queryString << std::endl;
#endif
        // send the query using Get http method
        auto res = client.Get(queryString.c_str());

        // validate connection and result
        if (isConnectionValid() && res->status == 200) {
            // parse the result if valid
            returnResult = nlohmann::json::parse(res->body);
        }
        else {
            // otherwise output what caused the error
            std::cerr << "HTTP Get Failed:-->:";
            if (!res) {
                std::cerr << "Connection Error!" << std::endl;
            }
            else {
                std::cerr << "HTTP Status Code: " << res->status << std::endl;
            }
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

#ifdef DEBUG_BUILD_VERBOSE
    std::cout << "In Function: HomeLights::convertValueToFromPercentage" << std::endl;
    std::cout << std::boolalpha << "\tFunction Arguments:-->toFromPercentage: " << toFromPercentage << " | value: " << value << std::noboolalpha << std::endl;
#endif
    int returnValue = 0;
    if (toFromPercentage) {
        // if true, conversion is from API value to percentage
        returnValue = static_cast<int>(std::round((static_cast<double>(value) / 255.0) * 100.0));
    }
    else {
        // if false, conversion is from percentage to API value
        returnValue = static_cast<int>(std::round((static_cast<double>(value) / 100.0) * 255.0));
    }

    return returnValue;
}

void HomeLights::inspectDataForChanges(bool checkForNewData) {

#ifdef DEBUG_BUILD_VERBOSE
    std::cout << "In Function: HomeLights::inspectDataForChanges" << std::endl;
    std::cout << std::boolalpha << "\tFunction Argument:-->checkForNewData: " << checkForNewData << std::noboolalpha << std::endl;
#endif

    if(checkForNewData) {
        // loop through newLightData and detect and changes or new lights
        for (auto &newLight : newLightData) {
            std::string searchId = newLight[lightKeys[0]];

#ifdef DEBUG_BUILD_SIMPLE
            std::cout << "New Light: " << newLight << std::endl;
#endif

#ifdef DEBUG_BUILD_VERBOSE
            std::cout << "\tcurrentLightData: " << currentLightData << std::endl;
            std::cout << "\tsearchId: " << searchId << std::endl;
            std::cout << "\tlightKeys[0]: " << lightKeys[0] << std::endl;
#endif

            // Search for the light by ID in currentLightData
            auto currentLightMatch = std::find_if(
                    currentLightData.begin(),
                    currentLightData.end(),
                    [&searchId, this](const nlohmann::json &candidate) {
                        return candidate.contains(lightKeys[0]) && candidate[lightKeys[0]] == searchId;
                    }
            );


            // If match found does not equal to end, we found an existing light and need to inspect for any changes
            // and capture found changes.
            if (currentLightMatch != currentLightData.end()) {
                // Found an existing light; safe to dereference iterator
                const auto &currentLight = *currentLightMatch;

#ifdef DEBUG_BUILD_SIMPLE
                std::cout << "currentLight: " << currentLight << std::endl;
                std::cout << "Light found in current light data..." << std::endl;
#endif
                try {
                    // work through all keys, except "id", for comparison of new data to current data
                    for(const std::string &key : lightKeys){
                        if(key == "id") {
                            continue;
                        }

#ifdef DEBUG_BUILD_VERBOSE
                        std::cout << "\tnewLight[key]: " << newLight[key] << " | " << typeid(newLight[key]).name() << std::endl;
                        std::cout << "\tcurrentLight[key]: " << currentLight[key] << " | " << typeid(currentLight[key]).name() << std::endl;
                        std::cout << "\tcomparison: " << std::boolalpha << (newLight[key] != currentLight[key]) << std::noboolalpha << std::endl;
#endif
                        // if new data does not match current, we have a change and need to capture it
                        if(newLight[key] != currentLight[key]) {

#ifdef DEBUG_BUILD_VERBOSE
                            std::cout << "Change to Light has been Identified..." << std::endl;
                            std::cout << "\tsearchId: " << searchId << " | " << typeid(searchId).name() << std::endl;
                            std::cout << "\tkey: " << key << " | " << typeid(key).name() << std::endl;
                            std::cout << "\tnewLight[key]: " << newLight[key] << " | " << typeid(newLight[key]).name() << std::endl;
#endif

                            nlohmann::ordered_json temp = {{lightKeys[0], searchId},
                                                           {key, newLight[key]}};
                            changesToLightState.emplace(temp);
                        }
                    }
                }
                catch (const nlohmann::json::exception &e) {
                    std::cerr << "JSON Exception: " << e.what() << std::endl;
                }
                catch (const std::exception &exception) {
                    std::cerr << "Standard Exception: " << exception.what() << std::endl;
                }
                catch (...) {
                    std::cerr << "An unknown exception occurred..." << std::endl;
                }

//                if (newLight != currentLight) {
//
//#ifdef DEBUG_BUILD_SIMPLE
//                    std::cout << "Updating currentLightData with newLightData..." << std::endl;
//#endif
//                    currentLightData = newLightData;
//                }
            }
            else {
                // If match does equal to end, we have a new light and need to capture all light data.

#ifdef DEBUG_BUILD_SIMPLE
                std::cout << "New light found..." << std::endl;
#endif
                changesToLightState.emplace(newLight);
            }
        }

        // loop through currentLightData to check and see if it no longer exists in newLightData, which means that a light has been removed
        for (auto &oldLight: currentLightData) {
            std::string oldId = oldLight[lightKeys[0]];

            auto newLightMatch = std::find_if(
                    newLightData.begin(),
                    newLightData.end(),
                    [&oldId, this](const nlohmann::json &candidate) {
                        return candidate.contains(lightKeys[0]) && candidate[lightKeys[0]] == oldId;
                    }
            );

            if (newLightMatch == newLightData.end()) {
                // Light exists in old data, not in new ➡ removed
                std::cout << oldLight[lightKeys[1]] << " (" << oldId << ") has been removed" << std::endl;
            }
        }

        // update the stored state
        currentLightData = newLightData;
    }
    else {
//        unused
    }
}

bool HomeLights::areAnyChangesInQueue() {

#ifdef DEBUG_BUILD_VERBOSE
    std::cout << "In Function: HomeLights::areAnyChangesInQueue" << std::endl;
    std::cout << std::boolalpha << "\tchangesToLightState queue empty status: " << changesToLightState.empty() << std::noboolalpha << std::endl;
#endif

    return changesToLightState.empty();
}


nlohmann::ordered_json HomeLights::getLightStateChange() {
    nlohmann::ordered_json frontChange = changesToLightState.front();

#ifdef DEBUG_BUILD_VERBOSE
    std::cout << "In Function: HomeLights::getLightStateChange" << std::endl;
    std::cout << "\tfrontChange: " << frontChange.dump(2) << std::endl;
#endif

    changesToLightState.pop();
    return frontChange;
}
