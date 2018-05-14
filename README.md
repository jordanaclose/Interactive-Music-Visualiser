# Interactive-Music-Visualiser
An interactive, 3D music visualiser that uses projection mapping and a flocking simulation (university final project)

Made for MacOS

To be downloaded:
- [AudioFrequencyMeter](https://github.com/arduino-libraries/AudioFrequencyMeter) onto Arduino Zero
- [Firmata](https://github.com/firmata/arduino) onto Arduino Uno
- [Syphon](http://syphon.v002.info/)
- Projection Mapping software (I used [HeavyM](https://heavym.net/en/))

How to run:
- Build circuits according to schematic/breadboard plans found in "schematics" folder
- Install AudioFrequencyMeter library
- Upload "AudioDetection.ino" to Arduino Zero
- Install Firmata library
- Upload "StandardFirmata" to Arduino Uno
- Open "InteractiveMusicVisualiser.xcodeproj" in Xcode
- Add path to Syphon framework to the Xcode project
- Set up projection mapping software 
- Run project in openFrameworks
- Start Syphon within the projection mapping software
- Project the visuals and enjoy
