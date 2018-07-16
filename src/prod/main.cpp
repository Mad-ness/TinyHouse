#include <Arduino.h>
#include <pin.h>
#include <air.h>

DPin p(4);
APin p2(A1);
Air air( "1Note", "2Note", 4, 5 );

void setup() {
    p.Output();
    p.Low();
    p2.Value();
}


void loop() {

}


