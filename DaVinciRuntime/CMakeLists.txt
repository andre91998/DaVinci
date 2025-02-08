cmake_minimum_required(VERSION 3.16)
project(DaVinciRuntime C CXX)

# Enable testing
enable_testing()

set(CMAKE_CXX_STANDARD 17)

find_package(PahoMqttCpp REQUIRED)
find_package(GTest REQUIRED)
#find_package(GMock REQUIRED)

# Find and link the jsoncpp library
find_package(jsoncpp CONFIG REQUIRED)

# Include directories
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/util)
include_directories(${JSONCPP_INCLUDE_DIRS})
include_directories(${GTest_INCLUDE_DIRS})

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
    jsoncpp_lib
)

# Test Source Files
set(TEST_SOURCES
    test/test_main.cpp
    test/test_mqtt_client.cpp
    test/test_json.cpp
    test/test_JSONProcessorFactory.cpp
    src/mqtt_client.cpp  # Include implementation files required for tests
    src/config.cpp
)

# Add test executable
add_executable(runTests ${TEST_SOURCES})

# Link test libraries
target_link_libraries(runTests
    PahoMqttCpp::paho-mqttpp3
    jsoncpp_lib
    GTest::gtest
    GTest::gtest_main
    GTest::gmock
    GTest::gmock_main
)

# Add tests
add_test(NAME runTests COMMAND runTests)