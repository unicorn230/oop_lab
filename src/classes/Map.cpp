#include "../../headers/Map.h"
#include "../dbHandlers/db_handlers.h"
#include <iostream>

using namespace std;

Map::Map(){
    Map_db db=Map_db();
    number_of_deps = db.read_number();
    map=db.read_data();
}

Map::Map(int number, const connection* new_map){
    this->number_of_deps = number;
    for(int i=0; i<number; i++){
        this->map[i]=new_map[i];
    }
}

Map::Map(const Map &new_map){
    this->number_of_deps = new_map.number_of_deps;
    for(int i=0; i<new_map.number_of_deps; i++){
        this->map[i]=new_map.map[i];
    }
}

Map::~Map(){
    delete[] map;
}


int Map::get_number_of_deps() const {return this->number_of_deps;}
connection *Map::get_map() const{return this->map;}

int Map::set_number_of_deps(int n){this->number_of_deps =n; return this->number_of_deps;}
connection* Map::set_map(connection *new_map){this->map=new_map; return this->map;}


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

            if(map[counter].car/pars.get_final_speed(CAR, premium) <= map[counter].plane/pars.get_final_speed(PLANE, premium) &
               map[counter].car/pars.get_final_speed(CAR, premium) <= map[counter].ship/pars.get_final_speed(SHIP, premium) &
               map[counter].car/pars.get_final_speed(CAR, premium) <= map[counter].train/pars.get_final_speed(TRAIN, premium) &
               map[counter].car/pars.get_final_speed(CAR, premium) !=0){
                graph[i][j]=map[counter].car/pars.get_final_speed(CAR, premium);
                con_graph[i][j]=CAR;
            }else if(map[counter].plane/pars.get_final_speed(PLANE, premium) <= map[counter].car/pars.get_final_speed(CAR, premium) &
                     map[counter].plane/pars.get_final_speed(PLANE, premium) <= map[counter].ship/pars.get_final_speed(SHIP, premium) &
                     map[counter].plane/pars.get_final_speed(PLANE, premium) <= map[counter].train/pars.get_final_speed(TRAIN, premium) &
                     map[counter].plane/pars.get_final_speed(PLANE, premium) !=0){
                graph[i][j]=map[counter].plane/pars.get_final_speed(PLANE, premium);
                con_graph[i][j]=PLANE;
            }else if(map[counter].ship/pars.get_final_speed(SHIP, premium) <= map[counter].car/pars.get_final_speed(CAR, premium) &
                     map[counter].ship/pars.get_final_speed(SHIP, premium) <= map[counter].plane/pars.get_final_speed(PLANE, premium) &
                     map[counter].ship/pars.get_final_speed(SHIP, premium) <= map[counter].train/pars.get_final_speed(TRAIN, premium) &
                     map[counter].ship/pars.get_final_speed(SHIP, premium) !=0){
                graph[i][j]=map[counter].ship/pars.get_final_speed(SHIP, premium);
                con_graph[i][j]=SHIP;
            }else if(graph[i][j]=map[counter].train/pars.get_final_speed(TRAIN, premium) != 0){
                graph[i][j]=map[counter].train/pars.get_final_speed(TRAIN, premium);
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

            if(map[counter].car*pars.get_final_cost(CAR, premium) <= map[counter].plane*pars.get_final_cost(PLANE, premium) &
               map[counter].car*pars.get_final_cost(CAR, premium) <= map[counter].ship*pars.get_final_cost(SHIP, premium) &
               map[counter].car*pars.get_final_cost(CAR, premium) <= map[counter].train*pars.get_final_cost(TRAIN, premium)&
               map[counter].car*pars.get_final_cost(CAR, premium)!=0){
                graph[i][j]=map[counter].car*pars.get_final_cost(CAR, premium);
                con_graph[i][j]=CAR;
            }else if(map[counter].plane*pars.get_final_cost(PLANE, premium) <= map[counter].car*pars.get_final_cost(CAR, premium) &
                     map[counter].plane*pars.get_final_cost(PLANE, premium) <= map[counter].ship*pars.get_final_cost(SHIP, premium) &
                     map[counter].plane*pars.get_final_cost(PLANE, premium) <= map[counter].train*pars.get_final_cost(TRAIN, premium)&
                     map[counter].plane*pars.get_final_cost(PLANE, premium)!=0){
                graph[i][j]=map[counter].plane*pars.get_final_cost(PLANE, premium);
                con_graph[i][j]=PLANE;
            }else if(map[counter].ship*pars.get_final_cost(SHIP, premium) <= map[counter].car*pars.get_final_cost(CAR, premium) &
                     map[counter].ship*pars.get_final_cost(SHIP, premium) <= map[counter].plane*pars.get_final_cost(PLANE, premium) &
                     map[counter].ship*pars.get_final_cost(SHIP, premium) <= map[counter].train*pars.get_final_cost(TRAIN, premium)&
                     map[counter].ship*pars.get_final_cost(SHIP, premium)!=0){
                graph[i][j]=map[counter].ship*pars.get_final_cost(SHIP, premium);
                con_graph[i][j]=SHIP;
            }else if(map[counter].train*pars.get_final_cost(TRAIN, premium)!=0){
                graph[i][j]=map[counter].train*pars.get_final_cost(TRAIN, premium);
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

void Map::print(){
   int count=0;
   for(int i=0; i<number_of_deps; i++){
       for(int j=0; j<number_of_deps; j++){
            cout<<map[count].plane<<','<<map[count].ship<<','<<map[count].train<<','<<map[count].car<<" ";
            count++;
       }
       cout<<endl;
   }
}