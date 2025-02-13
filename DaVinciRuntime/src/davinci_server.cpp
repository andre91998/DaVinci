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
#include "buffers.h"
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

Status DaVinciServiceImpl::GetDimmerData(ServerContext* context, const Empty* request, RPC_DimmerDataArray* response) {
    std::lock_guard<std::mutex> lock(buffer_mutex);
    for (const auto& data : dimmer_buffer) {
        auto* new_data = response->add_dimmer_data();
        new_data->set_source(data.getSource());
        new_data->set_brightness(data.getBrightness());
        new_data->set_state(data.getState());
        new_data->set_timestamp(data.getTimestamp());
    }
    return Status::OK;
}

Status DaVinciServiceImpl::GetPlugData(ServerContext* context, const Empty* request, RPC_PlugDataArray* response) {
    std::lock_guard<std::mutex> lock(buffer_mutex);
    for (const auto& data : plug_buffer) {
        auto* new_data = response->add_plug_data();
        new_data->set_source(data.getSource());
        new_data->set_power(data.getPower());
        new_data->set_timestamp(data.getTimestamp());
    }
    return Status::OK;
}

Status DaVinciServiceImpl::GetTemperatureData(ServerContext* context, const Empty* request, RPC_TemperatureDataArray* response) {
    std::lock_guard<std::mutex> lock(buffer_mutex);
    for (const auto& data : temperature_buffer) {
        auto* new_data = response->add_temperature_data();
        new_data->set_source(data.getSource());
        new_data->set_humidity(data.getHumidity());
        new_data->set_temperature(data.getTemperature());
        new_data->set_timestamp(data.getTimestamp());
    }
    return Status::OK;
}

void RunServer(const std::string& port) {
    std::string server_address("0.0.0.0:50051");
    DaVinciServiceImpl service;

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