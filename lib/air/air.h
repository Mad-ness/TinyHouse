#ifndef __AIR_H__
#define __AIR_H__

#ifdef ARDUINO_ARCH_AVR
    #include <RF24.h>
#elif __LINUX__
    #include <RF24/src/RF24.h>
#endif // Platform selection
#include "airproto.h"

class Air {
    private:
        struct {
            air_byte_t read[6];
            air_byte_t write[6];
        } m_pipes;        
        RF24 m_rf24;
#ifdef __LINUX__
        const char *m_spidevice;   // /dev/spidev0.0
#endif // __LINUX__
        AirPacket m_packet;
        void onReceivedPacket();
        void setup();
    public:
#ifdef ARDUINO_ARCH_AVR
        Air(const air_byte_t *read_addr, const air_byte_t *write_addr, const int ce_pin, const int csn_pin);
#elif __LINUX__
        Air(const char *device, const char *read_addr, const char *write_addr, const int ce_pin, const int csn_pin);
#endif // __LINUX__
        AirPacket &packet() { return this->m_packet; };
        bool sendRequest(AirPacket &pkt);
        bool sendRequest(const air_int8_t packet_id, const air_int8_t object_id, const air_byte_t command, const air_byte_t data, const int8_t len, const void *payload);
};

#endif // __AIR_H__

