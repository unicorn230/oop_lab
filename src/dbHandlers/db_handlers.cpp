#include <fstream>
#include <iostream>
#include <string>
#include "../classes/classes.h"
#include <ctime>

int read_map_number(){
    int a;
    ifstream infile;
    infile.open("../src/db/map_db.txt");

    infile >> a;
    infile.close();
    return a;
}

connection* read_map(){
    int a;
    ifstream infile;
    infile.open("../src/db/map_db.txt");
    infile >> a;

    connection *map = new connection[a*a];

    for(int i=0; i<a*a; i++){
        string data;
        infile >>data;
        int digits[4]={0,0,0,0};
        int k=0;

        string digit="";
        for(int j=0; j<data.length(); j++){
            if(data[j]!=','){
                digit+=data[j];
            }else{
                digits[k]=stoi(digit);
                digit="";
                k++;
            }
        }

        connection con={(double) digits[0], (double) digits[1], (double)digits[2], (double)digits[3]};
        map[i]=con;

    }
    infile.close();
    return map;

}

int read_parcels_number(){
    int a;
    ifstream infile;
    infile.open("../src/db/parcels_history_db.txt");

    infile >> a;

    infile.close();
    return a;

}

Parcel* read_parcels(){
    int a;
    ifstream infile;
    infile.open("../src/db/parcels_history_db.txt");
    infile >> a;
    string users[2];
    int k=0;

    Parcel *parcels=new Parcel[a];

    string digit="";
    for(int i=0; i<a; i++){
        string data;
        int digits[13];
        infile >>data;

        int j=0, l=0;
        while(j<13){
            if(data[l]==','){
                digits[j]=stoi(digit);
                digit="";
                j++;
            }else{
                digit+=data[l];
            }
            l++;
        }
        int s=0;
        string str="";
        while(s<2){
            if(data[l]==','){
                users[s]=str;
                str="";
                s++;
            }else{
                str+=data[l];
            }
            l++;
        }
        cout<<digits[2]<<" "<<digits[3]<<" "<<digits[4]<<endl;
        Date sending_date(digits[2], digits[3], digits[4]);
        Date receiving_date(digits[5], digits[6], digits[7]);
        Parcel par(digits[0],digits[1], sending_date, receiving_date, digits[8], digits[9], digits[10], digits[11], (bool) digits[12], users[0], users[1]);
        parcels[i]=par;
    }
    infile.close();
    return parcels;

}

void save_parcel(int weight, int volume, Date sending_date,  Date receiving_date, int price, int origin, int destination, bool premium, string sender, string recepient) {
    string data="";
    ifstream infile;
    infile.open("../src/db/parcels_history_db.txt", ios::in);


    int n;
    string part;
    infile>>n;
    n++;

    while (getline(infile, part)) {
        data+=part+'\n';
    }
    data += to_string(weight)+','+to_string(volume)+','+to_string(sending_date.get_day())+','+to_string(sending_date.get_month())+','+to_string(sending_date.get_year())+','+to_string(receiving_date.get_day())+','+to_string(receiving_date.get_month())+','+to_string(receiving_date.get_year())+','+to_string(price)+','+to_string(origin)+','+to_string(destination)+','+to_string(n)+','+to_string(premium)+','+sender+','+recepient+',';
    infile.close();

    ofstream onfile;
    onfile.open("../src/db/parcels_history_db.txt");
    onfile<<n;
    onfile<<data;
    onfile.close();
}
