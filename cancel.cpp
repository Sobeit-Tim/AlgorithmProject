#include <cstdio>
#include "RBtree.h"
#include "Path_finder.h"
extern Tree T;
extern Path_finder* P;

extern int timetable[32][26][26][23];

void cancel_reservation_print_menu(char* name, int date, char src, char dst)
{
    printf("===== Cancel reservation =====\n");
    printf("Name: %s\n", name);
    printf("Dep. date: %2d\n", date);
    printf("From: %c\n", src);
    printf("To: %c\n", dst);
}

void cancel_reservation()
{
    int r_id;

    printf("Enter your reservation id: ");
    scanf("%d", &r_id);
    getchar();
    printf("\n");

    Node* customer = T.search(T.root, r_id, NULL);
    if (customer->reserve_id != r_id) {
        printf("Cannot find reservation for given reservation id (%d)\n", r_id);
        return;
    } else {
		Path* p = customer->path;
        cancel_reservation_print_menu(customer->name, customer->path->dep_time[0], \
                customer->path->source + 'A', customer->path->dest + 'A');
        P->printPath(p);
		char sel;
        printf("Check your reservation info.\n");
        printf("Cancel this reservation? (y/n) ");
        scanf("%c", &sel);
        getchar();

        if (sel == 'y') {
			for(int i = 1; i<100; i++){
				if(p->flight_path[i] == -1)
					break;
				timetable[p->flight_date[i]][p->flight_path[i-1]][p->flight_path[i]][2]--;
				timetable[p->flight_date[i]][p->flight_path[i-1]][p->flight_path[i]][2+p->flight_seat[i]] = 0;
			}

            T.remove(r_id);
            printf("Successfully cancelled reservation (Reservation ID: %d)\n", r_id);
        }
    }
}
