//
// Created by mcleans on 11/6/23.
//

#ifndef SECURE_BOOT_FLASHER_DEBUG_H
#define SECURE_BOOT_FLASHER_DEBUG_H

#include <stdio.h>
#include BOOT_TALK_HW_CONFIG_FILE

#ifdef BOOT_TALK_LINUX
#define DEBUG(fmt, ...) printf("[Boot-talk]\t" fmt "\r\n", ##__VA_ARGS__)
#else 
#define DEBUG(fmt, ...) 
#endif

#endif //SECURE_BOOT_FLASHER_DEBUG_H
