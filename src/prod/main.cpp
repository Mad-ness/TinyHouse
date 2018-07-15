#include <Arduino.h>
#include <pin.h>

DPin p(4);
APin p2(A1);

void setup() {
    p.Output();
    p.Low();
    p2.Value();
}


void loop() {

}


