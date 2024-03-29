#include <cstdio>
#include <cstring>
#include "RBtree.h"
#include "Path.h"
#include "Path_finder.h"

extern Tree T;
extern Path_finder *P;
void check_reservation_print_menu(char* name, int date, char src, char dst)
{
    printf("===== Check reservation ======\n");
    printf("Name: %s\n", name);
    printf("Dep. date: %2d\n", date);
    printf("From: %c\n", src);
    printf("To: %c\n", dst);
}

void check_reservation(void)
{
    int r_id;
    printf("Enter your reservation id: ");
    scanf("%d", &r_id);
    getchar();

    Node* customer = T.search(T.root, r_id, T.NIL);
    if (customer->reserve_id != r_id) {
        printf("Cannot find reservation for given reservation id (%d)\n", r_id);
        return;
    } else {
        Path *p = customer->path;
        check_reservation_print_menu(customer->name, customer->path->dep_time[0], \
                customer->path->source + 'A', customer->path->dest + 'A');
        P->printPath(p);
        printf("This is reservation info for given reservation id (%d)\n", r_id);
    }
}
