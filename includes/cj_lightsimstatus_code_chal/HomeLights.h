//
// Created by Cory Jaramillo on 7/19/2025.
//

#ifndef CJ_LIGHTSIMSTATUS_CODE_CHAL_HOMELIGHTS_H
#define CJ_LIGHTSIMSTATUS_CODE_CHAL_HOMELIGHTS_H

// Standard Libraries
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <cmath>
#include <queue>

// Local Libraries

// Third Party Libraries
#include "json_fwd.hpp"
#include "json.hpp"
#include "httplib.h"

/**
 * @class HomeLights
 * @brief Manages smart home light data and communicates with a light control REST API.
 *
 * This class encapsulates all operations required to:
 * - Connect to a lights API server
 * - Query lights for status updates
 * - Detect and queue light state changes
 * - Display light information
 */
class HomeLights {

public:
    /**
     * @brief Constructs a HomeLights object and connects to the given host and port.
     * @param host Hostname or IP address of the light API server.
     * @param port TCP port of the light API server.
     */
    HomeLights(const std::string &host, int port);

    /**
     * @brief Destructor for HomeLights.
     */
    ~HomeLights() = default;

    /**
     * @brief Retrieves and removes the next queued light state change.
     *
     * This function pops the front element from the internal queue of pending light
     * state changes and returns it to the caller.
     *
     * @warning This function does not check whether the queue is empty before
     *          accessing its front element. Calling it when the queue is empty
     *          results in undefined behavior.
     *
     * @note Callers should invoke areAnyChangesInQueue() (or perform an equivalent
     *       check) before using this function to ensure at least one change is available.
     *
     * @return An ordered JSON object describing the state change.
     */
    nlohmann::ordered_json getLightStateChange();

    // Utility Methods
    /**
     * @brief Captures light data from the API, optionally detecting changes since last fetch.
     * @param checkForNewData If true, compares with previous state to identify changes.
     */
    void captureLightData(bool checkForNewData = false);
    /**
     * @brief Checks if the connection to the light API server is currently valid.
     * @return True if the connection is valid, false otherwise.
     */
    bool isConnectionValid();
    /**
     * @brief Determines if there are any pending light state changes in the queue.
     * @return True if the changes queue is non-empty, false otherwise.
     */
    bool areAnyChangesInQueue();
    /**
     * @brief Outputs a formatted list of all lights and their current states to stdout.
     */
    void displayAllLights();


protected:
    /**
     * @brief Extracts light state details from the current API response.
     * @param checkForNewData If true, also compares new data against stored state.
     */
    void extractLightStates(bool checkForNewData);

private:
    // ==== INTERNAL STATE ====
    std::string myHost;                                     ///< Hostname or IP of the API server
    int myPort;                                             ///< TCP port of the API server
    std::vector<std::string> lightKeys;                     ///< Keys (field names) used in light JSON objects
    nlohmann::ordered_json currentLightData;                ///< Last known light data snapshot
    nlohmann::ordered_json newLightData;                    ///< Most recently fetched light data from API
    std::queue<nlohmann::ordered_json> changesToLightState; ///< Queue of detected light state changes


    // API HTTP Connection
    // ==== NETWORK ====
    httplib::Client client; ///< HTTP client for communicating with the lights API
    httplib::Server server; ///< Optional local HTTP server (if used for callbacks or simulations)

    /**
     * @brief Queries the lights API using HTTP GET or PUT to fetch/update light state.
     * @param query Optional query string for specifying a single light or subresource.
     * @return JSON response from the API (empty if request failed or error occurred).
     */
    nlohmann::json queryLightsAPI(const std::string &query = "");
    /**
     * @brief Compares new light data to current state and records any changes in the queue.
     * @param checkForNewData If true, detects both updates to existing lights and new/removal events.
     */
    void inspectDataForChanges(bool checkForNewData = false);
    /**
     * @brief Converts brightness values between absolute integers and percentages.
     * @param toFromPercentage True to convert an absolute value to percentage, false for the reverse.
     * @param value The value to convert.
     * @return Converted integer value.
     */
    static int convertValueToFromPercentage(bool toFromPercentage, int value); //true:toPercentage;false:fromPercentage
};


#endif //CJ_LIGHTSIMSTATUS_CODE_CHAL_HOMELIGHTS_H
