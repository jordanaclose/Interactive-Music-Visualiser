/*
  Simple Frequency Meter for Arduino Zero

  Demonstrates how to sample an input signal and get back its frequency

  This example code is in the public domain

  http://arduino.cc/en/Tutorial/SimpleAudioFrequencyMeter

  created by Arturo Guadalupi <a.guadalupi@arduino.cc>
  10 Nov 2015
*/

#include <AudioFrequencyMeter.h>

AudioFrequencyMeter meter; //initialise AudioFrequencyMeter

int prevAmp; //variable to store previous amplitude
int ampDiff; //variable to store increase in amplitude

void setup() {
  //set prevAmp to 100, so that ampDiff will definitely be less than 30 with the first audio value received 
  prevAmp = 100;

  //initialise serial at a baud rate of 115200 
  Serial.begin(115200);
  Serial.println("started");

  meter.setBandwidth(20.00, 1500);    // Ignore frequency out of this range
  meter.begin(A0, 45000);             // Intialize A0 at sample rate of 45kHz
}

void loop() {

  float frequency = meter.getFrequency(); //variable to store frequency value received
  int amplitude = meter.getMaxAmp(); //variable to store amplitude value received 

  ampDiff = amplitude - prevAmp; //calculate increase in amplitude

/*
  if(frequency > 0){
    Serial.print(frequency);
    Serial.println(" Hz");

    Serial.print("Amplitude:: ");
    Serial.println(amplitude);
  }
*/

    //"sub bass" case - if the frequency received is 80Hz or less and the increase in
    //amplitude is greater than 30, write 's' to serial
    if(ampDiff > 30 && frequency <= 80){
      Serial.write('s');
    }
    //"rhythm" case - if the frequency received is between 200Hz and 1000Hz
    //and the increase in amplitude is greater than 30, write 'r' to serial
    if(ampDiff > 30 && frequency > 200 && frequency < 1000){
      Serial.write('r');
    }
    //"treble" case - if the frequency received is 1000Hz or more and the increase in
    //amplitude is greater than 30, write 't' to serial
    if(ampDiff > 30 && frequency >= 1000){
      Serial.write('t');
    }
    //"bass" case - if the frequency received is greater than 0Hz, 150Hz or less and 
    //the increase in amplitude is 30 or less, write 'b' to serial
    if(ampDiff <= 30 && frequency > 0 && frequency <= 150){
      Serial.write('b');
    }
    //"midrange" case - if the frequency received is 200Hz or more, less than 1000Hz,
    //amplitude is greater than 30 and the increase in amplitude is 30 orf less, 
    //write 'm' to serial 
    if(ampDiff <= 30 && frequency >= 200 && frequency < 1000 && amplitude > 30){
      Serial.write('m');
    }
    //"high" case - if the frequency received is 1000Hz or more and the increase in
    //amplitude is 30 or less, write 'h' to serial
    if(ampDiff <= 30 && frequency >= 1000){
      Serial.write('h');
    }

    prevAmp = amplitude; //update previous amplitude

    delay(10); //pause for 10ms 
}
