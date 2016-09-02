// tell the Arduino you're using the Awesome Shield library
#include <Awesome.h>
// tell the Arduino you're using the Awesome Shield hardware
Awesome awesome;

// declare variables here
int freq, r, g, b, knobReading, ambientLight, lightReading;

void lightSensorWorkingSignal() {
  
}

void setup() {
  awesome.setup(9600);
  // set up all port pins as outputs
  pinMode(port1PrimaryPin,OUTPUT);
  pinMode(port1SecondaryPin,OUTPUT);
  pinMode(port2PrimaryPin,OUTPUT);
  pinMode(port2SecondaryPin,OUTPUT);
  pinMode(port3PrimaryPin,OUTPUT);
  pinMode(port3SecondaryPin,OUTPUT);

  // write all port pins high
  digitalWrite(port1PrimaryPin,HIGH);
  digitalWrite(port1SecondaryPin,HIGH);
  digitalWrite(port2PrimaryPin,HIGH);
  digitalWrite(port2SecondaryPin,HIGH);
  digitalWrite(port3PrimaryPin,HIGH);
  digitalWrite(port3SecondaryPin,HIGH);

  ambientLight = awesome.lightSensor.reading();
}

void loop() {
  // lightSensor controls buzzer frequency
  lightReading = awesome.lightSensor.reading();
  if ( lightReading != 0 && lightReading < 0.4*ambientLight ) {
    freq = 800;
  } else {
    freq = 200;
  }

  // button press turns buzzer on
  if ( awesome.button.isDown() ) {
    awesome.buzzer.turnOn(freq);
  } else {
    awesome.buzzer.turnOff();
  }

  /* knob test
   * turn knob as far counter-clockwise as possible
   * LED should be white
   * turn knob all the way clockwise
   * LED should change to red, then green, then blue, then white again
   */
  knobReading = awesome.knob.reading();
  if ( knobReading == 0 || knobReading == 1023) {
    r = 255;
    g = 255;
    b = 255;
  } else if ( knobReading < 341 ) {
    r = 255;
    g = 0;
    b = 0;
  } else if ( knobReading < 681 ) {
    r = 0;
    g = 255;
    b = 0;
  } else if ( knobReading < 1023 ) {
    r = 0;
    g = 0;
    b = 255;
  }

  if ( awesome.toggleSwitch.isOff() ) {
    awesome.LED.turnOff();
  } else {
    awesome.LED.turnOn(r,g,b);
  }
}
