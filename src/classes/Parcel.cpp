#include "../../headers/Parcel.h"
#include "../../headers/Date.h"
#include <iostream>
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

Parcel::Parcel(int weight, int volume,const Date &sending_date, const Date &receiving_date, int price, int origin, int destination, int id, bool premium, string &sender, string &recipient){
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
    this->recipient = recipient;
}

Parcel::Parcel(const Parcel &parcel){
    this->weight = parcel.weight;
    this->volume = parcel.volume;
    this->sending_date = parcel.sending_date;
    this->receiving_date = parcel.receiving_date;
    this->price = parcel.price;
    this->origin= parcel.origin;
    this->destination = parcel.destination;
    this->id = parcel.id;
    this->premium = parcel.premium;
    this->sender= parcel.sender;
    this->recipient = parcel.recipient;
}


int Parcel::get_weight() const {return weight;}
int Parcel::get_volume() const {return volume;}
Date Parcel::get_sending_date() const {return sending_date;}
Date Parcel::get_receiving_date() const {return receiving_date;}
int Parcel::get_price() const {return price;}
int Parcel::get_origin() const {return origin;}
int Parcel::get_destination() const {return destination;}
int Parcel::get_id() const {return id;}
bool Parcel::get_premium() const {return premium;}
string Parcel::get_sender() const {return sender;}
string Parcel::get_recipient() const {return recipient;}

int Parcel::set_weight(int new_weight){this->weight =new_weight; return this->weight;}
int Parcel::set_volume(int new_volume){this->volume=new_volume; return this->volume;}
Date Parcel::set_sending_date(Date &new_sending_date){this->sending_date=new_sending_date; return this->sending_date;}
Date Parcel::set_receiving_date(Date &new_receiving_date){this->receiving_date=new_receiving_date; return this->receiving_date;}
int Parcel::set_price(int new_price){this->price=new_price; return this->price;}
int Parcel::set_origin(int new_origin){this->origin=new_origin; return this->origin;}
int Parcel::set_destination(int new_destination){this->destination=new_destination; return this->destination;}
int Parcel::set_id(int new_id){this->id=new_id; return this->id;}
bool Parcel::set_premium(bool new_premium){this->premium=new_premium; return this->premium;}
string Parcel::set_sender(string &new_sender){this->sender=new_sender; return this->sender;}
string Parcel::set_recipient(string &new_recipient){this->recipient=new_recipient; return this->recipient;}

void Parcel::print(){
    cout<<"Parcel #"<<this->id<<endl;
    cout<<"sender: "<<this->sender<<endl;
    cout<<"recipient: "<<this->recipient<<endl;
    cout<<"origin: "<<this->origin<<endl;
    cout<<"destination: "<<this->destination<<endl;
    cout<<"price: "<<this->price<<endl;
    cout<<"premium: "<<this->premium<<endl;
    cout<<"sending date: ";
    this->sending_date.print();
    cout<<"receiving date: ";
    this->receiving_date.print();
    cout<<"weight: "<<this->weight<<endl;
    cout<<"volume: "<<this->volume<<endl;
    cout<<endl;
}

Parcel Parcel:: operator + (const Parcel& c) {
    Parcel t(*this);
    t.weight = t.weight + c.weight;
    t.volume = t.volume + c.volume;
    t.price = t.price + c.price;
    return t;
}
int Parcel:: operator < (const Parcel& c) {   //за ціною
    return (price<c.price);
}
int Parcel:: operator > (const Parcel& c) {   //за  ціною
    return (price > c.price) ;
}
int Parcel:: operator == (const Parcel& c) {           //за вагою,об'ємом, ціною, початковим та кінцевим відділенням
    int k = ((weight == c.weight) && (volume == c.volume) && (price == c.price) && (origin == c.origin) && (destination == c.destination));
    return k;
}
int Parcel:: operator != (const Parcel& c) {
    return !(*this==c);
}
Parcel& Parcel:: operator = (const Parcel& c) {
    if (this != &c) {
        weight = c.weight;
        volume = c.volume;
        price = c.price;
        origin = c.origin;
        destination = c.destination;
        id = c.id;
        premium = c.premium;
        sender = c.sender;
        recipient = c.recipient;
        sending_date = c.sending_date;
        receiving_date = c.receiving_date;
    }return *this;
}

