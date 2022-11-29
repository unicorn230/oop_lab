#pragma once
#include <string>

using namespace std;

class Date{
    int day;
    int month;
    int year;
public:
    Date();
    Date(int d, int m, int y);
    int get_day(){return day;}
    int get_month(){return month;}
    int get_year(){return year;}
    void set_day(int d){this->day=d;}
    void set_month(int m){this->month=m;}
    void set_year(int y){this->year=y;}

};


struct connection{
    double plane;
    double ship;
    double train;
    double car;
};

enum Connections{
    PLANE,
    SHIP,
    TRAIN,
    CAR
};

struct path{
    int origin;
    int destination;
    Connections type_of_connection;
};


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

class Parameters{
    connection speed;
    connection cost;
public:
    Parameters(){
        speed = connection{1,2,3,4};
        cost = connection{1,2,3,4};
    }
    int get_speed(int type);
    int get_cost(int type);
    void set_speed(connection speed){this->speed=speed;}
    void set_cost(connection cost){this->cost=cost;}

};

class Events{

};

class Map{
    int number_of_deps;
    connection *map;
public:
    Map();
    int get_number_of_deps(){return number_of_deps;}
    connection *get_map(){return map;}
    void set_number_of_deps(int n){this->number_of_deps =n;}
    void set_mpa(connection *map){this->map=map;}
    path * find_fastest_path(int o, int d, Parameters pars);
    path * find_cheapest_path(int o, int d, Parameters pars);
};

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
class Calculator{
    History history;
public:
    Calculator();
    History get_history(){return history;}
    void set_history(History history){this->history = history;}
    void add_parcel(int weight, int volume, Date sending_date, Date receiving_date, int price, int origin, int destination, bool premium, string sender, string recepient);
    void list_parcels();
    void find_path(int type, Parcel parcel);
};

