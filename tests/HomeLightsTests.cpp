#include "TestFramework.h"
#include "MockHomeLights.h"
#include "HomeLights.h"
#include "json.hpp"
#include <string>
#include <cmath>

/**
 * Unit tests for the HomeLights class
 */
class HomeLightsTests {
private:
    TestFramework testFramework;

public:
    void runAllTests() {
        // Constructor tests
        testFramework.addTest("Test_Constructor_ValidHostAndPort", [this]() { test_Constructor_ValidHostAndPort(); });
        testFramework.addTest("Test_Constructor_EmptyHost", [this]() { test_Constructor_EmptyHost(); });
        
        // Brightness conversion tests
        testFramework.addTest("Test_BrightnessConversion_ToPercentage_MinValue", [this]() { test_BrightnessConversion_ToPercentage_MinValue(); });
        testFramework.addTest("Test_BrightnessConversion_ToPercentage_MaxValue", [this]() { test_BrightnessConversion_ToPercentage_MaxValue(); });
        testFramework.addTest("Test_BrightnessConversion_ToPercentage_MiddleValue", [this]() { test_BrightnessConversion_ToPercentage_MiddleValue(); });
        testFramework.addTest("Test_BrightnessConversion_FromPercentage_MinValue", [this]() { test_BrightnessConversion_FromPercentage_MinValue(); });
        testFramework.addTest("Test_BrightnessConversion_FromPercentage_MaxValue", [this]() { test_BrightnessConversion_FromPercentage_MaxValue(); });
        testFramework.addTest("Test_BrightnessConversion_FromPercentage_MiddleValue", [this]() { test_BrightnessConversion_FromPercentage_MiddleValue(); });
        
        // Queue management tests  
        testFramework.addTest("Test_ChangesQueue_InitiallyEmpty", [this]() { test_ChangesQueue_InitiallyEmpty(); });
        testFramework.addTest("Test_ChangesQueue_AddAndRetrieve", [this]() { test_ChangesQueue_AddAndRetrieve(); });
        testFramework.addTest("Test_ChangesQueue_MultipleChanges", [this]() { test_ChangesQueue_MultipleChanges(); });
        
        // Light data processing tests
        testFramework.addTest("Test_LightData_ValidJsonResponse", [this]() { test_LightData_ValidJsonResponse(); });
        testFramework.addTest("Test_LightData_EmptyJsonResponse", [this]() { test_LightData_EmptyJsonResponse(); });
        testFramework.addTest("Test_LightData_InvalidJsonKeys", [this]() { test_LightData_InvalidJsonKeys(); });
        
        // Change detection tests
        testFramework.addTest("Test_ChangeDetection_NoChanges", [this]() { test_ChangeDetection_NoChanges(); });
        testFramework.addTest("Test_ChangeDetection_BrightnessChange", [this]() { test_ChangeDetection_BrightnessChange(); });
        testFramework.addTest("Test_ChangeDetection_OnOffToggle", [this]() { test_ChangeDetection_OnOffToggle(); });
        testFramework.addTest("Test_ChangeDetection_NewLightAdded", [this]() { test_ChangeDetection_NewLightAdded(); });
        testFramework.addTest("Test_ChangeDetection_LightRemoved", [this]() { test_ChangeDetection_LightRemoved(); });
        
        // Edge case tests
        testFramework.addTest("Test_EdgeCase_EmptyLightData", [this]() { test_EdgeCase_EmptyLightData(); });
        testFramework.addTest("Test_EdgeCase_MissingRequiredKeys", [this]() { test_EdgeCase_MissingRequiredKeys(); });
        
        testFramework.runAllTests();
    }

private:
    // Constructor tests
    void test_Constructor_ValidHostAndPort() {
        HomeLights lights("localhost", 8080);
        ASSERT_TRUE(true); // If constructor doesn't throw, test passes
    }
    
    void test_Constructor_EmptyHost() {
        HomeLights lights("", 8080);
        ASSERT_TRUE(true); // Constructor should handle empty host gracefully
    }

    // Brightness conversion tests - accessing static method through derived class
    void test_BrightnessConversion_ToPercentage_MinValue() {
        // Test conversion from 0 (API) to 0 (percentage)
        int result = MockHomeLights::testConvertValueToFromPercentage(true, 0);
        ASSERT_EQ(0, result);
    }
    
    void test_BrightnessConversion_ToPercentage_MaxValue() {
        // Test conversion from 255 (API) to 100 (percentage)
        int result = MockHomeLights::testConvertValueToFromPercentage(true, 255);
        ASSERT_EQ(100, result);
    }
    
    void test_BrightnessConversion_ToPercentage_MiddleValue() {
        // Test conversion from 128 (API) to ~50 (percentage)
        int result = MockHomeLights::testConvertValueToFromPercentage(true, 128);
        int expected = static_cast<int>(std::round((128.0 / 255.0) * 100.0));
        ASSERT_EQ(expected, result);
    }
    
    void test_BrightnessConversion_FromPercentage_MinValue() {
        // Test conversion from 0 (percentage) to 0 (API)
        int result = MockHomeLights::testConvertValueToFromPercentage(false, 0);
        ASSERT_EQ(0, result);
    }
    
    void test_BrightnessConversion_FromPercentage_MaxValue() {
        // Test conversion from 100 (percentage) to 255 (API)
        int result = MockHomeLights::testConvertValueToFromPercentage(false, 100);
        ASSERT_EQ(255, result);
    }
    
    void test_BrightnessConversion_FromPercentage_MiddleValue() {
        // Test conversion from 50 (percentage) to ~128 (API)
        int result = MockHomeLights::testConvertValueToFromPercentage(false, 50);
        int expected = static_cast<int>(std::round((50.0 / 100.0) * 255.0));
        ASSERT_EQ(expected, result);
    }

    // Queue management tests
    void test_ChangesQueue_InitiallyEmpty() {
        MockHomeLights mockLights("localhost", 8080);
        ASSERT_TRUE(mockLights.areAnyChangesInQueue());
    }
    
    void test_ChangesQueue_AddAndRetrieve() {
        MockHomeLights mockLights("localhost", 8080);
        
        // Setup test data
        nlohmann::ordered_json currentData = nlohmann::ordered_json::array({
            {{"id", "1"}, {"name", "Living Room"}, {"room", "living_room"}, {"on", true}, {"brightness", 50}}
        });
        
        nlohmann::ordered_json newData = nlohmann::ordered_json::array({
            {{"id", "1"}, {"name", "Living Room"}, {"room", "living_room"}, {"on", true}, {"brightness", 75}}
        });
        
        mockLights.setCurrentLightData(currentData);
        mockLights.setNewLightData(newData);
        mockLights.testInspectDataForChanges(true);
        
        ASSERT_FALSE(mockLights.areAnyChangesInQueue());
        
        auto change = mockLights.getLightStateChange();
        ASSERT_STREQ("1", change["id"].get<std::string>());
        ASSERT_EQ(75, change["brightness"].get<int>());
    }
    
    void test_ChangesQueue_MultipleChanges() {
        MockHomeLights mockLights("localhost", 8080);
        
        // Setup test data with multiple changes
        nlohmann::ordered_json currentData = nlohmann::ordered_json::array({
            {{"id", "1"}, {"name", "Living Room"}, {"room", "living_room"}, {"on", true}, {"brightness", 50}},
            {{"id", "2"}, {"name", "Kitchen"}, {"room", "kitchen"}, {"on", false}, {"brightness", 25}}
        });
        
        nlohmann::ordered_json newData = nlohmann::ordered_json::array({
            {{"id", "1"}, {"name", "Living Room"}, {"room", "living_room"}, {"on", false}, {"brightness", 75}},
            {{"id", "2"}, {"name", "Kitchen"}, {"room", "kitchen"}, {"on", true}, {"brightness", 25}}
        });
        
        mockLights.setCurrentLightData(currentData);
        mockLights.setNewLightData(newData);
        mockLights.testInspectDataForChanges(true);
        
        ASSERT_FALSE(mockLights.areAnyChangesInQueue());
        
        // Should have multiple changes queued
        size_t changeCount = 0;
        while (!mockLights.areAnyChangesInQueue()) {
            auto change = mockLights.getLightStateChange();
            changeCount++;
        }
        
        ASSERT_TRUE(changeCount > 0);
    }

    // Light data processing tests
    void test_LightData_ValidJsonResponse() {
        MockHomeLights mockLights("localhost", 8080);
        
        nlohmann::ordered_json validData = nlohmann::ordered_json::array({
            {{"id", "1"}, {"name", "Living Room"}, {"room", "living_room"}, {"on", true}, {"brightness", 128}}
        });
        
        mockLights.setCurrentLightData(validData);
        
        ASSERT_FALSE(mockLights.getCurrentLightData().empty());
        ASSERT_EQ(1, mockLights.getCurrentLightData().size());
    }
    
    void test_LightData_EmptyJsonResponse() {
        MockHomeLights mockLights("localhost", 8080);
        
        nlohmann::ordered_json emptyData = nlohmann::ordered_json::array();
        mockLights.setCurrentLightData(emptyData);
        
        ASSERT_TRUE(mockLights.getCurrentLightData().empty());
    }
    
    void test_LightData_InvalidJsonKeys() {
        MockHomeLights mockLights("localhost", 8080);
        
        // Missing required keys
        nlohmann::ordered_json invalidData = nlohmann::ordered_json::array({
            {{"invalid_key", "value"}}
        });
        
        mockLights.setCurrentLightData(invalidData);
        ASSERT_FALSE(mockLights.getCurrentLightData().empty());
        
        // The data is present but will cause issues during processing
        // This test verifies the structure can handle malformed data
    }

    // Change detection tests
    void test_ChangeDetection_NoChanges() {
        MockHomeLights mockLights("localhost", 8080);
        
        nlohmann::ordered_json sameData = nlohmann::ordered_json::array({
            {{"id", "1"}, {"name", "Living Room"}, {"room", "living_room"}, {"on", true}, {"brightness", 50}}
        });
        
        mockLights.setCurrentLightData(sameData);
        mockLights.setNewLightData(sameData);
        mockLights.testInspectDataForChanges(true);
        
        ASSERT_TRUE(mockLights.areAnyChangesInQueue());
    }
    
    void test_ChangeDetection_BrightnessChange() {
        MockHomeLights mockLights("localhost", 8080);
        
        nlohmann::ordered_json currentData = nlohmann::ordered_json::array({
            {{"id", "1"}, {"name", "Living Room"}, {"room", "living_room"}, {"on", true}, {"brightness", 50}}
        });
        
        nlohmann::ordered_json newData = nlohmann::ordered_json::array({
            {{"id", "1"}, {"name", "Living Room"}, {"room", "living_room"}, {"on", true}, {"brightness", 75}}
        });
        
        mockLights.setCurrentLightData(currentData);
        mockLights.setNewLightData(newData);
        mockLights.testInspectDataForChanges(true);
        
        ASSERT_FALSE(mockLights.areAnyChangesInQueue());
        
        auto change = mockLights.getLightStateChange();
        ASSERT_EQ(75, change["brightness"].get<int>());
    }
    
    void test_ChangeDetection_OnOffToggle() {
        MockHomeLights mockLights("localhost", 8080);
        
        nlohmann::ordered_json currentData = nlohmann::ordered_json::array({
            {{"id", "1"}, {"name", "Living Room"}, {"room", "living_room"}, {"on", true}, {"brightness", 50}}
        });
        
        nlohmann::ordered_json newData = nlohmann::ordered_json::array({
            {{"id", "1"}, {"name", "Living Room"}, {"room", "living_room"}, {"on", false}, {"brightness", 50}}
        });
        
        mockLights.setCurrentLightData(currentData);
        mockLights.setNewLightData(newData);
        mockLights.testInspectDataForChanges(true);
        
        ASSERT_FALSE(mockLights.areAnyChangesInQueue());
        
        auto change = mockLights.getLightStateChange();
        ASSERT_FALSE(change["on"].get<bool>());
    }
    
    void test_ChangeDetection_NewLightAdded() {
        MockHomeLights mockLights("localhost", 8080);
        
        nlohmann::ordered_json currentData = nlohmann::ordered_json::array({
            {{"id", "1"}, {"name", "Living Room"}, {"room", "living_room"}, {"on", true}, {"brightness", 50}}
        });
        
        nlohmann::ordered_json newData = nlohmann::ordered_json::array({
            {{"id", "1"}, {"name", "Living Room"}, {"room", "living_room"}, {"on", true}, {"brightness", 50}},
            {{"id", "2"}, {"name", "Kitchen"}, {"room", "kitchen"}, {"on", false}, {"brightness", 25}}
        });
        
        mockLights.setCurrentLightData(currentData);
        mockLights.setNewLightData(newData);
        mockLights.testInspectDataForChanges(true);
        
        ASSERT_FALSE(mockLights.areAnyChangesInQueue());
        
        auto change = mockLights.getLightStateChange();
        ASSERT_STREQ("2", change["id"].get<std::string>());
    }
    
    void test_ChangeDetection_LightRemoved() {
        MockHomeLights mockLights("localhost", 8080);
        
        nlohmann::ordered_json currentData = nlohmann::ordered_json::array({
            {{"id", "1"}, {"name", "Living Room"}, {"room", "living_room"}, {"on", true}, {"brightness", 50}},
            {{"id", "2"}, {"name", "Kitchen"}, {"room", "kitchen"}, {"on", false}, {"brightness", 25}}
        });
        
        nlohmann::ordered_json newData = nlohmann::ordered_json::array({
            {{"id", "1"}, {"name", "Living Room"}, {"room", "living_room"}, {"on", true}, {"brightness", 50}}
        });
        
        mockLights.setCurrentLightData(currentData);
        mockLights.setNewLightData(newData);
        
        // The actual method prints removed lights to stdout, so we just verify it doesn't crash
        mockLights.testInspectDataForChanges(true);
        
        ASSERT_TRUE(true); // Test passes if no exception thrown
    }

    // Edge case tests
    void test_EdgeCase_EmptyLightData() {
        MockHomeLights mockLights("localhost", 8080);
        
        nlohmann::ordered_json emptyData = nlohmann::ordered_json::array();
        mockLights.setCurrentLightData(emptyData);
        mockLights.setNewLightData(emptyData);
        mockLights.testInspectDataForChanges(true);
        
        ASSERT_TRUE(mockLights.areAnyChangesInQueue());
    }
    
    void test_EdgeCase_MissingRequiredKeys() {
        MockHomeLights mockLights("localhost", 8080);
        
        // Data missing 'id' key
        nlohmann::ordered_json badData = nlohmann::ordered_json::array({
            {{"name", "Living Room"}, {"room", "living_room"}, {"on", true}, {"brightness", 50}}
        });
        
        mockLights.setCurrentLightData(badData);
        
        // Should handle gracefully without crashing
        ASSERT_FALSE(mockLights.getCurrentLightData().empty());
    }
};

int main() {
    HomeLightsTests tests;
    tests.runAllTests();
    return 0;
}
