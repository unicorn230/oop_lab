#pragma once
#include "./Parcel.h"


class History{
    int parcels_number;
    Parcel *parcels_history;
public:
    History();
    History(const History &history);
    History(int);
    History(int number, Parcel *parcels);
    ~History();


    int get_parcels_number ()const;
    Parcel *get_parcels_history ()const;
    int set_parcels_number(int n);
    Parcel* set_parcels_number(Parcel *new_parcels_history);

    void print();

    void update();

    Parcel& operator [] (int);

};