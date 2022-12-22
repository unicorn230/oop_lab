#include "../../headers/Date.h"
#include <iostream>

using namespace std;

Date::Date(int d, int m, int y) {
    this->day =d;
    this->month = m;
    this->year = y;
}

Date::Date(){day=0;month=0;year=0;}

Date::Date(const Date &date){
    this->day = date.day;
    this->month = date.month;
    this->year = date.year;
}

int Date::get_day() const {return this->day;}
int Date::get_month() const {return this->month;}
int Date::get_year() const {return this->year;}

int Date::set_day(int d){this->day=d; return this->day;}
int Date::set_month(int m){this->month=m; return this->month;}
int Date::set_year(int y){this->year=y; return this->year;}

void Date::print(){
    cout<<this->day<<"."<<this->month<<"."<< this->month<<endl;
}

Date Date:: operator ++ (int i) {
    Date t(*this);
    if (day == 31) {
        if (month == 12) { day = 1; month = 1; year++; return t; }
        day = 1; month++;
    }
    else day++;
    return t;
}
Date& Date :: operator ++ () {
    if (day == 31) {
        if (month == 12) { day = 1; month = 1; year++; return *this; }
        day = 1; month++;
    }
    else day++;
    return *this; }
Date Date:: operator -- (int i) {
    Date t(*this);
    if (day == 1) {
        if (month == 1) { day = 31; month = 12; year--; return *this; }
        day = 31; month--;
    }
    else day--;
    return t;
}
Date& Date :: operator -- () {
    if (day == 1) {
        if (month == 1) { day = 31; month = 12; year--; return *this; }
        day = 31; month--;
    }
    else day--;
    return *this; }
ostream& operator <<(ostream& out,const Date& x) {
    out << "Date:  " << x.get_day() << "." << x.get_month() <<"."<<x.get_year();
    return out;
}
istream& operator >> (istream& in, Date& x) {
    in >> x.day >> x.month >> x.year;
    return in;
}
Date& Date :: operator = (const Date& c) {
    if (this != &c) {
        day = c.day;
        month = c.month;
        year = c.year;
    }return *this;
}