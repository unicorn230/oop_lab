#pragma once
#include "./History.h"
#include "./Map.h"
#include "./Parameters.h"
#include "./DTOs.h"
#include <vector>
#include <string>

using namespace std;

class Calculator{
    History history;
    Map map;
    Parameters pars;
public:
    Calculator();
    Calculator(connection speed, connection cost, connection premiun_speed, connection premium_cost, double volume_cost_coef, double weight_cost_coef);
    History get_history(){return history;}
    void set_history(History history){this->history = history;}
    void add_parcel(int weight, int volume,int origin, int destination, bool premium, string sender, string recepient, type type);
    vector <path> find_path(type type, int origin, int destination, bool premium);
    double calculate_cost(vector<path> path, bool premium);
    double calculate_time(vector<path> path, bool premium);
};
