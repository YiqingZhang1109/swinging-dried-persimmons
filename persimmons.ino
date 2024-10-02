/**************************************************************************
  Animation:
  1. 12 dried persimmons hanged on vertical white strings from the top.
  2. Each string has a different length.
  3. The persimmons and strings swing from left to right slowly as if there is a gentle wind.
 **************************************************************************/
#include <TFT_eSPI.h> 
#include <SPI.h>
#include <math.h>

TFT_eSPI tft = TFT_eSPI(); 

// Define colors
#define PERSIMMON_COLOR TFT_ORANGE
#define STRING_COLOR TFT_WHITE
#define STEM_COLOR 0x51c4
#define BACKGROUND_COLOR 0xc1e5  

// Define persimmon parameters
#define NUM_PERSIMMONS 12

// Store x position, string length, and swing phase for each persimmon
int persimmonX[NUM_PERSIMMONS];
int stringLength[NUM_PERSIMMONS];
float swingPhase[NUM_PERSIMMONS];

// Angle and speed for swinging
float swingAngle = 0;
float swingSpeed = 0.02;  // Slow swinging

// Screen dimensions
int screenWidth, screenHeight;

// Initialize the TFT display
void setup() {
  tft.init();
  tft.setRotation(1);   // Set to landscape
  screenWidth = tft.width();
  screenHeight = tft.height();

  // Initialize persimmons at random horizontal positions and string lengths
  for (int i = 0; i < NUM_PERSIMMONS; i++) {
    persimmonX[i] = screenWidth / NUM_PERSIMMONS * i + 10;  // Distribute horizontally
    stringLength[i] = random(50, 100);  // Random string length between 50 and 100
    swingPhase[i] = random(0, 360);  // Random starting phase for each persimmon's swing
  }

  tft.fillScreen(BACKGROUND_COLOR);  
}

// The main animation loop
void loop() {
  tft.fillScreen(BACKGROUND_COLOR);  

  // Draw each persimmon and its swinging string
  for (int i = 0; i < NUM_PERSIMMONS; i++) {
    drawSwingingPersimmon(persimmonX[i], stringLength[i], swingPhase[i]);
  }

  // Update swing angle
  swingAngle += swingSpeed;
  if (swingAngle > 360) {
    swingAngle -= 360;
  }

  delay(50);  // Control the speed of animation
}

void drawSwingingPersimmon(int x, int length, float phase) {
  // Calculate the horizontal offset for the swinging effect
  float offsetX = sin(swingAngle + phase) * 10;  // Swing offset based on the current angle

  // Draw the string
  tft.drawLine(x + offsetX, 0, x + offsetX, length, STRING_COLOR);

  // Draw the stem at the top of the persimmon
  tft.fillRect(x + offsetX - 3, length - 3, 10, 2, STEM_COLOR);  

  // Draw the persimmon at the end of the string 
  tft.fillEllipse(x + offsetX, length + 10, 9.5, 10, PERSIMMON_COLOR);  
}
