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
    Map(int number, const connection* new_map);
    Map(const Map &new_map);
    ~Map();

    int get_number_of_deps() const;
    connection *get_map() const;

    int set_number_of_deps(int n);
    connection* set_map(connection *map);

    double get_specific_weight(int i, int j, int type);
    vector <path> find_fastest_path(int o, int d, Parameters pars, bool premium);
    vector <path> find_cheapest_path(int o, int d, Parameters pars, bool premium);

    void print();
};