#include <Arduino.h>
#include <Keyboard.h>

#ifndef KEYBOARD_HALF
#define KEYBOARD_HALF 1
#endif

constexpr uint8_t rowCount = 5;
constexpr uint8_t columnCount = 6;
constexpr uint8_t keyCount = 26;
constexpr uint32_t debounceMs = 10;

#if KEYBOARD_HALF == 1
constexpr uint8_t rowPins[rowCount] = {3, 4, 2, 1, 26};
constexpr uint8_t columnPins[columnCount] = {6, 7, 0, 29, 27, 28};
#elif KEYBOARD_HALF == 2
constexpr uint8_t rowPins[rowCount] = {0, 3, 4, 2, 1};
constexpr uint8_t columnPins[columnCount] = {26, 27, 28, 29, 6, 7};
#else
#error KEYBOARD_HALF must be 1 for U1 or 2 for U2
#endif

struct KeyState {
  bool reading;
  bool pressed;
  uint32_t changedAt;
};

KeyState keys[keyCount]{};

void setup() {
  for (uint8_t pin : rowPins) {
    pinMode(pin, INPUT);
    digitalWrite(pin, LOW);
  }
  for (uint8_t pin : columnPins) {
    pinMode(pin, INPUT_PULLUP);
  }
  Keyboard.begin();
}

void loop() {
  bool readings[keyCount]{};
  for (uint8_t row = 0; row < rowCount; ++row) {
    pinMode(rowPins[row], OUTPUT);
    digitalWrite(rowPins[row], LOW);
    delayMicroseconds(5);
    for (uint8_t column = 0; column < columnCount; ++column) {
      const uint8_t index = row * columnCount + column;
      if (index < keyCount) {
        readings[index] = digitalRead(columnPins[column]) == LOW;
      }
    }
    pinMode(rowPins[row], INPUT);
  }

  const uint32_t now = millis();
  for (uint8_t index = 0; index < keyCount; ++index) {
    KeyState &key = keys[index];
    if (readings[index] != key.reading) {
      key.reading = readings[index];
      key.changedAt = now;
    }
    if (key.reading != key.pressed && now - key.changedAt >= debounceMs) {
      key.pressed = key.reading;
      if (key.pressed) {
        Keyboard.write(static_cast<uint8_t>('a' + index));
      }
    }
  }
  delay(1);
}
