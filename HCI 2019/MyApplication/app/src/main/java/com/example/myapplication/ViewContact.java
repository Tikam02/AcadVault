package com.example.myapplication;

import android.content.Intent;
import android.database.Cursor;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.BitmapShader;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.graphics.Shader;
import android.os.Bundle;
import android.support.design.widget.FloatingActionButton;
import android.support.design.widget.Snackbar;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.Toolbar;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.TextView;

public class ViewContact extends AppCompatActivity {
    DataModel dm;
    Button del,edit,heart;
    TextView nm,ph,relation;
    ImageView imageView;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.content_view_contact);


        nm = findViewById(R.id.name);
        ph = findViewById(R.id.phone);
        relation = findViewById(R.id.relation);
        dm = getIntent().getExtras().getParcelable("Obj");
        nm.setText(dm.getName());
        ph.setText(dm.getPhone());
        relation.setText(dm.getRelation());
        imageView = findViewById(R.id.propic);
        if(dm.getImage()==null){
            imageView.setImageResource(R.drawable.ic_android);
        }
        else{
            Bitmap bitmap = BitmapFactory.decodeFile(dm.getImage());
            //Bitmap b = getCircularBitmapWithWhiteBorder(bitmap, 2);
            imageView.setImageBitmap(bitmap);
        }

        final Contact c = new Contact(dm.getName(),dm.getPhone(),dm.getRelation(),dm.getImage());
        final DatabaseHelper databaseHelper = new DatabaseHelper(getApplicationContext());

        heart = findViewById(R.id.heart);

        Cursor cursor = databaseHelper.getFavContactID(c);
        if(cursor.getCount()==0){
            heart.setBackgroundTintList(getResources().getColorStateList(R.color.white));
        }
        else{
            heart.setBackgroundTintList(getResources().getColorStateList(R.color.red));
        }

        View addContact = findViewById(R.id.rectangle_5);
        addContact.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent myIntent = new Intent(ViewContact.this, addContact.class);
                myIntent.setFlags(Intent.FLAG_ACTIVITY_REORDER_TO_FRONT);
                startActivityIfNeeded(myIntent, 0);
            }
        });

        View phoneCall = findViewById(R.id.rectangle_8);
        phoneCall.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent myIntent = new Intent(ViewContact.this, phoneCall.class);
                myIntent.setFlags(Intent.FLAG_ACTIVITY_REORDER_TO_FRONT);
                startActivityIfNeeded(myIntent, 0);
            }
        });

        View favList = findViewById(R.id.rectangle_3);
        favList.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent myIntent = new Intent(ViewContact.this, FavContacts.class);
                myIntent.setFlags(Intent.FLAG_ACTIVITY_REORDER_TO_FRONT);
                startActivityIfNeeded(myIntent, 0);
            }
        });

        View utilities = findViewById(R.id.rectangle_10);
        utilities.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent myIntent = new Intent(ViewContact.this, contactsList.class);
                myIntent.putExtra("Utilities", 1);
                myIntent.setFlags(Intent.FLAG_ACTIVITY_REORDER_TO_FRONT);
                startActivityIfNeeded(myIntent, 0);
            }
        });

        View emer = findViewById(R.id.rectangle_2);
        emer.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent myIntent = new Intent(ViewContact.this, EmergencyContacts.class);
                myIntent.setFlags(Intent.FLAG_ACTIVITY_REORDER_TO_FRONT);
                startActivityIfNeeded(myIntent, 0);
            }
        });

        View cab = findViewById(R.id.rectangle_9);
        cab.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent myIntent = new Intent(ViewContact.this, Cab.class);
                myIntent.setFlags(Intent.FLAG_ACTIVITY_REORDER_TO_FRONT);
                startActivityIfNeeded(myIntent, 0);
            }
        });


        heart.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {

                Cursor cursor = databaseHelper.getFavContactID(c);
                if(cursor.getCount()==0){
                    databaseHelper.addFavContact(c);
                    heart.setBackgroundTintList(getResources().getColorStateList(R.color.red));
                }
                else{
                    cursor.moveToFirst();
                    int id = cursor.getInt(0);
                    databaseHelper.deleteFavContact(id);
                    heart.setBackgroundTintList(getResources().getColorStateList(R.color.white));
                }
            }
        });

        del = findViewById(R.id.DelContact);
        del.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Cursor cursor = databaseHelper.getContactID(c);
                Cursor cu = databaseHelper.getFavContactID(c);
                if(cu.getCount()!=0){
                    cu.moveToFirst();
                    int idd = cu.getInt(0);
                    databaseHelper.deleteFavContact(idd);
                }
                cursor.moveToFirst();
                int id = cursor.getInt(0);
                Log.i("id", String.valueOf(id));
                databaseHelper.deleteContact(id);
                Intent i = new Intent(ViewContact.this, contactsList.class);
                i.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK | Intent.FLAG_ACTIVITY_CLEAR_TASK);
                ViewContact.this.startActivity(i);
            }
        });

        edit = findViewById(R.id.EditContact);
        edit.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent i = new Intent(ViewContact.this, addContact.class);
                i.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK | Intent.FLAG_ACTIVITY_CLEAR_TASK);
                i.putExtra("flag", 1);
                i.putExtra("Obj",dm);
                ViewContact.this.startActivity(i);
            }
        });

    }

    public static Bitmap getCircularBitmapWithWhiteBorder(Bitmap bitmap,
                                                          int borderWidth) {
        if (bitmap == null || bitmap.isRecycled()) {
            return null;
        }

        final int width = bitmap.getWidth() + borderWidth;
        final int height = bitmap.getHeight() + borderWidth;

        Bitmap canvasBitmap = Bitmap.createBitmap(width, height, Bitmap.Config.ARGB_8888);
        BitmapShader shader = new BitmapShader(bitmap, Shader.TileMode.CLAMP, Shader.TileMode.CLAMP);
        Paint paint = new Paint();
        paint.setAntiAlias(true);
        paint.setShader(shader);

        Canvas canvas = new Canvas(canvasBitmap);
        float radius = width > height ? ((float) height) / 2f : ((float) width) / 2f;
        canvas.drawCircle(width / 2, height / 2, radius, paint);
        paint.setShader(null);
        paint.setStyle(Paint.Style.STROKE);
        paint.setColor(Color.BLUE);
        paint.setStrokeWidth(borderWidth);
        canvas.drawCircle(width / 2, height / 2, radius - borderWidth / 2, paint);
        return canvasBitmap;
    }

}
