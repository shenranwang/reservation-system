#include "projekti.c"

int main()
{
    char filename[100];
    printf("To run the time reservation program interactively, press Enter.\n");
    printf("To run a file with commands, enter the name of the file (testing and debugging purposes): ");
    fgets(filename, 100, stdin);
    if (filename[0] == '\n')
    {
        printf("Welcome to the time reservation program!\n");
        run_program(stdin);
    }
    else
    {
        strtok(filename, "\n");
        FILE *fp = fopen(filename, "r");
        if (!fp)
        {
            printf("Error loading file %s.\n", filename);
            return 1;
        }
        run_program(fp);
        fclose(fp);
    }

    return 0;
}
