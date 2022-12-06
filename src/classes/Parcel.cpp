#include "../../headers/Parcel.h"
#include "../../headers/Date.h"
#include <string>

using namespace std;

Parcel::Parcel(){
    this->weight = 0;
    this->volume = 0;
    this->sending_date = Date();
    this->receiving_date = Date();
    this->price = 0;
    this->origin=0;
    this->destination = 0;
    this->id = 0;
    this->premium = 0;
    this->sender = "";
    this->recipient = "";
}

Parcel::Parcel(int weight, int volume, Date sending_date, Date receiving_date, int price, int origin, int destination, int id, bool premium, string sender, string recepient){
    this->weight = weight;
    this->volume = volume;
    this->sending_date = sending_date;
    this->receiving_date = receiving_date;
    this->price = price;
    this->origin=origin;
    this->destination = destination;
    this->id = id;
    this->premium = premium;
    this->sender=sender;
    this->recipient = recepient;
}