#ifndef __AIRPROTO_H__
#define __AIRPROTO_H__

#ifdef ARDUINO_ARCH_AVR
    #include <Arduino.h>
#elif __LINUX__
    #include <inttypes.h>
#endif // __LINUX__

typedef int8_t air_int8_t;
typedef uint8_t air_uint8_t;
typedef int16_t air_int16_t;
typedef uint16_t air_uint16_t;
typedef unsigned char air_byte_t;

struct AirPacket {
    air_int8_t pid;       // packet id
    air_int8_t oid;       // object id (like sensor id, pin id)
    air_int8_t cmd;       // command
    air_byte_t value;     // value
    int8_t len;           // length of the payload
    air_byte_t payload[32-6]; // additional data
    bool is_response() { return ( cmd & 0x80 ) > 0; };
    air_int8_t command() { return ( cmd & 0x7f ); };
    int8_t size() { return ( 5 + len ); };
};

#define CMD_DPIN_SET_MODE       0x1
#define CMD_DPIN_SET_VALUE      0x2
#define CMD_DPIN_GET_VALUE      0x3

#define CMD_APIN_SETVALUE	0x1
#define CMD_APIN_GETVALUE	0x2

#endif // __AIRPROTO_H__

