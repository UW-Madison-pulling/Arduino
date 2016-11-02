#include <SoftwareSerial.h>
#define MainPeriod 100  // measurement frame, milliseconds
#define f_input_pin 4   // input pin for pulseIn
SoftwareSerial mySerial(2, 3); //RX, TX

long previousMillis = 0;
unsigned long duration=0; // receive pulse width
long pulsecount=0;
String sparator = ", ";
String payload = "";

void setup()
{
  pinMode(f_input_pin, INPUT);
  Serial.begin(19200);
  mySerial.begin(19200);
  delay(20);
}

void loop()
{
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= MainPeriod)
  {
    previousMillis = currentMillis;
    // write current time and F values to the serial port
    payload += currentMillis;
    payload += sparator;
    float Freq=0.5e6/float(duration); // assume pulse duty cycle 0.5
    Freq*=pulsecount;
    payload += Freq;
    payload += sparator;
    payload += pulsecount;
    payload += sparator;
    payload += duration;
    mySerial.println(payload);
    Serial.println(payload);
    payload = "";
    duration=0;
    pulsecount=0;
  }
  // instead of single measurement per cycle - accumulate and average
  duration += pulseIn(f_input_pin, HIGH, MainPeriod*900);
  pulsecount++;
}
