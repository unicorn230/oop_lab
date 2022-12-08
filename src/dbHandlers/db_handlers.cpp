#include <fstream>
#include <iostream>
#include <string>
#include "../../headers/Parcel.h"
#include "../../headers/DTOs.h"
#include "./db_handlers.h"

#define MAP_DB "../src/db/map_db.txt"
#define HISTORY_DB "../src/db/parcels_history_db.txt"

int Map_db::read_number(){
    int number_of_deps;
    ifstream db;
    db.open(MAP_DB);

    db >> number_of_deps;
    db.close();
    return number_of_deps;
}

connection* Map_db::read_data(){
    int number_of_deps;
    ifstream db;
    db.open(MAP_DB);
    db>> number_of_deps;

    connection *map = new connection[number_of_deps*number_of_deps];

    for(int i=0; i<number_of_deps*number_of_deps; i++){
        int plane;
        int ship;
        int train;
        int car;
        db>>plane;
        db>>ship;
        db>>train;
        db>>car;

        map[i]={(double) plane, (double) ship, (double) train, (double)car};
    }

    db.close();
    return map;
}

int History_db::read_number() {
    int number_of_parcels;
    ifstream db;
    db.open(HISTORY_DB);

    db >> number_of_parcels;

    db.close();
    return number_of_parcels;
}

Parcel* History_db::read_data() {
    int number_of_parcels;
    ifstream db;
    db.open(HISTORY_DB);
    db >> number_of_parcels;

    Parcel  *parcels =new Parcel[number_of_parcels];

    for(int i=0; i<number_of_parcels; i++){
        string weight;
        string volume;
        string sending_day;
        string sending_month;
        string sending_year;
        string receiving_day;
        string receiving_month;
        string receiving_year;
        string price;
        string origin;
        string destination;
        string id;
        string premium;
        string sender;
        string recipient;

        db>>weight;
        db>>volume;
        db>>sending_day;
        db>>sending_month;
        db>>sending_year;
        db>>receiving_day;
        db>>receiving_month;
        db>>receiving_year;
        db>>price;
        db>>origin;
        db>>destination;
        db>>id;
        db>>premium;
        db>>sender;
        db>>recipient;

        parcels[i]=Parcel(stoi(weight),
                          stoi(volume),
                          Date(stoi(sending_day),stoi(sending_month),stoi(sending_year)),
                          Date(stoi(receiving_day), stoi(receiving_month), stoi(receiving_year)),
                          stoi(price),
                          stoi(origin),
                          stoi(destination),
                          stoi(id),
                          (bool)stoi(premium),
                          sender,
                          recipient);
    }
    db.close();
    return parcels;
}

void History_db::save_data(int weight, int volume, Date sending_date, Date receiving_date, int price, int origin, int destination, bool premium, string sender, string recipient) {
    string data;
    ifstream db;
    db.open(HISTORY_DB, ios::in);


    int n;
    string part;
    db>>n;
    n++;

    while (getline(db, part)) {
        data+=part+'\n';
    }
    data += to_string(weight)+'\n'+to_string(volume)+'\n'+to_string(sending_date.get_day())+'\n'+to_string(sending_date.get_month())+'\n'+to_string(sending_date.get_year())+'\n'+to_string(receiving_date.get_day())+'\n'+to_string(receiving_date.get_month())+'\n'+to_string(receiving_date.get_year())+'\n'+to_string(price)+'\n'+to_string(origin)+'\n'+to_string(destination)+'\n'+to_string(n)+'\n'+to_string(premium)+'\n'+sender+'\n'+recipient+'\n';
    db.close();

    ofstream onfile;
    onfile.open(HISTORY_DB);
    onfile<<n;
    onfile<<data;
    onfile.close();
}

