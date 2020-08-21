# reservation-system

Implement a system for scheduling that can be used to schedule one-hour meeting times. There should be only one reservation per hour. It should also be possible to cancel meetings and print them according to time. The meeting should be presented with one string description and at least 20 characters should be supported, but you can decide how to handle longer strings. You can assume that there are no white spaces in the string. The string for the meeting doesn’t have to unique. The system can only handle one year at the time so you don’t need to keep record of the year.

## The program has the following functions:

* A description month day hour: ***Add entry***: Add an entry with the given parameters to the scheduling system. Check that month, day and hour are reasonable. You can assume that every month would have 31 days. If the given time is already reserved, error message should be printed. For example, ```A Haircut 3 26 14``` would reserve a slot for haircutting on 26.3. at 14. The system should use 24-hour clock.

* D month day hour: ***Delete entry***: Delete an entry with the given parameters. If there is no entry with the given parameters, error message should be printed. For example, ```D 3 26 14``` would delete the entry added above.

* L : ***Output calendar***: Prints the current entries according to scheduled time. The earliest entry should the printed first and the latest last. For every entry, description and time should be printed in the following format: ```description XX.YY. at ZZ``` where XX is the day, YY is the month and ZZ is the time.

* W filename : ***Save calendar***: Writes the calendar to a file with the given filename.

* O filename : ***Load calendar***: Loads the calendar from file, and replaces the existing calendar in memory.

* Q : ***Exit program***: Exits program and releases all allocated memory.

In addition to the above commands, there should be a working main function that repeatedly asks commands from user and acts accordingly.

The commands start with one capital letter and may be followed by some number of parameters, separated by space, depending on the command. Below is an example of possible input sequence:

```
A Haircut 3 26 14
A C-lecture 3 27 12
A C-exercise 3 27 14
A Math_lecture 3 26 14
D 3 26 14
A Math_lecture 3 26 14
L
W calendar
Q
```

After this, the calendar should save the first three entries since the first “Math_lecture” shouldn’t be succesful because the time is already reserved in previous entry. After the entry is deleted with the command “D”, adding the “Math_lecture” should be successful. After these, the calendar is printed and saved to the file “calendar”.

You can design your program in any way you want, but apply clear structure to logical functions, and name the functions and variables appropriately so that the program is easy to read. Implement the program in single .c file. You can also use one header file for your definitions, but you can include them also in the .c file and omit the header file.

Other general requirements and instructions:

* To facilitate testing, the aforementioned command syntax must be precisely followed.

* You must use dynamic memory to implement the storage. A large static array is not acceptable. The dynamic memory allocation should be done based on the actual need: malloc(1000000) is not acceptable.

* After every command, the system must give an output that tells whether the command was succesful, or whether its execution failed.

* You can assume a maximum lenght for user input line. For example, 80 characters is sufficient.

* Clearly erroneus commands must give on error message, and at least the program must not crash as result. However, you can assume that names and other strings not contain whitespaces (i.e., whitespaces can be assumed as command field separators).

# main.c

A version of main.c, where one can choose to start up the interactive program or take a file of commands as input.

```
#include "projekti.c"

int main()
{
    char filename[100];
    printf("To run the time reservation program interactively, press Enter.\n");
    printf("To run a file with commands, enter the name of the file (testing and debugging purposes): ");
    fgets(filename, 100, stdin);
    if (filename[0] == '\n') {
        printf("Welcome to the time reservation program!\n");
        run_program(stdin);
    } else {
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
```