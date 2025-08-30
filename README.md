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

---

### Test n: Get All Light States
_Get all existing lights and their states._
##### Starting the Code Challenge Application will automatically output the light states.
- [ ]  _Verify that your Code Challenge Execution is displaying at least the following output:_
```json
[
    {
        "id": "2c85bb59-c136-49f1-a429-f02f52b6c765",
        "name": "Pantry Light",
        "room": "Kitchen",
        "on": false,
        "brightness": 0
    },
    {
        "id": "56a00ec5-e3d5-4a6b-a2cf-6d88c8f6464c",
        "name": "Office Sconce 1",
        "room": "Office",
        "on": true,
        "brightness": 7
    },
    {
        "id": "edc1b691-a5af-4524-9b57-80341d90bfa2",
        "name": "Office Sconce 2",
        "room": "Office",
        "on": true,
        "brightness": 14
    },
    {
        "id": "f06b0ed2-cc50-4edd-a0f8-5c98a3c9d151",
        "name": "Living Room Lamp Left",
        "room": "Living Room",
        "on": true,
        "brightness": 95
    },
    {
        "id": "2ed8eb8e-e38b-4f86-8b9d-cbaf37be7275",
        "name": "Kitchen Overheads",
        "room": "Kitchen",
        "on": false,
        "brightness": 0
    },
    {
        "id": "af80e5c2-b235-471d-8df9-490703699eda",
        "name": "Kitchen Chandelier",
        "room": "Kitchen",
        "on": false,
        "brightness": 0
    },
    {
        "id": "9df68fec-06ac-46bf-ab61-57e9d4e963e8",
        "name": "Office Downlights",
        "room": "Office",
        "on": true,
        "brightness": 45
    },
    {
        "id": "1b1920d5-22f1-43aa-9d35-371b2075d33d",
        "name": "Porch Light",
        "room": "Porch",
        "on": false,
        "brightness": 39
    },
    {
        "id": "6ff183b0-710d-40de-94a8-81584d8ae3e8",
        "name": "String Lights",
        "room": "Back Yard",
        "on": false,
        "brightness": 47
    },
    {
        "id": "ad7e8bb4-ff0a-4b9f-b676-e94baf878e8f",
        "name": "Living Room Lamp Right",
        "room": "Living Room",
        "on": true,
        "brightness": 95
    }
]
```

---

### Test 1: Turn the Light ON

- [ ]  In the simulator's UI or via your application, send the command to turn the light ON.
- [ ]  Verify that the simulator reflects the light as ON.
- [ ]  Check that your application correctly updates and displays the new state.
- [ ]  [ ] _Add any additional verification or steps here._

---

### Test 2: Turn the Light OFF

- [ ]  In the simulator's UI or via your application, send the command to turn the light OFF.
- [ ]  Verify that the simulator reflects the light as OFF.
- [ ]  Check that your application correctly updates and displays the OFF state.
- [ ]  [ ] _Add any additional verification or steps here._

---

### Test n: Change Light Name
_Change the name of a current, existing light._
- [ ]  _Describe the goal or expected result of the test._
- [ ]  _Step 1_
- [ ]  _Step 2_
- [ ]  _Step 3_
- [ ]  [ ] _Additional steps or notes_

---

### Test n: Change Light Room
_Change the room location of the light._
- [ ]  _Describe the goal or expected result of the test._
- [ ]  _Step 1_
- [ ]  _Step 2_
- [ ]  _Step 3_
- [ ]  [ ] _Additional steps or notes_

---

### Test n: Change Light Brightness
_Change the brightness of the light._
- [ ]  _Describe the goal or expected result of the test._
- [ ]  _Step 1_
- [ ]  _Step 2_
- [ ]  _Step 3_
- [ ]  [ ] _Additional steps or notes_

---

### Test n: Add New Lights
_Add 2 new lights to the house._
- [ ]  _Describe the goal or expected result of the test._
- [ ]  _Step 1_
- [ ]  _Step 2_
- [ ]  _Step 3_
- [ ]  [ ] _Additional steps or notes_

---

### Test n: Bulk Light Info Change 1
_Change the name and on/off status of a light._
- [ ]  _Describe the goal or expected result of the test._
- [ ]  _Step 1_
- [ ]  _Step 2_
- [ ]  _Step 3_
- [ ]  [ ] _Additional steps or notes_

---

### Test n: Bulk Light Info Change 2
_Change the name and room of a light._
- [ ]  _Describe the goal or expected result of the test._
- [ ]  _Step 1_
- [ ]  _Step 2_
- [ ]  _Step 3_
- [ ]  [ ] _Additional steps or notes_

---

### Test n: Bulk Light Info Change 3
_Change the name and brightness of a light._
- [ ]  _Describe the goal or expected result of the test._
- [ ]  _Step 1_
- [ ]  _Step 2_
- [ ]  _Step 3_
- [ ]  [ ] _Additional steps or notes_

---

### Test n: Bulk Light Info Change 4
_Change the room and on/off status of a light._
- [ ]  _Describe the goal or expected result of the test._
- [ ]  _Step 1_
- [ ]  _Step 2_
- [ ]  _Step 3_
- [ ]  [ ] _Additional steps or notes_

---

### Test n: Bulk Light Info Change 5
_Change the name and brightness status of a light._
- [ ]  _Describe the goal or expected result of the test._
- [ ]  _Step 1_
- [ ]  _Step 2_
- [ ]  _Step 3_
- [ ]  [ ] _Additional steps or notes_

---

### Test n: Bulk Light Info Change 6
_Change the on/off status and brightness of a light._
- [ ]  _Describe the goal or expected result of the test._
- [ ]  _Step 1_
- [ ]  _Step 2_
- [ ]  _Step 3_
- [ ]  [ ] _Additional steps or notes_

---

### Test n: Bulk Light Info Change 7
_Change the name, room, and on/off status of a light._
- [ ]  _Describe the goal or expected result of the test._
- [ ]  _Step 1_
- [ ]  _Step 2_
- [ ]  _Step 3_
- [ ]  [ ] _Additional steps or notes_

---

### Test n: Bulk Light Info Change 8
_Change the name, room, and brightness of a light._
- [ ]  _Describe the goal or expected result of the test._
- [ ]  _Step 1_
- [ ]  _Step 2_
- [ ]  _Step 3_
- [ ]  [ ] _Additional steps or notes_

---

### Test n: Bulk Light Info Change 9
_Change the name, room, on/off status, and brightness of a light._
- [ ]  _Describe the goal or expected result of the test._
- [ ]  _Step 1_
- [ ]  _Step 2_
- [ ]  _Step 3_
- [ ]  [ ] _Additional steps or notes_

---

### Test n: Remove a Light
_Remove a light from the existing lights._
- [ ]  _Describe the goal or expected result of the test._
- [ ]  _Step 1_
- [ ]  _Step 2_
- [ ]  _Step 3_
- [ ]  [ ] _Additional steps or notes_

---

### Test n: Failed Code Challenge Start 1
_Starting the Code Challenge Application before the LightSimulator Executable and Light Simulator Browser._
- [ ]  _Step 1_
- [ ]  _Step 2_
- [ ]  _Step 3_
- [ ]  [ ] _Additional steps or notes_

---

### Test n: Failed Code Challenge Start 2
_Starting the Code Challenge Application with only the Light Simulator Browser running, but not the LightSimulator Executable._
- [ ]  _Describe the goal or expected result of the test._
- [ ]  _Step 1_
- [ ]  _Step 2_
- [ ]  _Step 3_
- [ ]  [ ] _Additional steps or notes_

---

### Test n: Failed Code Challenge Start 3
_Starting the Code Challenge Application with only the LightSimulator Executable running, but not the Light Simulator Browser._
- [ ]  _Describe the goal or expected result of the test._
- [ ]  _Step 1_
- [ ]  _Step 2_
- [ ]  _Step 3_
- [ ]  [ ] _Additional steps or notes_

---

### Test n: Failed Code Challenge Running 1
_While the Code Challenge Application, LightSimulator Executable, and the Light Simulator Browser are running, then the Light Simulator Browser only is closed._
- [ ]  _Describe the goal or expected result of the test._
- [ ]  _Step 1_
- [ ]  _Step 2_
- [ ]  _Step 3_
- [ ]  [ ] _Additional steps or notes_

---

### Test n: Failed Code Challenge Running 2
_While the Code Challenge Application, LightSimulator Executable, and the Light Simulator Browser are running, then the LightSimulator Executable only is closed._
- [ ]  _Describe the goal or expected result of the test._
- [ ]  _Step 1_
- [ ]  _Step 2_
- [ ]  _Step 3_
- [ ]  [ ] _Additional steps or notes_

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