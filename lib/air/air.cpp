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

void Air::init() {
    
}

void
Air::onReceivedPacket() {
    
}

bool
Air::sendRequest(const air_int8_t packet_id, const air_int8_t object_id, const air_byte_t command, const air_byte_t data, const int8_t length, const void *payload) {
    AirPacket pkt;
    pkt.pid = packet_id;
    pkt.oid = object_id;
    pkt.cmd = command;
    pkt.data = data;
    pkt.len = length;
    memcpy(&pkt.payload, payload, length);
    return this->sendRequest(pkt);
}

bool
Air::sendRequest(const AirPacket &pkt) {
    return true; 
}



