package com.daVinci.hub;

import android.util.Log;
import davinci.io.grpc.RPC_SensorArray;
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
    private static final String TAG = "GrpcClient";
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
            Log.e(TAG, "Exception in getSupportedSensorTypes: " + e.getMessage());
            return RPC_SupportedSensorTypes.newBuilder().build();
        }
    }

    public RPC_SensorArray getAllSensors() {
        Empty request = Empty.newBuilder().build();
        try {
            return blockingStub.getSensorList(request);
        } catch (StatusRuntimeException e) {
            // Handle exceptions as needed
            Log.e(TAG, "Exception in getAllSensors:  " + e.getMessage());
            return RPC_SensorArray.newBuilder().build();
        }
    }

    //ZERO INDEX OF THE DATA ARRAYS IS THE OLDEST DATA POINT, NOT THE MOST RECENT

    public RPC_DimmerDataArray getDimmerData() {
        Empty request = Empty.newBuilder().build();
        try {
            return blockingStub.getDimmerData(request);
        } catch (StatusRuntimeException e) {
            // Handle exceptions as needed
            Log.e(TAG, "Exception in getDimmerData: " + e.getMessage());
            return RPC_DimmerDataArray.newBuilder().build();
        }
    }

    public RPC_PlugDataArray getPlugData() {
        Empty request = Empty.newBuilder().build();
        try {
            return blockingStub.getPlugData(request);
        } catch (StatusRuntimeException e) {
            // Handle exceptions as needed
            Log.e(TAG, "Exception in getPlugData: " + e.getMessage());

            return RPC_PlugDataArray.newBuilder().build();
        }
    }

    public RPC_TemperatureDataArray getTemperatureData() {
        Empty request = Empty.newBuilder().build();
        try {
            return blockingStub.getTemperatureData(request);
        } catch (StatusRuntimeException e) {
            // Handle exceptions as needed
            Log.e(TAG, "Exception in getTemperatureData: " + e.getMessage());
            return RPC_TemperatureDataArray.newBuilder().build();
        }
    }

    public void shutdown() {
        channel.shutdown();
    }
}