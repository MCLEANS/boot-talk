cmake_minimum_required(VERSION 3.19.0 FATAL_ERROR)

add_library(boot-talk INTERFACE)

if(DEFINED TARGET_FLASHER)

        set(PLATFORM_SOURCES
                ${CMAKE_CURRENT_LIST_DIR}/hw_comms_interface/x86_linux/uart/uart_hw_interface.cpp
        )

elseif(DEFINED TARGET_DEVICE)

        set(PLATFORM_SOURCES 
                ${CMAKE_CURRENT_LIST_DIR}/hw_comms_interface/stm32f4/uart/uart_hw_interface.cpp
        )
else()

        set(PLATFORM_SOURCES 
                ${CMAKE_CURRENT_LIST_DIR}/hw_comms_interface/stm32f4/uart/uart_hw_interface.cpp
        )


endif()


target_include_directories(boot-talk INTERFACE
                ${CMAKE_CURRENT_LIST_DIR}/hw_comms_interface/hw_abstract_interface
                ${CMAKE_CURRENT_LIST_DIR}/common
                ${CMAKE_CURRENT_LIST_DIR}/protocol_interface
                ${CMAKE_CURRENT_LIST_DIR}/utils
        )

target_sources(boot-talk INTERFACE
                ${PLATFORM_SOURCES}
                ${CMAKE_CURRENT_LIST_DIR}/protocol_interface/protocol_interface.cpp
        )




