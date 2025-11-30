#include <stdio.h>
#include <string.h>
#include "passenger.h"

struct Passenger pass_list[MAX_PASSENGERS];
int pcount = 0;

int next_pass_id() {
    return 2000 + pcount + 1;
}

void add_passenger() {
    if (pcount >= MAX_PASSENGERS) {
        printf("Passenger storage full.\n");
        return;
    }

    struct Passenger p;
    p.id = next_pass_id();

    printf("Enter name: ");
    scanf("%s", p.name);
    printf("Enter age: ");
    scanf("%d", &p.age);
    printf("Enter contact: ");
    scanf("%s", p.contact);

    pass_list[pcount++] = p;

    printf("Passenger added. ID=%d\n", p.id);
}

void view_passengers() {
    if (pcount == 0) {
        printf("No passengers.\n");
        return;
    }

    printf("\n--- PASSENGERS ---\n");
    for (int i = 0; i < pcount; i++) {
        printf("%d) %s | Age %d | Contact %s | ID %d\n",
            i+1,
            pass_list[i].name,
            pass_list[i].age,
            pass_list[i].contact,
            pass_list[i].id
        );
    }
}
