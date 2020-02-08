package com.example.myapplication;

import android.os.Parcel;
import android.os.Parcelable;
import android.provider.ContactsContract;

public class DataModel implements Parcelable {

    String name;
    String phone="google";
    String relation="google";
    String image;

    public DataModel(String name, String phone, String relation,String image) {
        this.name = name;
        this.phone = phone;
        this.relation=relation;
        this.image=image;
    }

    public DataModel(Parcel in){
        name = in.readString();
        phone = in.readString();
        relation = in.readString();
        image = in.readString();
    }
    @Override
    public void writeToParcel(Parcel dest, int flags) {
        dest.writeString(name);
        dest.writeString(phone);
        dest.writeString(relation);
        dest.writeString(image);
    }

    @Override
    public int describeContents() {
        return 0;
    }

    public static final Creator<DataModel> CREATOR = new Creator<DataModel>() {
        @Override
        public DataModel createFromParcel(Parcel in) {
            return new DataModel(in);
        }

        @Override
        public DataModel[] newArray(int size) {
            return new DataModel[size];
        }
    };


    public String getName() {
        return name;
    }

    public String getPhone() {
        return phone;
    }

    public String getRelation() {
        return relation;
    }

    public String getImage() {
        return image;
    }
}