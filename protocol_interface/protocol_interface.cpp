//
// Created by mcleans on 11/6/23.
//

#include "protocol_interface.h"

ProtocolInterface::ProtocolInterface(){

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

}

void ProtocolInterface::stop_boot_talk() {

}

int ProtocolInterface::send_chunk(void *buffer, size_t len) {

    return 0;
}

bool ProtocolInterface::is_ACK() {
    return true;
}

bool ProtocolInterface::is_NACK() {
    return true;
}