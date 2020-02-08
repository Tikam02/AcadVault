package com.example.myapplication;

import android.Manifest;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.net.Uri;
import android.support.v4.app.ActivityCompat;
import android.support.v4.content.ContextCompat;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.TextView;

import org.w3c.dom.Text;

public class phoneCall extends AppCompatActivity {
    TextView textView;
    TextView backspace;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_phone_call);

        backspace = findViewById(R.id.back);
        textView = findViewById(R.id.tv);

        backspace.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {

                String str=textView.getText().toString();
                if(str!=null) {
                    if (str.length() >= 1) {
                        str = str.substring(0, str.length() - 1);
                        textView.setText(str);
                    }
                }
            }
        });

        View addContact = findViewById(R.id.rectangle_5);
        addContact.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent myIntent = new Intent(phoneCall.this, addContact.class);
                myIntent.setFlags(Intent.FLAG_ACTIVITY_REORDER_TO_FRONT);
                startActivityIfNeeded(myIntent, 0);
            }
        });

        View contactList = findViewById(R.id.rectangle_4);
        contactList.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent myIntent = new Intent(phoneCall.this, contactsList.class);
                myIntent.setFlags(Intent.FLAG_ACTIVITY_REORDER_TO_FRONT);
                startActivityIfNeeded(myIntent, 0);
            }
        });

        View favList = findViewById(R.id.rectangle_3);
        favList.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent myIntent = new Intent(phoneCall.this, FavContacts.class);
                myIntent.setFlags(Intent.FLAG_ACTIVITY_REORDER_TO_FRONT);
                startActivityIfNeeded(myIntent, 0);
            }
        });

        View utilities = findViewById(R.id.rectangle_10);
        utilities.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent myIntent = new Intent(phoneCall.this, contactsList.class);
                myIntent.putExtra("Utilities", 1);
                myIntent.setFlags(Intent.FLAG_ACTIVITY_REORDER_TO_FRONT);
                startActivityIfNeeded(myIntent, 0);
            }
        });

        View emer = findViewById(R.id.rectangle_2);
        emer.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent myIntent = new Intent(phoneCall.this, EmergencyContacts.class);
                myIntent.setFlags(Intent.FLAG_ACTIVITY_REORDER_TO_FRONT);
                startActivityIfNeeded(myIntent, 0);
            }
        });

        View cab = findViewById(R.id.rectangle_9);
        cab.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent myIntent = new Intent(phoneCall.this, Cab.class);
                myIntent.setFlags(Intent.FLAG_ACTIVITY_REORDER_TO_FRONT);
                startActivityIfNeeded(myIntent, 0);
            }
        });

    }

    public void clickNum(View v){
        TextView tv = (TextView) v;
        String str = textView.getText().toString();
        str = str + tv.getText().toString();
        textView.setText(str);
    }

    public void call(View V){
        String str = textView.getText().toString();
        Intent callIntent = new Intent(Intent.ACTION_CALL);
        callIntent.setData(Uri.parse("tel:"+str));//change the number
        if (ContextCompat.checkSelfPermission(phoneCall.this, Manifest.permission.CALL_PHONE) != PackageManager.PERMISSION_GRANTED) {
            ActivityCompat.requestPermissions(phoneCall.this, new String[]{Manifest.permission.CALL_PHONE},1);
        }
        else
        {
            startActivity(callIntent);
        }
    }
}
