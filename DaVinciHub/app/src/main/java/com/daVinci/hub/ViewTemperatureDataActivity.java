package com.daVinci.hub;

import android.graphics.Color;
import android.graphics.DashPathEffect;
import android.graphics.drawable.Drawable;
import android.os.Bundle;
import android.util.Log;
import android.widget.TextView;

import androidx.appcompat.app.AppCompatActivity;
import androidx.core.content.ContextCompat;

import com.github.mikephil.charting.charts.LineChart;
import com.github.mikephil.charting.components.Description;
import com.github.mikephil.charting.data.Entry;
import com.github.mikephil.charting.data.LineData;
import com.github.mikephil.charting.data.LineDataSet;
import com.github.mikephil.charting.interfaces.datasets.ILineDataSet;
import com.github.mikephil.charting.utils.Utils;

import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.Callable;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.Future;

import davinci.io.grpc.RPC_ShellyPlusTemperatureData;
import davinci.io.grpc.RPC_TemperatureDataArray;

public class ViewTemperatureDataActivity extends AppCompatActivity {

    private String TAG = "ViewTemperatureDataActivity";
    private LineChart mChart;
    private GrpcClient mGrpcClient;
    private ExecutorService mExecutor;
    private RPC_TemperatureDataArray mTemperatureDataArray;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_viewtemperaturedata);

        //Hard Coded local address for now
        mGrpcClient = new GrpcClient("75.6.165.166", 2026); // Adjust as needed
        mExecutor = Executors.newFixedThreadPool(1);
        GetTemperatureDataCallable temperatureDataCallable = new GetTemperatureDataCallable();
        Future<RPC_TemperatureDataArray> temperatureDataFuture = mExecutor.submit(temperatureDataCallable);

        TextView sensorName = findViewById(R.id.titleBar);
        String name = getIntent().getStringExtra("sensorName");
        if (name != null && !name.isEmpty()) {
            sensorName.setText(String.format("Sensor Name: %s", name));
        }

        TextView currentTemperature = findViewById(R.id.currentTemperature);

        ArrayList<Entry> tempValues = new ArrayList<>();
        ArrayList<Entry> humidityValues = new ArrayList<>();
        //TODO: convert timestamp float to time
        //TODO: fix humidity and temperature are swapped
        try {
            mTemperatureDataArray = temperatureDataFuture.get();
            if(mTemperatureDataArray != null && !mTemperatureDataArray.getTemperatureDataList().isEmpty()) {
                for (int i = 0; i < mTemperatureDataArray.getTemperatureDataCount(); i++) {
                    RPC_ShellyPlusTemperatureData tempData = mTemperatureDataArray.getTemperatureData(i);
                    tempValues.add(new Entry((float) tempData.getTimestamp(), (float) tempData.getTemperature()));
                    humidityValues.add(new Entry((float) tempData.getTimestamp(), (float) tempData.getHumidity()));
                    //TODO: set Current Temperature and current humidity
                }
            } else {
                Log.d(TAG, "empty temperature data");
            }
        } catch (ExecutionException | InterruptedException e) {
            e.printStackTrace();
        }

        // on below line we are initializing our graph view.
        mChart = findViewById(R.id.chart);
        mChart.setTouchEnabled(true);
        mChart.setPinchZoom(true);
        mChart.getXAxis().setTextColor(Color.WHITE);
        mChart.getAxisLeft().setTextColor(Color.WHITE);
        mChart.getAxisRight().setTextColor(Color.WHITE);

        LineDataSet set1;
        LineDataSet set2;
        if (mChart.getData() != null &&
                mChart.getData().getDataSetCount() > 0) {
            set1 = (LineDataSet) mChart.getData().getDataSetByIndex(0);
            set1.setValues(tempValues);
            set2 = (LineDataSet) mChart.getData().getDataSetByIndex(1);
            set2.setValues(humidityValues);
            mChart.getData().notifyDataChanged();
            mChart.notifyDataSetChanged();
        } else {
            set1 = new LineDataSet(tempValues, "Temperature Data");
            set1.setDrawIcons(false);
            //set1.enableDashedLine(10f, 5f, 0f);
            //set1.enableDashedHighlightLine(10f, 5f, 0f);
            set1.setColor(Color.GREEN);
            set1.setCircleColor(Color.GREEN);
            set1.setLineWidth(1f);
            set1.setCircleRadius(3f);
            set1.setDrawCircleHole(false);
            set1.setValueTextSize(9f);
            set1.setDrawFilled(true);
            set1.setFormLineWidth(1f);
            //set1.setFormLineDashEffect(new DashPathEffect(new float[]{10f, 5f}, 0f));
            set1.setFormSize(15.f);
//            if (Utils.getSDKInt() >= 18) {
//                Drawable drawable = ContextCompat.getDrawable(this, R.drawable.fade_blue);
//                set1.setFillDrawable(drawable);
//            } else {
//                set1.setFillColor(Color.DKGRAY);
//            }
            ArrayList<ILineDataSet> dataSets = new ArrayList<>();
            dataSets.add(set1);

            set2 = new LineDataSet(humidityValues, "Humidity Data");
            set2.setDrawIcons(false);
            set2.setColor(Color.CYAN);
            set2.setCircleColor(Color.CYAN);
            set2.setLineWidth(1f);
            set2.setCircleRadius(3f);
            set2.setDrawCircleHole(false);
            set2.setValueTextSize(9f);
            set2.setDrawFilled(true);
            set2.setFormLineWidth(1f);
            set2.setFormSize(15.f);
            dataSets.add(set2);

            LineData data = new LineData(dataSets);
            mChart.setData(data);
        }
    }

    class GetTemperatureDataCallable implements Callable<RPC_TemperatureDataArray> {
        @Override
        public RPC_TemperatureDataArray call() throws Exception {
            return mGrpcClient.getTemperatureData();
        }
    }

}
