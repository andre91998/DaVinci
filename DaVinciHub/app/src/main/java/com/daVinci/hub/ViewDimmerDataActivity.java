package com.daVinci.hub;

import android.graphics.Color;
import android.graphics.DashPathEffect;
import android.graphics.drawable.Drawable;
import android.os.Bundle;
import android.os.Handler;
import android.util.Log;
import android.widget.TextView;

import androidx.appcompat.app.AppCompatActivity;
import androidx.core.content.ContextCompat;

import com.daVinci.hub.util.LineChartTimeAxisValueFormatter;
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

import davinci.io.grpc.RPC_DimmerDataArray;
import davinci.io.grpc.RPC_ShellyPlusDimmerData;
import davinci.io.grpc.RPC_ShellyPlusTemperatureData;
import davinci.io.grpc.RPC_TemperatureDataArray;

public class ViewDimmerDataActivity extends AppCompatActivity {

    private String TAG = "ViewDimmerDataActivity";
    private LineChart mChart;
    private GrpcClient mGrpcClient;
    private ExecutorService mExecutor;
    private RPC_DimmerDataArray mDimmerDataArray;
    private Future<RPC_DimmerDataArray> mDimmerDataFuture;
    private TextView currentBrightness, currentState;
    private RPC_ShellyPlusDimmerData latestBrightnessData;
    //TODO: all thread logic
    private Handler mHandler;
    private Thread updateDataThread;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_viewdimmerdata);

        //Hard Coded local address for now
        mGrpcClient = new GrpcClient("75.6.165.166", 2026); // Adjust as needed
        mExecutor = Executors.newFixedThreadPool(1);
        GetDimmerDataCallable dimmerDataCallable = new GetDimmerDataCallable();
        mDimmerDataFuture = mExecutor.submit(dimmerDataCallable);

        TextView sensorName = findViewById(R.id.titleBar);
        String name = getIntent().getStringExtra("sensorName");
        if (name != null && !name.isEmpty()) {
            sensorName.setText(String.format("Sensor Name: %s", name));
        }

        currentBrightness = findViewById(R.id.currentBrightness);
        currentState = findViewById(R.id.currentState);

        ArrayList<Entry> brightnessValues = new ArrayList<>();

        try {
            mDimmerDataArray = mDimmerDataFuture.get();
            if(mDimmerDataArray != null && !mDimmerDataArray.getDimmerDataList().isEmpty()) {
                for (int i = 0; i < mDimmerDataArray.getDimmerDataCount(); i++) {
                    latestBrightnessData = mDimmerDataArray.getDimmerData(i);
                    //might have to divide ts by 1000 for formatting
                    brightnessValues.add(new Entry((float) latestBrightnessData.getTimestamp(), (float) latestBrightnessData.getBrightness()));
                    if (i == mDimmerDataArray.getDimmerDataCount() - 1) {
                        currentBrightness.setText(String.format("Current Brightness: %s", latestBrightnessData.getBrightness() + "%"));
                        currentState.setText(String.format("Current State: " + (latestBrightnessData.getState() ? "On" : "Off")));
                    }
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
        mChart.getXAxis().setValueFormatter(new LineChartTimeAxisValueFormatter());
        mChart.getAxisLeft().setTextColor(Color.WHITE);
        mChart.getAxisRight().setTextColor(Color.WHITE);

        UpdateChart();

        mHandler = new Handler();
        mHandler.post(new UpdateDataRunnable());
        mHandler.postDelayed(new UpdateUiRunnable(), 1000);
    }

    private void UpdateData() {
        try {
            GetDimmerDataCallable dimmerDataCallable = new GetDimmerDataCallable();
            mDimmerDataFuture = mExecutor.submit(dimmerDataCallable);
            mDimmerDataArray = mDimmerDataFuture.get();
        } catch (ExecutionException e) {
            throw new RuntimeException(e);
        } catch (InterruptedException e) {
            throw new RuntimeException(e);
        }
    }

    private void UpdateChart() {

        ArrayList<Entry> brightnessValues = new ArrayList<>();

        try {
            mDimmerDataArray = mDimmerDataFuture.get();
            if(mDimmerDataArray != null && !mDimmerDataArray.getDimmerDataList().isEmpty()) {
                for (int i = 0; i < mDimmerDataArray.getDimmerDataCount(); i++) {
                    latestBrightnessData = mDimmerDataArray.getDimmerData(i);
                    //might have to divide ts by 1000 for formatting
                    brightnessValues.add(new Entry((float) latestBrightnessData.getTimestamp(), (float) latestBrightnessData.getBrightness()));
                    if (i == mDimmerDataArray.getDimmerDataCount() - 1) {
                        currentBrightness.setText(String.format("Current Brightness: %s", latestBrightnessData.getBrightness() + "%"));
                        currentState.setText(String.format("Current State: " + (latestBrightnessData.getState() ? "On" : "Off")));
                    }
                }
            } else {
                Log.d(TAG, "empty temperature data");
            }
        } catch (ExecutionException | InterruptedException e) {
            e.printStackTrace();
        }

        LineDataSet set1;
        if (mChart.getData() != null &&
                mChart.getData().getDataSetCount() > 0) {
            set1 = (LineDataSet) mChart.getData().getDataSetByIndex(0);
            set1.setValues(brightnessValues);;
            mChart.getData().notifyDataChanged();
            mChart.notifyDataSetChanged();
        } else {
            set1 = new LineDataSet(brightnessValues, "Dimmer Data");
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

            LineData data = new LineData(dataSets);
            mChart.setData(data);
        }
    }
    class GetDimmerDataCallable implements Callable<RPC_DimmerDataArray> {
        @Override
        public RPC_DimmerDataArray call() throws Exception {
            return mGrpcClient.getDimmerData();
        }
    }

    class UpdateDataRunnable implements Runnable {
        @Override
        public void run() {
            UpdateData();
            mHandler.postDelayed(this, 30000);
        }
    }

    class UpdateUiRunnable implements Runnable {
        @Override
        public void run() {
            currentBrightness.setText(String.format("Current Brightness: %s", latestBrightnessData.getBrightness() + "%"));
            currentState.setText(String.format("Current State: " + (latestBrightnessData.getState() ? "On" : "Off")));
            UpdateChart();
            mHandler.postDelayed(this, 60000);
        }
    }
}

