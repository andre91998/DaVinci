cmake_minimum_required(VERSION 3.16)
project(DaVinciRuntime C CXX)

# Enable testing
enable_testing()

set(CMAKE_CXX_STANDARD 17)

find_package(PahoMqttCpp REQUIRED)
find_package(GTest REQUIRED)

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

# Test Source Files
set(TEST_SOURCES
    tests/test_main.cpp
    tests/test_mqtt_client.cpp
    src/mqtt_client.cpp  # Include implementation files required for tests
)

# Add test executable
add_executable(runTests ${TEST_SOURCES})

# Link test libraries
target_link_libraries(runTests
    PahoMqttCpp::paho-mqttpp3
    ${JsonCpp_LIBRARIES}
    GTest::gtest
    GTest::gtest_main
)

# Add tests
add_test(NAME runTests COMMAND runTests)