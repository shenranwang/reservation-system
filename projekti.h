typedef struct Reservation { 
    char *description;
    int month;
    int day;
    int hour;
    struct Reservation *next;
} Reservation;