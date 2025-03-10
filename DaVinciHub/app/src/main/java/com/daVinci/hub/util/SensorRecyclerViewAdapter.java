package com.daVinci.hub.util;

import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;


import androidx.annotation.NonNull;
import androidx.recyclerview.widget.RecyclerView;

import com.daVinci.hub.R;
import java.util.ArrayList;
import java.util.List;

import davinci.io.grpc.RPC_SensorArray;

public class SensorRecyclerViewAdapter extends RecyclerView.Adapter<SensorRecyclerViewAdapter.MyViewHolder> {

    private RPC_SensorArray mSensorList;

    public SensorRecyclerViewAdapter(RPC_SensorArray scopeList) {
        mSensorList = scopeList;
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
        holder.titleTextView.setText(sensor);    }

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
