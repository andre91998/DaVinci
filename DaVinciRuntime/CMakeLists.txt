cmake_minimum_required(VERSION 3.16)
project(DaVinciRuntime C CXX)

include(cmake/common.cmake)

# Enable testing
enable_testing()

set(CMAKE_CXX_STANDARD 17)

find_package(PahoMqttCpp REQUIRED)
find_package(GTest REQUIRED)
#find_package(GMock REQUIRED)

# Find and link the jsoncpp library
find_package(jsoncpp CONFIG REQUIRED)

# Proto file
get_filename_component(dv_proto "${CMAKE_CURRENT_SOURCE_DIR}/proto/davinci.proto" ABSOLUTE)
get_filename_component(dv_proto_path "${dv_proto}" PATH)

# Generated sources
message(CMAKE_CURRENT_BINARY_DIR="${CMAKE_CURRENT_BINARY_DIR}")
message(_PROTOBUF_PROTOC="${_PROTOBUF_PROTOC}")
set(dv_proto_srcs "${CMAKE_CURRENT_BINARY_DIR}/davinci.pb.cc")
set(dv_proto_hdrs "${CMAKE_CURRENT_BINARY_DIR}/davinci.pb.h")
set(dv_grpc_srcs "${CMAKE_CURRENT_BINARY_DIR}/davinci.grpc.pb.cc")
set(dv_grpc_hdrs "${CMAKE_CURRENT_BINARY_DIR}/davinci.grpc.pb.h")
add_custom_command(
      OUTPUT "${dv_proto_srcs}" "${dv_proto_hdrs}" "${dv_grpc_srcs}" "${dv_grpc_hdrs}"
      COMMAND ${_PROTOBUF_PROTOC}
      ARGS --grpc_out "${CMAKE_CURRENT_BINARY_DIR}"
        --cpp_out "${CMAKE_CURRENT_BINARY_DIR}"
        -I "${dv_proto_path}"
        --plugin=protoc-gen-grpc="${_GRPC_CPP_PLUGIN_EXECUTABLE}"
        "${dv_proto}"
      DEPENDS "${dv_proto}")

# Include directories
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/util)
include_directories(${JSONCPP_INCLUDE_DIRS})
include_directories(${GTest_INCLUDE_DIRS})
# Include generated *.pb.h files
include_directories("${CMAKE_CURRENT_BINARY_DIR}")

# dv_grpc_proto
add_library(dv_grpc_proto
  ${dv_grpc_srcs}
  ${dv_grpc_hdrs}
  ${dv_proto_srcs}
  ${dv_proto_hdrs})
target_link_libraries(dv_grpc_proto
  absl::check
  ${_REFLECTION}
  ${_GRPC_GRPCPP}
  ${_PROTOBUF_LIBPROTOBUF})

# Source Files
set (SOURCES
    src/main.cpp
    src/mqtt_client.cpp
    src/config.cpp
    src/davinci_server.cpp
    src/util/ShellyPlusDimmerData.cpp
    src/util/ShellyPlusPlugData.cpp
    src/util/ShellyPlusTemperatureData.cpp
    src/util/ShellyPlusDimmerNotificationProcessor.cpp
    src/util/ShellyPlusPlugNotificationProcessor.cpp
    src/util/ShellyPlusTemperatureNotificationProcessor.cpp
    src/util/buffers.cpp
)

# Add Executable
add_executable(DaVinciRuntime ${SOURCES})

# Link Libraries
target_link_libraries(DaVinciRuntime 
    PahoMqttCpp::paho-mqttpp3
    jsoncpp_lib
    dv_grpc_proto
)

# Test Source Files
set(TEST_SOURCES
    test/test_main.cpp
    test/test_mqtt_client.cpp
    test/test_json.cpp
    test/test_JSONProcessorFactory.cpp
    test/test_ShellyPlusTemperatureNotificationProcessor.cpp
    test/test_ShellyPlusTemperatureData.cpp
    test/test_ShellyPlusPlugNotificationProcessor.cpp
    test/test_ShellyPlusPlugData.cpp
    test/test_ShellyPlusDimmerNotificationProcessor.cpp
    test/test_ShellyPlusDimmerData.cpp
    test/test_davinci_server.cpp
    src/mqtt_client.cpp  # Include implementation files required for tests
    src/config.cpp
    src/davinci_server.cpp
    src/util/ShellyPlusDimmerData.cpp
    src/util/ShellyPlusPlugData.cpp
    src/util/ShellyPlusTemperatureData.cpp
    src/util/ShellyPlusDimmerNotificationProcessor.cpp
    src/util/ShellyPlusPlugNotificationProcessor.cpp
    src/util/ShellyPlusTemperatureNotificationProcessor.cpp
    src/util/buffers.cpp
)

# Add test executable
add_executable(runTests ${TEST_SOURCES})

# Link test libraries
target_link_libraries(runTests
    PahoMqttCpp::paho-mqttpp3
    jsoncpp_lib
    dv_grpc_proto    
    GTest::gtest
    GTest::gtest_main
    GTest::gmock
    GTest::gmock_main
)

# Add tests
add_test(NAME runTests COMMAND runTests)