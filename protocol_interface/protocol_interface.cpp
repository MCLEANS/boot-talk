//
// Created by mcleans on 11/6/23.
//

#include "protocol_interface.h"
#include <string.h>

ProtocolInterface::ProtocolInterface(){

}

void ProtocolInterface::initialize() {
    _hw_interface = AbstractHardwareInterface::get_instance();
    _hw_interface->initialize();
}

// CRC-32 polynomial
const uint32_t CRC32_POLYNOMIAL = 0xEDB88320;

uint32_t ProtocolInterface::calculateCRC32(uint8_t *data, size_t length) {

    uint32_t crc = 0xFFFFFFFF;  // Initial CRC value

    for (std::size_t i = 0; i < length; i++) {
        crc ^= static_cast<uint32_t>(data[i]);
        for (int j = 0; j < 8; j++) {
            if (crc & 1) {
                crc = (crc >> 1) ^ CRC32_POLYNOMIAL;
            } else {
                crc >>= 1;
            }
        }
    }

    return ~crc;  // Final XOR and bit inversion
}

void ProtocolInterface::start_boot_talk() {
    uint8_t payload[6];

    payload[0] = CM_BOOT_START;
    payload[1] = 0;

    int crc = calculateCRC32(payload, 2);
    memcpy( (void*) &payload[2], (const void*) &crc,4);

    _hw_interface->write((void*) payload, sizeof(payload));

}

void ProtocolInterface::stop_boot_talk() {
    uint8_t payload[6];

    payload[0] = CM_BOOT_END;
    payload[1] = 0;

    int crc = calculateCRC32(payload, 2);
    memcpy( (void*) &payload[2], (const void*) &crc,4);

    _hw_interface->write((void*) payload, sizeof(payload));

}

int ProtocolInterface::send_chunk(void *buffer, size_t len) {
    uint8_t payload[6];

    payload[0] = CM_BOOT_CHUNK;
    payload[1] = (uint8_t) len;

    uint32_t crc = calculateCRC32(payload, 2);
    memcpy( (void*) &payload[2], (const void*) &crc,4);

    _hw_interface->write((void*) payload, sizeof(payload));

    uint8_t* buff = (uint8_t*) buffer;
    crc = calculateCRC32(buff, len);

    uint8_t chunk_buffer[len + 4];
    memcpy((void*) chunk_buffer, (void*) &crc, 4 );

    memcpy((void*) (chunk_buffer + 4), (void*)buff, len);

    _hw_interface->write((void*) chunk_buffer, sizeof(chunk_buffer));

    return sizeof(chunk_buffer) + sizeof(payload);
}

bool ProtocolInterface::is_ACK() {
    return true;
}

bool ProtocolInterface::is_NACK() {
    return true;
}