#include "../../headers/Calculator.h"
#include "../../headers/History.h"
#include "../../headers/Map.h"
#include "../../headers/Parameters.h"
#include "../../headers/DTOs.h"
#include "../../headers/Date.h"
#include "../dbHandlers/db_handlers.h"
#include <vector>
#include <string>
#include <math.h>

using namespace std;

Calculator::Calculator() {
    this->history = History();
    this->map = Map();
    this->pars = Parameters();
}


Calculator::Calculator(connection speed, connection cost, connection premiun_speed, connection premium_cost, double volume_cost, double weight_cost) {
    this->history = History();
    this->map = Map();
    this->pars= Parameters(speed, cost,premiun_speed, premium_cost, volume_cost, weight_cost);
}

void Calculator::add_parcel(int weight, int volume, int origin, int destination, bool premium, string sender, string recepient, type type) {
    time_t now = time(0);
    tm *ltm = localtime(&now);

    int days = ceil(calculate_time(find_path(type, origin, destination, premium), premium));
    int price = ceil(calculate_cost(find_path(type, origin, destination, premium), premium));

    save_parcel(weight, volume, Date{ltm->tm_mday, ltm->tm_mon, ltm->tm_year}, Date{(ltm->tm_mday+days)%30, (int)(ltm->tm_mon+floor(days/30)), ltm->tm_year}, price, origin, destination, premium, sender, recepient);
    history = History();
}

vector <path> Calculator::find_path(type type, int origin, int destination, bool premium){
    if(type == 0) return this->map.find_fastest_path(origin, destination, this->pars, premium);
    if(type == 1) return this->map.find_cheapest_path(origin, destination, this->pars, premium);
}


double Calculator::calculate_cost(vector<path> path, bool premium) {

    double sum=0;
    for(int i=0; i<path.size(); i++){
        double path_weight = this->map.get_specific_weight(path[i].origin, path[i].destination, path[i].type_of_connection);
        sum+=path_weight*this->pars.get_cost(path[i].type_of_connection, premium);
    }
    return sum;
}

double Calculator::calculate_time(vector<path> path, bool premium) {

    double time=0;
    for(int i=0; i<path.size(); i++){
        double path_weight = this->map.get_specific_weight(path[i].origin, path[i].destination, path[i].type_of_connection);
        time+=path_weight/this->pars.get_speed(path[i].type_of_connection, premium);
    }
    return time;
}
