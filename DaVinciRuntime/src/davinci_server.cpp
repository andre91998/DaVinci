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
#include "sensor_types.h"

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
using daVinciRPC::RPC_SensorArray;
using daVinciRPC::RPC_Sensor;

std::unique_ptr<Server> server;

DaVinciServiceImpl::DaVinciServiceImpl(Database* db) : db_(db) {}

grpc::Status DaVinciServiceImpl::GetSupportedSensorTypes(grpc::ServerContext* context, const daVinciRPC::Empty* request, daVinciRPC::RPC_SupportedSensorTypes* response) {
    std::vector<SensorType> sensor_types = {SensorType::SHELLY_TEMP, SensorType::SHELLY_DIMMER, SensorType::SHELLY_PLUG};
    for (const auto& type : sensor_types) {
        response->add_sensor_types(GetSensorTypeString(type));
    }
    return Status::OK;
}

grpc::Status DaVinciServiceImpl::GetSensorList(grpc::ServerContext* context, const daVinciRPC::Empty* request, daVinciRPC::RPC_SensorArray* response) {
    try {
        std::vector<std::string> tableList = db_->listTables();
        for (int i = 0; i < tableList.size(); i++) {
            std::vector<std::string> sensorSubList = GetUniqueColumnValues(db_, tableList.at(i), "source");
            std::copy(sensorSubList.begin(), sensorSubList.end(), std::ostream_iterator<std::string>(std::cout, " "));
            std::cout << std::endl;
            for (int j = 0; j < sensorSubList.size(); j++) {
                std::string sensor_type = tableList.at(i);
                sensor_type[0] = std::toupper(sensor_type[0]);
                daVinciRPC::RPC_Sensor* sensor = response->add_rpc_sensor();
                sensor->set_sensor_name(sensorSubList.at(j));
                sensor->set_sensor_type(sensor_type);
            }
        }

        return grpc::Status::OK;

    } catch (const std::exception& e) {
        std::cerr << "Error in GetSensorList: " << e.what() << std::endl;
        return grpc::Status(grpc::StatusCode::INTERNAL, e.what());
    }
}

grpc::Status DaVinciServiceImpl::GetDimmerData(grpc::ServerContext* context, const daVinciRPC::Empty* request, daVinciRPC::RPC_DimmerDataArray* response) {
    try {
        auto rows = db_->query("SELECT source, brightness, state, timestamp FROM shellyPlusDimmer");
        for (const auto& row : rows) {
            auto* data = response->add_dimmer_data();
            data->set_source(row[0]);
            data->set_brightness(std::stoi(row[1]));
            data->set_state(std::stoi(row[2]));
            data->set_timestamp(std::stoll(row[3]));
        }
        return grpc::Status::OK;
    } catch (const std::exception& e) {
        std::cerr << "Error in GetDimmerData: " << e.what() << std::endl;
        return grpc::Status(grpc::StatusCode::INTERNAL, e.what());
    }
}

grpc::Status DaVinciServiceImpl::GetPlugData(grpc::ServerContext* context, const daVinciRPC::Empty* request, daVinciRPC::RPC_PlugDataArray* response) {
    try {
        auto rows = db_->query("SELECT source, power, timestamp FROM shellyPlusPlug");
        std::cout << "Plug rows: " << rows.size() << std::endl;
        for (const auto& row : rows) {
            auto* data = response->add_plug_data();
            data->set_source(row[0]);
            data->set_power(std::stod(row[1]));
            data->set_timestamp(std::stoll(row[2]));
        }
        return grpc::Status::OK;
    } catch (const std::exception& e) {
        std::cerr << "Error in GetPlugData: " << e.what() << std::endl;
        return grpc::Status(grpc::StatusCode::INTERNAL, e.what());
    }
}

grpc::Status DaVinciServiceImpl::GetTemperatureData(grpc::ServerContext* context, const daVinciRPC::Empty* request, daVinciRPC::RPC_TemperatureDataArray* response) {
    try {
        auto rows = db_->query("SELECT source, humidity, temperature, timestamp FROM shellyPlusTemperature");
        for (const auto& row : rows) {
            auto* data = response->add_temperature_data();
            data->set_source(row[0]);
            data->set_humidity(std::stod(row[1]));
            data->set_temperature(std::stod(row[2]));
            data->set_timestamp(std::stoll(row[3]));
        }
        return grpc::Status::OK;
    } catch (const std::exception& e) {
        std::cerr << "Error in GetTemperatureData: " << e.what() << std::endl;
        return grpc::Status(grpc::StatusCode::INTERNAL, e.what());
    }
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

std::vector<std::string> GetUniqueColumnValues(Database* db, const std::string& tableName, const std::string& columnName) {
    std::vector<std::string> uniqueValues;
    std::cout << "Get unique values for: " << columnName << std::endl;
    try {
        std::string query = "SELECT DISTINCT " + columnName + " FROM " + tableName;
        auto rows = db->query(query);

        for (const auto& row : rows) {
            if (!row.empty()) {
                std::cout << "Unique value: " << row[0] << std::endl;
                uniqueValues.push_back(row[0]);
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "Error in GetUniqueColumnValues: " << e.what() << std::endl;
    }
    return uniqueValues;
}

std::string GetSensorTypeString(SensorType type) {
    switch (type) {
        case SensorType::SHELLY_TEMP:
            return "ShellyPlusTemperature";
            break;
        case SensorType::SHELLY_DIMMER:
            return "ShellyPlusDimmer";
            break;
        case SensorType::SHELLY_PLUG:
            return "ShellyPlusPlug";
            break;
        default:
            return "Unkown";
    }
}