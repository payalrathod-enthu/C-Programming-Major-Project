#ifndef BAGGAGE_H
#define BAGGAGE_H

#define MAX_BAGS 500

struct Baggage {
    int id;
    int booking_index;
    char status[20];
};

extern struct Baggage bag_list[MAX_BAGS];
extern int bagcount;

int next_bag_id();
void check_in();
void view_bags();

#endif
