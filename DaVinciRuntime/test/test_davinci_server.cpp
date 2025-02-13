#include <gtest/gtest.h>
#include <grpc++/grpc++.h>
#include "davinci.grpc.pb.h"
#include "davinci_server.h"
#include "buffers.h"

class DaVinciServiceTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Initialize the buffers with some test data
        dimmer_buffer.clear();
        dimmer_buffer.push_back(ShellyPlusDimmerData("source1", 50, true, 1234567890));
        plug_buffer.clear();
        plug_buffer.push_back(ShellyPlusPlugData("source1", 100.0, 1234567890));
        temperature_buffer.clear();
        temperature_buffer.push_back(ShellyPlusTemperatureData("source1", 25.0, 60.0, 1234567890));
    }

    void TearDown() override {
        // Clear the buffers
        dimmer_buffer.clear();
        plug_buffer.clear();
        temperature_buffer.clear();
    }

    DaVinciServiceImpl service;
};

TEST_F(DaVinciServiceTest, GetDimmerData) {
    grpc::ServerContext context;
    daVinciRPC::Empty request;
    daVinciRPC::RPC_DimmerDataArray response;

    grpc::Status status = service.GetDimmerData(&context, &request, &response);
    ASSERT_TRUE(status.ok());
    ASSERT_EQ(response.dimmer_data_size(), 1);
}

TEST_F(DaVinciServiceTest, GetPlugData) {
    grpc::ServerContext context;
    daVinciRPC::Empty request;
    daVinciRPC::RPC_PlugDataArray response;

    grpc::Status status = service.GetPlugData(&context, &request, &response);
    ASSERT_TRUE(status.ok());
    ASSERT_EQ(response.plug_data_size(), 1);
}

TEST_F(DaVinciServiceTest, GetTemperatureData) {
    grpc::ServerContext context;
    daVinciRPC::Empty request;
    daVinciRPC::RPC_TemperatureDataArray response;

    grpc::Status status = service.GetTemperatureData(&context, &request, &response);
    ASSERT_TRUE(status.ok());
    ASSERT_EQ(response.temperature_data_size(), 1);
}