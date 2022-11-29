#include "./classes.h"
#include "../dbHandlers/db_handlers.h"
#include <iostream>
#include <cstring>

using namespace std;

int Parameters::get_cost(int type){
    switch(type){
        case 0: return cost.plane;
        case 1: return cost.ship;
        case 2: return cost.train;
        case 3: return cost.car;
        default: return speed.train;
    }
}

int Parameters::get_speed(int type){
    switch(type){
        case 0: return speed.plane;
        case 1: return speed.ship;
        case 2: return speed.train;
        case 3: return speed.car;
        default: return speed.train;
    }
}

Map::Map(){
    number_of_deps = read_map_number();
    map=read_map();
}

path *Map::find_fastest_path(int origin, int destination, Parameters pars) {

    double graph[number_of_deps][number_of_deps], d[number_of_deps], temp, minimun;
    int v[number_of_deps], min_index, begin_index=origin-1;
    Connections con_graph[number_of_deps][number_of_deps];

    int counter=0;
    for(int i=0; i<number_of_deps; i++){
        for(int j=0; j<number_of_deps; j++){

            if(map[counter].car/pars.get_speed(CAR) <= map[counter].plane/pars.get_speed(PLANE) &
               map[counter].car/pars.get_speed(CAR) <= map[counter].ship/pars.get_speed(SHIP) &
               map[counter].car/pars.get_speed(CAR) <= map[counter].train/pars.get_speed(TRAIN) &
               map[counter].car/pars.get_speed(CAR) !=0){
                graph[i][j]=map[counter].car/pars.get_speed(CAR);
                con_graph[i][j]=CAR;
            }else if(map[counter].plane/pars.get_speed(PLANE) <= map[counter].car/pars.get_speed(CAR) &
                     map[counter].plane/pars.get_speed(PLANE) <= map[counter].ship/pars.get_speed(SHIP) &
                     map[counter].plane/pars.get_speed(PLANE) <= map[counter].train/pars.get_speed(TRAIN) &
                     map[counter].plane/pars.get_speed(PLANE) !=0){
                graph[i][j]=map[counter].plane/pars.get_speed(PLANE);
                con_graph[i][j]=PLANE;
            }else if(map[counter].ship/pars.get_speed(SHIP) <= map[counter].car/pars.get_speed(CAR) &
                     map[counter].ship/pars.get_speed(SHIP) <= map[counter].plane/pars.get_speed(PLANE) &
                     map[counter].ship/pars.get_speed(SHIP) <= map[counter].train/pars.get_speed(TRAIN) &
                     map[counter].ship/pars.get_speed(SHIP) !=0){
                graph[i][j]=map[counter].ship/pars.get_speed(SHIP);
                con_graph[i][j]=SHIP;
            }else if(graph[i][j]=map[counter].train/pars.get_speed(TRAIN) !=0){
                graph[i][j]=map[counter].train/pars.get_speed(TRAIN);
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

    path *shortest= new path[k-1];

    for (int i = k - 1; i >= 0; i--) {
        if (i == k - 1) shortest[0] = {0, ver[k - 1] - 1, con_graph[0][ver[k - 1] - 1]};
        else shortest[k - 1 - i] = {ver[k - 1 - i] - 1, con_graph[0][ver[k - 1] - 1]};
    }
    return shortest;
}

path *Map::find_cheapest_path(int origin, int destination, Parameters pars) {

    int graph[number_of_deps][number_of_deps], d[number_of_deps], temp, minimun;
    int v[number_of_deps], min_index, begin_index=origin-1;
    Connections con_graph[number_of_deps][number_of_deps];

    int counter=0;
    for(int i=0; i<number_of_deps; i++){
        for(int j=0; j<number_of_deps; j++){

            if(map[counter].car*pars.get_cost(CAR) <= map[counter].plane*pars.get_cost(PLANE) &
               map[counter].car*pars.get_cost(CAR) <= map[counter].ship*pars.get_cost(SHIP) &
               map[counter].car*pars.get_cost(CAR) <= map[counter].train*pars.get_cost(TRAIN)&
               map[counter].car*pars.get_cost(CAR)!=0){
                graph[i][j]=map[counter].car*pars.get_cost(CAR);
                con_graph[i][j]=CAR;
            }else if(map[counter].plane*pars.get_cost(PLANE) <= map[counter].car*pars.get_cost(CAR) &
                     map[counter].plane*pars.get_cost(PLANE) <= map[counter].ship*pars.get_cost(SHIP) &
                     map[counter].plane*pars.get_cost(PLANE) <= map[counter].train*pars.get_cost(TRAIN)&
                     map[counter].plane*pars.get_cost(PLANE)!=0){
                graph[i][j]=map[counter].plane*pars.get_cost(PLANE);
                con_graph[i][j]=PLANE;
            }else if(map[counter].ship*pars.get_cost(SHIP) <= map[counter].car*pars.get_cost(CAR) &
                     map[counter].ship*pars.get_cost(SHIP) <= map[counter].plane*pars.get_cost(PLANE) &
                     map[counter].ship*pars.get_cost(SHIP) <= map[counter].train*pars.get_cost(TRAIN)&
                     map[counter].ship*pars.get_cost(SHIP)!=0){
                graph[i][j]=map[counter].ship*pars.get_cost(SHIP);
                con_graph[i][j]=SHIP;
            }else if(map[counter].train*pars.get_cost(TRAIN)!=0){
                graph[i][j]=map[counter].train*pars.get_cost(TRAIN);
                con_graph[i][j]=TRAIN;
            }else {
                graph[i][j]=1000000000;
                con_graph[i][j]=CAR;
            }
            counter++;
        }
    }

//    for (int i = 0; i<number_of_deps; i++)
//    {
//        for (int j = 0; j<number_of_deps; j++)
//            cout<<graph[i][j]<<" ";
//        cout<<endl;
//    }

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

    path *cheapest= new path[k-1];

    for (int i = k - 1; i >= 0; i--) {
        if (i == k - 1) cheapest[0] = {0, ver[k - 1] - 1, con_graph[0][ver[k - 1] - 1]};
        else cheapest[k - 1 - i] = {ver[k - 1 - i] - 1, con_graph[0][ver[k - 1] - 1]};
    }
    return cheapest;

}
Date::Date(){day=0;month=0;year=0;}

Date::Date(int d, int m, int y) {
    this->day =d;
    this->month = month;
    this->year = year;
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
}

void Calculator::add_parcel(int weight, int volume, Date sending_date, Date receiving_date, int price, int origin, int destination, bool premium, string sender, string recepient) {
    add_parcel(weight, volume, sending_date, receiving_date, price, origin, destination, premium, sender, recepient);
    history = History();
}