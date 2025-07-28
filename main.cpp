// Standard Libraries


// Local Libraries
#include "HomeLights.h"

// Third Party Libraries
#include "json_fwd.hpp"
#include "json.hpp"

// REQUIREMENTS
//    print out text based on the state of the lights
//    printouts need to be in JSON format
//    upon startup, all lights and their state should be printed out in the order of: name, id, room, on, brightness
//    the 'on' property is a boolean for light on or off
//    The brightness property is 0-100 integer output representing % brightness. API range is 0-255, so must translate to percentage accurately.
//    all subsequent printouts shall only printout any changes in the lights' states, but just individual changes.
//    program detects when a light has been added or removed from the system
//    newly discovered light get a full state print
//    removed lights get a print message containing id and name of light
//    program runs until stopped by user
//    program will send requests to an http server to interrogate and modify the state of the lights.


int main() {


//    httplib::Server server;
//
//    server.Get("/hi", [](const httplib::Request &, httplib::Response &res) {
//        res.set_content("Hello World!", "text/plain");
//    });
//
//    server.listen("0.0.0.0", 8080);

    std::string currentHost = "localhost";
    int currentPort = 8080;

    HomeLights homeLights(currentHost, currentPort);
    homeLights.captureLightData();
    homeLights.displayAllLights();





    return 0;
}
