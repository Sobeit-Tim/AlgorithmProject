#include <cstdio>
#include <cstring>
#include <cstdlib>
#include "Path.h"
#include "RBtree.h"
#include "Path_finder.h"

#ifndef CLS
//#define CLS     system("clear")
#define CLS     printf("\n\n")
#endif

extern Tree T;
extern Path_finder* P;

void make_reservation_print_menu(char* name, int date, char src, char dst)
{
    printf("=====  Make reservation =====\n");
    printf("Name: %s\n", name);
    printf("Dep. date: %2d\n", date);
    printf("From: %c\n", src);
    printf("To: %c\n", dst);
}

void make_reservation(void)
{
    char name[10] = {0, };
    int date = 1;
    char src = ' ';
    char dst = ' ';

    make_reservation_print_menu(name, date, src, dst);
    char buf[500];
    printf("Enter your name (Up to 9 characters): ");
    fgets(buf, 500, stdin);
    if (strlen(buf) > 10) {
        printf("Invalid input: The length of name should be less than 9\n");
        printf("Return to main screen...\n");
        return;
    }
    if (buf[strlen(buf) - 1] == '\n') buf[strlen(buf) - 1] = 0;
    strncpy(name, buf, 10);
    CLS;

    make_reservation_print_menu(name, date, src, dst);
    printf("Enter departure date (1 ~ 31): ");
    scanf("%d", &date);
    if (date < 1 || date > 31) {
        printf("Invalid input: The date should be in range from 1 to 31\n");
        printf("Return to main screen...\n");
        return;
    }
    CLS;

    make_reservation_print_menu(name, date, src, dst);
    printf("Enter source city (A ~ Z): ");
    scanf("\n%c", &src);
    if (src < 'A' || src > 'Z') {
        printf("Invalid input: The source city should be in range from 'A' to 'Z'\n");
        printf("Return to main screen...\n");
        return;
    }
    CLS;

    make_reservation_print_menu(name, date, src, dst);
    printf("Enter destination city (A ~ Z): ");
    scanf("\n%c", &dst);
    getchar();
    if (dst < 'A' || dst > 'Z') {
        printf("Invalid input: The destination city should be in range from 'A' to 'Z'\n");
        printf("Return to main screen...\n");
        return;
    }
    CLS;

    make_reservation_print_menu(name, date, src, dst);

    Path* newpath = P->get_path(date, src - 'A', dst - 'A');
   	if(newpath->flight_time == -1){
        printf("Cannot find path from %c to %c\n", src, dst);
		delete(newpath);
	}else{
		int r_id = T.insert(name, newpath);
    	printf("Your reservation id is %d\n", r_id);
	}
    return;
}
