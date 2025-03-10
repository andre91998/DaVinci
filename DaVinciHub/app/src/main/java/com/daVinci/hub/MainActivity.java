/*
 * Copyright 2015 The gRPC Authors
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

package com.daVinci.hub;

import android.os.Bundle;
import androidx.appcompat.app.AppCompatActivity;

import android.text.method.ScrollingMovementMethod;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;

import java.util.concurrent.Callable;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.Future;

import davinci.io.grpc.RPC_DimmerDataArray;
import davinci.io.grpc.RPC_PlugDataArray;
import davinci.io.grpc.RPC_Sensors;
import davinci.io.grpc.RPC_SupportedSensorTypes;
import davinci.io.grpc.RPC_TemperatureDataArray;

public class MainActivity extends AppCompatActivity {
  private static final String TAG = "MainActivity";
  private Button sendButton;
  private TextView dimmerText, temperatureText, plugText;
  private GrpcClient grpcClient;

  @Override
  protected void onCreate(Bundle savedInstanceState) {
    super.onCreate(savedInstanceState);
    setContentView(R.layout.activity_main);
    //Hard Coded local address for now
    grpcClient = new GrpcClient("192.168.86.73", 50051); // Adjust as needed

    dimmerText = (TextView) findViewById(R.id.textView3);
    dimmerText.setMovementMethod(new ScrollingMovementMethod());
    temperatureText = (TextView) findViewById(R.id.textView);
    temperatureText.setMovementMethod(new ScrollingMovementMethod());
    plugText = (TextView) findViewById(R.id.textView2);
    plugText.setMovementMethod(new ScrollingMovementMethod());

    ExecutorService executor = Executors.newFixedThreadPool(1);

    GetSensorTypesCallable callable = new GetSensorTypesCallable();
    Future<String> future = executor.submit(callable);

    GetDimmerDataCallable callable1 = new GetDimmerDataCallable();
    Future<RPC_DimmerDataArray> dimmerFuture = executor.submit(callable1);

    GetPlugDataCallable callable2 = new GetPlugDataCallable();
    Future<RPC_PlugDataArray> plugFuture = executor.submit(callable2);

    GetTemperatureDataCallable callable3 = new GetTemperatureDataCallable();
    Future<RPC_TemperatureDataArray> temperatureFuture = executor.submit(callable3);

    GetSensorsCallable callable4 = new GetSensorsCallable();
    Future<RPC_Sensors> sensorsFuture = executor.submit(callable4);

    try {
      String result = future.get();
      System.out.println("Result from thread: " + result);

      //If tables are empty, this crashes
      RPC_DimmerDataArray dimmerDataArray = dimmerFuture.get();
      if (dimmerDataArray != null) {
        dimmerText.setText(String.valueOf(dimmerDataArray.getDimmerData(dimmerDataArray.getDimmerDataCount() - 1).getBrightness()));
      } else {
        dimmerText.setText("N/A");
      }

      RPC_PlugDataArray plugDataArray = plugFuture.get();
      if (plugDataArray != null) {
        plugText.setText(String.valueOf(plugDataArray.getPlugData(plugDataArray.getPlugDataCount() - 1).getPower()));
      } else {
        plugText.setText("N/A");
      }

      RPC_TemperatureDataArray temperatureDataArray = temperatureFuture.get();
      if (temperatureDataArray != null) {
        temperatureText.setText(String.valueOf(temperatureDataArray.getTemperatureData(temperatureDataArray.getTemperatureDataCount() - 1).getTemperature()));
      } else {
        temperatureText.setText("N/A");
      }

      RPC_Sensors sensors = sensorsFuture.get();
      if (sensors != null) {
        Log.d(TAG, sensors.getSensorNamesList().toString());
      }
    } catch (InterruptedException | ExecutionException | IndexOutOfBoundsException e) {
      e.printStackTrace();
    } finally {
      executor.shutdown();
    }
  }

  @Override
  protected void onDestroy() {
    super.onDestroy();
    grpcClient.shutdown();
  }

  class GetSensorTypesCallable implements Callable<String> {
    @Override
    public String call() throws Exception {
      RPC_SupportedSensorTypes sensorTypes = grpcClient.getSupportedSensorTypes();
      if (sensorTypes != null) {
        Log.d(TAG, "Supported Sensor Types: " + sensorTypes.getSensorTypesList());
        return sensorTypes.toString();
      }
      return "N/A";
    }
  }

  class GetDimmerDataCallable implements Callable<RPC_DimmerDataArray> {
    @Override
    public RPC_DimmerDataArray call() throws Exception {
        return grpcClient.getDimmerData();
    }
  }

  class GetTemperatureDataCallable implements Callable<RPC_TemperatureDataArray> {
    @Override
    public RPC_TemperatureDataArray call() throws Exception {
        return grpcClient.getTemperatureData();
    }
  }

  class GetPlugDataCallable implements Callable<RPC_PlugDataArray> {
    @Override
    public RPC_PlugDataArray call() throws Exception {
        return grpcClient.getPlugData();
    }
  }

  class GetSensorsCallable implements Callable<RPC_Sensors> {
    @Override
    public RPC_Sensors call() throws Exception {
        return grpcClient.getAllSensors();
    }
  }
}
