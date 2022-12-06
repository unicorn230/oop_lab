#pragma once
#include "./DTOs.h"
#include <vector>
#include "./Parameters.h"

using namespace std;

class Map{
    int number_of_deps;
    connection *map;
public:
    Map();
    int get_number_of_deps(){return number_of_deps;}
    connection *get_map(){return map;}
    double get_specific_weight(int i, int j, int type);
    void set_number_of_deps(int n){this->number_of_deps =n;}
    void set_mpa(connection *map){this->map=map;}
    vector <path> find_fastest_path(int o, int d, Parameters pars, bool premium);
    vector <path> find_cheapest_path(int o, int d, Parameters pars, bool premium);
};