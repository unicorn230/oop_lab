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
    Calculator(connection speed, connection cost, connection premium_speed, connection premium_cost, connection volume_cost_coef, connection weight_cost_coef);
    Calculator(const Calculator &calculator);
    ~Calculator()=default;

    History get_history() const;
    Map get_map() const;
    Parameters get_pars() const;

    History set_history(const History &new_history);
    Map set_map(const Map &new_map);
    Parameters set_pars(const Parameters &new_pars);


    void add_parcel(int weight, int volume,int origin, int destination, bool premium, string sender, string recipient, type type);
    vector <path> find_path(type type, int origin, int destination, bool premium);
    double calculate_cost(vector<path> path, bool premium);
    double calculate_time(vector<path> path, bool premium);
    Parcel *list_parcels();
    int get_parcels_number();


};
