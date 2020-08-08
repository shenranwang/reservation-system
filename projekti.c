#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "projekti.h"

#define MAX_LENGTH 80

int check_n_args(int n_args)
{

    return 1;
}

void perform_command(char *command)
{
    switch (command[0])
    {
    case 'A':
        printf("Add reservation!\n");
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
        break;
    default:
        printf("Invalid command!\n");
        break;
    }
}

void parse_command()
{
    char command[MAX_LENGTH];
    do
    {
        fgets(command, 80, stdin);
        perform_command(command);
    } while (command[0] != 'Q');
}
