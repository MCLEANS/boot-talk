#ifndef _BOOTLOADER_COMMON_H
#define _BOOTLOADER_COMMON_H

#include <stdint.h>

enum bootloader_cmds: unsigned int {
    CM_BOOT_SYNC,
    CM_BOOT_FW_INFO,
    CM_BOOT_START, /** Start of firmware transfer **/
    CM_BOOT_END, /** End of firmware transfer **/
    CM_BOOT_CHUNK,
    CM_BOOT_ACK,
    CM_BOOT_NACK
};

#endif //_BOOTLOADER_COMMON_H