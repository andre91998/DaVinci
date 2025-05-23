#include <gtest/gtest.h>
#include <grpc++/grpc++.h>
#include <thread>
#include <filesystem>
#include "davinci.grpc.pb.h"
#include "davinci_server.h"
#include "database.h"
#include "encrypter.h"

class DaVinciServiceTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Create a test database
        test_db_path = "test_davinci.db";
        db = Database::getInstance(test_db_path);

        // Initialize the database with some test data
        db->execute("CREATE TABLE IF NOT EXISTS shellyPlusDimmer (source TEXT, brightness INTEGER, state INTEGER, timestamp INTEGER)");
        db->execute("CREATE TABLE IF NOT EXISTS shellyPlusPlug (source TEXT, power REAL, timestamp INTEGER)");
        db->execute("CREATE TABLE IF NOT EXISTS shellyPlusTemperature (source TEXT, temperature REAL, humidity REAL, timestamp INTEGER)");

        db->execute("INSERT INTO shellyPlusDimmer (source, brightness, state, timestamp) VALUES (" +
            Encrypter::encrypt("source1") + ", " +
            Encrypter::encrypt("50") + ", " +
            Encrypter::encrypt("1") + ", " +
            Encrypter::encrypt("1234567890") + ")");
        db->execute("INSERT INTO shellyPlusPlug (source, power, timestamp) VALUES (" +
            Encrypter::encrypt("source1") + ", " +
            Encrypter::encrypt("100.0") + ", " +
            Encrypter::encrypt("1234567890") + ")");
        db->execute("INSERT INTO shellyPlusTemperature (source, humidity, temperature, timestamp) VALUES (" +
            Encrypter::encrypt("source1") + ", " +
            Encrypter::encrypt("25.0") + ", " +
            Encrypter::encrypt("60.0") + ", " +
            Encrypter::encrypt("1234567890") + ")");

        service = new DaVinciServiceImpl(db);
    }

    void TearDown() override {
        // Cleanup
        delete service;
        db->destroyInstance();
        std::filesystem::remove(test_db_path);
    }

    Database* db;
    DaVinciServiceImpl* service;
    std::string test_db_path;
};

TEST_F(DaVinciServiceTest, GetDimmerData) {
    grpc::ServerContext context;
    daVinciRPC::Empty request;
    daVinciRPC::RPC_DimmerDataArray response;

    grpc::Status status = service->GetDimmerData(&context, &request, &response);
    ASSERT_TRUE(status.ok());
    ASSERT_EQ(response.dimmer_data_size(), 1);
}

TEST_F(DaVinciServiceTest, GetPlugData) {
    grpc::ServerContext context;
    daVinciRPC::Empty request;
    daVinciRPC::RPC_PlugDataArray response;

    grpc::Status status = service->GetPlugData(&context, &request, &response);
    ASSERT_TRUE(status.ok());
    ASSERT_EQ(response.plug_data_size(), 1);
}

TEST_F(DaVinciServiceTest, GetTemperatureData) {
    grpc::ServerContext context;
    daVinciRPC::Empty request;
    daVinciRPC::RPC_TemperatureDataArray response;

    grpc::Status status = service->GetTemperatureData(&context, &request, &response);
    ASSERT_TRUE(status.ok());
    ASSERT_EQ(response.temperature_data_size(), 1);
}

TEST_F(DaVinciServiceTest, GetSupportedSensorTypes) {
    grpc::ServerContext context;
    daVinciRPC::Empty request;
    daVinciRPC::RPC_SupportedSensorTypes response;

    grpc::Status status = service->GetSupportedSensorTypes(&context, &request, &response);
    ASSERT_TRUE(status.ok());
    ASSERT_EQ(response.sensor_types_size(), 3);
    EXPECT_EQ(response.sensor_types(0), "ShellyPlusTemperature");
    EXPECT_EQ(response.sensor_types(1), "ShellyPlusDimmer");
    EXPECT_EQ(response.sensor_types(2), "ShellyPlusPlug");
}

TEST_F(DaVinciServiceTest, GetSensorList) {
    grpc::ServerContext context;
    daVinciRPC::Empty request;
    daVinciRPC::RPC_SensorArray response;

    grpc::Status status = service->GetSensorList(&context, &request, &response);
    ASSERT_TRUE(status.ok());
    ASSERT_EQ(response.rpc_sensor_size(), 3);
    EXPECT_EQ(response.rpc_sensor(0).sensor_name(), "source1");
    EXPECT_EQ(response.rpc_sensor(0).sensor_type(), "ShellyPlusDimmer");
    EXPECT_EQ(response.rpc_sensor(1).sensor_name(), "source1");
    EXPECT_EQ(response.rpc_sensor(1).sensor_type(), "ShellyPlusPlug");
    EXPECT_EQ(response.rpc_sensor(2).sensor_name(), "source1");
    EXPECT_EQ(response.rpc_sensor(2).sensor_type(), "ShellyPlusTemperature");
}

TEST_F(DaVinciServiceTest, RunServer) {
    std::thread server_thread([this]() {
        RunServer("50051", db);
    });

    // Let the server start
    std::this_thread::sleep_for(std::chrono::seconds(1));

    // Stop the server
    StopServer();

    // Wait for the server thread to finish
    if (server_thread.joinable()) {
        server_thread.join();
    }

    // If we reached here, the server started and stopped correctly
    SUCCEED();
}