package com.example.myapplication;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.ImageView;
import android.widget.Spinner;

import java.util.HashMap;

public class Cab extends AppCompatActivity {

    HashMap<String,Object> map;
    Spinner spinner;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_cab);

        Integer[] imageIconDatabase = { R.drawable.rick,
                R.drawable.sedan, R.drawable.micro, R.drawable.rental};

        // stores the image database names
        String[] imageNameDatabase = { "Rickshaw", "Sedan", "Micro", "Rental"};

        spinner = findViewById(R.id.cab_list123);
        CabAdapter c = new CabAdapter(this, imageNameDatabase, imageIconDatabase);
        spinner.setAdapter(c);

        View addContact = findViewById(R.id.rectangle_5);
        addContact.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent myIntent = new Intent(Cab.this, addContact.class);
                myIntent.setFlags(Intent.FLAG_ACTIVITY_REORDER_TO_FRONT);
                startActivityIfNeeded(myIntent, 0);
            }
        });

        View phoneCall = findViewById(R.id.rectangle_8);
        phoneCall.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent myIntent = new Intent(Cab.this, phoneCall.class);
                myIntent.setFlags(Intent.FLAG_ACTIVITY_REORDER_TO_FRONT);
                startActivityIfNeeded(myIntent, 0);
            }
        });

        View contactList = findViewById(R.id.rectangle_4);
        contactList.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent myIntent = new Intent(Cab.this, contactsList.class);
                myIntent.setFlags(Intent.FLAG_ACTIVITY_REORDER_TO_FRONT);
                //myIntent.setFlags(Intent.FLAG_ACTIVITY_SINGLE_TOP);
                startActivityIfNeeded(myIntent, 0);
            }
        });

        View favList = findViewById(R.id.rectangle_3);
        favList.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent myIntent = new Intent(Cab.this, FavContacts.class);
                myIntent.setFlags(Intent.FLAG_ACTIVITY_REORDER_TO_FRONT);
                startActivityIfNeeded(myIntent, 0);
            }
        });

        View utilities = findViewById(R.id.rectangle_10);
        utilities.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent myIntent = new Intent(Cab.this, contactsList.class);
                myIntent.putExtra("Utilities", 1);
                myIntent.setFlags(Intent.FLAG_ACTIVITY_REORDER_TO_FRONT);
                startActivityIfNeeded(myIntent, 0);
            }
        });

        View emer = findViewById(R.id.rectangle_2);
        emer.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent myIntent = new Intent(Cab.this, EmergencyContacts.class);
                myIntent.setFlags(Intent.FLAG_ACTIVITY_REORDER_TO_FRONT);
                startActivityIfNeeded(myIntent, 0);
            }
        });

    }

}
