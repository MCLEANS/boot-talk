cmake_minimum_required(VERSION 3.19.0 FATAL_ERROR)

add_library(boot-talk INTERFACE)

target_include_directories(boot-talk INTERFACE
        common
        hw_comms_interface/hw_abstract_interface
        protocol_interface
        utils
        )

target_sources(boot-talk INTERFACE
        hw_comms_interface/x86_linux/uart/uart_hw_interface.cpp
        protocol_interface/protocol_interface.cpp
        )




