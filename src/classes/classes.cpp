#include "./classes.h"
#include "../dbHandlers/db_handlers.h"
#include <iostream>
#include <cstring>
#include <vector>
#include <math.h>
#include <ctime>


using namespace std;

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

Date::Date(int d, int m, int y) {
    this->day =d;
    this->month = m;
    this->year = y;
}

Date::Date(){day=0;month=0;year=0;}

Map::Map(){
    number_of_deps = read_map_number();
    map=read_map();
}

double Map::get_specific_weight(int i, int j, int type) {
    switch(type){
        case 0: return map[i+j].plane;
        case 1: return map[i+j].ship;
        case 2: return map[i+j].train;
        case 3: return map[i+j].car;
        default: return 0;
    }
}

vector <path> Map::find_fastest_path(int origin, int destination, Parameters pars, bool premium) {

    double **graph= new double*[number_of_deps];
    for(int i = 0; i < number_of_deps; ++i)
        graph[i] = new double[number_of_deps];

    double d[number_of_deps];
    double temp, minimun;
    int v[number_of_deps], min_index, begin_index=origin-1;
    Connections con_graph[number_of_deps][number_of_deps];

    int counter=0;
    for(int i=0; i<number_of_deps; i++){
        for(int j=0; j<number_of_deps; j++){

            if(map[counter].car/pars.get_speed(CAR, premium) <= map[counter].plane/pars.get_speed(PLANE, premium) &
               map[counter].car/pars.get_speed(CAR, premium) <= map[counter].ship/pars.get_speed(SHIP, premium) &
               map[counter].car/pars.get_speed(CAR, premium) <= map[counter].train/pars.get_speed(TRAIN, premium) &
               map[counter].car/pars.get_speed(CAR, premium) !=0){
                graph[i][j]=map[counter].car/pars.get_speed(CAR, premium);
                con_graph[i][j]=CAR;
            }else if(map[counter].plane/pars.get_speed(PLANE, premium) <= map[counter].car/pars.get_speed(CAR, premium) &
                     map[counter].plane/pars.get_speed(PLANE, premium) <= map[counter].ship/pars.get_speed(SHIP, premium) &
                     map[counter].plane/pars.get_speed(PLANE, premium) <= map[counter].train/pars.get_speed(TRAIN, premium) &
                     map[counter].plane/pars.get_speed(PLANE, premium) !=0){
                graph[i][j]=map[counter].plane/pars.get_speed(PLANE, premium);
                con_graph[i][j]=PLANE;
            }else if(map[counter].ship/pars.get_speed(SHIP, premium) <= map[counter].car/pars.get_speed(CAR, premium) &
                     map[counter].ship/pars.get_speed(SHIP, premium) <= map[counter].plane/pars.get_speed(PLANE, premium) &
                     map[counter].ship/pars.get_speed(SHIP, premium) <= map[counter].train/pars.get_speed(TRAIN, premium) &
                     map[counter].ship/pars.get_speed(SHIP, premium) !=0){
                graph[i][j]=map[counter].ship/pars.get_speed(SHIP, premium);
                con_graph[i][j]=SHIP;
            }else if(graph[i][j]=map[counter].train/pars.get_speed(TRAIN, premium) !=0){
                graph[i][j]=map[counter].train/pars.get_speed(TRAIN, premium);
                con_graph[i][j]=TRAIN;
            }else{
                graph[i][j]=1000000000;
                con_graph[i][j]=CAR;
            }
            counter++;
        }
    }

    for (int i = 0; i<number_of_deps; i++)
    {
        d[i] = 1000000000;
        v[i] = 1;
    }
    d[begin_index]=0;

    do {
        min_index = 1000000000;
        minimun = 1000000000;
        for (int i = 0; i<number_of_deps; i++){
            if ((v[i] == 1) && (d[i]<minimun)){
                minimun = d[i];
                min_index = i;
            }
        }
        if (min_index != 1000000000)
        {
            for (int i = 0; i<number_of_deps; i++)
            {
                if (graph[min_index][i] > 0)
                {
                    temp = minimun + graph[min_index][i];
                    if (temp < d[i])
                    {
                        d[i] = temp;
                    }
                }
            }
            v[min_index] = 0;
        }
    } while (min_index < 1000000000);

    int ver[number_of_deps];
    int end = destination-1;
    ver[0] = end + 1;
    int k = 1;
    int weight = d[end];

    while (end != begin_index)
    {
        for (int i = 0; i<number_of_deps; i++) {
            if (graph[i][end] != 0) {
                int temp1 = weight - graph[i][end];
                if (temp1 == d[i]) {
                    weight = temp1;
                    end = i;
                    ver[k] = i + 1;
                    k++;
                }
            }
        }
    }

    vector<path> fastest;

    for (int i = k - 1; i >= 0; i--) {
        if (i == k - 1) fastest.push_back({origin, ver[k - 1] - 1, con_graph[0][ver[k - 1] - 1]});
        else fastest.push_back({ver[k - 1 - i] - 1, con_graph[0][ver[k - 1] - 1]});
    }

    for(int i = 0; i < number_of_deps; ++i) {
        delete [] graph[i];
    }
    delete [] graph;

    return fastest;
}

vector <path> Map::find_cheapest_path(int origin, int destination, Parameters pars, bool premium) {

    double **graph= new double*[number_of_deps];
    for(int i = 0; i < number_of_deps; ++i)
        graph[i] = new double[number_of_deps];

    double d[number_of_deps];
    double temp, minimun;
    int v[number_of_deps], min_index, begin_index=origin-1;
    Connections con_graph[number_of_deps][number_of_deps];

    int counter=0;
    for(int i=0; i<number_of_deps; i++){
        for(int j=0; j<number_of_deps; j++){

            if(map[counter].car*pars.get_cost(CAR, premium) <= map[counter].plane*pars.get_cost(PLANE, premium) &
               map[counter].car*pars.get_cost(CAR, premium) <= map[counter].ship*pars.get_cost(SHIP, premium) &
               map[counter].car*pars.get_cost(CAR, premium) <= map[counter].train*pars.get_cost(TRAIN, premium)&
               map[counter].car*pars.get_cost(CAR, premium)!=0){
                graph[i][j]=map[counter].car*pars.get_cost(CAR, premium);
                con_graph[i][j]=CAR;
            }else if(map[counter].plane*pars.get_cost(PLANE, premium) <= map[counter].car*pars.get_cost(CAR, premium) &
                     map[counter].plane*pars.get_cost(PLANE, premium) <= map[counter].ship*pars.get_cost(SHIP, premium) &
                     map[counter].plane*pars.get_cost(PLANE, premium) <= map[counter].train*pars.get_cost(TRAIN, premium)&
                     map[counter].plane*pars.get_cost(PLANE, premium)!=0){
                graph[i][j]=map[counter].plane*pars.get_cost(PLANE, premium);
                con_graph[i][j]=PLANE;
            }else if(map[counter].ship*pars.get_cost(SHIP, premium) <= map[counter].car*pars.get_cost(CAR, premium) &
                     map[counter].ship*pars.get_cost(SHIP, premium) <= map[counter].plane*pars.get_cost(PLANE, premium) &
                     map[counter].ship*pars.get_cost(SHIP, premium) <= map[counter].train*pars.get_cost(TRAIN, premium)&
                     map[counter].ship*pars.get_cost(SHIP, premium)!=0){
                graph[i][j]=map[counter].ship*pars.get_cost(SHIP, premium);
                con_graph[i][j]=SHIP;
            }else if(map[counter].train*pars.get_cost(TRAIN, premium)!=0){
                graph[i][j]=map[counter].train*pars.get_cost(TRAIN, premium);
                con_graph[i][j]=TRAIN;
            }else {
                graph[i][j]=1000000000;
                con_graph[i][j]=CAR;
            }
            counter++;
        }
    }

    for (int i = 0; i<number_of_deps; i++)
    {
        d[i] = 1000000000;
        v[i] = 1;
    }
    d[begin_index]=0;

    do {
        min_index = 1000000000;
        minimun = 1000000000;
        for (int i = 0; i<number_of_deps; i++){
            if ((v[i] == 1) && (d[i]<minimun)){
                minimun = d[i];
                min_index = i;
            }
        }
        if (min_index != 1000000000)
        {
            for (int i = 0; i<number_of_deps; i++)
            {
                if (graph[min_index][i] > 0)
                {
                    temp = minimun + graph[min_index][i];
                    if (temp < d[i])
                    {
                        d[i] = temp;
                    }
                }
            }
            v[min_index] = 0;
        }
    } while (min_index < 1000000000);

    int ver[number_of_deps];
    int end = destination-1;
    ver[0] = end + 1;
    int k = 1;
    int weight = d[end];

    while (end != begin_index)
    {
        for (int i = 0; i<number_of_deps; i++) {
            if (graph[i][end] != 0) {
                int temp1 = weight - graph[i][end];
                if (temp1 == d[i]) {
                    weight = temp1;
                    end = i;
                    ver[k] = i + 1;
                    k++;
                }
            }
        }
    }

    vector <path> cheapest;

    for (int i = k - 1; i >= 0; i--) {
        if (i == k - 1) cheapest.push_back({origin, ver[k - 1] - 1, con_graph[0][ver[k - 1] - 1]});
        else cheapest.push_back({ver[k - 1 - i] - 1, con_graph[0][ver[k - 1] - 1]});
    }

    for(int i = 0; i < number_of_deps; ++i) {
        delete [] graph[i];
    }
    delete [] graph;

    return cheapest;

}



Parcel::Parcel(){
    this->weight = 0;
    this->volume = 0;
    this->sending_date = Date();
    this->receiving_date = Date();
    this->price = 0;
    this->origin=0;
    this->destination = 0;
    this->id = 0;
    this->premium = 0;
    this->sender = "";
    this->recipient = "";
}

Parcel::Parcel(int weight, int volume, Date sending_date, Date receiving_date, int price, int origin, int destination, int id, bool premium, string sender, string recepient){
    this->weight = weight;
    this->volume = volume;
    this->sending_date = sending_date;
    this->receiving_date = receiving_date;
    this->price = price;
    this->origin=origin;
    this->destination = destination;
    this->id = id;
    this->premium = premium;
    this->sender=sender;
    this->recipient = recepient;
}

History::History() {
    this->parcels_number = read_parcels_number();
    this->parcels_history = read_parcels();
}

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

void Calculator::add_parcel(int weight, int volume, int origin, int destination, bool premium, string sender, string recepient, bool path_type) {
    time_t now = time(0);
    tm *ltm = localtime(&now);

    int days = ceil(calculate_time(find_path(path_type, origin, destination, premium), premium));
    int price = ceil(calculate_cost(find_path(path_type, origin, destination, premium), premium));

    save_parcel(weight, volume, Date{ltm->tm_mday, ltm->tm_mon, ltm->tm_year}, Date{(ltm->tm_mday+days)%30, (int)(ltm->tm_mon+floor(days/30)), ltm->tm_year}, price, origin, destination, premium, sender, recepient);
    history = History();
}

vector <path> Calculator::find_path(int type, int origin, int destination, bool premium){
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
