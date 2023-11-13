//
// Created by mcleans on 11/3/23.
//

#ifndef SECURE_BOOT_FLASHER_HW_ABSTRACT_INTERFACE_H
#define SECURE_BOOT_FLASHER_HW_ABSTRACT_INTERFACE_H

#include <stdint.h>
#include <cstdio>

class AbstractHardwareInterface {

public:
    /**
     * Initialize the hardware interface
     * @return status code, 0 for success and -1 for error
     */
    virtual int initialize() = 0;

    /**
     * Write data to the hardware interface
     * @param buffer payload to send across the hardware interface
     * @param len length of the payload
     * @return number of bytes written
     */
    virtual ssize_t write(void* buffer, size_t len) = 0;

    /**
     * Read data from the hardware interface
     * @param buffer buffer to read received payload into
     * @param len length of the received payload
     * @return number of bytes written
     */
    virtual ssize_t read(void* buffer, size_t len) = 0;

    /**
     * Check whether there is data available in rx buffer
     * @return true or false
     */
    virtual bool rx_available() = 0;

    /**
    *
    * @returns number of bytes available to read
    */
    virtual int available() = 0;

    /**
     * Clear the current contents of the circular buffer
     */
    virtual void clear_buffer() = 0;

    /**
     * Write character to circular buffer
     * @param c char to write
     */
    virtual void write_buff(char c) = 0;

    /**
     * Get default instance of the AbstractHardwareInterface
     */
    static AbstractHardwareInterface* get_instance();

};

#endif //SECURE_BOOT_FLASHER_HW_ABSTRACT_INTERFACE_H
