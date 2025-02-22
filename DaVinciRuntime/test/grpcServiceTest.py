import grpc
import sys
import os
import davinci_pb2
import davinci_pb2_grpc

def get_dimmer_data(stub):
    request = davinci_pb2.Empty()
    response = stub.GetDimmerData(request)
    if not response.dimmer_data:
        return False
    return True

def get_plug_data(stub):
    request = davinci_pb2.Empty()
    response = stub.GetPlugData(request)
    if not response.plug_data:
        return False
    return True

def get_temperature_data(stub):
    request = davinci_pb2.Empty()
    response = stub.GetTemperatureData(request)
    if not response.temperature_data:
        return False
    return True

def run():
    try:
        channel = grpc.insecure_channel('localhost:50051')
        stub = davinci_pb2_grpc.DaVinciServiceStub(channel)
        
        if not get_dimmer_data(stub):
            return False
        if not get_plug_data(stub):
            return False
        if not get_temperature_data(stub):
            return False
            
        return True
    except Exception as e:
        print(f"An error occurred: {e}")
        return False

if __name__ == '__main__':
    success = run()
    if success:
        print("gRPC Service Availability Test: PASSED!")
        sys.exit(1)
    else:
        print("gRPC Service Availability Test: FAILED!")
        sys.exit(0)