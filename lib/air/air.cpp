#ifdef __LINUX__
    #include <string.h>
#endif // __LINUX__

#include "air.h"

#ifdef ARDUINO_ARCH_AVR
Air::Air(const air_byte_t *read_addr, const air_byte_t *write_addr, const int ce_pin, const int csn_pin) 
    : m_rf24(ce_pin, csn_pin)
#elif __LINUX__
Air::Air(const char *device, const char *read_addr, const char *write_addr, const int ce_pin, const int csn_pin) 
    : m_rf24(ce_pin, csn_pin, device)
#endif // __LINUX__ || ARDUINO_ARCH_AVR
{
    memcpy( m_pipes.read, read_addr, 6 );
    memcpy( m_pipes.write, write_addr, 6 );
#ifdef __LINUX__
    this->m_spidevice = device;
#endif // __LINUX__
}

void Air::setup() {
    m_rf24.begin();
    m_rf24.setPALevel(RF24_PA_LOW);
    m_rf24.setDataRate(RF24_250KBPS);
#if defined(ARDUINO)
    this->m_rf24.openReadingPipe(1, this->m_pipes.read);
    this->m_rf24.openWritingPipe(this->m_pipes.write);
#elif defined(__LINUX__)
    uint64_t pipes[2];
    memcpy(&pipes[0], this->m_pipes.read, sizeof(this->m_pipes.read));
    memcpy(&pipes[1], this->m_pipes.write, sizeof(this->m_pipes.write));
    this->m_rf24.openReadingPipe(1, pipes[0]);
    this->m_rf24.openWritingPipe(pipes[1]);
#endif
    this->m_rf24.startListening(); 
}

void
Air::onReceivedPacket() {
    
}

bool
Air::sendRequest(const air_int8_t packet_id, const air_int8_t object_id, const air_byte_t command, const air_byte_t value, const int8_t length, const void *payload) {
    AirPacket pkt;
    pkt.pid = packet_id;
    pkt.oid = object_id;
    pkt.cmd = command;
    pkt.value = value;
    pkt.len = length;
    memcpy(&pkt.payload, payload, length);
    return this->sendRequest(pkt);
}

bool
Air::sendRequest(AirPacket &pkt) {
	m_rf24.stopListening();
	bool result = false;
	int attempts = 0;
	while ( attempts++ < 5 ) {
		if ( m_rf24.write(&pkt, pkt.size()) ) {
			result = true;
			break;
		}
	}
	m_rf24.startListening();
    return result;
}



