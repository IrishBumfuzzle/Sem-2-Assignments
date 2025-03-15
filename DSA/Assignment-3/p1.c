#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

// structure of the tree node
struct node
{
    int data;
    struct node *left;
    struct node *right;
    int ht;
};

// function prototyping
struct node *create(int);                 // Creates a new tree node with the given data and returns it
struct node *insert(struct node *, int);  // Inserts a new node in the AVL tree and returns the root of the tree
struct node *delete(struct node *, int);  // Deletes *one* occurrence of the given data from the AVL tree, does nothing if the data is not found and returns the root of the tree
struct node *search(struct node *, int);  // Searches for the given data in the AVL tree, returns the node if found, NULL otherwise
struct node *rotate_left(struct node *);  // Rotates the tree rooted at the given node to the left and returns the new root
struct node *rotate_right(struct node *); // Rotates the tree rooted at the given node to the right and returns the new root
int balance_factor(struct node *);        // returns the balance factor of the given node
int height(struct node *);                // returns the height of the given node
int largest(struct node *);

struct node *create(int data)
{
    struct node *new_node = (struct node *)malloc(sizeof(struct node));
    assert(new_node != NULL);
    new_node->data = data;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

struct node *rotate_left(struct node *root)
{
    struct node *right_child = root->right;
    root->right = right_child->left;
    right_child->left = root;

    // update the heights of the nodes
    root->ht = height(root);
    right_child->ht = height(right_child);

    // return the new node after rotation
    return right_child;
}

struct node *rotate_right(struct node *root)
{
    struct node *left_child = root->left;
    root->left = left_child->right;
    left_child->right = root;

    // update the heights of the nodes
    root->ht = height(root);
    left_child->ht = height(left_child);

    // return the new node after rotation
    return left_child;
}

int balance_factor(struct node *root)
{
    int lh, rh;
    if (root == NULL)
        return 0;
    if (root->left == NULL)
        lh = 0;
    else
        lh = 1 + root->left->ht;
    if (root->right == NULL)
        rh = 0;
    else
        rh = 1 + root->right->ht;
    return lh - rh;
}

int height(struct node *root)
{
    int lh, rh;
    if (root == NULL)
        return 0;
    if (root->left == NULL)
        lh = 0;
    else
        lh = 1 + root->left->ht;
    if (root->right == NULL)
        rh = 0;
    else
        rh = 1 + root->right->ht;
    if (lh > rh)
        return (lh);
    return (rh);
}

struct node *insert(struct node *root, int data)
{
    if (root == NULL)
    {
        struct node *new_node = create(data);
        if (new_node == NULL)
        {
            return NULL;
        }
        root = new_node;
    }
    else if (data < root->data)
    {
        // Insert into left subtree
        root->left = insert(root->left, data);

        // Balance the tree
        if (balance_factor(root) == 2)
        {
            if (data < root->left->data)
            {
                root = rotate_right(root);
            }
            else
            {
                root->left = rotate_left(root->left);
                root = rotate_right(root);
            }
        }
    }
    else
    {
        // Insert into right subtree
        root->right = insert(root->right, data);

        // Balance the tree
        if (balance_factor(root) == -2)
        {
            if (data >= root->right->data)
            {
                root = rotate_left(root);
            }
            else
            {
                root->right = rotate_right(root->right);
                root = rotate_left(root);
            }
        }
    }

    // Update height
    root->ht = height(root);
    return root;
}

struct node *delete(struct node *root, int x)
{
    if (root == NULL)
    {
        return NULL;
    }

    if (x < root->data)
    {
        root->left = delete (root->left, x);
    }
    else if (x > root->data)
    {
        root->right = delete (root->right, x);
    }
    else
    { // Found the node to delete
        if (root->left == NULL)
        {
            struct node *temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL)
        {
            struct node *temp = root->left;
            free(root);
            return temp;
        }
        else
        {
            // Find successor (smallest value in right subtree)
            struct node *temp = root->right;
            while (temp->left != NULL)
            {
                temp = temp->left;
            }

            // Replace data with successor value
            root->data = temp->data;

            // Delete the duplicate node from the right subtree
            root->right = delete (root->right, temp->data);
        }
    }

    // Update height
    root->ht = height(root);

    // Balance the tree
    int bf = balance_factor(root);

    if (bf == 2)
    {
        if (balance_factor(root->left) >= 0)
        {
            root = rotate_right(root);
        }
        else
        {
            root->left = rotate_left(root->left);
            root = rotate_right(root);
        }
    }
    else if (bf == -2)
    {
        if (balance_factor(root->right) <= 0)
        {
            root = rotate_left(root);
        }
        else
        {
            root->right = rotate_right(root->right);
            root = rotate_left(root);
        }
    }

    return root;
}

struct node *search(struct node *root, int key)
{
    if (root == NULL)
    {
        return root;
    }

    if (root->data == key)
    {
        return root;
    }

    if (key > root->data)
    {
        return search(root->right, key);
    }
    else
    {
        return search(root->left, key);
    }
}

int least(struct node *root)
{
    if (root == NULL)
        return -1;
    if (root->left == NULL)
    {
        return root->data;
    }
    return least(root->left);
}

typedef struct el
{
    int x, type, h;
} el;

int comp(const void *x, const void *y)
{
    el *a = (el *)x;
    el *b = (el *)y;
    if (a->x == b->x)
    {
        return a->type - b->type;
    }
    return a->x > b->x ? 1 : -1;
}

void heapify(el *arr, int n, int i)
{
    int change = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < n && comp(&arr[change], &arr[l]) < 0)
    {
        change = l;
    }
    if (r < n && comp(&arr[change], &arr[r]) < 0)
    {
        change = r;
    }

    if (change != i)
    {
        el temp = arr[i];
        arr[i] = arr[change];
        arr[change] = temp;

        heapify(arr, n, change);
    }
}


void heapsort(el* arr, int size){
    for(int i = size/2-1; i >= 0; i--){
        heapify(arr, size, i);
    }
    for(int i = 0; i < size; i++){
        el temp = arr[size-1-i];
        arr[size-1-i] = arr[0];
        arr[0] = temp;
        heapify(arr, size-1-i, 0);
    }
}

int main()
{
    int n;
    scanf("%d", &n);
    struct node *root = NULL;
    el *arr = (el *)malloc(2 * n * sizeof(el));

    for (int i = 0; i < n; i++)
    {
        int x, y;
        scanf("%d %d", &x, &y);
        int h = y - x + 1;
        arr[2 * i].x = x, arr[2 * i].type = 0, arr[2 * i].h = h;
        arr[2 * i + 1].x = y, arr[2 * i + 1].type = 2, arr[2 * i + 1].h = h;
    }

    int q;
    scanf("%d", &q);
    arr = (el *)realloc(arr, (2 * n + q) * sizeof(el));
    for (int i = 0; i < q; i++)
    {
        int x;
        scanf("%d", &x);
        arr[2 * n + i].x = x, arr[2 * n + i].type = 1, arr[2 * n + i].h = i;
    }

    // qsort(arr, 2 * n + q, sizeof(el), comp);
    heapsort(arr, 2 * n + q);

    int ans[q];

    for (int i = 0; i < 2 * n+q; i++)
    {
        if (arr[i].type == 0)
        {
            root = insert(root, arr[i].h);
        }
        else if (arr[i].type == 2)
        {
            root = delete(root, arr[i].h);
        }
        else{
            ans[arr[i].h] = least(root);
        }
    }

    for (int i = 0; i < q; i++)
    {
        printf("%d\n", ans[i]);
    }
}