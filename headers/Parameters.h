#pragma once
#include "./DTOs.h"

class Parameters{
    connection speed;
    connection cost;
    connection premium_speed_coef;
    connection premium_cost_coef;
    connection volume_cost_coef;
    connection weight_cost_coef;
public:
    Parameters();
    Parameters(connection speed, connection cost, connection premium_speed, connection premium_cost, connection volume_cost, connection weight_cost);
    Parameters(const Parameters &pars);
    ~Parameters()=default;

    double get_final_speed (int type, bool premium) const;
    double get_final_cost (int type, bool premium) const;


    connection get_speed() const;
    connection get_cost() const;
    connection get_premium_speed_coef() const;
    connection get_premium_cost_coef() const;
    connection get_volume_cost_coef() const;
    connection get_weight_cost_coef() const;

    connection set_speed(connection new_speed);
    connection set_cost(connection new_cost);
    connection set_premium_speed(connection new_premium_speed);
    connection set_premium_cost(connection new_premium_cost);
    connection set_volume_cost(connection new_volume_cost);
    connection set_weight_cost(connection new_weight_cost);

    void print();
};