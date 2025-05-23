import grpc
import logging
import sys

# Import the generated classes
# NOTE: These are updated only when runAll.py is run
import davinci_pb2 as pb2
import davinci_pb2_grpc as pb2_grpc

# Configure logging
logging.basicConfig(level=logging.INFO)



def main():
    def test_supported_sensor_types(stub):
        try:
            request = pb2.Empty()
            response = stub.GetSupportedSensorTypes(request)
            #logging.info(f"GetSupportedSensorTypes response: {response}")
            return True
        except grpc.RpcError as e:
            logging.error(f"An error occurred during GetSupportedSensorTypes: {e.details()}")
            logging.error(f"Error code: {e.code()}")
            logging.error(f"Debug details: {e.debug_error_string()}")
            return False
        
    def test_sensor_list(stub):
        try:
            request = pb2.Empty()
            response = stub.GetSensorList(request)
            #logging.info(f"GetSensorList response: {response}")
            return True
        except grpc.RpcError as e:
            logging.error(f"An error occurred during GetSensorList: {e.details()}")
            logging.error(f"Error code: {e.code()}")
            logging.error(f"Debug details: {e.debug_error_string()}")
            return False

    def test_dimmer_data(stub):
        try:
            request = pb2.Empty()
            response = stub.GetDimmerData(request)
            #logging.info(f"GetDimmerData response: {response}")
            return True
        except grpc.RpcError as e:
            logging.error(f"An error occurred during GetDimmerData: {e.details()}")
            logging.error(f"Error code: {e.code()}")
            logging.error(f"Debug details: {e.debug_error_string()}")
            return False

    def test_plug_data(stub):
        try:
            request = pb2.Empty()
            response = stub.GetPlugData(request)
            #logging.info(f"GetPlugData response: {response}")
            return True
        except grpc.RpcError as e:
            logging.error(f"An error occurred during GetPlugData: {e.details()}")
            logging.error(f"Error code: {e.code()}")
            logging.error(f"Debug details: {e.debug_error_string()}")
            return False

    def test_temperature_data(stub):
        try:
            request = pb2.Empty()
            response = stub.GetTemperatureData(request)
            #logging.info(f"GetTemperatureData response: {response}")
            return True
        except grpc.RpcError as e:
            logging.error(f"An error occurred during GetTemperatureData: {e.details()}")
            logging.error(f"Error code: {e.code()}")
            logging.error(f"Debug details: {e.debug_error_string()}")
            return False
    grpc_server = "localhost:50051"  # Update with the actual gRPC server address

    # Create a channel and stub
    channel = grpc.insecure_channel(grpc_server)
    stub = pb2_grpc.DaVinciServiceStub(channel)

    # Run tests
    supported_sensor_types_test = test_supported_sensor_types(stub)
    sensor_list_test = test_sensor_list(stub)
    dimmer_data_test = test_dimmer_data(stub)
    plug_data_test = test_plug_data(stub)
    temperature_data_test = test_temperature_data(stub)

    # Check results
    if supported_sensor_types_test and sensor_list_test and dimmer_data_test and plug_data_test and temperature_data_test:
        logging.info("All gRPC Service Tests: PASSED!")
        sys.exit(1)
    else:
        logging.info("One or more gRPC Service Tests: FAILED!")
        sys.exit(0)

if __name__ == "__main__":
    main()