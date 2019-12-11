#include <cstdio>
#include <cstring>
#include <cstdlib>
#include "list.h"
#ifndef CLS
//#define CLS     system("clear")
#define CLS     printf("\n\n")
#endif

extern int timetable[32][26][26][23];
extern List map[26];
void seat_print_menu(char* name, int date, char src, char dst)
{
    printf("=====  Seat information =====\n");
    printf("Dep. date: %2d\n", date);
    printf("From: %c\n", src);
    printf("To: %c\n", dst);
}

void seat_information(void)
{
    char name[10] = {0, };
    int date = 1;
    char src = ' ';
    char dst = ' ';

    seat_print_menu(name, date, src, dst);
    printf("Enter departure date (1 ~ 31): ");
    scanf("%d", &date);
    if (date < 1 || date > 31) {
        printf("Invalid input: The date should be in range from 1 to 31\n");
        printf("Return to main screen...\n");
        return;
    }
    CLS;

    seat_print_menu(name, date, src, dst);
    printf("Enter source city (A ~ Z): ");
    scanf("\n%c", &src);
    if (src < 'A' || src > 'Z') {
        printf("Invalid input: The source city should be in range from 'A' to 'Z'\n");
        printf("Return to main screen...\n");
        return;
    }
    CLS;

    seat_print_menu(name, date, src, dst);
    printf("Enter destination city (A ~ Z): ");
    scanf("\n%c", &dst);
    if (dst < 'A' || dst > 'Z') {
        printf("Invalid input: The destination city should be in range from 'A' to 'Z'\n");
        printf("Return to main screen...\n");
        return;
    }
    getchar();
    CLS;

    seat_print_menu(name, date, src, dst);
    src -= 'A';
    dst -= 'A';
    if(map[src].find(dst) == -1){
        printf("There is no airplane\n");
        return;
    }
    printf("\nAirplane Capacity Information(O - available, X - not)\n");	
    printf("seat(1~10):\t");
    for(int i = 0; i<20; i++){
        if(i == 10)
            printf("\nseat(11~20):\t");
        if(timetable[date][src][dst][3+i] == 0)
            printf("O");
        else
            printf("X");
        if(i == 4 || i == 14)
            printf("   ");
    }
    printf("\n");
    return;
}
