#include <fstream>
#include <iostream>
#include "./src/dbHandlers/db_handlers.h"
#include <vector>
#include "./headers/Calculator.h"

using namespace std;

int main(){
    //задаємо початкові параметри:
    //щвидкість: літак, корабель, поїзд, машина
    connection speed={1,4,3,2};
    //вартість: літак, корабель, поїзд, машина
    connection cost={4,2,1,3};
    //коефіцієнт швидкості для преміума: літак, корабель, поїзд, машина
    connection premium_speed = {1,1,1,1};
    //коефіцієнт вартості для преміума: літак, корабель, поїзд, машина
    connection premium_cost = {0.7,0.8,1,1};
    // коефіцієнт вартості за одиницю об'єму та маси
    double volume_cost =0.1;
    double weight_cost =0.1;

    // - ініціалізація
    Calculator calc(speed, cost, premium_speed, premium_cost, volume_cost, weight_cost);

    // виведемо список посилок з бд
    Parcel *parcels = calc.get_history().get_parcels_history();

    for(int i=0; i<calc.get_history().get_parcels_number(); i++){
        cout<<"id: "<<parcels[i].get_id()<<endl;
        cout<<"sender: "<<parcels[i].get_sender()<<endl;
        cout<<"recipient: "<<parcels[i].get_recipient()<<endl;
        cout<<"origin: "<<parcels[i].get_origin()<<endl;
        cout<<"destination: "<<parcels[i].get_destination()<<endl;
        cout<<"price: "<<parcels[i].get_price()<<endl;
        cout<<"premium: "<<parcels[i].get_premium()<<endl;
        cout<<"sending date: "<<parcels[i].get_sending_date().get_day()<<" "<<parcels[i].get_sending_date().get_month()<<" "<<parcels[i].get_sending_date().get_year()<<endl;
        cout<<"receiving date: "<<parcels[i].get_receiving_date().get_day()<<" "<<parcels[i].get_receiving_date().get_month()<<" "<<parcels[i].get_receiving_date().get_year()<<endl;
        cout<<"weight: "<<parcels[i].get_weight()<<endl;
        cout<<"volume: "<<parcels[i].get_volume()<<endl;
        cout<<endl;
    }

    //знайдемо найшвидший та найдовший маршрути
    // найшвидший
    vector <path> f=calc.find_path(FAST, 1,3, 1);
    //найдешевший
    vector <path> c=calc.find_path(CHEAP,3,2,0);

    //виведемо один
    string connections_types[4]={"plane", "ship", "train", "car"};
    for(int i=0; i<f.size(); i++){
        cout<<f.at(i).origin<<" -"<<connections_types[f.at(i).type_of_connection]<<"-> "<<f.at(i).destination<<endl;
    }
    //вартість по плану преміум (потрібно ще домножити на об'єм та масу посилки)
    cout<<calc.calculate_cost(f, 1);

    //додамо посилку
    calc.add_parcel(250, 33,1,3,1,"Max", "John", CHEAP);

    // виведемо посилки
    parcels = calc.get_history().get_parcels_history();

    for(int i=0; i<calc.get_history().get_parcels_number(); i++){
        cout<<"id: "<<parcels[i].get_id()<<endl;
        cout<<"sender: "<<parcels[i].get_sender()<<endl;
        cout<<"recipient: "<<parcels[i].get_recipient()<<endl;
        cout<<"origin: "<<parcels[i].get_origin()<<endl;
        cout<<"destination: "<<parcels[i].get_destination()<<endl;
        cout<<"price: "<<parcels[i].get_price()<<endl;
        cout<<"premium: "<<parcels[i].get_premium()<<endl;
        cout<<"sending date: "<<parcels[i].get_sending_date().get_day()<<" "<<parcels[i].get_sending_date().get_month()<<" "<<parcels[i].get_sending_date().get_year()<<endl;
        cout<<"receiving date: "<<parcels[i].get_receiving_date().get_day()<<" "<<parcels[i].get_receiving_date().get_month()<<" "<<parcels[i].get_receiving_date().get_year()<<endl;
        cout<<"weight: "<<parcels[i].get_weight()<<endl;
        cout<<"volume: "<<parcels[i].get_volume()<<endl;
        cout<<endl;
    }
}