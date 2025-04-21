package com.daVinci.hub;

import static org.junit.jupiter.api.Assertions.*;
import static org.mockito.Mockito.*;

import android.util.Log;

import io.grpc.ManagedChannel;
import io.grpc.StatusRuntimeException;
import org.junit.jupiter.api.*;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.extension.ExtendWith;
import org.mockito.*;
import org.mockito.junit.jupiter.MockitoExtension;

import java.lang.reflect.Field;

import davinci.io.grpc.*;

//@ExtendWith(MockitoExtension.class)
public class GrpcClientTest {

    @Mock
    private ManagedChannel mockChannel;

    @Mock
    private DaVinciServiceGrpc.DaVinciServiceBlockingStub mockBlockingStub;

    private GrpcClient grpcClient;

    @BeforeEach
    public void setUp() {
        // Initialize Mockito annotations
        MockitoAnnotations.openMocks(this);

        grpcClient = new GrpcClient("75.6.165.166", 50051);
        try {
            setGrpcClientBlockingStub(grpcClient, mockBlockingStub);
            Field blockingStubField = GrpcClient.class.getDeclaredField("blockingStub");
            blockingStubField.setAccessible(true);
            Object injectedStub = blockingStubField.get(grpcClient);
            assertEquals(mockBlockingStub, injectedStub, "The mockBlockingStub was not correctly injected!");
        } catch (NoSuchFieldException | IllegalAccessException e) {
            fail("Failed to set up GrpcClient: " + e.getMessage());
        }

        mockStatic(Log.class);
        when(Log.e(anyString(), anyString())).thenReturn(0);
    }

    @AfterEach
    public void tearDown() {
        clearAllCaches();
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
        assertEquals(RPC_SupportedSensorTypes.newBuilder().build().getSensorTypesCount(),
                actualResponse.getSensorTypesCount());
    }

    @Test
    public void testGetAllSensors() {
        RPC_Sensor sensor = RPC_Sensor.newBuilder().setSensorName("sensor1").setSensorType("type1")
                .build();
        RPC_SensorArray expectedResponse = RPC_SensorArray.newBuilder()
                .addRPCSensor(sensor)
                .build();

        when(mockBlockingStub.getSensorList(any(Empty.class))).thenReturn(expectedResponse);

        RPC_SensorArray actualResponse = grpcClient.getAllSensors();
        assertNotNull(actualResponse);
        assertEquals(expectedResponse, actualResponse);
    }

    @Test
    public void testGetAllSensorsWithException() {
        when(mockBlockingStub.getSensorList(any(Empty.class))).thenThrow(StatusRuntimeException.class);

        RPC_SensorArray actualResponse = grpcClient.getAllSensors();
        assertEquals(RPC_SensorArray.newBuilder().build().getRPCSensorCount(),
                actualResponse.getRPCSensorCount());
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
        assertEquals(RPC_DimmerDataArray.newBuilder().build().getDimmerDataCount(),
                actualResponse.getDimmerDataCount());
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
        assertEquals(RPC_PlugDataArray.newBuilder().build().getPlugDataCount(),
                actualResponse.getPlugDataCount());
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
        assertEquals(RPC_TemperatureDataArray.newBuilder().build().getTemperatureDataCount(),
                actualResponse.getTemperatureDataCount());
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