package com.daVinci.hub.util;

import static android.content.Intent.FLAG_ACTIVITY_NEW_TASK;

import android.content.Context;
import android.content.Intent;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;

import androidx.annotation.NonNull;
import androidx.recyclerview.widget.RecyclerView;

import com.daVinci.hub.R;
import com.daVinci.hub.ViewTemperatureDataActivity;

import davinci.io.grpc.RPC_SensorArray;

public class SensorRecyclerViewAdapter extends RecyclerView.Adapter<SensorRecyclerViewAdapter.MyViewHolder> {

    private RPC_SensorArray mSensorList;
    private Context mContext;

    public SensorRecyclerViewAdapter(RPC_SensorArray scopeList, Context context) {
        mSensorList = scopeList;
        mContext = context;
    }

    @Override
    @NonNull
    public MyViewHolder onCreateViewHolder(ViewGroup parent, int viewType) {
        View view = LayoutInflater.from(parent.getContext())
                .inflate(R.layout.sensor_item_row, parent, false);
        return new MyViewHolder(view);
    }

    @Override
    public void onBindViewHolder(final MyViewHolder holder, int position) {

        //final Scope scope = mScopeList.get(position);
        String sensor  = mSensorList.getRPCSensorList().get(position).getSensorName();

        // Set data for the views
        holder.titleTextView.setText(sensor);

        //On Click listener for entire holder rather than just the text view
        holder.itemView.setOnClickListener(v -> {
            //TODO: Launch view sensor data activity
            Intent intent = new Intent(mContext.getApplicationContext(), ViewTemperatureDataActivity.class);
            intent.addFlags(FLAG_ACTIVITY_NEW_TASK);
            mContext.startActivity(intent);
        });
    }

    @Override
    public int getItemCount() {
        if(mSensorList == null || mSensorList.getRPCSensorList().isEmpty()) {
            return 0;
        } else {
            return mSensorList.getRPCSensorCount();
        }
    }
    public void updateData(RPC_SensorArray newSensors) {
        mSensorList = newSensors;
        notifyDataSetChanged();
    }
    public class MyViewHolder extends RecyclerView.ViewHolder {

        private TextView titleTextView;

        public MyViewHolder(View itemView) {
            super(itemView);
            // Bind the views from the layout
            titleTextView = itemView.findViewById(R.id.title_text_view);
        }
    }
}
