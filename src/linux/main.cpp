#include <air/air.h>

Air air( "/dev/spidev0.0", "1Note", "2Note", 4, 5 );

void setup() {
}


void loop() {

}

int main() {
	setup();
	for ( ;; ) {
		loop();
	}
}

