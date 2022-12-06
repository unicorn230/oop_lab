#pragma once
#include "./DTOs.h"

class Parameters{
    connection speed;
    connection cost;
    connection premium_speed_coef;
    connection premium_cost_coef;
    double volume_cost_coef;
    double weight_cost_coef;
public:
    Parameters(){
        volume_cost_coef=0.1;
        weight_cost_coef=0.1;
        speed = connection{1,4,3,2};
        cost = connection{4,2,1,3};
        premium_speed_coef = connection{1,1,1,1};
        premium_cost_coef = connection{0.7,0.8,1,1};
    }
    Parameters(connection speed, connection cost, connection premiun_speed, connection premium_cost, double volume_cost, double weight_cost);
    double get_speed(int type, bool premium);
    double get_cost(int type, bool premium);
    void set_speed(connection speed){this->speed=speed;}
    void set_cost(connection cost){this->cost=cost;}

};