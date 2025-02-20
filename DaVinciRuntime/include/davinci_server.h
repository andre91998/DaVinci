#ifndef DAVINCI_SERVER_H
#define DAVINCI_SERVER_H

#include <grpc++/grpc++.h>
#include "davinci.grpc.pb.h"
#include "ShellyPlusDimmerData.h"
#include "ShellyPlusPlugData.h"
#include "ShellyPlusTemperatureData.h"
#include "database.h"
//#include "buffers.h"

class DaVinciServiceImpl final : public daVinciRPC::DaVinciService::Service {
public:
    explicit DaVinciServiceImpl(Database* db);

    grpc::Status GetSupportedSensorTypes(grpc::ServerContext* context, const daVinciRPC::Empty* request, daVinciRPC::RPC_SupportedSensorTypes* response) override;
    grpc::Status GetDimmerData(grpc::ServerContext* context, const daVinciRPC::Empty* request, daVinciRPC::RPC_DimmerDataArray* response) override;
    grpc::Status GetPlugData(grpc::ServerContext* context, const daVinciRPC::Empty* request, daVinciRPC::RPC_PlugDataArray* response) override;
    grpc::Status GetTemperatureData(grpc::ServerContext* context, const daVinciRPC::Empty* request, daVinciRPC::RPC_TemperatureDataArray* response) override;

private:
    Database* db_;
};

void RunServer(const std::string& port, Database* db);
void StopServer();

#endif // DAVINCI_SERVER_H