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