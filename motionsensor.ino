// This #include statement was automatically added by the Particle IDE.
#include <Ubidots.h>
#include <ThingSpeak.h>

#define TOKEN "BBFF-P4G71ug6emlNrpnkyYFyLxdEqjThza"

Ubidots ubidots(TOKEN);

// LED on pin D0
int buzzer = D1;
int led = D0;
// PIR on D7
int pir = D7;
// tracks if the publish was successful
bool published;
//initializes count
int count=0;

void setup()
{
    // sets the LED pin as output
    pinMode(led, OUTPUT);
   pinMode(buzzer, AN_INPUT);
    // sets the PIR sensor input pin as input
    pinMode(pir, INPUT_PULLUP);
    // ensures the LED is off
    digitalWrite(led, LOW);
    Serial.begin(9600);
  // Subscribe to the integration response event
  Particle.subscribe("hook-response/MotionDetected", myHandler);
}

void myHandler(const char *event, const char *data) {
  // Handle the integration response
}

void loop()
{
    if (digitalRead(pir) == 1)
    // if motion is detected
    {
        // turn on the LED to indicate that motion was detected
        digitalWrite(led, HIGH);
        count++;
        delay(1000);
        tone(buzzer, 3000, 200);
        digitalWrite(led,LOW);
       // published = Particle.publish("MakePhotonsGreatAgain", "true");
        //Particle.publish("MotionDetected", String(count), 60);
        Serial.println(count);
        //Serial.println(digitalRead(pir));
        // Trigger the integration
        //if (!published)
        // if the publish was unsuccessful
       // {
            // flash the LED 10 times as an indicator of the publish failure
         //   for (int i = 0; i < 10; i++)
           // {
          //      digitalWrite(led, LOW);
           //     delay(500);
            //    digitalWrite(led, HIGH);
            //    delay(500);
          //  }
       // }
    }
    //else
        // if no motion is detected, turn off the LED
       // digitalWrite(led, LOW);
//delay(2000);
      ubidots.add("noOfusers", count);
      ubidots.send();
}