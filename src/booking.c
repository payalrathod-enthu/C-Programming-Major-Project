#include <stdio.h>
#include <string.h>
#include "booking.h"
#include "flight.h"
#include "passenger.h"

struct Booking book_list[MAX_BOOKINGS];
int bcount = 0;

void make_pnr(char pnr[], int seq) {
    sprintf(pnr, "PNR%04d", seq + 1);
}

int find_booking_by_pnr(char pnr[]) {
    for (int i = 0; i < bcount; i++) {
        if (strcmp(book_list[i].pnr, pnr) == 0)
            return i;
    }
    return -1;
}

void book_ticket() {
    if (pcount == 0) { printf("Add passenger first.\n"); return; }
    if (fcount == 0) { printf("No flights.\n"); return; }

    int pchoice, fchoice;
    view_passengers();
    printf("Select passenger: ");
    scanf("%d", &pchoice);
    pchoice--;

    view_flights();
    printf("Select flight: ");
    scanf("%d", &fchoice);
    fchoice--;

    struct Booking bk;
    make_pnr(bk.pnr, bcount);
    bk.pass_index = pchoice;
    bk.flight_index = fchoice;

    bk.seat_no = assign_seat(fchoice);
    bk.paid = flight_list[fchoice].fare;
    bk.active = 1;
    bk.checked_in = 0;
    bk.bag_count = 0;

    book_list[bcount++] = bk;

    printf("\nBooking successful!\nPNR: %s\n", bk.pnr);
}

void view_bookings() {
    if (bcount == 0) { printf("No bookings.\n"); return; }

    printf("\n--- BOOKINGS ---\n");
    for (int i = 0; i < bcount; i++) {
        printf("%d) %s | Passenger: %s | %s->%s | Seat %d | %s\n",
            i+1,
            book_list[i].pnr,
            pass_list[book_list[i].pass_index].name,
            flight_list[book_list[i].flight_index].from,
            flight_list[book_list[i].flight_index].to,
            book_list[i].seat_no,
            book_list[i].active ? "Active" : "Cancelled"
        );
    }
}

void modify_booking() {
    char pnr[16];
    printf("Enter PNR: ");
    scanf("%s", pnr);

    int idx = find_booking_by_pnr(pnr);
    if (idx == -1) { printf("PNR not found.\n"); return; }

    view_flights();
    int nf;
    printf("Select new flight: ");
    scanf("%d", &nf);
    nf--;

    int oldf = book_list[idx].flight_index;
    int seat = book_list[idx].seat_no;
    flight_list[oldf].seat_used[seat-1] = 0;
    flight_list[oldf].seats_left++;

    int newseat = assign_seat(nf);

    book_list[idx].flight_index = nf;
    book_list[idx].seat_no = newseat;
    book_list[idx].paid = flight_list[nf].fare;

    printf("Booking updated.\n");
}

void cancel_booking() {
    char pnr[16];
    printf("Enter PNR: ");
    scanf("%s", pnr);

    int idx = find_booking_by_pnr(pnr);
    if (idx == -1) { printf("PNR not found.\n"); return; }

    book_list[idx].active = 0;

    int fidx = book_list[idx].flight_index;
    int seat = book_list[idx].seat_no;

    flight_list[fidx].seat_used[seat-1] = 0;
    flight_list[fidx].seats_left++;

    printf("Booking cancelled.\n");
}
