// Define colours
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

// Function signatures
void inorder_tree_walk(tree t);
tree rbt_search(tree t, const char data[]);
void rbt_insert(tree *t, const char *data, int len);
void left_rotate(tree *root, tree *node);
void right_rotate(tree *root, tree *node);
void rbt_insert_fixup(tree *t, tree *z);
void add_to_list(tree *t, list *l, int len);
