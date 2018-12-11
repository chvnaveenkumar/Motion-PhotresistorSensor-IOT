// This #include statement was automatically added by the Particle IDE.
#include <SparkFunMicroOLED.h>

// This #include statement was automatically added by the Particle IDE.
#include <Ubidots.h>

/*

* Project IOTFinal

* Description:

* Author:

* Date:

*/

#define TOKEN "BBFF-Qj97dH0DB1XwCHLyznb6smRPyw7OUW"  // Put here your Ubidots TOKEN


Ubidots ubidots(TOKEN);

MicroOLED oled;

int greeny = D0;

int openPhoto = A0;

int buzzbuzz = D1;

int closePhoto = A1;

int countOpen = 0;

int countClosed = 0;

int baseOpen = 0.0;

int currentClose = 0.0;

int baseClose = 0.0;

int currentOpen = 0.0;

int total = 0;

int tempOpen = 0;

int tempClose = 0;


int resets(String command) {

  countOpen = 0.0;

 countClosed = 0.0;

  total = 0;

 return 0;
}

// setup() runs once, when the device is first turned on.

void setup() {

  // Put initialization like pinMode and begin functions here.

pinMode(openPhoto, AN_INPUT);

pinMode(closePhoto, AN_INPUT);

pinMode(greeny, OUTPUT);

pinMode(buzzbuzz, OUTPUT);

  oled.begin();    // Initialize the OLED
  oled.clear(PAGE); // Clear the display's internal memory
  //oled.display();  // Display what's in the buffer (splashscreen)
  delay(1000); 


Particle.variable("countOpen", countOpen);

Particle.variable("countClosed", countClosed);

Particle.variable("TotalCount", total);

Particle.function("doorCycle", doorCycle); 

Particle.function("resetSet", resets);

captureBaseReadings();

 

}
int doorCycle(String command){
    if(currentOpen = currentClose){
        return 1;
    }
    else{
        return 0;
    }
}
 

// loop() runs over and over again, as quickly as it can execute.

void loop() {
    

 
  // The core of your code will likely live here.

captureCurrentReadings();

if(currentOpen/baseOpen < 0.5){

  digitalWrite(greeny, HIGH);
  tone(buzzbuzz, 300, 200);
  countOpen ++;
  tempOpen = 1;
    updateDisplay();

}

else if(currentClose/baseClose < 0.5){

  digitalWrite(greeny, HIGH);
  tone(buzzbuzz, 700, 200);
  countClosed ++;
  if( tempOpen == 1) {
      tempClose = 1;
  }
  updateDisplay();
}

else{

  digitalWrite(greeny, LOW);

}

  if( tempClose == 1){
      total ++;
      tempClose = 0;
      tempOpen = 0;
  }

  ubidots.add("TimesOpen", countOpen);

  ubidots.add("TimesClosed", countClosed);
  
  ubidots.add("TotalCount", total);

    ubidots.send();

}

 void updateDisplay(){
    oled.clear(PAGE);
    oled.setCursor(0,0);
    oled.printf("Open: %d\n", countOpen);
    oled.printf("Closed: %d\n",  countClosed);
    oled.display();
 }

void captureBaseReadings() {

//read in brightness

baseOpen = analogRead(openPhoto);

baseClose = analogRead(closePhoto);

}

void captureCurrentReadings() {

//read in brightness

currentOpen = analogRead(openPhoto);

currentClose = analogRead(closePhoto);

}