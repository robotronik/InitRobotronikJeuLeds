#include <Arduino.h>

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN 16
//#define MAX_MEAN_SPEED 15
#define MEAN_INTERVAL 200
#define LED_PER_SPEED 1.0

#define BT_1_PIN 17
#define BT_2_PIN 5

void initStrip();
void colorWipe(uint32_t c, uint8_t wait);
void rainbow(uint8_t wait);
void rainbowCycle(uint8_t wait);
void theaterChase(uint32_t c, uint8_t wait);
void theaterChaseRainbow(uint8_t wait) ;
uint32_t Wheel(byte WheelPos);

void showColors(uint16_t player1Leds, uint16_t player2Leds);
void showWinner(uint16_t player);

uint16_t meanConvertToIncrement(float mean);
