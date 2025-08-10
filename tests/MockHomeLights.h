#ifndef MOCK_HOME_LIGHTS_H
#define MOCK_HOME_LIGHTS_H

#include "HomeLights.h"

/**
 * Mock class for HomeLights to enable testing without requiring actual HTTP server
 */
class MockHomeLights : public HomeLights {
private:
    bool mockConnectionValid = true;
    nlohmann::json mockApiResponse;
    bool shouldThrowException = false;
    
public:
    MockHomeLights(const std::string &host, int port) : HomeLights(host, port) {}
    
    // Override to control connection validation for testing
    void setMockConnectionValid(bool valid) {
        mockConnectionValid = valid;
    }
    
    // Override to set mock API response
    void setMockApiResponse(const nlohmann::json& response) {
        mockApiResponse = response;
    }
    
    // Override to simulate exceptions
    void setShouldThrowException(bool shouldThrow) {
        shouldThrowException = shouldThrow;
    }
    
    // Expose protected method for testing
    void testExtractLightStates(bool checkForNewData = false) {
        extractLightStates(checkForNewData);
    }
    
    // Getters for private member testing
    const nlohmann::ordered_json& getCurrentLightData() const {
        return currentLightData;
    }
    
    const nlohmann::ordered_json& getNewLightData() const {
        return newLightData;
    }
    
    size_t getChangesQueueSize() const {
        size_t count = 0;
        auto temp = changesToLightState;
        while (!temp.empty()) {
            temp.pop();
            count++;
        }
        return count;
    }
    
    // Test method to directly set current light data
    void setCurrentLightData(const nlohmann::ordered_json& data) {
        currentLightData = data;
    }
    
    // Test method to directly set new light data
    void setNewLightData(const nlohmann::ordered_json& data) {
        newLightData = data;
    }
    
    // Test method to call inspectDataForChanges
    void testInspectDataForChanges(bool checkForNewData = false) {
        inspectDataForChanges(checkForNewData);
    }
    
    // Static method wrapper for testing brightness conversion
    static int testConvertValueToFromPercentage(bool toFromPercentage, int value) {
        return convertValueToFromPercentage(toFromPercentage, value);
    }
};

#endif // MOCK_HOME_LIGHTS_H
