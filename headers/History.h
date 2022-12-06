#pragma once
#include "./Parcel.h"


class History{
    int parcels_number;
    Parcel *parcels_history;
public:
    History();
    int get_parcels_number(){return parcels_number;}
    Parcel *get_parcels_history(){return parcels_history;}
    void set_parcels_number(int n){this->parcels_number=n;}
    void set_parcels_number(Parcel *parcels_history){this->parcels_history=parcels_history;}

};