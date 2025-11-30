#ifndef PASSENGER_H
#define PASSENGER_H

#define MAX_PASSENGERS 200

struct Passenger {
    int id;
    char name[50];
    int age;
    char contact[30];
};

extern struct Passenger pass_list[MAX_PASSENGERS];
extern int pcount;

int next_pass_id();
void add_passenger();
void view_passengers();

#endif
