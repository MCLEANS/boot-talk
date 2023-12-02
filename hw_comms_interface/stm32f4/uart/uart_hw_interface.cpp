//
// Created by mcleans on 11/3/23.
//

#include "uart_hw_interface.h"
#include <cassert>

#define INVALID_FD_RETURN   -1

#define BOOT_TALK_USART         USART2 
#define BOOT_TALK_USART_PORT    GPIOA
#define BOOT_TALK_USART_RX      3
#define BOOT_TALK_USART_TX      2
#define BOOT_TALK_USART_BAUD    115200

UARTHardwareInterfaceStm32f4::UARTHardwareInterfaceStm32f4(): _uart(BOOT_TALK_USART,
                                                                    BOOT_TALK_USART_PORT,
                                                                    BOOT_TALK_USART_RX,
                                                                    BOOT_TALK_USART_TX,
                                                                    BOOT_TALK_USART_BAUD)
{

}

int UARTHardwareInterfaceStm32f4::initialize()
{
    static bool initialized = false;

    if (!initialized) {
        _uart.initialize();

        NVIC_SetPriority(USART1_IRQn,0x03);
	    NVIC_EnableIRQ(USART1_IRQn);

        // DEBUG("Successfully initialized serial port");
    }

    return 0;

}

void UARTHardwareInterfaceStm32f4::clear_buffer()
{
    _rx_buffer.reset();
}


bool UARTHardwareInterfaceStm32f4::rx_available()
{

    if (_rx_buffer.size() > 0) {
        return true;
    }
    return false;

}

int UARTHardwareInterfaceStm32f4::available()
{
    return (int) _rx_buffer.size();
}

void UARTHardwareInterfaceStm32f4::write_buff(char c)
{
    _rx_buffer.push(c);
}


extern "C" void USART1_IRQHandler(void){
    if(BOOT_TALK_USART->SR & USART_SR_RXNE){
		BOOT_TALK_USART->SR &= ~USART_SR_RXNE;
        AbstractHardwareInterface::get_instance()->write_buff(USART1->DR);
	}
}

void UARTHardwareInterfaceStm32f4::rx_callback()
{
 
}


ssize_t UARTHardwareInterfaceStm32f4::write(void* buffer, size_t len)
{
    clear_buffer();
    char* buff = (char*)buffer;

    _uart.print(buff);

    return len;
}

ssize_t UARTHardwareInterfaceStm32f4::read(void* buffer, size_t len)
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

#if defined (BOOT_FLASHER_PLATFORM_STM32F4)

AbstractHardwareInterface* AbstractHardwareInterface::get_instance()
{
    static UARTHardwareInterfaceStm32f4 hardware_interface;
    return &hardware_interface;
}

#endif




