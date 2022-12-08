#include "../../headers/Parameters.h"
#include <iostream>

using namespace std;

Parameters::Parameters():speed({1,1,1,1}), cost({1,1,1,1}),premium_speed_coef({0.1,0.1,0.1,0.1}), premium_cost_coef({0.1,0.1,0.1,0.1}), volume_cost_coef({0.1,0.1,0.1,0.1}), weight_cost_coef({0.1,0.1,0.1,0.1}){}

Parameters::Parameters(connection speed, connection cost, connection premium_speed, connection premium_cost, connection volume_cost, connection weight_cost):
speed(speed), cost(cost), premium_speed_coef(premium_speed), premium_cost_coef(premium_cost), volume_cost_coef(volume_cost), weight_cost_coef(weight_cost){}

Parameters::Parameters(const Parameters &pars):
speed(pars.speed), cost(pars.cost), premium_cost_coef(pars.premium_cost_coef), premium_speed_coef(pars.premium_speed_coef), volume_cost_coef(pars.volume_cost_coef),weight_cost_coef(pars.weight_cost_coef){}


double Parameters::get_final_cost (int type, bool premium) const{
    if(premium) {
        switch (type) {
            case 0: return cost.plane * this->premium_cost_coef.plane * this->volume_cost_coef.plane * this->weight_cost_coef.plane;
            case 1: return cost.ship * this->premium_cost_coef.ship * this->volume_cost_coef.ship * this->weight_cost_coef.ship;
            case 2: return cost.train * this->premium_cost_coef.train * this->volume_cost_coef.train * this->weight_cost_coef.train;
            case 3: return cost.car * this->premium_cost_coef.car * this->volume_cost_coef.car * this->weight_cost_coef.car;
            default: return 0;
        }
    }else{
        switch (type) {
            case 0:return cost.plane * this->volume_cost_coef.plane * this->weight_cost_coef.plane;
            case 1:return cost.ship * this->volume_cost_coef.ship * this->weight_cost_coef.ship;
            case 2:return cost.train * this->volume_cost_coef.train * this->weight_cost_coef.train;
            case 3:return cost.car* this->volume_cost_coef.car * this->weight_cost_coef.car;
            default:return 0;
        }
    }
}
double Parameters::get_final_speed (int type, bool premium) const{
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

connection Parameters::get_speed() const{return this->speed;}
connection Parameters::get_cost() const{return this->cost;}
connection Parameters::get_premium_speed_coef() const{return this->premium_speed_coef;}
connection Parameters::get_premium_cost_coef() const{return this->premium_cost_coef;}
connection Parameters::get_volume_cost_coef() const{return this->volume_cost_coef;}
connection Parameters::get_weight_cost_coef() const{return this->weight_cost_coef;}

connection Parameters::set_speed(connection new_speed){this->speed=new_speed; return this->speed;}
connection Parameters::set_cost(connection new_cost){this->cost=new_cost; return this->cost;}
connection Parameters::set_premium_speed(connection new_premium_speed){this->premium_speed_coef = new_premium_speed; return this->premium_speed_coef;}
connection Parameters::set_premium_cost(connection new_premium_cost){this->premium_cost_coef=new_premium_cost; return this->premium_cost_coef;}
connection Parameters::set_volume_cost(connection new_volume_cost){this->volume_cost_coef=new_volume_cost; return this->volume_cost_coef;}
connection Parameters::set_weight_cost(connection new_weight_cost){this->weight_cost_coef=new_weight_cost; return this->weight_cost_coef;}

void Parameters::print(){
    cout<<"speed: "<<this->speed.plane<<","<<this->speed.ship<<","<<this->speed.train<<","<<this->speed.car<<endl;
}