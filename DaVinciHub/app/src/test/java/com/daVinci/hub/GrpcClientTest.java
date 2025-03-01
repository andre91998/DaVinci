package com.daVinci.hub;

import static org.junit.jupiter.api.Assertions.*;
import static org.mockito.Mockito.*;

import io.grpc.ManagedChannel;
import io.grpc.StatusRuntimeException;
import org.junit.jupiter.api.*;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.extension.ExtendWith;
import org.mockito.*;
import org.mockito.junit.jupiter.MockitoExtension;

import java.lang.reflect.Field;

import davinci.io.grpc.*;

@ExtendWith(MockitoExtension.class)
public class GrpcClientTest {

    @Mock
    private ManagedChannel mockChannel;

    @Mock
    private DaVinciServiceGrpc.DaVinciServiceBlockingStub mockBlockingStub;

    private GrpcClient grpcClient;

    @BeforeEach
    public void setUp() {
        grpcClient = new GrpcClient("localhost", 50051);
        try {
            setGrpcClientBlockingStub(grpcClient, mockBlockingStub);
        } catch (NoSuchFieldException | IllegalAccessException e) {
            fail("Failed to set up GrpcClient: " + e.getMessage());
        }
    }

    private void setGrpcClientBlockingStub(GrpcClient grpcClient, DaVinciServiceGrpc.DaVinciServiceBlockingStub blockingStub)
            throws NoSuchFieldException, IllegalAccessException {
        Field blockingStubField = GrpcClient.class.getDeclaredField("blockingStub");
        blockingStubField.setAccessible(true);
        blockingStubField.set(grpcClient, blockingStub);
    }

    @Test
    public void testGetSupportedSensorTypes() {
        RPC_SupportedSensorTypes expectedResponse = RPC_SupportedSensorTypes.newBuilder()
                .addSensorTypes("Temperature")
                .addSensorTypes("Humidity")
                .build();

        when(mockBlockingStub.getSupportedSensorTypes(any(Empty.class))).thenReturn(expectedResponse);

        RPC_SupportedSensorTypes actualResponse = grpcClient.getSupportedSensorTypes();
        assertNotNull(actualResponse);
        assertEquals(expectedResponse, actualResponse);
    }

    @Test
    public void testGetSupportedSensorTypesWithException() {
        when(mockBlockingStub.getSupportedSensorTypes(any(Empty.class))).thenThrow(StatusRuntimeException.class);

        RPC_SupportedSensorTypes actualResponse = grpcClient.getSupportedSensorTypes();
        assertNull(actualResponse);
    }

    @Test
    public void testGetDimmerData() {
        RPC_DimmerDataArray expectedResponse = RPC_DimmerDataArray.newBuilder()
                .addDimmerData(RPC_ShellyPlusDimmerData.newBuilder().setSource("Dimmer1").build())
                .build();

        when(mockBlockingStub.getDimmerData(any(Empty.class))).thenReturn(expectedResponse);

        RPC_DimmerDataArray actualResponse = grpcClient.getDimmerData();
        assertNotNull(actualResponse);
        assertEquals(expectedResponse, actualResponse);
    }

    @Test
    public void testGetDimmerDataWithException() {
        when(mockBlockingStub.getDimmerData(any(Empty.class))).thenThrow(StatusRuntimeException.class);

        RPC_DimmerDataArray actualResponse = grpcClient.getDimmerData();
        assertNull(actualResponse);
    }

    @Test
    public void testGetPlugData() {
        RPC_PlugDataArray expectedResponse = RPC_PlugDataArray.newBuilder()
                .addPlugData(RPC_ShellyPlusPlugData.newBuilder().setSource("Plug1").build())
                .build();

        when(mockBlockingStub.getPlugData(any(Empty.class))).thenReturn(expectedResponse);

        RPC_PlugDataArray actualResponse = grpcClient.getPlugData();
        assertNotNull(actualResponse);
        assertEquals(expectedResponse, actualResponse);
    }

    @Test
    public void testGetPlugDataWithException() {
        when(mockBlockingStub.getPlugData(any(Empty.class))).thenThrow(StatusRuntimeException.class);

        RPC_PlugDataArray actualResponse = grpcClient.getPlugData();
        assertNull(actualResponse);
    }

    @Test
    public void testGetTemperatureData() {
        RPC_TemperatureDataArray expectedResponse = RPC_TemperatureDataArray.newBuilder()
                .addTemperatureData(RPC_ShellyPlusTemperatureData.newBuilder().setSource("Sensor1").build())
                .build();

        when(mockBlockingStub.getTemperatureData(any(Empty.class))).thenReturn(expectedResponse);

        RPC_TemperatureDataArray actualResponse = grpcClient.getTemperatureData();
        assertNotNull(actualResponse);
        assertEquals(expectedResponse, actualResponse);
    }

    @Test
    public void testGetTemperatureDataWithException() {
        when(mockBlockingStub.getTemperatureData(any(Empty.class))).thenThrow(StatusRuntimeException.class);

        RPC_TemperatureDataArray actualResponse = grpcClient.getTemperatureData();
        assertNull(actualResponse);
    }

    @Test
    public void testShutdown() {
        // Use reflection to access the private channel field
        try {
            Field channelField = GrpcClient.class.getDeclaredField("channel");
            channelField.setAccessible(true);
            ManagedChannel channel = (ManagedChannel) channelField.get(grpcClient);

            grpcClient.shutdown();
            assertTrue(channel.isShutdown(), "Channel should be shut down");
        } catch (NoSuchFieldException | IllegalAccessException | NullPointerException e) {
            fail("Failed to access or shutdown the channel: " + e.getMessage());
        }
    }
}