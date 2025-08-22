# Light Status Simulator Coding Challenge

A C++ software project to interact with the [Josh.ai LightSimulator](https://github.com/jstarllc/JoshCodingChallenge/releases/tag/v1.0) via API, demonstrating integration and control logic. Developed using CLion 2025.2 on Windows 11.
## Authors

- Cory Jaramillo - cory.jaramillo8@gmail.com


## Prerequisites

- [ ]  Windows 11 OS
- [ ]  CMake 3.31 or greater
- [ ]  CLion 2024 or greater
- [ ]  MinGW compiler 11.0w64 or greater (also comes bundled with CLion)
- [ ]  Git (recommended for cloning the repository)
- [ ]  [Josh.ai LightSimulator](https://github.com/jstarllc/JoshCodingChallenge/releases/tag/v1.0) executable for Windows

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

## Build Instructions

1. [ ]  In CLion, navigate to `File > Settings > Build, Execution, Deployment > CMake`.
2. [ ]  Add these four CMake build profiles:
- [ ]  `Debug_Simple`
    - [ ]  `Name: Debug_Simple`
    - [ ]  `Build type: Debug`
    - [ ]  `Build directory: build\debug_simple`
    - [ ]  `Leave all other profile settings to default`
- [ ]  `Debug_Verbose`
    - [ ]  `Name: Debug_Verbose`
    - [ ]  `Build type: Debug`
    - [ ]  `Build directory: build\debug_verbose`
    - [ ]  `Leave all other profile settings to default`
- [ ]  `Debug_All`
    - [ ]  `Name: Debug_All`
    - [ ]  `Build type: Debug`
    - [ ]  `Build directory: build\debug_all`
    - [ ]  `Leave all other profile settings to default`
- [ ]  `Release`
    - [ ]  `Name: Release`
    - [ ]  `Build type: Release`
    - [ ]  `Build directory: build\release`
    - [ ]  `Leave all other profile settings to default`
3. [ ]  Click Apply.
4. [ ]  Click OK.
5. [ ]  Set your active build profile in the CLion top-right dropdown.
6. [ ]  Click **Build** to build the project for the currently selected profile.
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

- [ ]  Launch LightSimulator.exe.  
  _If you do not have the LightSimulator downloaded, see the [Run Locally](#run-locally) section for download and installation steps._
- [ ]  Open your browser and go to http://localhost:8080 to confirm the simulator is running and ready.
- [ ]  Open the project in CLion.
- [ ]  Select your desired build profile.
- [ ]  Build and run your project from CLion so it's active and able to interact with the simulator.
- [ ]  [ ] _Add any additional environment or dependency setup here._


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

### Test 3: Query Light STATUS

- [ ]  Use your application (or the API, if supported) to request the current light STATUS.
- [ ]  Confirm that the returned/status value matches the simulator's display.
- [ ]  [ ] _Add any custom UI/API result checks as needed._

---

### Test 4: Handle Invalid Command

- [ ]  Attempt to send an invalid or malformed command from your application (e.g., a typo or an unsupported request).
- [ ]  Check that your application captures and displays an appropriate error message.
- [ ]  Verify that the simulator remains stable and no unexpected state changes occur.
- [ ]  [ ] _Add any further test details or variations here._

---

### Test 5: [New Test Template]

- [ ]  _Describe the goal or expected result of the test._
- [ ]  _Step 1_
- [ ]  _Step 2_
- [ ]  _Step 3_
- [ ]  [ ] _Additional steps or notes_

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