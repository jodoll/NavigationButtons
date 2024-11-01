> NOTE: This is still very much in progress, don't expect too much yet

# Vision
This project aims to be a firmware that can run on different diy handlebar controllers to control a (navigation) smartphone/tablet on a motorcycle.
For example controlling [DMD2](https://www.drivemodedashboard.com/) with JaxeAdv's [BarButtons](https://jaxeadv.com/barbuttons/).  
Instead of providing a fixed set of keymaps, users will be able to define and upload their keymaps to the controller via an Android app, thus allowing them to customize them to their needs.  
Moreover, this will eliminate the need to write a firmware from scratch for a new/different controller, as only the hardware mapping part has to be implemented/configured (+ creating a keymap).

# Feature Checklist
### Basic
- [ ] Support BarButtons (make them usable with this firmware)
- [ ] Control LED

### Keyboard Hardware Setup
- [x] Matrix Keypad Support
- [ ] Pin per Button Support

### KeyMaps
- [ ] Static Keymaps in Code
- [ ] Keymaps from Storage (as some kind of text file)
- [ ] Uploading Keymaps via App

### Android App
- [ ] Creating Keymaps
- [ ] Uploading Keymaps
- [ ] Uploading Firmware

# Development
This project contains a definition to emulate the BarButton's hardware setup with [WokWi](https://wokwi.com/) for easy development.
To use it, just install the [WokWi VsCode plugin](https://marketplace.visualstudio.com/items?itemName=Wokwi.wokwi-vscode) (`wokwi.wokwi-vscode`, a free license is needed) and execute the `WokWi: Start Simulator` task form the command pallete. You might need build the project first to successfully run the simulator.

To get a nicer serial terminal, you might want to try Microsofts [Serial Monitor plugin](https://marketplace.visualstudio.com/items?itemName=ms-vscode.vscode-serial-monitor) (`ms-vscode.vscode-serial-monitor`). After installing you can connect in `tcp`-mode to `localhost:4000`.

# Credits
All credit for used libraries goes to the original creators.

The currently used libraries and frameworks are:
* [ESP32-BLE-Keyboard](https://github.com/T-vK/ESP32-BLE-Keyboard) by T-vK and Contributors
    * This library has been modified, check [git/GitHub](https://github.com/jodoll/NavigationButtons/commits/main/lib/ESP32-BLE-Keyboard%400.3.2-beta) for the changes (the Initial commit contains the Library as obtained from [GitHub](https://github.com/T-vK/ESP32-BLE-Keyboard/releases/download/0.3.2-beta/ESP32-BLE-Keyboard.zip))
    * The changes include some fixes and some changes to the media key report, to support different keys
* [Keypad](https://github.com/Chris--A/Keypad) by Mark Stanley, Alexander Brevig
* [ArduinoLog](https://github.com/thijse/Arduino-Log) by Thijs Elenbaas, MrRobot62, rahuldeo2047, NOX73, dhylands, Josha, blemasle, mfalkvidd
    * This library has been modified, check [git/GitHub](https://github.com/jodoll/NavigationButtons/commits/main/lib/ArduinoLog) for the changes (the first commited version is v1.1.1, as obtained through the PlatformIO package manager)
    * The changes allow the log statements to stay in the code on the `native` platform for tests (while doing nothing when called)
* [Arduino ESP32](https://github.com/espressif/arduino-esp32) by espressif
* [The Arduino Framework](https://www.arduino.cc/)

For development:
* [Platform IO](https://platformio.org/)
* [Wokwi](https://wokwi.com/)

For testing:
* [GoogleTest](https://github.com/google/googletest/) by Google


Special thanks goes to [JaxeAdv](https://jaxeadv.com/) for his awesome [BarButtons](https://jaxeadv.com/barButtons) project that inspired this project. All credits for anything BarButtons related (hardware and software wise) go to him.