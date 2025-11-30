#ifndef BOOKING_H
#define BOOKING_H

#define MAX_BOOKINGS 300

struct Booking {
    char pnr[16];
    int pass_index;
    int flight_index;
    int seat_no;
    float paid;
    int active;
    int checked_in;
    int bag_ids[5];
    int bag_count;
};

extern struct Booking book_list[MAX_BOOKINGS];
extern int bcount;

void make_pnr(char pnr[], int seq);
void book_ticket();
void view_bookings();
int find_booking_by_pnr(char pnr[]);
void modify_booking();
void cancel_booking();

#endif
