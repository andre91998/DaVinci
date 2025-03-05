package com.daVinci.hub;

import android.os.Bundle;

import androidx.appcompat.app.AppCompatActivity;
import androidx.appcompat.widget.SwitchCompat;
import androidx.core.view.GravityCompat;
import androidx.drawerlayout.widget.DrawerLayout;
import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;

import android.util.Log;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.Spinner;
import com.daVinci.hub.util.SensorRecyclerViewAdapter;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
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
  private RecyclerView mSensorListView;
  private List<String> mSensorList;
  private SensorRecyclerViewAdapter mAdapter;
  private GrpcClient grpcClient;
  private ExecutorService mExecutor;


  @Override
  protected void onCreate(Bundle savedInstanceState) {
    super.onCreate(savedInstanceState);
    setContentView(R.layout.activity_main);

    //Hard Coded local address for now
    grpcClient = new GrpcClient("192.168.86.73", 50051); // Adjust as needed

    mExecutor = Executors.newFixedThreadPool(1);

    GetSensorTypesCallable sensorTypesCallable = new GetSensorTypesCallable();
    Future<List<String>> sensorTypesFuture = mExecutor.submit(sensorTypesCallable);

    // Reference the Toggle Button and Slider
    SwitchCompat toggleSpinner = findViewById(R.id.toggle_spinner);
    Spinner sensorTypeSpinner = findViewById(R.id.spinner4);

    /*
     * initialize RecyclerView
     * Add sample data to the list(this can be removed later of course
     * set the adapter
     */
    mSensorListView = findViewById(R.id.sensorListView);
    mSensorListView.setLayoutManager(new LinearLayoutManager(this));
    mSensorList = new ArrayList<>();

    //mAdapter = new SensorRecyclerViewAdapter(mSensorList); // Initialize adapter with mScopeList
    //mSensorListView.setAdapter(adapter);

    //Get all sensor types via GRPC
    List<String> sensorTypes = new ArrayList<>();
    try {
      sensorTypes = sensorTypesFuture.get();
      Log.d(TAG, sensorTypes.toString());
    } catch (ExecutionException | InterruptedException e) {
      e.printStackTrace();
    }

    // Create an ArrayAdapter using the string array and a default spinner layout.
    ArrayAdapter<String> adapter = new ArrayAdapter<>(this, android.R.layout.simple_spinner_dropdown_item, sensorTypes);
    // Specify the layout to use when the list of choices appears.
    adapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
    // Apply the adapter to the spinner.
    sensorTypeSpinner.setAdapter(adapter);
    if (toggleSpinner.isChecked()) {
      sensorTypeSpinner.setVisibility(View.VISIBLE);
    } else {
      sensorTypeSpinner.setVisibility(View.GONE);
    }
    sensorTypeSpinner.setActivated(toggleSpinner.isChecked());
    sensorTypeSpinner.setEnabled(toggleSpinner.isChecked());
    sensorTypeSpinner.setOnItemSelectedListener(new AdapterView.OnItemSelectedListener() {
      public void onItemSelected(AdapterView<?> parent, View view, int position, long id)
      {
          //String selectedSensorType = parent.getItemAtPosition(position).toString();
          String selectedSensorType = (String) sensorTypeSpinner.getSelectedItem();
          updateRecyclerView(filterSensorsByType(selectedSensorType));
      }
      public void onNothingSelected(AdapterView<?> parent)
      {
        updateRecyclerView(new ArrayList<>(mSensorList));
      }
    });

    // Set a listener for the toggle button
    toggleSpinner.setOnCheckedChangeListener((buttonView, isChecked) -> {
      // Enable or disable the slider based on the toggle button state
      sensorTypeSpinner.setEnabled(isChecked);
      sensorTypeSpinner.setActivated(isChecked);
      if (!isChecked) {
        sensorTypeSpinner.setVisibility(View.GONE);
        //Logic for show all sensors in system
        updateRecyclerView(new ArrayList<>(mSensorList));

      } else {
        sensorTypeSpinner.setVisibility(View.VISIBLE);
        //Logic for show filtered sensor list
        String selectedSensorType = (String) sensorTypeSpinner.getSelectedItem();
        updateRecyclerView(filterSensorsByType(selectedSensorType));
      }
    });

    // Set up the RecyclerView
    setupRecyclerView();
  }

  /**
   * Method for filtering the sensor list based sensor type
   * @param type
   * @return filtered list of scopes
   */
  private ArrayList<String> filterSensorsByType(String type) {
    //TODO: add filtering logic will require string mapping
    return new ArrayList<>(mSensorList.stream().filter());
  }

  /**
   * Method to update the Scope List view UI dynamically as the filter changes
   * @param filteredSensors
   */
  private void updateRecyclerView(ArrayList<String> filteredSensors) {
    mAdapter = new SensorRecyclerViewAdapter(filteredSensors);
    mSensorListView.setAdapter(mAdapter);
    mSensorListView.setLayoutManager(new LinearLayoutManager(this));
  }

  @Override
  public void onResume(){
    super.onResume();
    //setupRecyclerView();
  }

  @Override
  protected void onDestroy() {
    super.onDestroy();
    grpcClient.shutdown();
    mExecutor.shutdown();
  }

  /**
   * Sets up the RecyclerView to display a list of scopes from the database.
   */
  private void setupRecyclerView() {
    //Query the GRPC for all scopes and populate the list
    GetSensorsCallable sensorsCallable = new GetSensorsCallable();
    Future<RPC_Sensors> sensorsFuture = mExecutor.submit(sensorsCallable);
    try {
      mSensorList = sensorsFuture.get().getSensorNamesList();
      Log.d(TAG, mSensorList.toString());
    } catch (ExecutionException | InterruptedException e) {
      e.printStackTrace();
    }

    // Check if the list is empty and display a message if needed
    if (mSensorList == null || mSensorList.isEmpty()) {
      // Handle empty state, e.g., show a placeholder view or a message
      // This can be a TextView or other UI element to indicate "No data available"
      Log.d(TAG, "empty sensor list");
    } else {
      // Set up the adapter and layout manager for the RecyclerView
      Log.d(TAG, "setting up recycler view");
      updateRecyclerView(new ArrayList<>(mSensorList));
//      mAdapter = new SensorRecyclerViewAdapter(new ArrayList<>(mSensorList));
//      mSensorListView.setAdapter(mAdapter);
//      mSensorListView.setLayoutManager(new LinearLayoutManager(this));
    }
  }

  @Override
  public void onBackPressed() {
    DrawerLayout drawer = findViewById(R.id.drawer_layout);
    if (drawer.isDrawerOpen(GravityCompat.START)) {
      // Close the drawer if it is open
      drawer.closeDrawer(GravityCompat.START);
    } else {
      // Proceed with the normal back button behavior
      super.onBackPressed();
    }
  }

  class GetSensorTypesCallable implements Callable<List<String>> {
    @Override
    public List<String> call() throws Exception {
      RPC_SupportedSensorTypes sensorTypes = grpcClient.getSupportedSensorTypes();
      if (sensorTypes != null) {
        Log.d(TAG, "Supported Sensor Types: " + sensorTypes.getSensorTypesList());
        return sensorTypes.getSensorTypesList();
      }
      return Collections.emptyList();
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




//  private Button sendButton;
//  private TextView dimmerText, temperatureText, plugText;
//
//
//  @Override
//  protected void onCreate(Bundle savedInstanceState) {
//    super.onCreate(savedInstanceState);
//    setContentView(R.layout.activity_main);

//
//    GetDimmerDataCallable callable1 = new GetDimmerDataCallable();
//    Future<RPC_DimmerDataArray> dimmerFuture = executor.submit(callable1);
//
//    GetPlugDataCallable callable2 = new GetPlugDataCallable();
//    Future<RPC_PlugDataArray> plugFuture = executor.submit(callable2);
//
//    GetTemperatureDataCallable callable3 = new GetTemperatureDataCallable();
//    Future<RPC_TemperatureDataArray> temperatureFuture = executor.submit(callable3);
//
//    GetSensorsCallable callable4 = new GetSensorsCallable();
//    Future<RPC_Sensors> sensorsFuture = executor.submit(callable4);
//
//    try {
//      String result = future.get();
//      System.out.println("Result from thread: " + result);
//
//      //If tables are empty, this crashes
////      RPC_DimmerDataArray dimmerDataArray = dimmerFuture.get();
////      if (dimmerDataArray != null) {
////        dimmerText.setText(String.valueOf(dimmerDataArray.getDimmerData(dimmerDataArray.getDimmerDataCount() - 1).getBrightness()));
////      } else {
////        dimmerText.setText("N/A");
////      }
////
////      RPC_PlugDataArray plugDataArray = plugFuture.get();
////      if (plugDataArray != null) {
////        plugText.setText(String.valueOf(plugDataArray.getPlugData(plugDataArray.getPlugDataCount() - 1).getPower()));
////      } else {
////        plugText.setText("N/A");
////      }
////
////      RPC_TemperatureDataArray temperatureDataArray = temperatureFuture.get();
////      if (temperatureDataArray != null) {
////        temperatureText.setText(String.valueOf(temperatureDataArray.getTemperatureData(temperatureDataArray.getTemperatureDataCount() - 1).getTemperature()));
////      } else {
////        temperatureText.setText("N/A");
////      }
////
////      RPC_Sensors sensors = sensorsFuture.get();
////      if (sensors != null) {
////        Log.d(TAG, sensors.getSensorNamesList().toString());
////      }
//    } catch (InterruptedException | ExecutionException | IndexOutOfBoundsException e) {
//      e.printStackTrace();
//    } finally {
//      executor.shutdown();
//    }
//  }
//

//
//

}
