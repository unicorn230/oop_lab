#pragma once

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