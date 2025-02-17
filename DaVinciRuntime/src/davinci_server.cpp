#include <iostream>
#include <memory>
#include <string>
#include <deque>
#include <mutex>
#include <grpc++/grpc++.h>
#include "davinci.grpc.pb.h"
#include "ShellyPlusDimmerData.h"
#include "ShellyPlusPlugData.h"
#include "ShellyPlusTemperatureData.h"
#include "davinci_server.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using daVinciRPC::DaVinciService;
using daVinciRPC::Empty;
using daVinciRPC::RPC_DimmerDataArray;
using daVinciRPC::RPC_PlugDataArray;
using daVinciRPC::RPC_TemperatureDataArray;
using daVinciRPC::RPC_ShellyPlusDimmerData ;
using daVinciRPC::RPC_ShellyPlusPlugData;
using daVinciRPC::RPC_ShellyPlusTemperatureData;

std::unique_ptr<Server> server;

DaVinciServiceImpl::DaVinciServiceImpl(Database* db) : db_(db) {}

grpc::Status DaVinciServiceImpl::GetDimmerData(grpc::ServerContext* context, const daVinciRPC::Empty* request, daVinciRPC::RPC_DimmerDataArray* response) {
    auto rows = db_->query("SELECT source, brightness, state, timestamp FROM DimmerData");
    for (const auto& row : rows) {
        auto* data = response->add_dimmer_data();
        data->set_source(row[0]);
        data->set_brightness(std::stoi(row[1]));
        data->set_state(std::stoi(row[2]));
        data->set_timestamp(std::stoll(row[3]));
    }
    return grpc::Status::OK;
}

grpc::Status DaVinciServiceImpl::GetPlugData(grpc::ServerContext* context, const daVinciRPC::Empty* request, daVinciRPC::RPC_PlugDataArray* response) {
    auto rows = db_->query("SELECT source, power, timestamp FROM PlugData");
    for (const auto& row : rows) {
        auto* data = response->add_plug_data();
        data->set_source(row[0]);
        data->set_power(std::stod(row[1]));
        data->set_timestamp(std::stoll(row[2]));
    }
    return grpc::Status::OK;
}

grpc::Status DaVinciServiceImpl::GetTemperatureData(grpc::ServerContext* context, const daVinciRPC::Empty* request, daVinciRPC::RPC_TemperatureDataArray* response) {
    auto rows = db_->query("SELECT source, temperature, humidity, timestamp FROM TemperatureData");
    for (const auto& row : rows) {
        auto* data = response->add_temperature_data();
        data->set_source(row[0]);
        data->set_temperature(std::stod(row[1]));
        data->set_humidity(std::stod(row[2]));
        data->set_timestamp(std::stoll(row[3]));
    }
    return grpc::Status::OK;
}

void RunServer(const std::string& port, Database* db) {
    std::string server_address("0.0.0.0:50051");
    DaVinciServiceImpl service(db);

    ServerBuilder builder;
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);
    server = builder.BuildAndStart();
    std::cout << "Server listening on " << server_address << std::endl;
    server->Wait();
}

void StopServer() {
    if (server) {
        server->Shutdown();
        server->Wait();
        server.reset();
        std::cout << "Server stopped" << std::endl;
    }
}