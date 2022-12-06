#pragma once
#include "../../headers/Parcel.h"
#include "../../headers/DTOs.h"


int read_map_number();
int read_parcels_number();

connection* read_map();

Parcel* read_parcels();

void save_parcel(int weight, int volume, Date sendind_date, Date receiving_date, int price, int origin, int destination, bool premium, string sender, string recepient);