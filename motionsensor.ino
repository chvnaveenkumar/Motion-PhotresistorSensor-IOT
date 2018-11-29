// This #include statement was automatically added by the Particle IDE.

#include <ThingSpeak.h>


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
        Serial.println(count);
    }
}