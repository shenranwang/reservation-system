#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "projekti.h"

#define MAX_LENGTH 100
#define MAX_DESC 50

Reservation *create_reservation()
{
    Reservation *reservation = malloc(sizeof(Reservation));
    if (reservation != NULL)
    {
        reservation->description = malloc(sizeof(char) * (MAX_DESC + 1));
        reservation->next = NULL;
    }
    return reservation;
}

void add_reservation(int n_args, char *token, Reservation *reservations)
{
    char desc[MAX_DESC + 1];
    int date[3];
    if (token == NULL)
    {
        printf("Invalid number of arguments, %d required.\n", n_args);
        return;
    }
    strcpy(desc, token);

    int i = 0;
    do
    {
        token = strtok(NULL, " ");
        if (token == NULL || token[0] == '\n')
        {
            printf("Invalid number of arguments, %d required.\n", n_args);
            return;
        }
        int res = sscanf(token, " %d", &date[i++]);
        if (!res)
        {
            printf("Invalid value entered as argument, requires integer value.\n");
            return;
        }
    } while (token != NULL && i < 3);

    Reservation *new_reservation = create_reservation();

    Reservation *prev = reservations;
    Reservation *temp = reservations->next;
    while (temp != NULL)
    {
        if (date[0] < temp->month || (date[0] == temp->month && date[1] < temp->day) ||
            (date[0] == temp->month && date[1] == temp->day && date[2] <= temp->hour))
        {
            if (date[0] == temp->month && date[1] == temp->day && date[2] == temp->hour)
            {
                free(new_reservation->description);
                free(new_reservation);
                printf("Date already reserved. %02d.%02d. klo %02d\n", date[0], date[1], date[2]);
                return;
            }
            break;
        }
        prev = temp;
        temp = temp->next;
    }

    // check that there is exactly four arguments (1 str, 3 int)
    token = strtok(NULL, " ");
    if (token != NULL || i != 3)
    {
        free(new_reservation->description);
        free(new_reservation);
        printf("Invalid number of arguments, %d required.\n", n_args);
        return;
    }

    // check that date is valid
    if (!(date[0] >= 1 && date[0] <= 12 &&
          date[1] >= 1 && date[1] <= 31 &&
          date[2] >= 1 && date[2] <= 24))
    {
        free(new_reservation->description);
        free(new_reservation);
        printf("Invalid date for reservation: %02d.%02d. klo %02d\n", date[0], date[1], date[2]);
        return;
    }

    prev->next = new_reservation;
    strcpy(new_reservation->description, desc);
    new_reservation->month = date[0];
    new_reservation->day = date[1];
    new_reservation->hour = date[2];
    if (prev == temp)
    {
        new_reservation->next = NULL;
    }
    else
    {
        new_reservation->next = temp;
    }

    printf("Added reservation: A %s %d %d %d\n", new_reservation->description, new_reservation->month, new_reservation->day, new_reservation->hour);
}

void delete_reservation_list(Reservation *reservations, int to_remove)
{
    while (reservations->next != NULL)
    {
        delete_reservation_list(reservations->next, 1);
        reservations->next = NULL;
    }
    if (to_remove)
    {
        free(reservations->description);
        free(reservations);
    }
}

void delete_reservation(int n_args, char *token, Reservation *reservations)
{
    int date[3];
    Reservation *curr = reservations->next;
    if (curr == NULL)
    {
        printf("Empty list.\n");
        return;
    }

    int i = 0;
    do
    {
        token = strtok(NULL, " ");
        if (token == NULL)
        {
            printf("Invalid number of arguments, %d required.\n", n_args);
            return;
        }
        int res = sscanf(token, " %d", &date[i++]);
        if (!res)
        {
            printf("Invalid value entered as argument, requires integer value.\n");
            return;
        }
    } while (token != NULL && i < 3);

    // check that there is exactly four arguments (1 str, 3 int)
    token = strtok(NULL, " ");
    if (token != NULL || i != 3)
    {
        curr->next = NULL;
        printf("Invalid number of arguments, %d required.\n", n_args);
        return;
    }

    int found = 0;
    Reservation *prev = reservations;
    while (curr != NULL)
    {
        if (curr->month == date[0] && curr->day == date[1] && curr->hour == date[2])
        {
            found = 1;
            break;
        }
        prev = curr;
        curr = curr->next;
    }

    if (!found)
    {
        printf("Reservation not found.\n");
        return;
    }

    prev->next = curr->next;
    free(curr->description);
    free(curr);
    printf("Deleted reservation: D %d %d %d\n", date[0], date[1], date[2]);
}

void print_reservations(Reservation *reservations)
{
    Reservation *temp = reservations;
    if (temp->next == NULL)
    {
        return;
    }
    for (temp = temp->next; temp->next != NULL; temp = temp->next)
    {
        printf("%s %02d.%02d. klo %02d\n", temp->description, temp->month, temp->day, temp->hour);
    }
    printf("%s %02d.%02d. klo %02d\n", temp->description, temp->month, temp->day, temp->hour);
}

void save_reservations(int n_args, char *token, Reservation *reservations)
{
    char filename[MAX_DESC + 1];
    token = strtok(NULL, " \n");
    if (token == NULL)
    {
        printf("Invalid number of arguments, %d required.\n", n_args);
        return;
    }
    strcpy(filename, token);
    token = strtok(NULL, " ");
    if (token != NULL)
    {
        printf("Invalid number of arguments, %d required.\n", n_args);
        return;
    }
    FILE *fp = fopen(filename, "w");
    if (!fp)
    {
        printf("Error opening file %s.\n", filename);
        return;
    }
    Reservation *temp = reservations->next;
    while (temp != NULL)
    {
        fprintf(fp, "%s %d %d %d\n", temp->description, temp->month, temp->day, temp->hour);
        temp = temp->next;
    }
    fclose(fp);
    printf("Reservations saved to file %s.\n", filename);
}

void open_reservations(int n_args, char *token, Reservation *reservations)
{
    char filename[MAX_DESC + 1];
    char command[MAX_LENGTH];
    token = strtok(NULL, " \n");
    if (token == NULL)
    {
        printf("Invalid number of arguments, %d required.\n", n_args);
        return;
    }
    strcpy(filename, token);
    token = strtok(NULL, " ");
    if (token != NULL)
    {
        printf("Invalid number of arguments, %d required.\n", n_args);
        return;
    }
    FILE *fp = fopen(filename, "r");
    if (!fp)
    {
        printf("Error opening file %s.\n", filename);
        return;
    }
    delete_reservation_list(reservations, 0);
    printf("Deleted reservation list.\n");
    while (fgets(command, MAX_LENGTH, fp) != NULL)
    {
        token = strtok(command, " ");
        add_reservation(4, token, reservations);
    }
    fclose(fp);
    printf("Reservations loaded from file %s.\n", filename);
}

void perform_command(char *command, Reservation *reservations)
{
    char *token;
    token = strtok(command, " ");
    if (!(token[1] == 0x00 || token[1] == '\n'))
    {
        printf("Invalid command!\n");
        return;
    }
    switch (token[0])
    {
    case 'A':
        token = strtok(NULL, " ");
        add_reservation(4, token, reservations);
        break;
    case 'D':
        delete_reservation(3, token, reservations);
        break;
    case 'L':
        print_reservations(reservations);
        break;
    case 'W':
        save_reservations(1, token, reservations);
        break;
    case 'O':
        open_reservations(1, token, reservations);
        break;
    case 'Q':
        delete_reservation_list(reservations, 1);
        printf("Memory succesfully freed, quitting program!\n");
        break;
    default:
        printf("Invalid command!\n");
        break;
    }
}

void run_program(FILE *fp)
{
    char command[MAX_LENGTH];
    Reservation *reservations = create_reservation();
    do
    {
        fgets(command, MAX_LENGTH, fp);
        perform_command(command, reservations);
    } while (!(command[0] == 'Q' && command[1] == '\n'));
}
