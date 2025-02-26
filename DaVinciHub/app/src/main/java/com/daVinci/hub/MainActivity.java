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
import davinci.io.grpc.RPC_SupportedSensorTypes;
import davinci.io.grpc.RPC_TemperatureDataArray;

public class MainActivity extends AppCompatActivity {
  private static final String TAG = "MainActivity";
  private Button sendButton;
  private TextView resultText;
  private GrpcClient grpcClient;

  @Override
  protected void onCreate(Bundle savedInstanceState) {
    super.onCreate(savedInstanceState);
    setContentView(R.layout.activity_main);
    resultText = (TextView) findViewById(R.id.grpc_response_text);
    resultText.setMovementMethod(new ScrollingMovementMethod());

    sendButton = (Button) findViewById(R.id.send_button);
    sendButton.setOnClickListener(
            new View.OnClickListener() {
              @Override
              public void onClick(View v) {
                Log.d(TAG, "onClick()");
                ExecutorService executor = Executors.newFixedThreadPool(1);
                GetSensorTypesCallable callable = new GetSensorTypesCallable();
                Future<String> future = executor.submit(callable);
                GetDimmerDataCallable callable1 = new GetDimmerDataCallable();
                executor.submit(callable1);
                GetPlugDataCallable callable2 = new GetPlugDataCallable();
                executor.submit(callable2);
                GetTemperatureDataCallable callable3 = new GetTemperatureDataCallable();
                executor.submit(callable3);
                try {
                  String result = future.get();
                  System.out.println("Result from thread: " + result);
                  resultText.setText(result);
                } catch (InterruptedException | ExecutionException e) {
                  e.printStackTrace();
                } finally {
                  executor.shutdown();
                }
              }
            });

    //Hard Coded local address for now
    grpcClient = new GrpcClient("192.168.86.73", 50051); // Adjust as needed
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
      return "";
    }
  }

  class GetDimmerDataCallable implements Callable<RPC_DimmerDataArray> {
    @Override
    public RPC_DimmerDataArray call() throws Exception {
      RPC_DimmerDataArray dimmerData = grpcClient.getDimmerData();
      //TODO: LOGIC
      Log.d(TAG, "Dimmer Data [0]: " + dimmerData.getDimmerData(0).toString());
      return null;
    }
  }

  class GetTemperatureDataCallable implements Callable<RPC_TemperatureDataArray> {
    @Override
    public RPC_TemperatureDataArray call() throws Exception {
      RPC_TemperatureDataArray temperatureData = grpcClient.getTemperatureData();
      //TODO: LOGIC
      Log.d(TAG, "Temp Data [0]: " + temperatureData.getTemperatureData(0).toString());
      return null;
    }
  }

  class GetPlugDataCallable implements Callable<RPC_PlugDataArray> {
    @Override
    public RPC_PlugDataArray call() throws Exception {
      RPC_PlugDataArray plugData = grpcClient.getPlugData();
      //TODO: LOGIC
      Log.d(TAG, "Plug Data [0]: " + plugData.getPlugData(0).toString());
      return null;
    }
  }
}
