//
// Created by mcleans on 11/3/23.
//

#include "uart_hw_interface.h"

#include <stdio.h>
#include <unistd.h>         //Used for UART
#include <fcntl.h>          //Used for UART
#include <termios.h>        //Used for UART
#include <thread>
#include <chrono>
#include <cassert>
#include "debug.h"

#define INVALID_FD_RETURN   -1

int UARTHardwareInterfaceLinux::_uart = INVALID_FD_RETURN;

UARTHardwareInterfaceLinux::UARTHardwareInterfaceLinux()
{

}

int UARTHardwareInterfaceLinux::initialize()
{
    static bool initialized = false;

    if (!initialized) {

        _uart = open("/dev/ttyACM0", O_RDWR | O_NOCTTY | O_NDELAY);

        if (_uart == INVALID_FD_RETURN) {
            DEBUG("ERROR opening serial port");
            return -1;
        }

        struct termios options;

        tcgetattr(_uart, &options);
        options.c_cflag = B115200 | CS8 | CLOCAL | CREAD;         //<Set baud rate, enable receiver
        options.c_iflag = IGNPAR;
        options.c_oflag = 0;
        options.c_lflag = 0;
        tcflush(_uart, TCIFLUSH);
        tcsetattr(_uart, TCSANOW, &options);

        std::thread rx_recv_cb(rx_callback);

        rx_recv_cb.detach();
        initialized = true;

        DEBUG("Successfully initialized serial port");
    }

    return 0;

}

void UARTHardwareInterfaceLinux::clear_buffer()
{
    _rx_buffer.reset();
}


bool UARTHardwareInterfaceLinux::rx_available()
{

    if (_rx_buffer.size() > 0) {
        return true;
    }
    return false;

}

int UARTHardwareInterfaceLinux::available()
{
    return (int) _rx_buffer.size();
}

void UARTHardwareInterfaceLinux::write_buff(char c)
{
    _rx_buffer.push(c);
}

void UARTHardwareInterfaceLinux::rx_callback()
{
    char c;
    int bytesRead = 0;

    if (_uart == INVALID_FD_RETURN) {
        return;
    }

    while (true) {
        bytesRead = ::read(_uart, &c, 1);
        if (bytesRead > 0) {
            AbstractHardwareInterface::get_instance()->write_buff(c);
        }
    }
}


ssize_t UARTHardwareInterfaceLinux::write(void* buffer, size_t len)
{
    clear_buffer();
    uint8_t* buff = (uint8_t*)buffer;

    ssize_t bytes_written = 0;

    if (_uart == INVALID_FD_RETURN) {
        return 0;
    }

    bytes_written = ::write(_uart, buff, len);

    return bytes_written;
}

ssize_t UARTHardwareInterfaceLinux::read(void* buffer, size_t len)
{

    char* data  = (char*)buffer;
    assert(len <= BOOT_FLASHER_BUFFER_SIZE);

    if (available() <= 0) {
        return -1;
    }

    if (len > available()) {
        len = available();
    }

    ssize_t r = 0;
    while (available() && r < len) {
        char c ;

        if (_rx_buffer.pop(c)) {
            *data++ = c;
            r++;
        } else {
            break;
        }

    }

    return r;
}

#if defined (BOOT_TALK_LINUX)

AbstractHardwareInterface* AbstractHardwareInterface::get_instance()
{
    static UARTHardwareInterfaceLinux hardware_interface;
    return &hardware_interface;
}

#endif




