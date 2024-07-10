#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 64 
#define OLED_RESET    -1 
#define SCREEN_ADDRESS 0x3C 

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const int centerX = SCREEN_WIDTH / 2;
const int centerY = SCREEN_HEIGHT / 2;
const int clockRadius = 30;

void setup() {
  Serial.begin(115200);

  // Initialize the display
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); 
  }

  display.clearDisplay(); 
  display.display(); 
  randomSeed(analogRead(0));
}

void loop() {
  int hour = random(0, 24);    
  int minute = random(0, 60);  
  int second = random(0, 60);  

  display.clearDisplay();
  drawClockFace();
  drawClockHands(hour, minute, second);
  display.display();

  delay(1000);
}

void drawClockFace() {
  display.drawCircle(centerX, centerY, clockRadius, SSD1306_WHITE);

  for (int i = 0; i < 12; i++) {
    float angle = i * 30 * PI / 180;
    int x1 = centerX + (clockRadius - 2) * cos(angle);
    int y1 = centerY + (clockRadius - 2) * sin(angle);
    int x2 = centerX + clockRadius * cos(angle);
    int y2 = centerY + clockRadius * sin(angle);
    display.drawLine(x1, y1, x2, y2, SSD1306_WHITE);
  }

  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(centerX - 3, centerY - clockRadius - 8); 
  display.print("12");
  display.setCursor(centerX + clockRadius - 10, centerY - 3); 
  display.print("3");
  display.setCursor(centerX - 3, centerY + clockRadius - 5);
  display.print("6");
  display.setCursor(centerX - clockRadius + 2, centerY - 3); 
  display.print("9");
}

void drawClockHands(int hour, int minute, int second) {
  float secondAngle = second * 6 * PI / 180;
  float minuteAngle = (minute + second / 60.0) * 6 * PI / 180;
  float hourAngle = (hour % 12 + minute / 60.0) * 30 * PI / 180;
  drawHand(secondAngle, clockRadius - 5, SSD1306_WHITE);
  drawHand(minuteAngle, clockRadius - 8, SSD1306_WHITE);
  drawHand(hourAngle, clockRadius - 15, SSD1306_WHITE);
}

void drawHand(float angle, int length, uint16_t color) {
  int x = centerX + length * cos(angle - PI / 2);
  int y = centerY + length * sin(angle - PI / 2);
  display.drawLine(centerX, centerY, x, y, color);
}

