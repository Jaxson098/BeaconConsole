#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

const int trigPin  = 3; //UltraSonic Triger Pin AKA the transmitter
const int echoPin  = 4; //UltraSonic Echo Pin AKA the reciever
float timing = 0.0;
float distance; //in cm

const int ledCount = 14;
// Which pin on the Arduino is connected to the NeoPixels?
const int ledPin = 2;
Adafruit_NeoPixel strip(ledCount, ledPin, NEO_GRB + NEO_KHZ800);

//color indexes
int CF_color; //0=blue 1=red
int WM_color; //0=white 1=green
int M_color; //0=blue 1=green 2=yellow 3=red 4=purple
int A_color; //0=red 1=orange 2=yellow

int GM_index = 5; //0=CF starting blue 1=CF starting red 2=WM 3=M 4=A //5=off

int currentTime;
int prevTime;

void setColor(int delay, int r, int g, int b);
void CF();
void WM(); //to be implemented
void M(); //to be implemented
void A(); //to be implemented

void setup() {
  // put your setup code here, to run once:
  pinMode(trigPin,OUTPUT);
  pinMode(echoPin,INPUT);
  digitalWrite(trigPin,LOW);

  Serial.begin(9600);

  strip.begin();
  setColor(0,255,255,255);
}

void loop() {
  // put your main code here, to run repeatedly:

  digitalWrite(trigPin,HIGH);
  delay(10);
  digitalWrite(trigPin,LOW);

  timing = pulseIn(echoPin,HIGH);
  distance = (timing * 0.034) / 2; //time in microseconds * speed of sound in cm/microseconds /2 as its the distance back and forth otherwise

  if (Serial.available() > 0) {
    // read the incoming byte:
    int bytesRead = Serial.read()-'0';
    if (bytesRead == 0) {GM_index=0; CF_color=0; prevTime=millis(); setColor(30,0,0,255);}
    if (bytesRead == 1) {GM_index=0; CF_color=1; prevTime=millis(); setColor(30,255,0,0);}
    if (bytesRead == 2) {GM_index=2; setColor(30,0,255,0);}
    if (bytesRead == 3) {GM_index=3; setColor(30,255,0,255);}
    if (bytesRead == 4) {GM_index=4; setColor(30,255,127,0);}
    if (bytesRead == 5) {GM_index=5; setColor(0,255,255,255);}
  }

  if (GM_index == 0) {
    CF();
  }
}

void setColor(int delayMS, int r, int g, int b) {
  for (int i = 0; i < ledCount; i++) {
    strip.setPixelColor(ledCount-i-1, strip.Color(r, g, b));
    strip.show();
    if (delayMS > 0) delay(delayMS);
  }
}

void CF() {
  currentTime=millis();
  if (distance < 20) {
    if (CF_color == 0) {CF_color = 1; Serial.print(1); setColor(30,255,0,0);} else {CF_color = 0; Serial.print(0); setColor(30,0,0,255);}
  }
  if (currentTime-prevTime > 1000) {
    prevTime=currentTime;
    if (CF_color == 0) Serial.print(0);
    if (CF_color == 1) Serial.print(1);
  }
}
