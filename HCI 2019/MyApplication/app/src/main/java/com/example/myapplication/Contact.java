package com.example.myapplication;

import android.os.Parcel;
import android.os.Parcelable;

public class Contact implements Parcelable {
    String name;
    String phone;
    String relation;
    String image;

    public Contact() {
    }

    public Contact(String name, String phone, String relation, String image) {
        this.name = name;
        this.phone = phone;
        this.relation = relation;
        this.image = image;
    }

    public Contact(Parcel in){
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

    public static final Creator<Contact> CREATOR = new Creator<Contact>() {
        @Override
        public Contact createFromParcel(Parcel in) {
            return new Contact(in);
        }

        @Override
        public Contact[] newArray(int size) {
            return new Contact[size];
        }
    };

    public String getImage() {
        return image;
    }

    public void setImage(String image) {
        this.image = image;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getPhone() {
        return phone;
    }

    public void setPhone(String phone) {
        this.phone = phone;
    }

    public String getRelation() {
        return relation;
    }

    public void setRelation(String relation) {
        this.relation = relation;
    }
}
