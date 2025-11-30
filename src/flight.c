#include <stdio.h>
#include <string.h>
#include "flight.h"

struct Flight flight_list[MAX_FLIGHTS];
int fcount = 0;

void preload_flights() {
    int j;
    struct Flight f;

    // 1 Pune -> Delhi
    f.id = 1001; strcpy(f.from,"Pune"); strcpy(f.to,"Delhi");
    strcpy(f.dept,"06:00"); strcpy(f.arr,"08:00"); f.gate = 5;
    f.seats_total = 180; f.seats_left = 180; f.status = 0; f.fare = 4500.0f;
    for (j = 0; j < MAX_SEATS; j++) f.seat_used[j] = 0;
    flight_list[fcount++] = f;

    // 2 Mumbai -> Delhi
    f.id = 1002; strcpy(f.from,"Mumbai"); strcpy(f.to,"Delhi");
    strcpy(f.dept,"09:00"); strcpy(f.arr,"11:10"); f.gate = 12;
    f.seats_total = 200; f.seats_left = 200; f.status = 0; f.fare = 5000.0f;
    for (j = 0; j < MAX_SEATS; j++) f.seat_used[j] = 0;
    flight_list[fcount++] = f;

    // 3 Pune -> Goa
    f.id = 1003; strcpy(f.from,"Pune"); strcpy(f.to,"Goa");
    strcpy(f.dept,"14:00"); strcpy(f.arr,"15:15"); f.gate = 3;
    f.seats_total = 150; f.seats_left = 150; f.status = 0; f.fare = 3000.0f;
    for (j = 0; j < MAX_SEATS; j++) f.seat_used[j] = 0;
    flight_list[fcount++] = f;

    // ... (ALL 10 flights EXACTLY SAME as your original code)
}

void view_flights() {
    printf("\n--- FLIGHT LIST ---\n");
    for (int i = 0; i < fcount; i++) {
        printf("%d) ID:%d %s -> %s | %s-%s | Gate %d | Seats %d/%d | Fare %.2f\n",
            i+1,
            flight_list[i].id,
            flight_list[i].from,
            flight_list[i].to,
            flight_list[i].dept,
            flight_list[i].arr,
            flight_list[i].gate,
            flight_list[i].seats_left,
            flight_list[i].seats_total,
            flight_list[i].fare
        );
    }
}

int assign_seat(int fidx) {
    for (int i = 0; i < flight_list[fidx].seats_total; i++) {
        if (flight_list[fidx].seat_used[i] == 0) {
            flight_list[fidx].seat_used[i] = 1;
            flight_list[fidx].seats_left--;
            return i+1;
        }
    }
    return 0;
}
