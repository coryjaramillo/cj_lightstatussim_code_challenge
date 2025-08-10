#ifndef TEST_FRAMEWORK_H
#define TEST_FRAMEWORK_H

#include <iostream>
#include <string>
#include <functional>
#include <vector>
#include <exception>

/**
 * Lightweight C++ unit testing framework for the HomeLights project
 */
class TestFramework {
private:
    struct TestCase {
        std::string name;
        std::function<void()> test;
    };
    
    std::vector<TestCase> testCases;
    int totalTests = 0;
    int passedTests = 0;
    int failedTests = 0;

public:
    void addTest(const std::string& testName, std::function<void()> testFunc) {
        testCases.push_back({testName, testFunc});
    }

    void runAllTests() {
        std::cout << "Running all tests...\n" << std::endl;
        
        for (const auto& testCase : testCases) {
            totalTests++;
            try {
                std::cout << "Running: " << testCase.name << "... ";
                testCase.test();
                std::cout << "PASSED" << std::endl;
                passedTests++;
            } catch (const std::exception& e) {
                std::cout << "FAILED - " << e.what() << std::endl;
                failedTests++;
            } catch (...) {
                std::cout << "FAILED - Unknown exception" << std::endl;
                failedTests++;
            }
        }
        
        printSummary();
    }

    void printSummary() {
        std::cout << "\n========== TEST SUMMARY ===========" << std::endl;
        std::cout << "Total Tests: " << totalTests << std::endl;
        std::cout << "Passed: " << passedTests << std::endl;
        std::cout << "Failed: " << failedTests << std::endl;
        std::cout << "Success Rate: " << (totalTests > 0 ? (passedTests * 100 / totalTests) : 0) << "%" << std::endl;
        std::cout << "===================================" << std::endl;
    }
};

// Test assertion macros
#define ASSERT_TRUE(condition) \
    if (!(condition)) { \
        throw std::runtime_error("Assertion failed: " #condition); \
    }

#define ASSERT_FALSE(condition) \
    if (condition) { \
        throw std::runtime_error("Assertion failed: !(" #condition ")"); \
    }

#define ASSERT_EQ(expected, actual) \
    if ((expected) != (actual)) { \
        throw std::runtime_error("Assertion failed: expected " + std::to_string(expected) + " but got " + std::to_string(actual)); \
    }

#define ASSERT_NE(expected, actual) \
    if ((expected) == (actual)) { \
        throw std::runtime_error("Assertion failed: expected " + std::to_string(expected) + " to not equal " + std::to_string(actual)); \
    }

#define ASSERT_STREQ(expected, actual) \
    if ((expected) != (actual)) { \
        throw std::runtime_error("Assertion failed: expected \"" + std::string(expected) + "\" but got \"" + std::string(actual) + "\""); \
    }

#define ASSERT_THROWS(exception_type, code) \
    try { \
        code; \
        throw std::runtime_error("Expected exception " #exception_type " was not thrown"); \
    } catch (const exception_type&) { \
        /* Expected exception caught */ \
    }

#endif // TEST_FRAMEWORK_H
