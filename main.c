#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define RED 'r'
#define BLACK 'b'

// RBT Node
struct tnode {
    struct tnode *left, *right, *parent;
    char colour;
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
void rbt_insert(tree t, const char *data, int len);
void left_rotate(tree *root, tree *node);
void right_rotate(tree *root, tree *node);
void rbt_insert_fixup(tree t, tree node);

int main() {

    return 0;
}

void inorder_tree_walk(tree t) {
    if(t == NULL) return;
    inorder_tree_walk(t->left);
    printf("%s", t->data);
    inorder_tree_walk(t->right);
}

tree rbt_search(tree t, const char *data) {
    int search_result = strcmp(data, t->data);
    if(!search_result || t == NULL) return t;
    else if(search_result < 0) return rbt_search(t->left, data);
    else return rbt_search(t->right, data);
}

void rbt_insert(tree t, const char *data, int len) {
    tree new_node = malloc(sizeof(struct tnode) + sizeof(char) * (len + 1));
    strcpy(new_node->data, data);
    tree tmp = NULL, root = t;

    while(root != NULL) {
        tmp = root;
        if(strcmp(new_node->data, root->data) < 0)
            root = root->left;
        else root = root->right;
    }
    new_node->parent = tmp;
    if(tmp == NULL) t = new_node;
    else if(strcmp(new_node->data, tmp->data) < 0)
        tmp->left = new_node;
    else tmp->right = new_node;
    new_node->left = NULL;
    new_node->right = NULL;
    new_node->colour = RED;
    rbt_insert_fixup(t, new_node);
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


void rbt_insert_fixup(tree t, tree node) {

}
