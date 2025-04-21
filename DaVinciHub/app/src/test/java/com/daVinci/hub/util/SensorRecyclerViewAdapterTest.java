package com.daVinci.hub.util;

import android.content.Context;
import android.content.Intent;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;
import androidx.recyclerview.widget.RecyclerView;
import com.daVinci.hub.R;
import com.daVinci.hub.ViewDimmerDataActivity;
import com.daVinci.hub.ViewPlugDataActivity;
import com.daVinci.hub.ViewTemperatureDataActivity;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.extension.ExtendWith;
import org.mockito.InjectMocks;
import org.mockito.Mock;
import org.mockito.MockitoAnnotations;
import org.mockito.junit.jupiter.MockitoExtension;

import java.util.ArrayList;
import java.util.Collections;
import davinci.io.grpc.RPC_SensorArray;
import davinci.io.grpc.RPC_Sensor;
import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertNotNull;
import static org.mockito.Mockito.*;

//@ExtendWith(MockitoExtension.class)
public class SensorRecyclerViewAdapterTest {

    @Mock
    Context mockContext;

    @Mock
    RPC_SensorArray mockSensorArray;

    @InjectMocks
    SensorRecyclerViewAdapter adapter;

    @BeforeEach
    public void setUp() {
        MockitoAnnotations.openMocks(this);
        RPC_Sensor sensor = RPC_Sensor.newBuilder()
                .setSensorName("TestSensor")
                .setSensorType("ShellyPlusTemperature")
                .build();
        mockSensorArray = RPC_SensorArray.newBuilder().addRPCSensor(sensor).build();
        adapter = new SensorRecyclerViewAdapter(mockSensorArray, mockContext);
    }

    @Test
    public void testGetItemCount() {
        assertEquals(1, adapter.getItemCount());
    }

    @Test
    public void testOnCreateViewHolder() {
        ViewGroup parent = mock(ViewGroup.class);
        LayoutInflater mockInflater = mock(LayoutInflater.class);
        View mockItemView = mock(View.class);

        // Mock Context from parent ViewGroup
        when(parent.getContext()).thenReturn(mockContext);

        // Mock LayoutInflater.from() behavior
        mockStatic(LayoutInflater.class);
        when(LayoutInflater.from(mockContext)).thenReturn(mockInflater);

        // Mock inflate() to return a mocked item view
        when(mockInflater.inflate(R.layout.sensor_item_row, parent, false)).thenReturn(mockItemView);

        // Call onCreateViewHolder
        SensorRecyclerViewAdapter.MyViewHolder viewHolder = adapter.onCreateViewHolder(parent, 0);

        // Assert that the viewHolder is created with the mocked item view
        assertNotNull(viewHolder);
        assertEquals(mockItemView, viewHolder.itemView);
    }

//    @Test
//    public void testOnBindViewHolder() {
//        View itemView = mock(View.class);
//        TextView titleTextView = mock(TextView.class);
//        SensorRecyclerViewAdapter.MyViewHolder holder = adapter.new MyViewHolder(itemView);
//        when(itemView.findViewById(R.id.title_text_view)).thenReturn(titleTextView);
//
//
//        adapter.onBindViewHolder(holder, 0);
//        verify(titleTextView).setText("TestSensor");
//
//        holder.itemView.performClick();
//        verify(mockContext, times(1)).startActivity(any(Intent.class));
//    }

//    @Test
//    public void testUpdateData() {
//        RPC_Sensor newSensor = RPC_Sensor.newBuilder()
//                .setSensorName("NewSensor")
//                .setSensorType("ShellyPlusPlug")
//                .build();
//        RPC_SensorArray newSensorArray = RPC_SensorArray.newBuilder().addRPCSensor(newSensor).build();
//
//        adapter.updateData(newSensorArray);
//        assertEquals(1, adapter.getItemCount());
//    }
}