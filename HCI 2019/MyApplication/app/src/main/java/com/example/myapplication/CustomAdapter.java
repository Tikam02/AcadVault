package com.example.myapplication;

import android.Manifest;
import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.net.Uri;
import android.support.v4.app.ActivityCompat;
import android.support.v4.content.ContextCompat;
import android.support.v7.widget.RecyclerView;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ImageView;
import android.widget.TextView;

import java.util.ArrayList;

public class CustomAdapter extends RecyclerView.Adapter<CustomAdapter.MyViewHolder> {

    private ArrayList<DataModel> dataSet;
    private Context context;
    private Activity activity;

    public static class MyViewHolder extends RecyclerView.ViewHolder {

        TextView textViewName;
        ImageView imageViewIcon;

        public MyViewHolder(View itemView) {
            super(itemView);
            this.textViewName = (TextView) itemView.findViewById(R.id.tvMiddleCardView);
            this.imageViewIcon = (ImageView) itemView.findViewById(R.id.iconLeftCardView);
        }
    }

    public CustomAdapter(Context context, ArrayList<DataModel> data, Activity activity) {
        this.dataSet = data;
        this.context = context;
        this.activity = activity;
    }

    public Context getContext(){
        return context;
    }

    @Override
    public MyViewHolder onCreateViewHolder(ViewGroup parent,
                                           int viewType) {
        View view = LayoutInflater.from(parent.getContext())
                .inflate(R.layout.card_view, parent, false);

        //view.setOnClickListener(MainActivity.myOnClickListener);

        MyViewHolder myViewHolder = new MyViewHolder(view);
        return myViewHolder;
    }

    @Override
    public void onBindViewHolder(final MyViewHolder holder, final int listPosition) {

        TextView textViewName = holder.textViewName;
        ImageView imageView = holder.imageViewIcon;
        if(dataSet.get(listPosition).getImage()==null){
            imageView.setImageResource(R.drawable.ic_android);
        }
        else{
            Bitmap bitmap = BitmapFactory.decodeFile(dataSet.get(listPosition).getImage());
            //Bitmap b = getCircularBitmapWithWhiteBorder(bitmap, 2);
            imageView.setImageBitmap(bitmap);
        }

        textViewName.setText(dataSet.get(listPosition).getName());

        if(!dataSet.get(listPosition).getRelation().equals("Emergency")) {
            holder.textViewName.setOnClickListener(new View.OnClickListener() {
                @Override
                public void onClick(View v) {
                    DataModel dm = dataSet.get(listPosition);
                    Intent i = new Intent(context, ViewContact.class);
                    i.putExtra("Obj", dm);
                    i.addFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
                    context.startActivity(i);
                }
            });
        }
        else{
            holder.textViewName.setOnClickListener(new View.OnClickListener() {
                @Override
                public void onClick(View v) {
                    DataModel dm = dataSet.get(listPosition);
                    String str = dm.getPhone();
                    Intent callIntent = new Intent(Intent.ACTION_CALL);
                    callIntent.addFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
                    callIntent.setData(Uri.parse("tel:"+str));//change the number
                    if (ContextCompat.checkSelfPermission(context, Manifest.permission.CALL_PHONE) != PackageManager.PERMISSION_GRANTED) {
                        ActivityCompat.requestPermissions(activity, new String[]{Manifest.permission.CALL_PHONE},1);
                    }
                    else
                    {
                        context.startActivity(callIntent);
                    }
                }
            });
        }
        holder.imageViewIcon.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                DataModel dm = dataSet.get(listPosition);
                String str = dm.getPhone();
                Intent callIntent = new Intent(Intent.ACTION_CALL);
                callIntent.addFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
                callIntent.setData(Uri.parse("tel:"+str));//change the number
                if (ContextCompat.checkSelfPermission(context, Manifest.permission.CALL_PHONE) != PackageManager.PERMISSION_GRANTED) {
                    ActivityCompat.requestPermissions(activity, new String[]{Manifest.permission.CALL_PHONE},1);
                }
                else
                {
                    context.startActivity(callIntent);
                }
            }
        });
    }

    @Override
    public int getItemCount() {
        return dataSet.size();
    }

}
