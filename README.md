# Light Status Simulator Coding Challenge

A C++ software project to interact with the [Josh.ai LightSimulator](https://github.com/jstarllc/JoshCodingChallenge/releases/tag/v1.0) via API, demonstrating integration and control logic. Developed using CLion 2025.2 on Windows 11.

---

## Authors

- Cory Jaramillo - cory.jaramillo8@gmail.com

---

## Prerequisites

- [ ]  Windows 11 OS
- [ ]  CMake 3.31 or greater
- [ ]  CLion 2024 or greater
- [ ]  MinGW compiler 11.0w64 or greater (also comes bundled with CLion)
- [ ]  Git (recommended for cloning the repository)
- [ ]  [Josh.ai LightSimulator](https://github.com/jstarllc/JoshCodingChallenge/releases/tag/v1.0) executable for Windows

---

## Run Locally

1. [ ]  Clone the repository:

```bash
git clone --branch code_challenge_dev https://github.com/coryjaramillo/cj_lightstatussim_code_challenge.git
cd cj_lightstatussim_code_challenge
```
2. [ ]  Download the [Josh.ai LightSimulator](https://github.com/jstarllc/JoshCodingChallenge/releases/tag/v1.0) for Windows.
3. [ ]  Extract and launch the LightSimulator executable.
4. [ ]  Open CLion.
5. [ ]  Go to `File > Open` and select the root project folder: "/cj_lightstatussim_code_challenge".

---

## CLion Build Instructions

1. [ ]  Open the project in CLion.
2. [ ]  In CLion, navigate to `File > Settings > Build, Execution, Deployment > CMake`.
2. [ ]  Add these four CMake build profiles:
- [ ]  `Debug_Simple`
   - [ ]  `Name: Debug_Simple`
   - [ ]  `Build type: Debug`
   - [ ]  `Leave all other profile settings to default`
- [ ]  `Debug_Verbose`
   - [ ]  `Name: Debug_Verbose`
   - [ ]  `Build type: Debug`
   - [ ]  `Leave all other profile settings to default`
- [ ]  `Debug_All`
   - [ ]  `Name: Debug_All`
   - [ ]  `Build type: Debug`
   - [ ]  `Leave all other profile settings to default`
- [ ]  `Release`
   - [ ]  `Name: Release`
   - [ ]  `Build type: Release`
   - [ ]  `Leave all other profile settings to default`
3. [ ]  Click Apply.
4. [ ]  Click OK.
5. [ ]  Set your active build profile in the CLion top-right dropdown.
6. [ ]  Click **Build** to build the project for the currently selected profile.

---

## Usage/Examples

- Ensure the LightSimulator.exe is running.

- When started, it will open a terminal window waiting for a connection confirmation.

- Open your web browser and go to http://localhost:8080 to confirm the LightSimulator is ready.

- With the simulator active, in CLion select your desired build profile and run the project.

- Interactions can now occur via the browser UI connected to the simulator.

- At this point, you should see initial output in the CLion terminal when you run the application.

```

```
## Testing

### Test Setup
- [ ]  [Verify LightSimulator Executable Setup](#lightsimulator-executable-setup)
- [ ]  [Verify Light Simulator Browser Setup](#light-simulator-browser-setup)
  _If you start the browser before the executale, you will need to refresh the browser to connect to the executable._
- [ ]  [Verify Code Challenge Execution](#code-challenge-execution)
- [ ]  [Option 1](#option-1)
-    _OR_
- [ ]  [Option 2](#option-2)

#### LightSimulator Executable Setup
- [ ]  Open File Explorer.
- [ ]  Locate LightSimulator folder on your system.
- [ ]  Launch LightSimulator_windows_amd64.exe.  
  _If you do not have the LightSimulator downloaded, see the [Run Locally](#run-locally) section for download and installation steps._
- [ ]  Validate the LightSimulator is running by locating an open terminal window with at least the following at the beginning of the output:
  ```sh
   [GIN-debug] [WARNING] Creating an Engine instance with the Logger and Recovery middleware already attached.
   
   [GIN-debug] [WARNING] Running in "debug" mode. Switch to "release" mode in production.
    - using env:   export GIN_MODE=release
    - using code:  gin.SetMode(gin.ReleaseMode)
   
   [GIN-debug] GET    /static/*filepath         --> github.com/gin-gonic/gin.(*RouterGroup).createStaticHandler.func1 (4 handlers)
   [GIN-debug] HEAD   /static/*filepath         --> github.com/gin-gonic/gin.(*RouterGroup).createStaticHandler.func1 (4 handlers)
   [GIN-debug] GET    /lights                   --> main.GetLights (4 handlers)
   [GIN-debug] GET    /lights/:id               --> main.GetLightByID (4 handlers)
   [GIN-debug] POST   /lights                   --> main.AddLight (4 handlers)
   [GIN-debug] DELETE /lights/:id               --> main.DeleteLightByID (4 handlers)
   [GIN-debug] PUT    /lights/:id               --> main.UpdateLightByID (4 handlers)
   [GIN-debug] GET    /                         --> main.main.func1 (4 handlers)
   [GIN-debug] [WARNING] You trusted all proxies, this is NOT safe. We recommend you to set a value.
   Please check https://pkg.go.dev/github.com/gin-gonic/gin#readme-don-t-trust-all-proxies for details.
   [GIN-debug] Listening and serving HTTP on :8080
  ```

#### Light Simulator Browser Setup
- [ ]  Open your browser.
- [ ]  Go to http://localhost:8080.
- [ ]  Verify the simulator is running and ready.

#### Code Challenge Execution
##### Option #1
- [ ]  Open the project in CLion.
- [ ]  Verify that CLion is configured with the 4 needed build profiles
- [ ] `cmake-build-debug-simple`
- [ ] `cmake-build-debug-verbose`
- [ ] `cmake-build-debug-all`
- [ ] `cmake-build-release`
  _If you do not have all 4 of the above build profiles, see [CLion Build Instructions](#clion-build-instructions) for build setup._
- [ ]  Select your desired build profile.
- [ ]  Build and run your project from CLion so it's active and able to interact with the simulator.

##### Option #2
- [ ]  Open File Explorer.
- [ ]  Navigate to the desired build folder.
- [ ]  Run the build's executable.
- [ ]  Verify the executable is running by locating the terminal pop-up window.

#### Obtain lights and their states
_Steps to execute commands in the Light Simulator Browser interface to obtain light info. All steps below are performed in the simulator UI._
- [ ]  Verify that the Light Simulator Browser is running.
   - _If is it not running, reference [LightSimulator Executable](#lightsimulator-executable-setup) and [Light Simulator Browser](#light-simulator-browser-setup)._
- [ ]  Click "Get all lights" button.
- ![Image showing a highlighted part to indicate where the "Get all lights" button is located on the simulator UI.](assets/simulator_UI/get_all_lights.png)
- [ ]  Click "Send".
- ![Image showing a highlighted part to indicate where the "Send" button is located on the simulator UI.](assets/simulator_UI/send_button.png)
- [ ]  Copy the "id" value of any light.
- ![Image of the json style output in the simulator UI after clicking "Get all lights" then "Send".](assets/simulator_UI/get_all_lights_output.png)
- [ ]  Click "Get light state".
- ![Image showing a highlighted part to indicate where the "Get light state" button is located on the simulator UI.](assets/simulator_UI/get_light_state.png)
- [ ]  Paste the copied value in place of "<id>" on the URL line. See example below.
```http request
/lights/9df68fec-06ac-46bf-ab61-57e9d4e963e8
```
- ![Image of the URL line populated with "/lights/9df68fec-06ac-46bf-ab61-57e9d4e963e8".](assets/simulator_UI/URL_populated.png)
- [ ]  Click "Send".
- ![Image of the URL line populated with "/lights/9df68fec-06ac-46bf-ab61-57e9d4e963e8" and the "Send" button.](assets/simulator_UI/URL_populated_with_send_button.png)
- [ ]  Verify that the output in the Light Simulator Browser interface looks like below.
```json
{
  "id": "9df68fec-06ac-46bf-ab61-57e9d4e963e8",
  "name": "Office Downlights",
  "room": "Office",
  "on": true,
  "brightness": 114
}
```
- ![Image of sending the query to get the light state and the output results in the simulator UI listed below the "Send" button.](assets/simulator_UI/send_get_light_state_output.png)

---

### Test 1: Get All Light States
_Get all existing lights and their states._
##### Starting the [Code Challenge](#code-challenge-execution) Application will automatically output the light states.
#### EXPECTED RESULT:
- [ ]  _Verify that your Code Challenge Execution is displaying at least the following output:_
- ![Image of the program start that shows all light states upon starting the api and simulator UI.](assets/terminal_UI/get_all_light_states_application_start.png)

---

### Test 2: Turn the Light OFF
_Turn off any light in the light system._
- [ ]  Repeat the steps in [Obtain Lights and their states](#obtain-lights-and-their-states) to get a light ID.
- [ ]  In the simulator UI, Click "Turn off".
- ![Image showing a highlighted part to indicate where the "Turn off" button is located on the simulator UI.](assets/simulator_UI/turn_off.png)
- [ ]  Paste the copied value in place of "<id>" on the URL line. See example below.
```http request
/lights/9df68fec-06ac-46bf-ab61-57e9d4e963e8
```
- ![Image of the URL line populated with "/lights/9df68fec-06ac-46bf-ab61-57e9d4e963e8".](assets/simulator_UI/URL_populated.png)
- [ ]  In the simulator UI, click "Send".
- ![Image showing a highlighted part to indicate where the "Send" button is located on the simulator UI.](assets/simulator_UI/send_button.png)
#### EXPECTED RESULTS:
- [ ]  Verify that the simulator reflects the light as OFF (false). See example below.
```json
{
   "id": "9df68fec-06ac-46bf-ab61-57e9d4e963e8",
   "name": "Office Downlights",
   "room": "Office",
   "on": false,
   "brightness": 114
}
```
- ![Image showing the output in the simulator UI of successfully turning off a light using the UI.](assets/simulator_UI/turn_off_output.png)
- [ ]  Check that your application correctly updates and displays the new state.
```json
{
   "id": "9df68fec-06ac-46bf-ab61-57e9d4e963e8",
   "on": false
}
```
- ![Image showing the output in the terminal UI of successfully turning off a light using the UI.](assets/terminal_UI/turn_off_output.png)

---

### Test 3: Turn the Light ON
_Turn on any light in the light system._
- [ ]  Repeat the steps in [Obtain Lights and their states](#obtain-lights-and-their-states) to get a light ID.
- [ ]  In the simulator UI, Click "Turn on".
- ![Image showing a highlighted part to indicate where the "Turn on" button is located on the simulator UI.](assets/simulator_UI/turn_on.png)
- [ ]  Paste the copied value in place of "<id>" on the URL line. See example below.
```http request
/lights/9df68fec-06ac-46bf-ab61-57e9d4e963e8
```
- ![Image of the URL line populated with "/lights/9df68fec-06ac-46bf-ab61-57e9d4e963e8".](assets/simulator_UI/URL_populated.png)
- [ ]  In the simulator UI, click "Send".
- ![Image showing a highlighted part to indicate where the "Send" button is located on the simulator UI.](assets/simulator_UI/send_button.png)
#### EXPECTED RESULTS:
- [ ]  Verify that the simulator reflects the light as ON (true). See example below.
```json
{
   "id": "9df68fec-06ac-46bf-ab61-57e9d4e963e8",
   "name": "Office Downlights",
   "room": "Office",
   "on": true,
   "brightness": 114
}
```
- ![Image showing the output in the simulator UI of successfully turning on a light using the UI.](assets/simulator_UI/turn_on_output.png)
- [ ]  Check that your application correctly updates and displays the new state.
```json
{
   "id": "9df68fec-06ac-46bf-ab61-57e9d4e963e8",
   "on": true
}
```
- ![Image showing the output in the terminal UI of successfully turning on a light using the UI.](assets/terminal_UI/turn_on_output.png)

---

### Test 4: Change Light Name
_Change the name of a current, existing light._
- [ ]  Repeat the steps in [Obtain Lights and their states](#obtain-lights-and-their-states) to get a light ID.
- [ ]  In the simulator UI, Click "Set name".
- ![Image showing a highlighted part to indicate where the "Set name" button is located on the simulator UI.](assets/simulator_UI/set_name.png)
- [ ]  Paste the copied value in place of "<id>" on the URL line. See example below.
```http request
/lights/9df68fec-06ac-46bf-ab61-57e9d4e963e8
```
- ![Image of the URL line populated with "/lights/9df68fec-06ac-46bf-ab61-57e9d4e963e8".](assets/simulator_UI/URL_populated.png)
- [ ]  In the simulator UI, replace "new name" with "Office Desk Light" in the "Message Body".
- ![Image of the message body showing a json input of "name" with "Office Desk Light" as the new data.](assets/simulator_UI/set_name_message_body_populated.png)
- [ ]  In the simulator UI, click "Send".
- ![Image showing a highlighted part to indicate where the "Send" button is located on the simulator UI.](assets/simulator_UI/send_button.png)
#### EXPECTED RESULTS:
- [ ]  Verify that the simulator reflects the light name as "Office Desk Light". See example below.
```json
{
   "id": "9df68fec-06ac-46bf-ab61-57e9d4e963e8",
   "name": "Office Desk Light",
   "room": "Office",
   "on": true,
   "brightness": 114
}
```
- ![Image showing the output in the simulator UI of successfully changing the name of a light using the UI.](assets/simulator_UI/set_name_output.png)
- [ ]  Check that your application correctly updates and displays the new state.
```json
{
   "id": "9df68fec-06ac-46bf-ab61-57e9d4e963e8",
   "name": "Office Desk Light"
}
```
- ![Image showing the output in the terminal UI of successfully changing the name of a light using the UI.](assets/terminal_UI/set_name_output.png)

---

### Test 5: Change Light Room
_Change the room location of the light._
- [ ]  Repeat the steps in [Obtain Lights and their states](#obtain-lights-and-their-states) to get a light ID.
- [ ]  In the simulator UI, Click "Set room".
- ![Image showing a highlighted part to indicate where the "Set room" button is located on the simulator UI.](assets/simulator_UI/set_room.png)
- [ ]  Paste the copied value in place of "<id>" on the URL line. See example below.
```http request
/lights/9df68fec-06ac-46bf-ab61-57e9d4e963e8
```
- ![Image of the URL line populated with "/lights/9df68fec-06ac-46bf-ab61-57e9d4e963e8".](assets/simulator_UI/URL_populated.png)
- [ ]  In the simulator UI, replace "new room" with "Main Office" in the "Message Body".
- ![Image of the message body showing a json input of "room" with "Main Office" as the new data.](assets/simulator_UI/set_room_message_body_populated.png)
- [ ]  In the simulator UI, click "Send".
- - ![Image showing a highlighted part to indicate where the "Send" button is located on the simulator UI.](assets/simulator_UI/send_button.png)
#### EXPECTED RESULTS:
- [ ]  Verify that the simulator reflects the light room as "Main Office". See example below.
```json
{
   "id": "9df68fec-06ac-46bf-ab61-57e9d4e963e8",
   "name": "Office Desk Light",
   "room": "Main Office",
   "on": true,
   "brightness": 114
}
```
- ![Image showing the output in the simulator UI of successfully changing the name of a room using the UI.](assets/simulator_UI/set_room_output.png)
- [ ]  Check that your application correctly updates and displays the new state.
```json
{
   "id": "9df68fec-06ac-46bf-ab61-57e9d4e963e8",
   "name": "Office Desk Light"
}
```
- ![Image showing the output in the terminal UI of successfully changing the name of a room using the UI.](assets/terminal_UI/set_room_output.png)

---

### Test 6: Change Light Brightness
_Change the brightness of the light._
- [ ]  Repeat the steps in [Obtain Lights and their states](#obtain-lights-and-their-states) to get a light ID.
- [ ]  In the simulator UI, Click "Set brightness".
- ![Image showing a highlighted part to indicate where the "Set brightness" button is located on the simulator UI.](assets/simulator_UI/set_brightness.png)
- [ ]  Paste the copied value in place of "<id>" on the URL line. See example below.
```http request
/lights/9df68fec-06ac-46bf-ab61-57e9d4e963e8
```
- ![Image of the URL line populated with "/lights/9df68fec-06ac-46bf-ab61-57e9d4e963e8".](assets/simulator_UI/URL_populated.png)
- [ ]  In the simulator UI, replace brightness value with an integer from 0 to 255 in the "Message Body".
- ![Image 1 of 3 of the message body showing a json input of "brightness" with a value in the range of 0 to 255 as the new data.](assets/simulator_UI/set_brightness_message_body_populated_1.png)
- [ ]  In the simulator UI, click "Send".
- ![Image showing a highlighted part to indicate where the "Send" button is located on the simulator UI.](assets/simulator_UI/send_button.png)
- [ ]  Repeat the value change at least 3 times. I did 10, 255, and 78.
- ![Image 1 of 3 of the message body showing a json input of "brightness" with a value in the range of 0 to 255 as the new data.](assets/simulator_UI/set_brightness_message_body_populated_1.png)
- ![Image 2 of 3 of the message body showing a json input of "brightness" with a value in the range of 0 to 255 as the new data.](assets/simulator_UI/set_brightness_message_body_populated_2.png)
- ![Image 3 of 3 of the message body showing a json input of "brightness" with a value in the range of 0 to 255 as the new data.](assets/simulator_UI/set_brightness_message_body_populated_3.png)
#### EXPECTED RESULTS:
- [ ]  Verify that the simulator reflects the "brightness" as your entered value. See example below.
- ![Image showing the output in the simulator UI of successfully changing the brightness of a room 3 times using the UI.](assets/simulator_UI/set_brightness_all_3_outputs.png)
- [ ]  Check that your application correctly updates and displays the new state for each change.
##### _NOTE: Terminal output will show the values in human readable percentage of brightness._
##### _Convert 0-255 to Percentage Equation: percentage = ._
```json
[
   {
      "id": "9df68fec-06ac-46bf-ab61-57e9d4e963e8",
      "brightness": 4
   },
   {
      "id": "9df68fec-06ac-46bf-ab61-57e9d4e963e8",
      "brightness": 100
   },
   {
      "id": "9df68fec-06ac-46bf-ab61-57e9d4e963e8",
      "brightness": 31
   }
]
```
- ![Image showing the output in the terminal UI of successfully changing the brightness of a room 3 times using the UI.](assets/terminal_UI/set_brightness_all_3_outputs.png)
- 
---

### Test 7: Add New Lights
_Add 2 new lights to the house._
- [ ]  _Describe the goal or expected result of the test._
- [ ]  _Step 1_
- [ ]  _Step 2_
- [ ]  _Step 3_
#### EXPECTED RESULTS:

---

### Test 8: Bulk Light Info Change 1
_Change the name and on/off status of a light._
- [ ]  Repeat the steps in [Obtain Lights and their states](#obtain-lights-and-their-states) to get a light ID.
- [ ]  _Step 1_
- [ ]  _Step 2_
- [ ]  _Step 3_
#### EXPECTED RESULTS:

---

### Test 9: Bulk Light Info Change 2
_Change the name and room of a light._
- [ ]  Repeat the steps in [Obtain Lights and their states](#obtain-lights-and-their-states) to get a light ID.
- [ ]  _Step 1_
- [ ]  _Step 2_
- [ ]  _Step 3_
#### EXPECTED RESULTS:

---

### Test 10: Bulk Light Info Change 3
_Change the name and brightness of a light._
- [ ]  Repeat the steps in [Obtain Lights and their states](#obtain-lights-and-their-states) to get a light ID.
- [ ]  _Step 1_
- [ ]  _Step 2_
- [ ]  _Step 3_
#### EXPECTED RESULTS:

---

### Test 11: Bulk Light Info Change 4
_Change the room and on/off status of a light._
- [ ]  Repeat the steps in [Obtain Lights and their states](#obtain-lights-and-their-states) to get a light ID.
- [ ]  _Step 1_
- [ ]  _Step 2_
- [ ]  _Step 3_
#### EXPECTED RESULTS:

---

### Test 12: Bulk Light Info Change 5
_Change the name and brightness status of a light._
- [ ]  Repeat the steps in [Obtain Lights and their states](#obtain-lights-and-their-states) to get a light ID.
- [ ]  _Step 1_
- [ ]  _Step 2_
- [ ]  _Step 3_
#### EXPECTED RESULTS:

---

### Test 13: Bulk Light Info Change 6
_Change the on/off status and brightness of a light._
- [ ]  Repeat the steps in [Obtain Lights and their states](#obtain-lights-and-their-states) to get a light ID.
- [ ]  _Step 1_
- [ ]  _Step 2_
- [ ]  _Step 3_
#### EXPECTED RESULTS:

---

### Test 14: Bulk Light Info Change 7
_Change the name, room, and on/off status of a light._
- [ ]  Repeat the steps in [Obtain Lights and their states](#obtain-lights-and-their-states) to get a light ID.
- [ ]  _Step 1_
- [ ]  _Step 2_
- [ ]  _Step 3_
#### EXPECTED RESULTS:

---

### Test 15: Bulk Light Info Change 8
_Change the name, room, and brightness of a light._
- [ ]  Repeat the steps in [Obtain Lights and their states](#obtain-lights-and-their-states) to get a light ID.
- [ ]  _Step 1_
- [ ]  _Step 2_
- [ ]  _Step 3_
#### EXPECTED RESULTS:

---

### Test 16: Bulk Light Info Change 9
_Change the name, room, on/off status, and brightness of a light._
- [ ]  Repeat the steps in [Obtain Lights and their states](#obtain-lights-and-their-states) to get a light ID.
- [ ]  _Step 1_
- [ ]  _Step 2_
- [ ]  _Step 3_
#### EXPECTED RESULTS:

---

### Test 17: Remove a Light
_Remove a light from the existing lights._
- [ ]  Repeat the steps in [Obtain Lights and their states](#obtain-lights-and-their-states) to get a light ID.
- [ ]  _Step 1_
- [ ]  _Step 2_
- [ ]  _Step 3_
#### EXPECTED RESULTS:

---

### Test 18: Failed Code Challenge Start 1
_Starting the Code Challenge Application before the LightSimulator Executable and Light Simulator Browser._
- [ ]  _Step 1_
- [ ]  _Step 2_
- [ ]  _Step 3_
#### EXPECTED RESULTS:

---

### Test 19: Failed Code Challenge Start 2
_Starting the Code Challenge Application with only the Light Simulator Browser running, but not the LightSimulator Executable._
- [ ]  _Describe the goal or expected result of the test._
- [ ]  _Step 1_
- [ ]  _Step 2_
- [ ]  _Step 3_
#### EXPECTED RESULTS:

---

### Test 20: Failed Code Challenge Start 3
_Starting the Code Challenge Application with only the LightSimulator Executable running, but not the Light Simulator Browser._
- [ ]  _Describe the goal or expected result of the test._
- [ ]  _Step 1_
- [ ]  _Step 2_
- [ ]  _Step 3_
#### EXPECTED RESULTS:

---

### Test 21: Failed Code Challenge Running 1
_While the Code Challenge Application, LightSimulator Executable, and the Light Simulator Browser are running, then the Light Simulator Browser only is closed._
- [ ]  _Describe the goal or expected result of the test._
- [ ]  _Step 1_
- [ ]  _Step 2_
- [ ]  _Step 3_
#### EXPECTED RESULTS:

---

### Test 22: Failed Code Challenge Running 2
_While the Code Challenge Application, LightSimulator Executable, and the Light Simulator Browser are running, then the LightSimulator Executable only is closed._
- [ ]  _Describe the goal or expected result of the test._
- [ ]  _Step 1_
- [ ]  _Step 2_
- [ ]  _Step 3_
#### EXPECTED RESULTS:

---

## FAQ

**Q:** CLion reports “build directory not found”  
**A:** Ensure all CMake profiles are properly configured in the settings and the corresponding directories exist.

**Q:** “Failed to connect to LightSimulator” error  
**A:** Ensure LightSimulator.exe is running and you have visited http://localhost:8080 in your browser to confirm it’s active.

**Q:** Application does not respond to simulator changes  
**A:** Double-check if the browser connection to LightSimulator is established and that the simulator’s status reflects your actions.
## Feedback

For questions or feedback, please open a GitHub issue on this repository or contact [Cory Jaramillo](https://github.com/coryjaramillo) through your GitHub profile.
## Related

- [Josh.ai LightSimulator Release v1.0](https://github.com/jstarllc/JoshCodingChallenge/releases/tag/v1.0)
- [JetBrains CLion Documentation](https://www.jetbrains.com/help/clion/)