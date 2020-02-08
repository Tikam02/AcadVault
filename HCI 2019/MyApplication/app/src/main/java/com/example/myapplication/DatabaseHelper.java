package com.example.myapplication;

import android.content.ContentValues;
import android.content.Context;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteOpenHelper;
import android.util.Log;

public class DatabaseHelper extends SQLiteOpenHelper {

    private static final String TAG = "DatabaseHelper";

    private static final String DATABASE_NAME = "contacts.db";
    private static final String TABLE_NAME = "contacts_table";
    private static final String TABLE_FAV = "fav_table";
    public static final String COL0 = "ID";
    public static final String COL1 = "NAME";
    public static final String COL2 = "PHONE_NUMBER";
    public static final String COL3 = "RELATION";
    public static final String COL4 = "PROFILE_PHOTO";


    public DatabaseHelper(Context context) {
        super(context, DATABASE_NAME, null, 1);
    }

    @Override
    public void onCreate(SQLiteDatabase db) {
        String sql = "CREATE TABLE " +
                TABLE_NAME + " ( " +
                COL0 + " INTEGER PRIMARY KEY AUTOINCREMENT, " +
                COL1 + " TEXT, " +
                COL2 + " TEXT, " +
                COL3 + " TEXT, " +
                COL4 + " TEXT ) ";

        String sql2 = "CREATE TABLE " +
                TABLE_FAV + " ( " +
                COL0 + " INTEGER PRIMARY KEY AUTOINCREMENT, " +
                COL1 + " TEXT, " +
                COL2 + " TEXT, " +
                COL3 + " TEXT, " +
                COL4 + " TEXT ) ";
        db.execSQL(sql);
        db.execSQL(sql2);
    }

    @Override
    public void onUpgrade(SQLiteDatabase db, int oldVersion, int newVersion) {
        db.execSQL("DROP IF TABLE EXISTS " + TABLE_NAME);
        db.execSQL("DROP IF TABLE EXISTS " + TABLE_FAV);
        onCreate(db);
    }

    /**
     * Insert a new contact into the database
     * @param contact
     * @return
     */
    public boolean addContact(Contact contact) {
        SQLiteDatabase db = this.getWritableDatabase();
        ContentValues contentValues = new ContentValues();
        contentValues.put(COL1, contact.getName());
        contentValues.put(COL2, contact.getPhone());
        contentValues.put(COL3, contact.getRelation());
        contentValues.put(COL4, contact.getImage());

        long result = db.insert(TABLE_NAME, null, contentValues);

        if (result == -1) {
            return false;
        } else {
            return true;
        }
    }

    public boolean addFavContact(Contact contact) {
        SQLiteDatabase db = this.getWritableDatabase();
        ContentValues contentValues = new ContentValues();
        contentValues.put(COL1, contact.getName());
        contentValues.put(COL2, contact.getPhone());
        contentValues.put(COL3, contact.getRelation());
        contentValues.put(COL4, contact.getImage());

        long result = db.insert(TABLE_FAV, null, contentValues);

        if (result == -1) {
            return false;
        } else {
            return true;
        }
    }

    /**
     * Retrieve all contacts from database
     * @return
     */
    public Cursor searchWithName(String str){
        SQLiteDatabase db = this.getWritableDatabase();
        return db.rawQuery("SELECT * FROM "+TABLE_NAME+" WHERE LOWER("+COL1+") = '"+str+"'",null);
    }
    public Cursor searchWithRelation(String str){
        SQLiteDatabase db = this.getWritableDatabase();
        Log.i("Query", "SELECT * FROM "+TABLE_NAME+" WHERE LOWER("+COL3+") = '"+str+"'");
        return db.rawQuery("SELECT * FROM "+TABLE_NAME+" WHERE LOWER("+COL3+") = '"+str+"'",null);
    }

    public Cursor searchWithRelName(String str1, String str2){
        SQLiteDatabase db = this.getWritableDatabase();
        return db.rawQuery("SELECT * FROM "+TABLE_NAME+" WHERE LOWER("+COL1+") = '"+str1+"' AND LOWER("+COL3+") = '"+str2+"'",null);
    }

    public Cursor getAllContacts(){
        SQLiteDatabase db = this.getWritableDatabase();
        return db.rawQuery("SELECT * FROM " + TABLE_NAME, null);
    }

    public Cursor getFavAllContacts(){
        SQLiteDatabase db = this.getWritableDatabase();
        return db.rawQuery("SELECT * FROM " + TABLE_FAV, null);
    }

    /**
     * Update a contact where id = @param 'id'
     * Replace the current contact with @param 'contact'
     * @param contact
     * @param id
     * @return
     */
    public boolean updateContact(Contact contact, int id){
        SQLiteDatabase db = this.getWritableDatabase();
        ContentValues contentValues = new ContentValues();
        contentValues.put(COL1, contact.getName());
        contentValues.put(COL2, contact.getPhone());
        contentValues.put(COL3, contact.getRelation());
        contentValues.put(COL4, contact.getImage());

        int update = db.update(TABLE_NAME, contentValues, COL0 + " = ? ", new String[] {String.valueOf(id)} );

        if(update != 1) {
            return false;
        }
        else{
            return true;
        }
    }


    /**
     * Retrieve the contact unique id from the database using @param
     * @param contact
     * @return
     */
    public Cursor getContactID(Contact contact){
        SQLiteDatabase db = this.getWritableDatabase();
        String sql = "SELECT * FROM " + TABLE_NAME  +
                " WHERE " + COL1 + " = '" + contact.getName() + "'" +
                " AND " + COL2 + " = '" + contact.getPhone() + "'";
        return db.rawQuery(sql, null);
    }

    public Cursor getFavContactID(Contact contact){
        SQLiteDatabase db = this.getWritableDatabase();
        String sql = "SELECT * FROM " + TABLE_FAV  +
                " WHERE " + COL1 + " = '" + contact.getName() + "'" +
                " AND " + COL2 + " = '" + contact.getPhone() + "'";
        return db.rawQuery(sql, null);
    }


    public Integer deleteContact(int id){
        SQLiteDatabase db = this.getWritableDatabase();
        return db.delete(TABLE_NAME, "ID = ?", new String[] {String.valueOf(id)});
    }

    public Integer deleteFavContact(int id){
        SQLiteDatabase db = this.getWritableDatabase();
        return db.delete(TABLE_FAV, "ID = ?", new String[] {String.valueOf(id)});
    }

    public Cursor getUtilities(){
        SQLiteDatabase db = this.getWritableDatabase();
        Log.i("sql", "SELECT * FROM "+TABLE_NAME+" WHERE LOWER("+COL3+") IN ('Carpenter', 'Doctor', 'Nurse', 'Plumber', 'Electrician')");
        return db.rawQuery("SELECT * FROM "+TABLE_NAME+" WHERE "+COL3+" IN ('Carpenter', 'Doctor', 'Nurse', 'Plumber', 'Electrician')",null);
    }

}
