
#include "ofApp.h"
#include "Flock.h"
#include "Global.h"
#include "Starling.h"
#include <iostream>

//--------------------------------------------------------------
void ofApp::setup(){
    
    //set up Syphon server to send openFrameworks window to HeavyM (or whatever projection mapping software)
    server.setName("Output");
    ofSetWindowTitle("ofxSyphon");
    
    //set the frame rate to 60
    ofSetFrameRate(60);
    
    //setup the serial connection to the Arduino Zero with "AudioDetection.ino" loaded onto it, at a baud rate of 115200
    serial.setup("/dev/tty.usbmodem1412", 115200);
    
    //serial.listDevices();
    //vector <ofSerialDeviceInfo> deviceList = serial.getDeviceList();
    
    //add starlings into the flock until it reaches the desired size
    for (int i = 0; i < Global::populationSize; i++)
    {
        Starling starling = Starling();
        flock.addStarling(starling);
    }
    
    //setup the serial connection to the Arduino Uno with "StandardFirmata.ino" (from Arduino libraries) loaded onto it, at a baud rate of 57600
    arduino.connect("/dev/tty.usbmodem1421", 57600);
    arduino.sendFirmwareVersionRequest();
    
    // listen for EInitialized notification. this indicates that the arduino is ready to receive commands and it is safe to call setupArduino()
    ofAddListener(arduino.EInitialized, this, &ofApp::setupArduino);
    bSetupArduino    = false;    // flag so we setup arduino when its ready, you don't need to touch this :)
}

//--------------------------------------------------------------
void ofApp::update(){
    
    //update the Arduino
    updateArduino();
}

//--------------------------------------------------------------
void ofApp::setupArduino(const int & version) {
    
    // remove listener because we don't need it anymore
    ofRemoveListener(arduino.EInitialized, this, &ofApp::setupArduino);
    
    // it is now safe to send commands to the Arduino
    bSetupArduino = true;
    
    // print firmware name and version to the console
    ofLogNotice() << arduino.getFirmwareName();
    ofLogNotice() << "firmata v" << arduino.getMajorFirmwareVersion() << "." << arduino.getMinorFirmwareVersion();
    
    // set pins A1,2,3 to analog input
    arduino.sendAnalogPinReporting(1, ARD_ANALOG);
    arduino.sendAnalogPinReporting(2, ARD_ANALOG);
    arduino.sendAnalogPinReporting(3, ARD_ANALOG);
    
    // Listen for changes on the analog pins
    ofAddListener(arduino.EAnalogPinChanged, this, &ofApp::analogPinChanged);
}

//--------------------------------------------------------------
void ofApp::updateArduino(){
    
    // update the arduino, get any data or messages.
    arduino.update();
}

//--------------------------------------------------------------
void ofApp::analogPinChanged(const int & pinNum) {
    
    //if Analog Pin 1 ia being used, get the value of the input (which will be a value between 0 and 1024) , divide by 4 (to make it a byte), then set the variable H to this number
    if(pinNum == 1){
        H = (arduino.getAnalog(pinNum))/4;
    }
    //if Analog Pin 2 ia being used, get the value of the input (which will be a value between 0 and 1024) , divide by 4 (to make it a byte), then set the variable S to this number
    else if(pinNum == 2){
        S = (arduino.getAnalog(pinNum))/4;
    }
    //if Analog Pin 3 ia being used, get the value of the input (which will be a value between 0 and 1024) , divide by 4 (to make it a byte), then set the variable L to this number
    else if(pinNum == 3){
        L = (arduino.getAnalog(pinNum))/4;
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    //set background colour to black
    ofBackground(0);
    
    //if the serial connection to Arduino Zero is running, set x to whatever char value is being received
    if (serial.available() > 0){
        x = serial.readByte();
    }
    
    //if the serial connection to Arduino Uno has not been set up, set a default colour of flock
    if (!bSetupArduino) {
        c.set(255, 255, 255);
        ofSetColor(c);
        ofFill();
    }
    else{ //otherwise, colour of flock is based on values read from Arduino Uno
        c = ofColor::fromHsb(H, S, L);
        ofSetColor(c);
        ofFill();
    }
    
    //run the flock
    flock.run();
    //call the audio reaction code
    musicReact();
    //publish the openFrameworks window to the Syphon server
    server.publishScreen();
    
    //set x to 'x' so that, if another value is not received over the serial, x is ignored rather than remaining the same as its previous value
    x = 'x';
}

//--------------------------------------------------------------
void ofApp::musicReact()
{
    //if the char received over serial is 's', draw a small ring in the middle of the screen
    if(x == 's')
    {
        ofSetColor(c, 150);
        ofFill();
        ofDrawCircle(Global::width/2, Global::height/2, Global::height/4);
        ofSetColor(0, 0, 0);
        ofFill();
        ofDrawCircle(Global::width/2, Global::height/2, Global::height/4 - 80);
    }
    //if the char received over serial is 'r', draw a medium-sized ring in the middle of the screen
    if(x == 'r')
    {
        ofSetColor(c, 150);
        ofFill();
        ofDrawCircle(Global::width/2, Global::height/2, Global::height/3);
        ofSetColor(0, 0, 0);
        ofFill();
        ofDrawCircle(Global::width/2, Global::height/2, Global::height/3 - 80);
    }
    //if the char received over serial is 't', draw a large ring in the middle of the screen
    if(x == 't')
    {
        ofSetColor(c, 150);
        ofFill();
        ofDrawCircle(Global::width/2, Global::height/2, Global::height/2);
        ofSetColor(0, 0, 0);
        ofFill();
        ofDrawCircle(Global::width/2, Global::height/2, Global::height/2 - 80);
    }
    //if the char received over serial is 'b', call bass() function on 1/3 of starlings in the flock
    if(x == 'b')
    {
        ofSetColor(c, 120);
        ofFill();
        for(int i = 0; i < (int)((Global::populationSize)/3); i++)
        {
            flock.getStarling().at(i).bass();
        }
    }
    //if the char received over serial is 'm', call midrange() function on 1/3 of starlings in the flock
    if(x == 'm')
    {
        for(int i = (int)((Global::populationSize)/3); i < (int)((2 * Global::populationSize)/3); i++)
        {
            flock.getStarling().at(i).midrange();
        }
    }
    //if the char received over serial is 'h', call high() function on 1/3 of starlings in the flock
    if(x == 'h')
    {
        for(int i = (int)((2 * Global::populationSize)/3); i < Global::populationSize; i++)
        {
            flock.getStarling().at(i).high();
        }
    }
}

