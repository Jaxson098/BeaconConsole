https://github.com/user-attachments/assets/eb08d9dd-4af4-47e6-a203-428a4220e6b2
## Beacon Console ##
The Beacon Console is a software application developed for the [Drones in School](https://www.dronesinschool.com/) program. It allows for the control of [Beacons](https://www.dronesinschool.com/product/Capture-the-Flag-Beacon) via a GUI, where uses can select gamemodes, run games, and save scores. It is designed for use both in competitions and in practices. All gamemodes are compatible with any amount of Beacons, but competitions use a set of 10. We are currently in an alpha testing stage, with limited use at competitions on the Island of Oahu, Hawaii. However teams are free to begin using it in practices to train pilots.

## Game Modes ##
As of alpha 0.3.25 the following gamemodes have been implemented or are in development:
### Capture The Flag ###

**Implemented**. The origional Beacon game played at official competitions. 2 teams face off against eachother to capture Beacons, turning them either red or blue. Every second a Beacon in a certain color, that teams points are incremeneted by one.
### Wack-A-Mole ###

**In Development**. A pilot or team of pilots attempts to triger the rendomly popping up green beacons as fast as possible. Scoring each point every time they do so.
### Memory ###

**In Development**. All beacons have a hidden color wich is only flashed for a short time. A pilot or team of pilots attempts to trigger the correct Beacon based on the color indicated by the GUI. The less incorrect guesses the more points they will earn.

### Altitude ###
**Concept**. All beacons are either red, orange, or yellow, indicating the altitude required to trigger them correctly. A pilot or team of pilots attempts to triger the all beacons correcty, scoring a point each time they succed and losing one for each failure.

## Installation And Setup ##
The Beacon Console (see [releases](https://github.com/Jaxson098/BeaconConsole/releases/tag/0.3.25)) requires uploading custom Beacon code inorder to comunicate with them. To do so:
1. download the [Arduino IDE](https://www.arduino.cc/en/software/)
2. Copy and paste the arduiono.cpp file into the IDE
3. Install the required Libraries
4. Connect the Beacon and select it from the select board menu as a nano
5. click upload

To have the best experience please disconnect any Serial devices other than the beacons from your computer.
