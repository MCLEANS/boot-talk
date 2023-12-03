//
// Created by mcleans on 11/6/23.
//

#ifndef SECURE_BOOT_FLASHER_PROTOCOL_INTERFACE_H
#define SECURE_BOOT_FLASHER_PROTOCOL_INTERFACE_H

#include "common.h"
#include "hw_abstract_interface.h"

class ProtocolInterface {

private:
    /**
     * Default constructor
     */
    ProtocolInterface();

    /**
     * Calculate crc32 for a given array of bytes
     * @param data buffer to calculate crc from
     * @param length length of buffer
     * @return calculated crc32
     */
    uint32_t calculateCRC32(uint8_t* data, size_t length);

    /**
     * Interface to handle hardware communication
     */
    AbstractHardwareInterface* _hw_interface;

public:
    /**
     * Initialize the protocol interface
     * @return 0 for success and -1 for failure
     */
    int initialize();

    /**
     * Send command to start bootloader communication
     */
    void start_boot_talk(void);

    /**
     * Send command to stop bootloader communication
     */
    void stop_boot_talk(void);

    /**
     * Send a chunk of data across the interface
     * @param buffer chunk of data to be sent
     * @param len length of data to be sent
     * @return number of bytes sent
     */
     int send_chunk(void* buffer, size_t len);

     /**
      * Check whether the response received is ACK
      * @return true pr false
      */
     bool is_ACK(void);

     /**
      * Check whether response received is NACK
      * @return true or false
      */
     bool is_NACK(void);

     /**
      * @return default instance of the protocol interface
      */
     static ProtocolInterface* get_instance();

};


#endif //SECURE_BOOT_FLASHER_PROTOCOL_INTERFACE_H
