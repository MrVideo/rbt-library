#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define RED 'r'
#define BLACK 'b'

// RBT Node
struct tnode {
    struct tnode *left, *right, *parent;
    char color;
    char data[];
};

// RBT Pointer
typedef struct tnode *tree;

// Linked List Node
struct lnode {
    struct lnode *next;
    char data[];
};

// Linked List Pointer
typedef struct lnode *list;

void inorder_tree_walk(tree t);
tree rbt_search(tree t, const char data[]);
void rbt_insert(tree *t, const char *data, int len);
void left_rotate(tree *root, tree *node);
void right_rotate(tree *root, tree *node);
void rbt_insert_fixup(tree *t, tree *z);
void add_to_list(tree *t, list *l, int len);
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
    rbt_insert(&t, data3, (int) strlen(data3));

    add_to_list(&t, &l, 5);

    inorder_tree_walk(t);
    print_list(l);

    destroy_list(&l);

    inorder_tree_walk(t);
    print_list(l);

    return 0;
}

void add_to_list(tree *t, list *l, int len) {
    if(*t == NULL) return;

    add_to_list(&(*t)->right, l, len);
    list tmp = malloc(sizeof(struct lnode) + sizeof(char) * (len + 1));
    strcpy(tmp->data, (*t)->data);
    tmp->next = *l;
    *l = tmp;
    add_to_list(&(*t)->left, l, len);
}

void inorder_tree_walk(tree t) {
    if(t == NULL) {
        printf("End of tree\n");
        return;
    }
    inorder_tree_walk(t->left);
    printf("%s\n", t->data);
    inorder_tree_walk(t->right);
}

tree rbt_search(tree t, const char *data) {
    int search_result;
    if(t == NULL) return t;
    else {
        search_result = strcmp(t->data, data);
        if(!search_result) return t;
        else if(search_result < 0) return rbt_search(t->right, data);
        else return rbt_search(t->left, data);
    }
}

void rbt_insert(tree *t, const char *data, int len) {
    tree z = malloc(sizeof(struct tnode) + sizeof(char) * (len + 1));
    strcpy(z->data, data);
    tree y = NULL, x = *t;

    while(x != NULL) {
        y = x;
        if(strcmp(z->data, x->data) < 0)
            x = x->left;
        else x = x->right;
    }
    z->parent = y;
    if(y == NULL) *t = z;
    else if(strcmp(z->data, y->data) < 0)
        y->left = z;
    else y->right = z;
    z->left = NULL;
    z->right = NULL;
    z->color = RED;
    rbt_insert_fixup(t, &z);
}

void left_rotate(tree *root, tree *node) {
    tree tmp = (*node)->right;
    (*node)->right = tmp->left;
    if(tmp->left != NULL)
        tmp->left->parent = *node;
    tmp->parent = (*node)->parent;
    if((*node)->parent == NULL)
        *root = tmp;
    else if(*node == (*node)->parent->left)
        (*node)->parent->left = tmp;
    else (*node)->parent->right = tmp;
    tmp->left = *node;
    (*node)->parent = tmp;
}

void right_rotate(tree *root, tree *node) {
    tree tmp = (*node)->left;
    (*node)->left = tmp->right;
    if(tmp->right != NULL)
        tmp->right->parent = (*node);
    tmp->parent = (*node)->parent;
    if((*node)->parent == NULL)
        *root = tmp;
    else if((*node) == (*node)->parent->left)
        (*node)->parent->left = tmp;
    else (*node)->parent->right = tmp;
    tmp->right = (*node);
    (*node)->parent = tmp;
}

void rbt_insert_fixup(tree *t, tree *z) {
    tree parent = NULL, grandparent = NULL;

    while(((*z) != *t) && ((*z)->color != BLACK) && ((*z)->parent->color == RED)) {
        parent = (*z)->parent;
        grandparent = (*z)->parent->parent;

        if(parent == grandparent->left) {
            tree uncle = grandparent->right;
            if(uncle != NULL && uncle->color == RED) {
                grandparent->color = RED;
                parent->color = BLACK;
                uncle->color = BLACK;
                *z = grandparent;
            } else {
                if((*z) == parent->right) {
                    left_rotate(t, &parent);
                    (*z) = parent;
                    parent = (*z)->parent;
                }
                right_rotate(t, &grandparent);
                parent->color = BLACK;
                grandparent->color = RED;
                (*z) = parent;
            }
        } else {
            tree uncle = grandparent->left;
            if(uncle != NULL && uncle->color == RED) {
                grandparent->color = RED;
                parent->color = BLACK;
                uncle->color = BLACK;
                *z = grandparent;
            } else {
                if((*z) == parent->left) {
                    right_rotate(t, &parent);
                    (*z) = parent;
                    parent = (*z)->parent;
                }
                left_rotate(t, &grandparent);
                parent->color = BLACK;
                grandparent->color = RED;
                (*z) = parent;
            }
        }
    }
    (*t)->color = BLACK;
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

