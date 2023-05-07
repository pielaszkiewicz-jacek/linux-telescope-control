cmake_minimum_required(VERSION 3.14)

project(tlins_indi LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules/")
set(CMAKE_MODULE_PATH "/home/jacek/Projects/indi/cmake_modules")

find_package(CFITSIO REQUIRED)
find_package(INDI REQUIRED)
find_package(QSI REQUIRED)
find_package(ZLIB REQUIRED)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Core REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core REQUIRED)

include_directories( ./include )
include_directories( ${CMAKE_SOURCE_DIR})
include_directories( ${INDI_INCLUDE_DIR})
include_directories( ${CFITSIO_INCLUDE_DIR})
include_directories( ${QSI_INCLUDE_DIR})
include_directories( ${CMAKE_SOURCE_DIR}/include)
include_directories( ${CMAKE_SOURCE_DIR}/../current_ui_lib)
include_directories( ${CMAKE_SOURCE_DIR}/../current/client/include/)
include_directories( ${CMAKE_SOURCE_DIR}/../current/generated/)
include_directories( ${CMAKE_SOURCE_DIR}/../current/include/)
include_directories( ${CMAKE_SOURCE_DIR}/../external/release/include/)
include_directories( ${CMAKE_SOURCE_DIR}/../current_ui_lib/)
include_directories( /usr/include/x86_64-linux-gnu/qt5/)
include_directories( /usr/include/x86_64-linux-gnu/qt5/QtCore/)
include_directories( ${CMAKE_SOURCE_DIR}/../current/client/include/)

link_directories( ${CMAKE_SOURCE_DIR}/../build-linux_telescope_ui_lib-Debug
                  ${CMAKE_SOURCE_DIR}/../external/release/lib
                  ${CMAKE_SOURCE_DIR}/../external/release/lib64
                  ${CMAKE_SOURCE_DIR}/../current/x86
                  )

add_executable(tlins_indi
  tlins_driver.cpp
    main.cpp
)
target_link_libraries(tlins_indi
    ${INDI_DRIVER_LIBRARIES}
    ${CFITSIO_LIBRARIES}
    ${QSI_LIBRARIES}
    -ltlins_client
    -ltlins_loger
    -ltlins_rpc
    -lprotobuf
    -lgrpc++
    -lgrpc
    -llinux_telescope_ui_lib
    -lQt5Sql
    -lQt5Core
    -pthread
    )
