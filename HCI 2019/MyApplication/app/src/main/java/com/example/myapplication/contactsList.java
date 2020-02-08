package com.example.myapplication;

import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.database.Cursor;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.support.v7.widget.DefaultItemAnimator;
import android.support.v7.widget.LinearLayoutManager;
import android.support.v7.widget.RecyclerView;
import android.text.Editable;
import android.text.TextWatcher;
import android.util.Log;
import android.view.View;
import android.view.inputmethod.InputMethodManager;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;

import java.util.ArrayList;
import java.util.Collection;
import java.util.Collections;
import java.util.Comparator;
import java.util.Locale;

public class contactsList extends AppCompatActivity {

    RecyclerView recyclerView;
    LinearLayoutManager layoutManager;
    ArrayList<DataModel> data, arrayList, univList;
    CustomAdapter adapter;
    DatabaseHelper databaseHelper;
    EditText search;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_contacts_list);
        databaseHelper = new DatabaseHelper(getApplicationContext());
        data = new ArrayList<>();
        arrayList = new ArrayList<>();
        univList = new ArrayList<>();
        layoutManager = new LinearLayoutManager(this);
        adapter = new CustomAdapter(getApplicationContext(), data, contactsList.this);
        addUnivList();
        arrayList.addAll(univList);
        recyclerView = findViewById(R.id.my_recycler_view);
        recyclerView.setHasFixedSize(true);
        recyclerView.setLayoutManager(layoutManager);
        recyclerView.setItemAnimator(new DefaultItemAnimator());
        recyclerView.setAdapter(adapter);


        View addContact = findViewById(R.id.rectangle_5);
        addContact.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent myIntent = new Intent(contactsList.this, addContact.class);
                myIntent.setFlags(Intent.FLAG_ACTIVITY_REORDER_TO_FRONT);
                startActivityIfNeeded(myIntent, 0);
            }
        });

        View phoneCall = findViewById(R.id.rectangle_8);
        phoneCall.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent myIntent = new Intent(contactsList.this, phoneCall.class);
                myIntent.setFlags(Intent.FLAG_ACTIVITY_REORDER_TO_FRONT);
                startActivityIfNeeded(myIntent, 0);
            }
        });
        //updateList();

        View favList = findViewById(R.id.rectangle_3);
        favList.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent myIntent = new Intent(contactsList.this, FavContacts.class);
                myIntent.setFlags(Intent.FLAG_ACTIVITY_REORDER_TO_FRONT);
                startActivityIfNeeded(myIntent, 0);
            }
        });

        View utilities = findViewById(R.id.rectangle_10);
        utilities.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent myIntent = new Intent(contactsList.this, contactsList.class);
                myIntent.putExtra("Utilities", 1);
                myIntent.setFlags(Intent.FLAG_ACTIVITY_REORDER_TO_FRONT);
                myIntent.setFlags(Intent.FLAG_ACTIVITY_SINGLE_TOP);
                startActivityIfNeeded(myIntent, 0);
            }
        });

        View emer = findViewById(R.id.rectangle_2);
        emer.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent myIntent = new Intent(contactsList.this, EmergencyContacts.class);
                myIntent.setFlags(Intent.FLAG_ACTIVITY_REORDER_TO_FRONT);
                startActivityIfNeeded(myIntent, 0);
            }
        });

        View cab = findViewById(R.id.rectangle_9);
        cab.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent myIntent = new Intent(contactsList.this, Cab.class);
                myIntent.setFlags(Intent.FLAG_ACTIVITY_REORDER_TO_FRONT);
                startActivityIfNeeded(myIntent, 0);
            }
        });

        search = findViewById(R.id.search);
        search.addTextChangedListener(new TextWatcher() {
            @Override
            public void beforeTextChanged(CharSequence s, int start, int count, int after) {
                //pass
            }

            @Override
            public void onTextChanged(CharSequence s, int start, int before, int count) {
                //pass
            }

            @Override
            public void afterTextChanged(Editable s) {
                String str = search.getText().toString();
                filter(str);
            }
        });

    }

    public void addUnivList(){
        Cursor cursor = databaseHelper.getAllContacts();

        while(cursor.moveToNext()){
            univList.add(new DataModel(
                    cursor.getString(1),//name
                    cursor.getString(2),//phone number
                    cursor.getString(3),//device
                    cursor.getString(4) //email
            ));
        }
    }

    public void focusSearch(View v){
        EditText e = findViewById(R.id.search);
        e.requestFocus();
        InputMethodManager imm = (InputMethodManager) getSystemService(Context.INPUT_METHOD_SERVICE);
        imm.showSoftInput(e, InputMethodManager.SHOW_IMPLICIT);
    }

    public void updateList(){

        data.clear();
        data.addAll(arrayList);
        Collections.sort(data, new CustomComparator());
        adapter.notifyDataSetChanged();

    }

    public class CustomComparator implements Comparator<DataModel> {
        @Override
        public int compare(DataModel o1, DataModel o2) {
            return o1.getName().compareToIgnoreCase(o2.getName());
        }
    }

    public void filter(String charText) {
        charText = charText.toLowerCase(Locale.getDefault());
        data.clear();
        if (charText.length() == 0) {
            data.addAll(univList);
        }
        else
        {
            for (DataModel wp : univList) {
                if (wp.getName().toLowerCase(Locale.getDefault()).contains(charText) || wp.getRelation().toLowerCase(Locale.getDefault()).contains(charText)) {
                    data.add(wp);
                }
            }
        }
        arrayList.clear();
        arrayList.addAll(data);
        Log.i("list", arrayList.toString());
        Collections.sort(data, new CustomComparator());
        adapter.notifyDataSetChanged();
    }

    @Override
    protected void onResume() {
        super.onResume();
        Bundle extras = getIntent().getExtras();
        if(extras!=null){
            String str = extras.getString("Relation");
            if(str!=null) {
                search.setText(str);
                search.clearFocus();
                filter(str);
                //getIntent().removeExtra("Relation");
            }
            else{
                data.clear();
                Cursor c = databaseHelper.getUtilities();
                while(c.moveToNext()){
                    data.add(new DataModel(
                            c.getString(1),//name
                            c.getString(2),//phone number
                            c.getString(3),//device
                            c.getString(4) //email
                    ));
                }
                Log.i("g", data.toString());
                arrayList.clear();
                arrayList.addAll(data);
                adapter.notifyDataSetChanged();
                //getIntent().removeExtra("Utilities");
            }
        }
        else{
            Log.i("Here 1", "Here");
            updateList();
        }
    }
}
