#pragma once
#include "../../headers/Parcel.h"
#include "../../headers/DTOs.h"


template <typename T> class Db{
public:
    virtual int read_number();
    virtual T* read_data();
    virtual void get_type();

};

class Map_db :Db<connection>{
public:
    Map_db()=default;
    int read_number() override;
    connection* read_data() override;
    void get_type(){cout<<"Map"<<endl;}
};

class History_db :Db<Parcel>{
public:
    History_db()=default;
    int read_number() override;
    Parcel* read_data() override;
    void save_data(int weight, int volume, Date sending_date, Date receiving_date, int price, int origin, int destination, bool premium, string sender, string recipient);
    void get_type(){cout<<"History"<<endl;}


};


//int read_map_number();
//int read_parcels_number();
//
//connection* read_map();
//
//Parcel* read_parcels();
//
//void save_parcel(int weight, int volume, Date &sending_date, Date &receiving_date, int price, int origin, int destination, bool premium, string &sender, string &recipient);