#pragma once
#include <iostream>

using namespace std;

class Date{
    int day;
    int month;
    int year;
public:
    Date();
    Date(int d, int m, int y);
    Date(const Date &date);
    ~Date() = default;

    int get_day() const;
    int get_month() const;
    int get_year() const;

    int set_day(int d);
    int set_month(int m);
    int set_year(int y);

    void print();

    Date operator ++ (int);
    Date& operator ++();
    Date operator -- (int);
    Date& operator --();
    Date& operator = (const Date&);
    friend ostream& operator <<(ostream&,const Date&);
    friend istream& operator >>(istream&, Date&);

};