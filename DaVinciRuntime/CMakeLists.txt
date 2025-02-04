cmake_minimum_required(VERSION 3.16)
project(DaVinciRuntime C CXX)

set(CMAKE_CXX_STANDARD 17)

find_package(PahoMqttCpp REQUIRED)

# Use pkg-config to find jsoncpp
find_package(PkgConfig REQUIRED)
pkg_check_modules(JSONCPP jsoncpp)

# Include directories
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${JSONCPP_INCLUDE_DIRS})

# Source Files
set (SOURCES
    src/main.cpp
    src/mqtt_client.cpp
    src/config.cpp
)

#Add Executable
add_executable(DaVinciRuntime ${SOURCES})

#Link Libraries
target_link_libraries(DaVinciRuntime 
    PahoMqttCpp::paho-mqttpp3
    ${JSONCPP_LIBRARIES}
)