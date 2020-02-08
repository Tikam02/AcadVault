package com.example.myapplication;

import android.Manifest;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.database.Cursor;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.net.Uri;
import android.provider.MediaStore;
import android.support.v4.app.ActivityCompat;
import android.support.v4.content.ContextCompat;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ImageView;
import android.widget.Spinner;
import android.widget.Toast;


public class addContact extends AppCompatActivity {

    final int PICK_IMAGE = 1;
    int click = 0;
    String image = null;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.add_contact);

        final Bundle extras = getIntent().getExtras();
        int f = 0;
        if(extras!=null){
            f = extras.getInt("flag", 0);
        }
        final int flag = f;
        final EditText name = findViewById(R.id.name);
        final EditText ph = findViewById(R.id.phone);
        final Spinner s = findViewById(R.id.spinner);
        final Button button = findViewById(R.id.addContact);
        final Button cam = findViewById(R.id.camera);
        final Button heart = findViewById(R.id.heart);
        String[] items = new String[]{"Mother", "Father", "Son", "Daughter", "Friend", "Wife", "Husband", "Sister", "Brother", "Carpenter", "Doctor", "Nurse", "Plumber", "Electrician"};
        ArrayAdapter<String> adapter = new ArrayAdapter<>(this, R.layout.spinner_item, items);
        s.setAdapter(adapter);

        if(flag==1){
            DataModel dm = extras.getParcelable("Obj");
            name.setText(dm.getName());
            ph.setText(dm.getPhone());
            s.setSelection(adapter.getPosition(dm.getRelation()));
            ImageView im = findViewById(R.id.propic);
            if(dm.getImage()==null){
                im.setImageResource(R.drawable.ic_android);
            }
            else{
                Bitmap bitmap = BitmapFactory.decodeFile(dm.getImage());
                //Bitmap b = getCircularBitmapWithWhiteBorder(bitmap, 2);
                im.setImageBitmap(bitmap);
            }
            DatabaseHelper databaseHelper = new DatabaseHelper(getApplicationContext());
            Contact contact = new Contact(name.getText().toString(),
                    ph.getText().toString(),
                    s.getSelectedItem().toString(),
                    image);
            Cursor cursor = databaseHelper.getFavContactID(contact);
            if(cursor.getCount()==0){
                heart.setBackgroundTintList(getResources().getColorStateList(R.color.white));
                click=0;
            }
            else{
                heart.setBackgroundTintList(getResources().getColorStateList(R.color.red));
                click=1;
            }
            button.setText("Finish");
        }
        else{
            ImageView im = findViewById(R.id.propic);
            im.setImageResource(R.drawable.ic_android);
            heart.setBackgroundTintList(getResources().getColorStateList(R.color.white));
        }

        View phoneCall = findViewById(R.id.rectangle_8);
        phoneCall.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent myIntent = new Intent(addContact.this, phoneCall.class);
                myIntent.setFlags(Intent.FLAG_ACTIVITY_REORDER_TO_FRONT);
                startActivityIfNeeded(myIntent, 0);
            }
        });

        View contactList = findViewById(R.id.rectangle_4);
        contactList.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent myIntent = new Intent(addContact.this, contactsList.class);
                myIntent.setFlags(Intent.FLAG_ACTIVITY_REORDER_TO_FRONT);
                startActivityIfNeeded(myIntent, 0);
            }
        });

        View favList = findViewById(R.id.rectangle_3);
        favList.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent myIntent = new Intent(addContact.this, FavContacts.class);
                myIntent.setFlags(Intent.FLAG_ACTIVITY_REORDER_TO_FRONT);
                startActivityIfNeeded(myIntent, 0);
            }
        });

        View utilities = findViewById(R.id.rectangle_10);
        utilities.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent myIntent = new Intent(addContact.this, contactsList.class);
                myIntent.putExtra("Utilities", 1);
                myIntent.setFlags(Intent.FLAG_ACTIVITY_REORDER_TO_FRONT);
                startActivityIfNeeded(myIntent, 0);
            }
        });

        View emer = findViewById(R.id.rectangle_2);
        emer.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent myIntent = new Intent(addContact.this, EmergencyContacts.class);
                myIntent.setFlags(Intent.FLAG_ACTIVITY_REORDER_TO_FRONT);
                startActivityIfNeeded(myIntent, 0);
            }
        });

        View cab = findViewById(R.id.rectangle_9);
        cab.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent myIntent = new Intent(addContact.this, Cab.class);
                myIntent.setFlags(Intent.FLAG_ACTIVITY_REORDER_TO_FRONT);
                startActivityIfNeeded(myIntent, 0);
            }
        });

        heart.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if(click==0){
                    heart.setBackgroundTintList(getResources().getColorStateList(R.color.red));
                    click = 1;
                }
                else{
                    heart.setBackgroundTintList(getResources().getColorStateList(R.color.white));
                    click = 0;
                }
            }
        });

        button.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                DatabaseHelper databaseHelper = new DatabaseHelper(getApplicationContext());
                Contact contact = new Contact(name.getText().toString(),
                                              ph.getText().toString(),
                                              s.getSelectedItem().toString(),
                                              image);
                if(flag==1){
                    DataModel dm = extras.getParcelable("Obj");
                    Contact c = new Contact(dm.getName(),dm.getPhone(),dm.getRelation(),dm.getImage());
                    Cursor cursor = databaseHelper.getContactID(c);
                    cursor.moveToFirst();
                    int id = cursor.getInt(0);
                    databaseHelper.updateContact(contact, id);
                    Toast.makeText(getApplicationContext(), "Updated Contact", Toast.LENGTH_LONG).show();
                    cursor = databaseHelper.getFavContactID(contact);
                    if(cursor.getCount()==0){
                        if(click==1) {
                            databaseHelper.addFavContact(contact);
                        }
                    }
                    else{
                        if(click==0) {
                            cursor.moveToFirst();
                            int id2 = cursor.getInt(0);
                            databaseHelper.deleteFavContact(id2);
                        }
                    }
                }
                else {
                        if(click==1) {
                            databaseHelper.addFavContact(contact);
                        }
                    databaseHelper.addContact(contact);
                    Toast.makeText(getApplicationContext(), "Added Contact", Toast.LENGTH_LONG).show();
                }
                Intent myIntent = new Intent(addContact.this, contactsList.class);
                myIntent.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK | Intent.FLAG_ACTIVITY_CLEAR_TASK);
                addContact.this.startActivity(myIntent);
            }
        });

        cam.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if (ContextCompat.checkSelfPermission(addContact.this, Manifest.permission.READ_EXTERNAL_STORAGE) != PackageManager.PERMISSION_GRANTED) {
                    ActivityCompat.requestPermissions(addContact.this, new String[]{Manifest.permission.READ_EXTERNAL_STORAGE},1);
                }
                else {
                    Intent intent = new Intent(Intent.ACTION_GET_CONTENT);
                    intent.setType("image/*");
                    startActivityForResult(intent, PICK_IMAGE);
                }
            }
        });

    }

    @Override
    public void onActivityResult(int requestCode, int resultCode, Intent data) {
        super.onActivityResult(requestCode, resultCode, data);
        switch(requestCode) {
            case PICK_IMAGE:
                if(resultCode == RESULT_OK){


                    Uri selectedImage = data.getData();
                    //Bitmap bitmap = MediaStore.Images.Media.getBitmap(this.getContentResolver(), selectedImage);
                    String[] filePathColumn = {MediaStore.Images.Media.DATA};
                    Cursor cursor = getContentResolver().query(selectedImage, filePathColumn, null, null, null);

                    cursor.moveToFirst();

                    int columnIndex = cursor.getColumnIndex(filePathColumn[0]);
                    String filePath = cursor.getString(columnIndex);
                    cursor.close();
                    if(filePath==null){
                        Log.i("yes","yes");
                    }
                    Log.i("cursor",filePath);

                    //getContentResolver().openInputStream(selectedImage);

                    //Bitmap bitmap=BitmapFactory.decodeStream(getContentResolver().openInputStream(selectedImage));

                    try {
                        Bitmap yourSelectedImage = BitmapFactory.decodeFile(filePath);
                        //ExifInterface exif = new ExifInterface(filePath);
                        ImageView im = findViewById(R.id.propic);
                        //Bitmap b = getCircularBitmapWithWhiteBorder(yourSelectedImage, 2);
                        im.setImageBitmap(yourSelectedImage);
                        image = filePath;
                    } catch (OutOfMemoryError e) {

                            Log.e("Error",e.toString());
                        }
                }
        }

    }
}
