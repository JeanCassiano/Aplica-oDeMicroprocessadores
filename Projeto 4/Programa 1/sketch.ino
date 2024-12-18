#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <ESP32Servo.h>

// Constantes de configuração do display
#define DISPLAY_WIDTH 128
#define DISPLAY_HEIGHT 64
#define OLED_RESET -1 // Define como -1 se não estiver usando o pino de reset
#define OLED_ADDRESS 0x3C // Endereço I2C do display OLED

// Pinos de entrada
#define PIN_SERVO 4
#define PIN_BTN_LOOP 13
#define PIN_BTN_MANUAL 12
#define PIN_BTN_STOP 14
#define PIN_POTENTIOMETER 34

// Configurações do servo
#define SERVO_MIN_MICROS 500 // largura de pulso mínima em microssegundos
#define SERVO_MAX_MICROS 2500 // largura de pulso máxima em microssegundos

// Variáveis de controle
bool isAutoMode = false;
bool isActive = true;
int currentAngle = 0;
unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 50;

// Instâncias de objetos
Adafruit_SSD1306 display(DISPLAY_WIDTH, DISPLAY_HEIGHT, &Wire, OLED_RESET);
Servo servo;

void setup() {
  Serial.begin(115200);
  setupDisplay();
  setupServo();
  setupButtons();
  updateDisplay("Pronto", currentAngle);
}

void loop() {
  handleButtonPress();
  if (isActive) {
    if (isAutoMode) {
      runAutomaticMode();
    } else {
      runManualMode();
    }
  }
}

void setupDisplay() {
  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDRESS)) {
    Serial.println("SSD1306 allocation failed");
    for (;;); // Loop infinito
  }
  display.clearDisplay();
  display.display();
}

void setupServo() {
  servo.attach(PIN_SERVO, SERVO_MIN_MICROS, SERVO_MAX_MICROS);
}

void setupButtons() {
  pinMode(PIN_BTN_LOOP, INPUT_PULLUP);
  pinMode(PIN_BTN_MANUAL, INPUT_PULLUP);
  pinMode(PIN_BTN_STOP, INPUT_PULLUP);
}

void handleButtonPress() {
  if (isButtonPressed(PIN_BTN_LOOP)) {
    isAutoMode = true;
    isActive = true;
  } else if (isButtonPressed(PIN_BTN_MANUAL)) {
    isAutoMode = false;
    isActive = true;
  } else if (isButtonPressed(PIN_BTN_STOP)) {
    isActive = false;
    updateDisplay("Parado", currentAngle);
  }
}

bool isButtonPressed(int pin) {
  bool state = digitalRead(pin) == LOW;
  if (state) {
    unsigned long currentTime = millis();
    if (currentTime - lastDebounceTime > debounceDelay) {
      lastDebounceTime = currentTime;
      return true;
    }
  }
  return false;
}

void runAutomaticMode() {
  static unsigned long lastUpdate = 0;
  static int direction = 1;
  if (millis() - lastUpdate > 50) {
    currentAngle += direction;
    if (currentAngle <= 0 || currentAngle >= 180) {
      direction = -direction;
      currentAngle = max(0, min(currentAngle, 180));
    }
    servo.write(currentAngle);
    updateDisplay("Automático", currentAngle);
    lastUpdate = millis();
  }
}

void runManualMode() {
  int sensorValue = analogRead(PIN_POTENTIOMETER);
  currentAngle = map(sensorValue, 0, 4095, 0, 180);
  servo.write(currentAngle);
  updateDisplay("Manual", currentAngle);
}

void updateDisplay(String mode, int angle) {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("Controle Servo");
  display.println("Modo: " + mode);
  display.println("Angulo: " + String(angle) + " graus");
  display.display();
}
