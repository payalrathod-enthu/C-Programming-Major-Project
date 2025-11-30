#ifndef FLIGHT_H
#define FLIGHT_H

#define MAX_FLIGHTS 50
#define MAX_SEATS 200

struct Flight {
    int id;
    char from[30];
    char to[30];
    char dept[10];
    char arr[10];
    int gate;
    int seats_total;
    int seats_left;
    int seat_used[MAX_SEATS];
    int status;  /* 0 scheduled, 1 delayed, 2 cancelled */
    float fare;
};

extern struct Flight flight_list[MAX_FLIGHTS];
extern int fcount;

void preload_flights();
void view_flights();
int assign_seat(int fidx);

#endif
