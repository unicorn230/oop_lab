#pragma once
#include "./Date.h"
#include <string>

using namespace std;

class Parcel{
    int weight;
    int volume;
    Date sending_date;
    Date receiving_date;
    int price;
    int origin;
    int destination;
    int id;
    bool premium;
    string sender;
    string recipient;
public:
    Parcel();
    Parcel(int weight, int volume, Date sending_date, Date receiving_date, int price, int origin, int destination, int id, bool premium, string sender, string recepient);
    int get_weight(){return weight;}
    int get_volume(){return volume;}
    Date get_sending_date(){return sending_date;}
    Date get_receiving_date(){return receiving_date;}
    int get_price(){return price;}
    int get_origin(){return origin;}
    int get_destination(){return destination;}
    int get_id(){return id;}
    bool get_premium(){return premium;}
    string get_sender(){return sender;}
    string get_recipient(){return recipient;}
    void set_weight(int weight){this->weight =weight;}
    void set_volume(int volume){this->volume=volume;}
    void set_sending_date(Date sending_date){this->sending_date=sending_date;}
    void set_receiving_date(Date receiving_date){this->receiving_date=receiving_date;}
    void set_price(int price){this->price=price;}
    void set_origin(int origin){this->origin=origin;}
    void set_destination(int destination){this->destination=destination;}
    void set_id(int id){this->id=id;}
    void set_premium(bool premium){this->premium=premium;}
    void set_sender(string sender){this->sender=sender;}
    void set_recipient(string recipient){this->recipient=recipient;}


};