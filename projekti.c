#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "projekti.h"

#define MAX_LENGTH 100

void deallocate_reservation(Reservation *reservation)
{
    free(reservation->description);
    free(reservation);
}

Reservation *allocate_reservation(Reservation *reservations)
{
    reservations = realloc(reservations, sizeof(reservations) + sizeof(Reservation));
    Reservation *new_reservation = reservations;
    while (!new_reservation)
    {
        new_reservation++;
    }
    new_reservation->description = malloc(sizeof(char) * 50);
    return reservations;
}

Reservation *add_reservation(int n_args, char *token, Reservation *reservations)
{
    token = strtok(NULL, " ");
    reservations = allocate_reservation(reservations);
    Reservation *new_reservation = reservations;
    while (!new_reservation)
    {
        new_reservation++;
    }
    new_reservation->description = token;

    int date[3];
    int i = 0;

    do
    {
        token = strtok(NULL, " ");
        sscanf(token, " %d", &date[i++]);
    } while (token != NULL && i < 3);

    // check that there is exactly four arguments (1 str, 3 int)
    token = strtok(NULL, " ");
    if (token != NULL || i != 3)
    {
        printf("Invalid number of arguments, %d required.", n_args);
        deallocate_reservation(new_reservation);
    }

    new_reservation->month = date[0];
    new_reservation->day = date[1];
    new_reservation->hour = date[2];

    printf("Added reservation: A %s %d %d %d\n", new_reservation->description, new_reservation->month, new_reservation->day, new_reservation->hour);

    return reservations;
}

void quit(Reservation *reservations) // TODO: Implement
{
    while (reservations)
    {
        deallocate_reservation(reservations++);
    }
}

Reservation *perform_command(char *command, Reservation *reservations)
{
    char *token;
    token = strtok(command, " ");
    if (!(token[1] == 0x00 || token[1] == '\n'))
    {
        printf("Invalid command!\n");
        return reservations;
    }
    switch (token[0])
    {
    case 'A':
        reservations = add_reservation(4, token, reservations);
        break;
    case 'D':
        printf("Delete reservation!\n");
        break;
    case 'L':
        printf("Print calendar!\n");
        break;
    case 'W':
        printf("Save calendar!\n");
        break;
    case 'O':
        printf("Open calendar!\n");
        break;
    case 'Q':
        printf("Quit program!\n");
        quit(reservations);
        break;
    default:
        printf("Invalid command!\n");
        break;
    }
    return reservations;
}

void run_program()
{
    char command[MAX_LENGTH];
    Reservation *reservations = malloc(sizeof(Reservation));
    do
    {
        fgets(command, MAX_LENGTH, stdin);
        reservations = perform_command(command, reservations);
    } while (!(command[0] == 'Q' && command[1] == '\n')); // TODO: fix it
}
