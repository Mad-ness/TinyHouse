#ifndef __PIN_H__
#define __PIN_H__

#include <Arduino.h>

// Digital Pin
struct DPin {
    int pin;
    DPin(int p) { pin = p; };
    inline void Input() { pinMode(pin, INPUT); };
    inline void Output() { pinMode(pin, OUTPUT); };
    inline void Low() { digitalWrite(pin, LOW); };
    inline void High() { digitalWrite(pin, HIGH); };
    inline int Value() { return digitalRead(pin); };
};

// Analog Pin
struct APin {
    int pin;
    APin(int p) { pin = p; };
    inline int16_t Value() { return analogRead( pin ); };
    inline void SetValue(uint8_t value) { analogWrite( pin, value ); };
};

#endif // __PIN_H__

