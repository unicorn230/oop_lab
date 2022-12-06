#include "../../headers/Map.h"
#include "../../headers/DTOs.h"
#include "../../headers/Parameters.h"
#include "../dbHandlers/db_handlers.h"


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