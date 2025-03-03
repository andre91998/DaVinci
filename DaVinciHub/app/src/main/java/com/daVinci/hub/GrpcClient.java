package com.daVinci.hub;

import davinci.io.grpc.RPC_Sensors;
import io.grpc.ManagedChannel;
import io.grpc.ManagedChannelBuilder;
import io.grpc.StatusRuntimeException;
import davinci.io.grpc.DaVinciServiceGrpc;
import davinci.io.grpc.Empty;
import davinci.io.grpc.RPC_SupportedSensorTypes;
import davinci.io.grpc.RPC_DimmerDataArray;
import davinci.io.grpc.RPC_PlugDataArray;
import davinci.io.grpc.RPC_TemperatureDataArray;

public class GrpcClient {
    private final ManagedChannel channel;
    private final DaVinciServiceGrpc.DaVinciServiceBlockingStub blockingStub;

    public GrpcClient(String host, int port) {
        this.channel = ManagedChannelBuilder.forAddress(host, port)
                .usePlaintext() // Disable SSL for simplicity
                .build();
        this.blockingStub = DaVinciServiceGrpc.newBlockingStub(channel);
    }

    public RPC_SupportedSensorTypes getSupportedSensorTypes() {
        Empty request = Empty.newBuilder().build();
        try {
            return blockingStub.getSupportedSensorTypes(request);
        } catch (StatusRuntimeException e) {
            // Handle exceptions as needed
            return null;
        }
    }

    public RPC_Sensors getAllSensors() {
        Empty request = Empty.newBuilder().build();
        try {
            return blockingStub.getSensorList(request);
        } catch (StatusRuntimeException e) {
            // Handle exceptions as needed
            return null;
        }
    }

    //ZERO INDEX OF THE DATA ARRAYS IS THE OLDEST DATA POINT, NOT THE MOST RECENT

    public RPC_DimmerDataArray getDimmerData() {
        Empty request = Empty.newBuilder().build();
        try {
            return blockingStub.getDimmerData(request);
        } catch (StatusRuntimeException e) {
            // Handle exceptions as needed
            return null;
        }
    }

    public RPC_PlugDataArray getPlugData() {
        Empty request = Empty.newBuilder().build();
        try {
            return blockingStub.getPlugData(request);
        } catch (StatusRuntimeException e) {
            // Handle exceptions as needed
            return null;
        }
    }

    public RPC_TemperatureDataArray getTemperatureData() {
        Empty request = Empty.newBuilder().build();
        try {
            return blockingStub.getTemperatureData(request);
        } catch (StatusRuntimeException e) {
            // Handle exceptions as needed
            return null;
        }
    }

    public void shutdown() {
        channel.shutdown();
    }
}