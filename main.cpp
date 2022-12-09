#include <iostream>
#include "./src/dbHandlers/db_handlers.h"
#include <vector>
#include "./headers/Calculator.h"

using namespace std;

int main(){
    connection speed={1,4,3,2};
    connection cost={4,2,1,3};
    connection premium_speed = {1,1,1,1};
    connection premium_cost = {0.7,0.8,1,1};
    connection volume_cost ={1,1,1,1};
    connection weight_cost ={1,1,1,1};

    Calculator calc(speed, cost, premium_speed, premium_cost, volume_cost, weight_cost);

    cout<<"parcels from db"<<endl<<endl;
    Parcel *parcels = calc.list_parcels();
    for(int i=0; i<calc.get_parcels_number(); i++){
        parcels[i].print();
   }
    cout<<endl;
    cout<<"find fastest path between departments 1 and 3"<<endl;
    vector <path> f=calc.find_path(FAST, 1,3, true);
    string connections_types[4]={"plane", "ship", "train", "car"};
    for(int i=0; i<f.size(); i++){
        cout<<f.at(i).origin<<" -"<<connections_types[f.at(i).type_of_connection]<<"-> "<<f.at(i).destination<<endl;
    }
    cout<<endl;
    cout<<"find cheapest path between departments 3 and 2"<<endl;
    vector <path> c=calc.find_path(CHEAP,3,2,false);
    for(int i=0; i<f.size(); i++){
        cout<<c.at(i).origin<<" -"<<connections_types[c.at(i).type_of_connection]<<"-> "<<c.at(i).destination<<endl;
    }
    cout<<endl;

    cout<<"calculate cost of path f"<<endl;
    cout<<calc.calculate_cost(f, true)<<endl;
    cout<<endl;
    cout<<"add parcel to db"<<endl;
    calc.add_parcel(250, 33,1,3,1,"Max", "John", CHEAP);
    cout<<endl;
    cout<<"new list of parcels"<<endl<<endl;
    parcels = calc.list_parcels();

    for(int i=0; i<calc.get_parcels_number(); i++){
        parcels[i].print();
    }
}