// Standard Libraries
#include <thread>

// Local Libraries
#include "HomeLights.h"

// Third Party Libraries
#include "json_fwd.hpp"
#include "json.hpp"

// REQUIREMENTS
//    print out text based on the state of the lights - DONE
//    printouts need to be in JSON format - DONE
//    upon startup, all lights and their state should be printed out in the order of: name, id, room, on, brightness - DONE
//    the 'on' property is a boolean for light on or off - DONE
//    The brightness property is 0-100 integer output representing % brightness. API range is 0-255, so must translate to percentage accurately. - DONE
//    all subsequent printouts shall only printout any changes in the lights' states, but just individual changes.
//    program detects when a light has been added or removed from the system
//    newly discovered light get a full state print
//    removed lights get a print message containing id and name of light
//    program runs until stopped by user
//    program will send requests to an http server to interrogate and modify the state of the lights.


int main() {
    std::string currentHost = "localhost";
    int currentPort = 8080;

    HomeLights homeLights(currentHost, currentPort);
    homeLights.captureLightData();
    homeLights.displayAllLights();


    do {
        homeLights.captureLightData(true);

        if (!homeLights.areAnyChangesInQueue()){
            while (!homeLights.areAnyChangesInQueue()) {
                auto change = homeLights.getLightStateChange();
#ifdef DEBUG_BUILD_SIMPLE
                std::cout << "CHANGE CAPTURED..." << std::endl;
#endif
                std::cout << change.dump(4) << std::endl;
            }
        }
        else {

#ifdef DEBUG_BUILD_SIMPLE
            std::cout << "Sleeping for 100 milliseconds..." << std::endl;
#endif

            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    } while(true);



    return 0;
}
