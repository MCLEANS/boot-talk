//
// Created by mcleans on 11/3/23.
//

#ifndef SECURE_BOOT_FLASHER_UART_HW_INTERFACE_H
#define SECURE_BOOT_FLASHER_UART_HW_INTERFACE_H

#include "hw_abstract_interface.h"
#include "circular_buffer.h"

#include "termios.h"
#include <string>
#include "stddef.h"
#include <mutex>

#define  BOOT_FLASHER_BUFFER_SIZE 1024
#define  BOOT_FLASHER_PLATFORM_LINUX

class UARTHardwareInterfaceLinux : public AbstractHardwareInterface {

private:

    static int _uart;

    /**
     * Store whether port is open or closed. This prevents opening an already open port
     */
    bool _port_is_open;

    /**
    * Buffer to store received bytes
    */
    CircularBuffer<char, BOOT_FLASHER_BUFFER_SIZE> _rx_buffer;

public:

    /**
    * Default constructor
   */
    UARTHardwareInterfaceLinux();

    /**
     * initialize the hardware interfaces
     */
    int initialize() override;

    /**
     * clear underlying RX buffer
     */
    void clear_buffer() override;

    /**
     * @param[in] data buffer to send
     * @param[in] len data len
     * @returns bytes sent on success or a non zero error
    */
    ssize_t write(void* buffer, size_t len) override;

    /**
     * blocks until len bytes are read
     * @param buffer buffer to write into
     * @param len bytes to read
     * @returns number of bytes read of negative error code
     */
    ssize_t read(void* buffer, size_t len) override;

    /**
     *
     * @returns true if theres bytes available to read
     */
    bool rx_available() override;

    /**
     *
     * @returns number of bytes available to read
     */
    int available() override;

    /**
     * Callback executed when a new byte is received
    */
    static void rx_callback();

    /**
     * Writes a character to the circular buffer
     * @param[in] char to write to buffer
    */
    void write_buff(char c);

    /**
     *
     * @returns a statically allocated instance on  UARTHardwareInterfacePico
     */
    static UARTHardwareInterfaceLinux* get_instance();

};


#endif //SECURE_BOOT_FLASHER_UART_HW_INTERFACE_H
