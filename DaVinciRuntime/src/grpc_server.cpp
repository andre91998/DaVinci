#include <grpcpp/grpcpp.h>
#include "sensor_data.grpc.pb.h"
#include "mqtt_client.h"

class SensorDataServiceImpl final : public daVinciRPC::SensorDataService::Service {
public:
    SensorDataServiceImpl(MQTTClient* mqtt_client) : mqtt_client_(mqtt_client) {}

    grpc::Status GetSensorData(grpc::ServerContext* context, const sensor::SensorRequest* request,
                               sensor::SensorResponse* response) override {
        // Fetch sensor data from MQTT client
        mqtt_client_->fetch_sensor_data();

        // For demonstration, we'll use dummy data
        response->set_sensor_id(request->sensor_id());
        response->set_temperature(25.0);
        response->set_humidity(60.0);
        response->set_timestamp(1615567890);

        return grpc::Status::OK;
    }

private:
    MQTTClient* mqtt_client_;
};

void RunServer() {
    std::string server_address("0.0.0.0:50051");
    MQTTClient mqtt_client("mqtt.example.com", 1883, "sensors/#");
    mqtt_client.connect();
    mqtt_client.subscribe();
    SensorDataServiceImpl service(&mqtt_client);

    grpc::ServerBuilder builder;
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);
    std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
    std::cout << "Server listening on " << server_address << std::endl;
    server->Wait();
}