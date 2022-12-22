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
    Parcel(int weight, int volume, const Date &sending_date, const Date &receiving_date, int price, int origin, int destination, int id, bool premium, string &sender, string &recipient);
    Parcel(const Parcel &parcel);
    ~Parcel()=default;

    int get_weight() const;
    int get_volume() const;
    Date get_sending_date() const;
    Date get_receiving_date() const;
    int get_price() const;
    int get_origin() const;
    int get_destination() const;
    int get_id() const;
    bool get_premium() const;
    string get_sender() const;
    string get_recipient() const;

    int set_weight(int new_weight);
    int set_volume(int new_volume);
    Date set_sending_date(Date &new_sending_date);
    Date set_receiving_date(Date &new_receiving_date);
    int set_price(int new_price);
    int set_origin(int new_origin);
    int set_destination(int new_destination);
    int set_id(int new_id);
    bool set_premium(bool new_premium);
    string set_sender(string &new_sender);
    string set_recipient(string &new_recipient);

    void print();

    Parcel operator + (const Parcel&);
    int operator < (const Parcel&);
    int operator > (const Parcel&);
    int operator == (const Parcel&);
    int operator != (const Parcel&);
    Parcel& operator = (const Parcel&);

};