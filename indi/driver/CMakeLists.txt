cmake_minimum_required(VERSION 2.4.7)
PROJECT(tlinsDriver CXX C)

set(CMAKE_C_COMPILER		gcc)
set(CMAKE_CXX_COMPILER	g++)
set(CMAKE_CXX_FLAGS     "-std=c++14")

set(BIN_INSTALL_DIR     "${CMAKE_INSTALL_PREFIX}/bin")
set(RULES_INSTALL_DIR   "/etc/udev/rules.d")

set(CMAKE_MODULE_PATH   "${CMAKE_SOURCE_DIR}/cmake_modules/")
set(CMAKE_MODULE_PATH   "/home/jacek/Projects/indi/cmake_modules")

find_package(CFITSIO REQUIRED)
find_package(INDI REQUIRED)
find_package(QSI REQUIRED)
find_package(ZLIB REQUIRED)

include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${CMAKE_SOURCE_DIR})
include_directories(${INDI_INCLUDE_DIR})
include_directories(${CFITSIO_INCLUDE_DIR})
include_directories(${QSI_INCLUDE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/../../current_ui_lib)
include_directories(${CMAKE_SOURCE_DIR}/../../current/client/include/)
include_directories(${CMAKE_SOURCE_DIR}/../../current/generated/)
include_directories(${CMAKE_SOURCE_DIR}/../../current/include/)
include_directories(${CMAKE_SOURCE_DIR}/../../external/release/include/)
include_directories(${CMAKE_SOURCE_DIR}/../../current_ui_lib/)
include_directories(/usr/include/x86_64-linux-gnu/qt5/)
include_directories(/usr/include/x86_64-linux-gnu/qt5/QtCore/)
include_directories(${CMAKE_SOURCE_DIR}/../../current/client/include/)

#link_directories( ${CMAKE_SOURCE_DIR}/../../external/release/lib
#                  ${CMAKE_SOURCE_DIR}/../../external/release/lib64
#                  )

set(tlins_SRCS
   ${CMAKE_SOURCE_DIR}/src/tlins_driver.cpp
)

add_executable(indi_tlins ${tlins_SRCS})

#set_target_properties(indi_tlins PROPERTIES COMPILE_FLAGS "-fPIC")

target_link_libraries(  indi_tlins
                        -L${CMAKE_SOURCE_DIR}/../../current/x86
                        -Wl,--whole-archive -ltlins_client -Wl,--no-whole-archive
                        -ltlins_loger
                        -ltlins_rpc
                        -L${CMAKE_SOURCE_DIR}/../../build-linux_telescope_ui_lib-Debug
                        -L${CMAKE_SOURCE_DIR}/../../external/release/lib
                        -L${CMAKE_SOURCE_DIR}/../../external/release/lib64
                        ${INDI_DRIVER_LIBRARIES}
                        ${CFITSIO_LIBRARIES}
                        ${QSI_LIBRARIES}
                        -lprotobuf
                        -lgrpc++
                        -lgrpc
                        -pthread
                        -llinux_telescope_ui_lib
                        -lQt5Sql
                        -lQt5Core
                        )

#
#                       -tlins_loger
#                       -tlins_rpc
#                       -tlins_client
