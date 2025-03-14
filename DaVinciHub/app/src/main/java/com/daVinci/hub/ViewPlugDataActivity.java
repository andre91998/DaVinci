package com.daVinci.hub;

import android.graphics.Color;
import android.graphics.DashPathEffect;
import android.graphics.drawable.Drawable;
import android.os.Bundle;
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

import davinci.io.grpc.RPC_PlugDataArray;
import davinci.io.grpc.RPC_ShellyPlusPlugData;
import davinci.io.grpc.RPC_ShellyPlusTemperatureData;
import davinci.io.grpc.RPC_TemperatureDataArray;

public class ViewPlugDataActivity extends AppCompatActivity {

    private String TAG = "ViewPlugDataActivity";
    private LineChart mChart;
    private GrpcClient mGrpcClient;
    private ExecutorService mExecutor;
    private RPC_PlugDataArray mPlugDataArray;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_viewplugdata);

        //Hard Coded local address for now
        mGrpcClient = new GrpcClient("75.6.165.166", 2026); // Adjust as needed
        mExecutor = Executors.newFixedThreadPool(1);
        GetPlugDataCallable plugDataCallable = new GetPlugDataCallable();
        Future<RPC_PlugDataArray> plugDataFuture = mExecutor.submit(plugDataCallable);

        TextView sensorName = findViewById(R.id.titleBar);
        String name = getIntent().getStringExtra("sensorName");
        if (name != null && !name.isEmpty()) {
            sensorName.setText(String.format("Sensor Name: %s", name));
        }

        TextView currentPower = findViewById(R.id.currentPower);

        ArrayList<Entry> plugValues = new ArrayList<>();
        try {
            mPlugDataArray = plugDataFuture.get();
            if(mPlugDataArray != null && !mPlugDataArray.getPlugDataList().isEmpty()) {
                for (int i = 0; i < mPlugDataArray.getPlugDataCount(); i++) {
                    RPC_ShellyPlusPlugData plugData = mPlugDataArray.getPlugData(i);
                    //might have to divide ts by 1000 for formatting
                    plugValues.add(new Entry((float) plugData.getTimestamp(), (float) plugData.getPower()));
                    if (i == mPlugDataArray.getPlugDataCount() - 1) {
                        currentPower.setText(String.format("Current Power Output: %s", plugData.getPower() + " W"));
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

        LineDataSet set1;
        if (mChart.getData() != null &&
                mChart.getData().getDataSetCount() > 0) {
            set1 = (LineDataSet) mChart.getData().getDataSetByIndex(0);
            set1.setValues(plugValues);
            mChart.getData().notifyDataChanged();
            mChart.notifyDataSetChanged();
        } else {
            set1 = new LineDataSet(plugValues, "Plug Data");
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

    class GetPlugDataCallable implements Callable<RPC_PlugDataArray> {
        @Override
        public RPC_PlugDataArray call() throws Exception {
            return mGrpcClient.getPlugData();
        }
    }

}
