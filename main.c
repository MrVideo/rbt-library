#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rbt.h"

void print_list(list l);
void destroy_list(list *l);

int main() {
    // Tree implementation testing
    tree t = NULL;
    list l = NULL;
    char data1[] = "abcde";
    char data2[] = "aaaaa";
    char data3[] = "mmmmm";
    rbt_insert(&t, data1, (int)strlen(data1));
    rbt_insert(&t, data2, (int)strlen(data2));
    rbt_insert(&t, data3, (int)strlen(data3));

    add_to_list(&t, &l, 5);

	printf("Tree structure:\n");
    inorder_tree_walk(t);

	printf("\nList structure:\n");
    print_list(l);

    destroy_list(&l);

	printf("\nTree structure:\n");
    inorder_tree_walk(t);

	printf("\nList structure (deleted)\n");
    print_list(l);

    return 0;
}

void print_list(list l) {
    list curr = l;
    while(curr != NULL) {
        printf("%s -> ", curr->data);
        curr = curr->next;
    }
    printf("END\n");
}

void destroy_list(list *l) {
    list curr = *l, tmp = NULL;
    while(curr != NULL) {
        tmp = curr->next;
        free(curr);
        curr = tmp;
    }
    free(tmp);
    *l = NULL;
    l = NULL;
}

