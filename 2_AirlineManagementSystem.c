#include <stdio.h>
#include <string.h>

#define MAX_FLIGHTS 50
#define MAX_PASSENGERS 200
#define MAX_BOOKINGS 300
#define MAX_BAGS 500
#define MAX_SEATS 200

/* Structure for pre added flights*/
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
    int status; /* 0 scheduled, 1 delayed, 2 cancelled */
    float fare;
};
// Structure for adding passenger details.
struct Passenger {
    int id;
    char name[50];
    int age;
    char contact[30];
};
// Structure for Booking flights using the passenger information
struct Booking {
    char pnr[16];
    int pass_index;
    int flight_index;
    int seat_no;
    float paid;
    int active;   /* 1 active, 0 cancelled */
    int checked_in; /* 0/1 */
    int bag_ids[5];
    int bag_count;
};

struct Baggage {
    int id;
    int booking_index;
    char status[20];
};

// Global lists and counters
struct Flight flight_list[MAX_FLIGHTS];
int fcount = 0;

struct Passenger pass_list[MAX_PASSENGERS];
int pcount = 0;

struct Booking book_list[MAX_BOOKINGS];
int bcount = 0;

struct Baggage bag_list[MAX_BAGS];
int bagcount = 0;

//Simple generators
int next_pass_id() { return 2000 + pcount + 1; }
int next_bag_id() { return 9000 + bagcount + 1; }

void make_pnr(char pnr[], int seq) {
    sprintf(pnr, "PNR%04d", seq+1);
}

//Preload 10 flights (uses strcpy)
void preload_flights() {
    int i, j;
    struct Flight f;

    /* 1 Pune -> Delhi */
    f.id = 1001; strcpy(f.from,"Pune"); strcpy(f.to,"Delhi");
    strcpy(f.dept,"06:00"); strcpy(f.arr,"08:00"); f.gate = 5;
    f.seats_total = 180; f.seats_left = 180; f.status = 0; f.fare = 4500.0f;
    for (j=0;j<MAX_SEATS;j++) f.seat_used[j]=0;
    flight_list[fcount++] = f;

    /* 2 Mumbai -> Delhi */
    f.id = 1002; strcpy(f.from,"Mumbai"); strcpy(f.to,"Delhi");
    strcpy(f.dept,"09:00"); strcpy(f.arr,"11:10"); f.gate = 12;
    f.seats_total = 200; f.seats_left = 200; f.status = 0; f.fare = 5000.0f;
    for (j=0;j<MAX_SEATS;j++) f.seat_used[j]=0;
    flight_list[fcount++] = f;

    /* 3 Pune -> Goa */
    f.id = 1003; strcpy(f.from,"Pune"); strcpy(f.to,"Goa");
    strcpy(f.dept,"14:00"); strcpy(f.arr,"15:15"); f.gate = 3;
    f.seats_total = 150; f.seats_left = 150; f.status = 0; f.fare = 3000.0f;
    for (j=0;j<MAX_SEATS;j++) f.seat_used[j]=0;
    flight_list[fcount++] = f;

    /* 4 Delhi -> Goa */
    f.id = 1004; strcpy(f.from,"Delhi"); strcpy(f.to,"Goa");
    strcpy(f.dept,"16:30"); strcpy(f.arr,"18:20"); f.gate = 9;
    f.seats_total = 160; f.seats_left = 160; f.status = 0; f.fare = 5200.0f;
    for (j=0;j<MAX_SEATS;j++) f.seat_used[j]=0;
    flight_list[fcount++] = f;

    /* 5 Mumbai -> Dubai */
    f.id = 1005; strcpy(f.from,"Mumbai"); strcpy(f.to,"Dubai");
    strcpy(f.dept,"22:00"); strcpy(f.arr,"00:30"); f.gate = 14;
    f.seats_total = 220; f.seats_left = 220; f.status = 0; f.fare = 15000.0f;
    for (j=0;j<MAX_SEATS;j++) f.seat_used[j]=0;
    flight_list[fcount++] = f;

    /* 6 Mumbai -> Goa */
    f.id = 1006; strcpy(f.from,"Mumbai"); strcpy(f.to,"Goa");
    strcpy(f.dept,"10:45"); strcpy(f.arr,"12:05"); f.gate = 4;
    f.seats_total = 140; f.seats_left = 140; f.status = 0; f.fare = 3500.0f;
    for (j=0;j<MAX_SEATS;j++) f.seat_used[j]=0;
    flight_list[fcount++] = f;

    /* 7 Bangalore -> Mumbai */
    f.id = 1007; strcpy(f.from,"Bangalore"); strcpy(f.to,"Mumbai");
    strcpy(f.dept,"07:15"); strcpy(f.arr,"09:05"); f.gate = 8;
    f.seats_total = 180; f.seats_left = 180; f.status = 0; f.fare = 4000.0f;
    for (j=0;j<MAX_SEATS;j++) f.seat_used[j]=0;
    flight_list[fcount++] = f;

    /* 8 Hyderabad -> Pune */
    f.id = 1008; strcpy(f.from,"Hyderabad"); strcpy(f.to,"Pune");
    strcpy(f.dept,"11:20"); strcpy(f.arr,"12:45"); f.gate = 6;
    f.seats_total = 170; f.seats_left = 170; f.status = 0; f.fare = 3200.0f;
    for (j=0;j<MAX_SEATS;j++) f.seat_used[j]=0;
    flight_list[fcount++] = f;

    /* 9 Chennai -> Delhi */
    f.id = 1009; strcpy(f.from,"Chennai"); strcpy(f.to,"Delhi");
    strcpy(f.dept,"13:50"); strcpy(f.arr,"16:40"); f.gate = 16;
    f.seats_total = 190; f.seats_left = 190; f.status = 0; f.fare = 5800.0f;
    for (j=0;j<MAX_SEATS;j++) f.seat_used[j]=0;
    flight_list[fcount++] = f;

    /* 10 Kolkata -> Bengaluru */
    f.id = 1010; strcpy(f.from,"Kolkata"); strcpy(f.to,"Bengaluru");
    strcpy(f.dept,"05:30"); strcpy(f.arr,"07:25"); f.gate = 10;
    f.seats_total = 160; f.seats_left = 160; f.status = 0; f.fare = 4200.0f;
    for (j=0;j<MAX_SEATS;j++) f.seat_used[j]=0;
    flight_list[fcount++] = f;
}
//View flights 
void view_flights() {
    int i;
    printf("\n--- FLIGHT LIST ---\n");
    for (i=0; i<fcount; i++) {
        printf("%d) ID:%d %s -> %s | %s-%s | Gate %d | Seats %d/%d | Fare %.2f\n",
            i+1, flight_list[i].id, flight_list[i].from, flight_list[i].to, flight_list[i].dept, flight_list[i].arr, flight_list[i].gate, flight_list[i].seats_left, flight_list[i].seats_total, flight_list[i].fare
        );
    }
}

//Add passenger 
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
    printf("Enter contact (phone/email): ");
    scanf("%s", p.contact);

    pass_list[pcount++] = p;
    printf("Passenger added. ID=%d\n", p.id);
}

//View passengers 
void view_passengers() {
    int i;
    if (pcount == 0) {
        printf("No passengers.\n");
        return;
    }
    printf("\n--- PASSENGERS ---\n");
    for (i=0; i<pcount; i++) {
        printf("%d) %s | Age %d | Contact %s | ID %d\n", i+1, pass_list[i].name, pass_list[i].age, pass_list[i].contact, pass_list[i].id);
    }
}

// Seat assignment 
int assign_seat(int fidx) {
    int i;
    for (i=0; i<flight_list[fidx].seats_total; i++) {
        if (flight_list[fidx].seat_used[i] == 0) {
            flight_list[fidx].seat_used[i] = 1;
            flight_list[fidx].seats_left--;
            return i+1; // seat numbers start from 1 
        }
    }
    return 0;
}

//Book ticket
void book_ticket() {
    if (pcount == 0) {
        printf("Please add a passenger first.\n");
        return;
    }
    if (fcount == 0) {
        printf("No flights present.\n");
        return;
    }
    int i;
    view_passengers();
    int pchoice;
    printf("Select passenger (1-%d): ", pcount);
    scanf("%d", &pchoice);
    if (pchoice < 1 || pchoice > pcount) { printf("Invalid passenger choice.\n"); return; }
    pchoice = pchoice - 1;

    view_flights();
    int fchoice;
    printf("Select flight (1-%d): ", fcount);
    scanf("%d", &fchoice);
    if (fchoice < 1 || fchoice > fcount) { printf("Invalid flight choice.\n"); return; }
    fchoice = fchoice - 1;

    if (flight_list[fchoice].status == 2) { printf("Flight is cancelled.\n"); return; }
    if (flight_list[fchoice].seats_left <= 0) { printf("No seats left.\n"); return; }
    if (bcount >= MAX_BOOKINGS) { printf("Booking storage full.\n"); return; }

    struct Booking bk;
    make_pnr(bk.pnr, bcount);
    bk.pass_index = pchoice;
    bk.flight_index = fchoice;
    bk.active = 1;
    bk.checked_in = 0;
    bk.bag_count = 0;

    bk.seat_no = assign_seat(fchoice);
    bk.paid = flight_list[fchoice].fare;

    book_list[bcount++] = bk;

    printf("\nBooking successful!\nPNR: %s\nPassenger: %s\nFlight: %s -> %s\nSeat: %d\nFare: %.2f\n",
        bk.pnr, pass_list[bk.pass_index].name, flight_list[bk.flight_index].from, flight_list[bk.flight_index].to, bk.seat_no, bk.paid);
}

// View bookings
void view_bookings() {
    int i;
    if (bcount == 0) { printf("No bookings.\n"); return; }
    printf("\n--- BOOKINGS ---\n");
    for (i=0; i<bcount; i++) {
        printf("%d) %s | %s -> %s | Passenger: %s | Seat %d | Paid %.2f | %s | CheckedIn:%s\n",
            i+1,
            book_list[i].pnr,
            flight_list[book_list[i].flight_index].from,
            flight_list[book_list[i].flight_index].to,
            pass_list[book_list[i].pass_index].name,
            book_list[i].seat_no,
            book_list[i].paid,
            book_list[i].active ? "Active":"Cancelled",
            book_list[i].checked_in ? "Yes":"No"
        );
    }
}

// Find booking by PNR 
int find_booking_by_pnr(char pnr[]) {
    int i;
    for (i=0; i<bcount; i++) {
        if (strcmp(book_list[i].pnr, pnr) == 0) return i;
    }
    return -1;
}

// Modify booking (change flight) 
void modify_booking() {
    char pnr[16];
    printf("Enter PNR to modify: ");
    scanf("%s", pnr);
    int idx = find_booking_by_pnr(pnr);
    if (idx == -1) { printf("PNR not found.\n"); return; }
    if (!book_list[idx].active) { printf("Booking is cancelled.\n"); return; }

    view_flights();
    int nf;
    printf("Select new flight (1-%d): ", fcount);
    scanf("%d", &nf);
    if (nf < 1 || nf > fcount) { printf("Invalid.\n"); return; }
    nf = nf - 1;
    if (flight_list[nf].seats_left <= 0) { printf("No seats on chosen flight.\n"); return; }

    /* free old seat */
    int oldf = book_list[idx].flight_index;
    int oldseat = book_list[idx].seat_no;
    if (oldseat > 0 && oldseat <= flight_list[oldf].seats_total) {
        flight_list[oldf].seat_used[oldseat-1] = 0;
        flight_list[oldf].seats_left++;
    }

    /* assign seat on new flight */
    int newseat = assign_seat(nf);
    if (newseat == 0) { printf("Failed seat assign.\n"); return; }

    book_list[idx].flight_index = nf;
    book_list[idx].seat_no = newseat;
    book_list[idx].paid = flight_list[nf].fare;

    printf("Booking updated. New flight %s -> %s Seat %d Fare %.2f\n",
        flight_list[nf].from, flight_list[nf].to, newseat, book_list[idx].paid);
}

// Cancel booking 
void cancel_booking() {
    char pnr[16];
    printf("Enter PNR to cancel: ");
    scanf("%s", pnr);
    int idx = find_booking_by_pnr(pnr);
    if (idx == -1) { printf("PNR not found.\n"); return; }
    if (!book_list[idx].active) { printf("Already cancelled.\n"); return; }

    book_list[idx].active = 0;

    /* free seat */
    int fidx = book_list[idx].flight_index;
    int seat = book_list[idx].seat_no;
    if (seat > 0 && seat <= flight_list[fidx].seats_total) {
        flight_list[fidx].seat_used[seat-1] = 0;
        flight_list[fidx].seats_left++;
    }

    printf("Booking cancelled.\n");
}

// Check-in & baggage 
void check_in() {
    char pnr[16];
    printf("Enter PNR to check-in: ");
    scanf("%s", pnr);
    int idx = find_booking_by_pnr(pnr);
    if (idx == -1) { printf("PNR not found.\n"); return; }
    if (!book_list[idx].active) { printf("Booking cancelled.\n"); return; }
    if (book_list[idx].checked_in) { printf("Already checked-in.\n"); return; }

    book_list[idx].checked_in = 1;

    int nb;
    printf("Number of bags to check-in (0-3): ");
    scanf("%d", &nb);
    if (nb < 0) nb = 0;
    if (nb > 3) nb = 3;
    int i;
    for (i=0; i<nb; i++) {
        if (bagcount >= MAX_BAGS) { printf("Bag storage full.\n"); break; }
        struct Baggage bg;
        bg.id = next_bag_id();
        bg.booking_index = idx;
        strcpy(bg.status, "Checked-in");
        bag_list[bagcount] = bg;
        book_list[idx].bag_ids[book_list[idx].bag_count++] = bagcount;
        bagcount++;
        printf("Bag registered ID=%d\n", bg.id);
    }

    printf("Checked-in. Boarding pass:\nPNR:%s Name:%s Flight:%s->%s Seat:%d Gate:%d Time:%s\n",
        book_list[idx].pnr,
        pass_list[book_list[idx].pass_index].name,
        flight_list[book_list[idx].flight_index].from,
        flight_list[book_list[idx].flight_index].to,
        book_list[idx].seat_no,
        flight_list[book_list[idx].flight_index].gate,
        flight_list[book_list[idx].flight_index].dept
    );
}

//View bags 
void view_bags() {
    int i;
    if (bagcount == 0) { printf("No bags registered.\n"); return; }
    printf("\n--- BAGS ---\n");
    for (i=0;i<bagcount;i++) {
        printf("%d) BagID:%d | PNR:%s | Status:%s\n",
            i+1,
            bag_list[i].id,
            book_list[bag_list[i].booking_index].pnr,
            bag_list[i].status
        );
    }
}

// Simple report to show details of the flight and their seats
void report_summary() {
    int i;
    printf("\n--- FLIGHT REPORT ---\n");
    for (i=0;i<fcount;i++) {
        int booked = flight_list[i].seats_total - flight_list[i].seats_left;
        printf("%d) %s -> %s | Booked:%d | Left:%d\n",
            flight_list[i].id,
            flight_list[i].from,
            flight_list[i].to,
            booked,
            flight_list[i].seats_left
        );
    }
}

// Main menu 
int main() {
    preload_flights();

    int choice;
    while (1) {
        printf("\n===== UPES AIRLINE =====\n");
        printf("1 View Flights\n");
        printf("2 Add Passenger\n");
        printf("3 View Passengers\n");
        printf("4 Book Ticket\n");
        printf("5 View Bookings\n");
        printf("6 Modify Booking\n");
        printf("7 Cancel Booking\n");
        printf("8 Check-In\n");
        printf("9 View Baggage\n");
        printf("10 Report\n");
        printf("11 Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: view_flights(); break;
            case 2: add_passenger(); break;
            case 3: view_passengers(); break;
            case 4: book_ticket(); break;
            case 5: view_bookings(); break;
            case 6: modify_booking(); break;
            case 7: cancel_booking(); break;
            case 8: check_in(); break;
            case 9: view_bags(); break;
            case 10: report_summary(); break;
            case 11: printf("Goodbye!\n"); return 0;
            default: printf("Invalid choice.\n");
        }
    }

    return 0;
}

