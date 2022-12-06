#pragma once

struct connection{
    double plane;
    double ship;
    double train;
    double car;
};

enum Connections{
    PLANE,
    SHIP,
    TRAIN,
    CAR
};

enum type{
    FAST,
    CHEAP
};

struct path{
    int origin;
    int destination;
    Connections type_of_connection;

};