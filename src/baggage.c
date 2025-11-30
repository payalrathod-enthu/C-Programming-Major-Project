#include <stdio.h>
#include <string.h>
#include "baggage.h"
#include "booking.h"
#include "flight.h"
#include "passenger.h"

struct Baggage bag_list[MAX_BAGS];
int bagcount = 0;

int next_bag_id() {
    return 9000 + bagcount + 1;
}

void view_bags() {
    if (bagcount == 0) { printf("No bags.\n"); return; }

    printf("\n--- BAGS ---\n");
    for (int i = 0; i < bagcount; i++) {
        printf("%d) BagID:%d | PNR:%s | Status:%s\n",
            i+1,
            bag_list[i].id,
            book_list[bag_list[i].booking_index].pnr,
            bag_list[i].status
        );
    }
}

void check_in() {
    char pnr[16];
    printf("Enter PNR: ");
    scanf("%s", pnr);

    int idx = find_booking_by_pnr(pnr);
    if (idx == -1) { printf("PNR not found.\n"); return; }

    book_list[idx].checked_in = 1;

    int nb;
    printf("Bags to check in (0–3): ");
    scanf("%d", &nb);

    for (int i = 0; i < nb; i++) {
        struct Baggage bg;
        bg.id = next_bag_id();
        bg.booking_index = idx;
        strcpy(bg.status, "Checked-in");

        bag_list[bagcount] = bg;
        book_list[idx].bag_ids[book_list[idx].bag_count++] = bagcount;
        bagcount++;

        printf("Bag registered: %d\n", bg.id);
    }

    printf("Check-in complete.\n");
}
