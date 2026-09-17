#include "main.h"

uint16_t count1 = 0;
uint16_t count2 = 0;
uint16_t tabSpeed1[] = {0,0,0,0,0};
uint16_t tabSpeed2[] = {0,0,0,0,0};
uint16_t meanIndex = 0;
float meanSpeed1 = 0;
float meanSpeed2 = 0;
int oldTime = 0;
int newTime = 0;

uint16_t nLeds1;
uint16_t nLeds2;

// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.

void setup() {

  Serial.begin(9600);

  pinMode(BT_1_PIN, INPUT_PULLUP);
  pinMode(BT_2_PIN, INPUT_PULLUP);

  initStrip();

  nLeds1 = 0;
  nLeds2 = 0;

}

void loop() {
  // Calcul de moyenne : comptage des entrées bouton
  if(digitalRead(BT_1_PIN) == LOW){
    delay(5);
    while(digitalRead(BT_1_PIN) == LOW);
    ++count1;
  }
  if(digitalRead(BT_2_PIN) == LOW){
    delay(5);
    while(digitalRead(BT_2_PIN) == LOW);
    ++count2;
  }

  newTime = millis();

  // Action par delta de temps de calcul de moyenne
  if(newTime > oldTime+MEAN_INTERVAL){
    oldTime = millis();
    tabSpeed1[meanIndex] = count1*(1000/MEAN_INTERVAL);
    tabSpeed2[meanIndex] = count2*(1000/MEAN_INTERVAL);
    count1=0;
    count2=0;

    float temp1 = 0;
    float temp2 = 0;

    //Stockage des 5 dernières moyennes en mémoire
    for(byte i=0; i<5; ++i){
      temp1 += tabSpeed1[i];
      temp2 += tabSpeed2[i];
    }
    meanSpeed1 = temp1/5.0;
    meanSpeed2 = temp2/5.0;

    ++meanIndex;
    if(meanIndex > 4){
      meanIndex = 0;
    }

    //Winner
    if(nLeds1 >= 240){
      showWinner(0);
    }
    if(nLeds2 >= 240){
      showWinner(1);
    }

    //Normal
    if(nLeds1+nLeds2 < 240){
      nLeds1 += meanConvertToIncrement(meanSpeed1);
      nLeds2 += meanConvertToIncrement(meanSpeed2);
    }

    //Cross
    else{
      if(meanSpeed1 > meanSpeed2){
        nLeds1 += meanConvertToIncrement(meanSpeed1);
        nLeds2 -= meanConvertToIncrement(meanSpeed1);
      }
      else{
        nLeds1 -= meanConvertToIncrement(meanSpeed2);
        nLeds2 += meanConvertToIncrement(meanSpeed2);
      }
    }

    Serial.print("mean1 : ");
    Serial.println(meanSpeed1);
    Serial.print("mean2 : ");
    Serial.println(meanSpeed2);
    Serial.println("\n");
    showColors(nLeds1, nLeds2);
    
  }


  /*
  if(digitalRead(BT_1_PIN) == LOW){
    delay(5);
    while(digitalRead(BT_1_PIN) == LOW);
    ++count;
  }

  newTime = millis();

  if(newTime > oldTime+MEAN_INTERVAL){
    oldTime = millis();
    tabSpeed[meanIndex] = count*(1000/MEAN_INTERVAL);
    count=0;

    float temp = 0;
    for(byte i=0; i<5; ++i){
      temp += tabSpeed[i];
    }
    meanSpeed = temp/5.0;

    ++meanIndex;
    if(meanIndex > 4){
      meanIndex = 0;
    }

    uint16_t nLeds = (strip.numPixels()*(uint16_t)meanSpeed)/MAX_MEAN_SPEED ;
    uint16_t color = 80 + (175*(uint16_t)meanSpeed)/MAX_MEAN_SPEED;

    for(uint16_t j=0; j<nLeds; j++) {
      strip.setPixelColor(j, Wheel(color));
    }
    for(uint16_t j=nLeds; j<240; j++){
      strip.setPixelColor(j, 0);
    }
    strip.show();
    
    
  }
  */
  

  /*
  if(digitalRead(17) == LOW){
    for(uint16_t j=0; j<strip.numPixels(); j++) {
      strip.setPixelColor(j, Wheel(80));
      }
    strip.show();
  }
  else{
    for(uint16_t j=0; j<strip.numPixels(); j++) {
      strip.setPixelColor(j, Wheel(255));
      }
    strip.show();
  }
  delay(1);
  */




  /*
  for(byte i=0;i<255;++i){ //50 vert, 255 rouge
    for(uint16_t j=0; j<strip.numPixels(); j++) {
      strip.setPixelColor(j, Wheel(i));
      }
    strip.show();
    delay(20);
  }
  //delay(3000);
  */



  /*
  // Some example procedures showing how to display to the pixels:
  colorWipe(strip.Color(255, 0, 0), 50); // Red
  colorWipe(strip.Color(0, 255, 0), 50); // Green
  colorWipe(strip.Color(0, 0, 255), 50); // Blue
//colorWipe(strip.Color(0, 0, 0, 255), 50); // White RGBW
  // Send a theater pixel chase in...
  theaterChase(strip.Color(127, 127, 127), 50); // White
  theaterChase(strip.Color(127, 0, 0), 50); // Red
  theaterChase(strip.Color(0, 0, 127), 50); // Blue
  
  rainbow(20);
  rainbowCycle(20);
  theaterChaseRainbow(50);
  */ 
}

