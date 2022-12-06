#include "../../headers/Parameters.h"


Parameters::Parameters(connection speed, connection cost, connection premiun_speed, connection premium_cost, double volume_cost, double weight_cost) {
    this->speed=speed;
    this->cost=cost;
    this->premium_speed_coef=premiun_speed;
    this->premium_cost_coef=premium_cost;
    this->volume_cost_coef=volume_cost;
    this->weight_cost_coef=weight_cost;
}

double Parameters::get_cost(int type, bool premium){
    if(premium) {
        switch (type) {
            case 0: return cost.plane * this->premium_cost_coef.plane * this->volume_cost_coef * this->weight_cost_coef;
            case 1: return cost.ship * this->premium_cost_coef.ship * this->volume_cost_coef * this->weight_cost_coef;
            case 2: return cost.train * this->premium_cost_coef.train * this->volume_cost_coef * this->weight_cost_coef;
            case 3: return cost.car * this->premium_cost_coef.car * this->volume_cost_coef * this->weight_cost_coef;
            default: return 0;
        }
    }else{
        switch (type) {
            case 0:return cost.plane * this->volume_cost_coef * this->weight_cost_coef;
            case 1:return cost.ship * this->volume_cost_coef * this->weight_cost_coef;
            case 2:return cost.train * this->volume_cost_coef * this->weight_cost_coef;
            case 3:return cost.car* this->volume_cost_coef * this->weight_cost_coef;
            default:return 0;
        }
    }
}

double Parameters::get_speed(int type, bool premium){
    if(premium){
        switch(type){
            case 0: return speed.plane*this->premium_speed_coef.plane;
            case 1: return speed.ship*this->premium_speed_coef.ship;
            case 2: return speed.train*this->premium_speed_coef.train;
            case 3: return speed.car*this->premium_speed_coef.car;
            default: return 0;
        }
    }else{
        switch(type){
            case 0: return speed.plane;
            case 1: return speed.ship;
            case 2: return speed.train;
            case 3: return speed.car;
            default: return 0;
        }
    }
}
