package com.example.myapplication;

import android.Manifest;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.database.Cursor;
import android.net.Uri;
import android.os.Build;
import android.speech.RecognitionListener;
import android.speech.RecognizerIntent;
import android.speech.SpeechRecognizer;
import android.speech.tts.TextToSpeech;
import android.support.v4.app.ActivityCompat;
import android.support.v4.content.ContextCompat;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.text.format.DateUtils;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.view.animation.Animation;
import android.view.animation.AnimationUtils;
import android.widget.TextView;
import android.widget.Toast;

import java.util.Arrays;
import java.util.Date;
import java.util.List;
import java.util.Locale;

public class MainActivity extends AppCompatActivity {

    View fab;
    private static final int MY_PERMISSIONS_REQUEST_RECORD_AUDIO = 1;
    private TextToSpeech tts;
    private SpeechRecognizer speechRecog;
    static int MAX_CHAR = 50;
    private TextView textView;
    private Constants constants;
    private Animation shake;
    DatabaseHelper databaseHelper;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        constants = new Constants();
        databaseHelper = new DatabaseHelper(getApplicationContext());
        shake = AnimationUtils.loadAnimation(this, R.anim.shake);
        shake.setRepeatCount(-1);

        fab = findViewById(R.id.button2);
        textView = findViewById(R.id.command);
        fab.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                // Here, thisActivity is the current activity
                if (ContextCompat.checkSelfPermission(MainActivity.this,
                        Manifest.permission.RECORD_AUDIO)
                        != PackageManager.PERMISSION_GRANTED) {

                    // Permission is not granted
                    // Should we show an explanation?
                    if (ActivityCompat.shouldShowRequestPermissionRationale(MainActivity.this,
                            Manifest.permission.RECORD_AUDIO)) {
                        // Show an explanation to the user *asynchronously* -- don't block
                        // this thread waiting for the user's response! After the user
                        // sees the explanation, try again to request the permission.
                    } else {
                        // No explanation needed; request the permission
                        ActivityCompat.requestPermissions(MainActivity.this,
                                new String[]{Manifest.permission.RECORD_AUDIO},MY_PERMISSIONS_REQUEST_RECORD_AUDIO);

                        // MY_PERMISSIONS_REQUEST_READ_CONTACTS is an
                        // app-defined int constant. The callback method gets the
                        // result of the request.
                    }
                } else {
                    // Permission has already been granted
                    fab.startAnimation(shake);
                    Intent intent = new Intent(RecognizerIntent.ACTION_RECOGNIZE_SPEECH);
                    intent.putExtra(RecognizerIntent.EXTRA_LANGUAGE_MODEL,RecognizerIntent.LANGUAGE_MODEL_FREE_FORM);
                    intent.putExtra(RecognizerIntent.EXTRA_MAX_RESULTS,1);
                    speechRecog.startListening(intent);
                }
            }
        });

        initializeTextToSpeech();
        initializeSpeechRecognizer();




        View addContact = findViewById(R.id.rectangle_5);
        addContact.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent myIntent = new Intent(MainActivity.this, addContact.class);
                myIntent.setFlags(Intent.FLAG_ACTIVITY_REORDER_TO_FRONT);
                startActivityIfNeeded(myIntent, 0);
            }
        });

        View phoneCall = findViewById(R.id.rectangle_8);
        phoneCall.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent myIntent = new Intent(MainActivity.this, phoneCall.class);
                myIntent.setFlags(Intent.FLAG_ACTIVITY_REORDER_TO_FRONT);
                startActivityIfNeeded(myIntent, 0);
            }
        });

        View contactList = findViewById(R.id.rectangle_4);
        contactList.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent myIntent = new Intent(MainActivity.this, contactsList.class);
                myIntent.setFlags(Intent.FLAG_ACTIVITY_REORDER_TO_FRONT);
                //myIntent.setFlags(Intent.FLAG_ACTIVITY_SINGLE_TOP);
                startActivityIfNeeded(myIntent, 0);
            }
        });

        View favList = findViewById(R.id.rectangle_3);
        favList.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent myIntent = new Intent(MainActivity.this, FavContacts.class);
                myIntent.setFlags(Intent.FLAG_ACTIVITY_REORDER_TO_FRONT);
                startActivityIfNeeded(myIntent, 0);
            }
        });

        View utilities = findViewById(R.id.rectangle_10);
        utilities.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent myIntent = new Intent(MainActivity.this, contactsList.class);
                myIntent.putExtra("Utilities", 1);
                myIntent.setFlags(Intent.FLAG_ACTIVITY_REORDER_TO_FRONT);
                startActivityIfNeeded(myIntent, 0);
            }
        });

        View emer = findViewById(R.id.rectangle_2);
        emer.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent myIntent = new Intent(MainActivity.this, EmergencyContacts.class);
                myIntent.setFlags(Intent.FLAG_ACTIVITY_REORDER_TO_FRONT);
                startActivityIfNeeded(myIntent, 0);
            }
        });

        View cab = findViewById(R.id.rectangle_9);
        cab.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent myIntent = new Intent(MainActivity.this, Cab.class);
                myIntent.setFlags(Intent.FLAG_ACTIVITY_REORDER_TO_FRONT);
                startActivityIfNeeded(myIntent, 0);
            }
        });


    }

    private void initializeSpeechRecognizer() {
        if (SpeechRecognizer.isRecognitionAvailable(this)) {
            speechRecog = SpeechRecognizer.createSpeechRecognizer(this);
            speechRecog.setRecognitionListener(new RecognitionListener() {
                @Override
                public void onReadyForSpeech(Bundle params) {

                }

                @Override
                public void onBeginningOfSpeech() {

                }

                @Override
                public void onRmsChanged(float rmsdB) {

                }

                @Override
                public void onBufferReceived(byte[] buffer) {

                }

                @Override
                public void onEndOfSpeech() {
                    fab.clearAnimation();
                }

                @Override
                public void onError(int error) {
                    fab.clearAnimation();
                }

                @Override
                public void onResults(Bundle results) {
                    List<String> result_arr = results.getStringArrayList(SpeechRecognizer.RESULTS_RECOGNITION);
                    processResult(result_arr.get(0));
                }

                @Override
                public void onPartialResults(Bundle partialResults) {
                    fab.clearAnimation();
                }

                @Override
                public void onEvent(int eventType, Bundle params) {

                }
            });
        }
    }

    private void processResult(String result_message) {
        fab.clearAnimation();
        textView.setText("");
        textView.setText(result_message);
        result_message = result_message.toLowerCase();
        Log.i("message", result_message);
        if(result_message.indexOf("call")!=-1){
            if(result_message.indexOf("my")!=-1){
                String[] bits = result_message.split(" ");
                Log.i("bits", bits[bits.length-2]);
                //String str = result_message.substring(result_message.lastIndexOf(" ")+1);
                if(bits[bits.length-2].equals("my")) {
                    String str = bits[bits.length-1];
                    Cursor c = databaseHelper.searchWithRelation(str);
                    if (c.getCount() == 0) {
                        speak("Unable to find your " + str);
                        textView.setText("");
                    } else if (c.getCount() == 1) {
                        Log.i("here", "here");
                        c.moveToFirst();
                        String Phone = c.getString(2);
                        Log.i("Phone", Phone);
                        callPhone(Phone);
                    } else {
                        speak("Which " + str + " ?");
                        Intent myIntent = new Intent(MainActivity.this, contactsList.class);
                        myIntent.putExtra("Relation", str);
                        myIntent.setFlags(Intent.FLAG_ACTIVITY_REORDER_TO_FRONT);
                        startActivityIfNeeded(myIntent, 0);
                    }
                }
                else{
                    String str1 = bits[bits.length - 1];
                    String str2 = bits[bits.length - 2];
                    Cursor c = databaseHelper.searchWithRelName(str1, str2);
                    if (c.getCount() == 0) {
                        speak("Unable to find your " + str2 +" "+str1);
                        textView.setText("");
                    } else if (c.getCount() == 1) {
                        Log.i("here", "here");
                        c.moveToFirst();
                        String Phone = c.getString(2);
                        Log.i("Phone", Phone);
                        callPhone(Phone);
                    } else {
                        //speak("Which " + str + " ?");
                        Intent myIntent = new Intent(MainActivity.this, contactsList.class);
                        myIntent.putExtra("Relation", str1);
                        myIntent.setFlags(Intent.FLAG_ACTIVITY_REORDER_TO_FRONT);
                        startActivityIfNeeded(myIntent, 0);
                    }
                }
            }
            else{
                String str = result_message.substring(result_message.lastIndexOf(" ")+1);
                Cursor c = databaseHelper.searchWithName(str);
                if(c.getCount()==0){
                    Cursor c1 = databaseHelper.searchWithRelation(str);
                    if(c1.getCount()==0){
                        speak("Unable to find your "+ str);
                        textView.setText("");
                    }
                    else if(c1.getCount()==1){
                        c1.moveToFirst();
                        String Phone = c1.getString(2);
                        Log.i("Phone", Phone);
                        callPhone(Phone);
                    }
                    else{
                        Intent myIntent = new Intent(MainActivity.this, contactsList.class);
                        myIntent.putExtra("Relation",str);
                        myIntent.setFlags(Intent.FLAG_ACTIVITY_REORDER_TO_FRONT);
                        startActivityIfNeeded(myIntent, 0);
                    }

                }
                else if(c.getCount()==1){
                    c.moveToFirst();
                    String Phone = c.getString(2);
                    Log.i("Phone", Phone);
                    callPhone(Phone);
                }
                else{
                    speak("Which "+str+" ?");
                    Intent myIntent = new Intent(MainActivity.this, contactsList.class);
                    myIntent.putExtra("Relation",str);
                    myIntent.setFlags(Intent.FLAG_ACTIVITY_REORDER_TO_FRONT);
                    startActivityIfNeeded(myIntent, 0);
                }

            }
        }
        if(result_message.indexOf("what") != -1){
            if(result_message.indexOf("your name") != -1){
                speak("My Name is Mr.Android. Nice to meet you!");
            }
            if (result_message.indexOf("time") != -1){
                String time_now = DateUtils.formatDateTime(this, new Date().getTime(),DateUtils.FORMAT_SHOW_TIME);
                speak("The time is now: " + time_now);
            }
        } else if (result_message.indexOf("earth") != -1){
            speak("Don't be silly, The earth is a sphere. As are all other planets and celestial bodies");
        } else if (result_message.indexOf("browser") != -1){
            speak("Opening a browser right away master.");
            Intent intent = new Intent(Intent.ACTION_VIEW, Uri.parse("https://www.google.co.in"));
            startActivity(intent);
        } else if(result_message.indexOf("open") != -1){
            if(result_message.indexOf("swiggy")!=-1){
                try {
                    Intent intent = getPackageManager().getLaunchIntentForPackage(constants.getSwiggy());
                    startActivity(intent);
                }
                catch (Exception e){
                    speak("Application not found!");
                }
            }
            else if(result_message.indexOf("chrome")!=-1){
                try {
                    Intent intent = getPackageManager().getLaunchIntentForPackage(constants.getChrome());
                    startActivity(intent);
                }
                catch (Exception e){
                    speak("Application not found!");
                }
            }
        }
    }

    private void initializeTextToSpeech() {
        tts = new TextToSpeech(this, new TextToSpeech.OnInitListener() {
            @Override
            public void onInit(int status) {
                if (tts.getEngines().size() == 0 ){
                    Toast.makeText(MainActivity.this, getString(R.string.tts_no_engines),Toast.LENGTH_LONG).show();
                    finish();
                } else {
                    tts.setLanguage(Locale.US);
                    //speak("Hello there, I am ready to start our conversation");
                }
            }
        });
    }

    private void speak(String message) {
        if(Build.VERSION.SDK_INT >= 21){
            tts.speak(message,TextToSpeech.QUEUE_FLUSH,null,null);
        } else {
            tts.speak(message, TextToSpeech.QUEUE_FLUSH,null);
        }
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.menu_main, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent activity in AndroidManifest.xml.
        int id = item.getItemId();

        //noinspection SimplifiableIfStatement
        if (id == R.id.action_settings) {
            return true;
        }

        return super.onOptionsItemSelected(item);
    }

    @Override
    protected void onPause() {
        super.onPause();
        tts.shutdown();
    }

    @Override
    protected void onResume() {
        super.onResume();
//        Reinitialize the recognizer and tts engines upon resuming from background such as after openning the browser
        textView.setText("");
        initializeSpeechRecognizer();
        initializeTextToSpeech();
    }



    static boolean twoStrings(String s1, String s2)
    {
        // vector for storing character occurrences
        boolean v[]=new boolean[MAX_CHAR];
        Arrays.fill(v,false);

        // increment vector index for every
        // character of str1
        for (int i = 0; i < s1.length(); i++)
            v[s1.charAt(i) - 'a'] = true;

        // checking common substring of str2 in str1
        for (int i = 0; i < s2.length(); i++)
            if (v[s2.charAt(i) - 'a'])
                return true;

        return false;
    }

    public void callPhone(String Phone){
        Intent callIntent = new Intent(Intent.ACTION_CALL);
        callIntent.setData(Uri.parse("tel:"+Phone));//change the number
        if (ContextCompat.checkSelfPermission(MainActivity.this, Manifest.permission.CALL_PHONE) != PackageManager.PERMISSION_GRANTED) {
            ActivityCompat.requestPermissions(MainActivity.this, new String[]{Manifest.permission.CALL_PHONE},1);
        }
        else
        {
            startActivity(callIntent);
        }
    }


}
