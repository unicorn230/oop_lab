#include "../../headers/history.h"
#include "../dbHandlers/db_handlers.h"

History::History(){
    History_db db = History_db();
    this->parcels_number = db.read_number();
    this->parcels_history = db.read_data();
}

History::History(int number, Parcel *parcels): parcels_number(number){
    this->parcels_history = new Parcel[number];
    for(int i=0; i<number; i++){
        parcels_history[i]=parcels[i];
    }
}

History::History(const History &history): parcels_number(history.parcels_number){
    this->parcels_history = new Parcel[history.parcels_number];
    for(int i=0; i<history.parcels_number; i++){
        parcels_history[i]=history.parcels_history[i];
    }
}

History::~History(){
    delete[] parcels_history;
}

int History::get_parcels_number() const {return this->parcels_number;}
Parcel* History::get_parcels_history() const{return this->parcels_history;}


int History::set_parcels_number(int n){this->parcels_number=n; return this->parcels_number;}
Parcel* History::set_parcels_number(Parcel *new_parcels_history){this->parcels_history=new_parcels_history; return this->parcels_history;}

void History::update() {
    History_db db = History_db();
    this->parcels_number = db.read_number();
    this->parcels_history = db.read_data();
}

void History::print(){
    for(int i=0; i<parcels_number; i++){
        parcels_history[i].print();
    }
}