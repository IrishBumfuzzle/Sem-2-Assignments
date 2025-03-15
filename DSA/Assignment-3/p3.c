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

void preorder(struct node *root, int *arr, int *idx, int k)
{
    if (root == NULL || *idx >= k)
    {
        return;
    }
    preorder(root->left, arr, idx, k);
    if (*idx >= k)
    {
        return;
    }
    arr[*idx] = root->data;
    *idx = *idx + 1;
    preorder(root->right, arr, idx, k);
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

int largest(struct node *root)
{
    if (root == NULL)
        return -1;
    if (root->right == NULL)
    {
        return root->data;
    }
    return largest(root->right);
}

void heapify(int *arr, int n, int i)
{
    int change = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < n && arr[l] > arr[change])
    {
        change = l;
    }
    if (r < n && arr[r] > arr[change])
    {
        change = r;
    }

    if (change != i)
    {
        int temp = arr[i];
        arr[i] = arr[change];
        arr[change] = temp;

        heapify(arr, n, change);
    }
}

void pop(int *arr, int *n)
{
    arr[0] = arr[*n - 1];
    *n = *n - 1;
    heapify(arr, *n, 0);
}

void inserth(int *arr, int *n, int x)
{
    arr[*n] = x;
    *n = *n + 1;

    int i = *n - 1;
    while (i > 0 && arr[(i - 1) / 2] < arr[i])
    {
        int temp = arr[i];
        arr[i] = arr[(i - 1) / 2];
        arr[(i - 1) / 2] = temp;

        i = (i - 1) / 2;
    }
}

void in(struct node **rootK, struct node **rootMain, int el, int *total, int k, long long *sum)
{
    if (*total < k)
    {
        (*rootK) = insert(*rootK, el);
        (*total)++;
        *sum += el;
    }
    else if (el < largest(*rootK))
    {
        int x = largest(*rootK);
        (*rootK) = insert(*rootK, el);
        (*rootK) = delete (*rootK, x);
        (*rootMain) = insert(*rootMain, x);
        *sum -= x;
        *sum += el;
    }
    else
    {
        (*rootMain) = insert(*rootMain, el);
    }
}

void del(struct node **rootK, struct node **rootMain, int el, int *total, int k, long long *sum)
{
    if (largest(*rootK) >= el)
    {
        (*rootK) = delete (*rootK, el);
        (*total)--;
        *sum -= el;
        if (least(*rootMain) > -1)
        {
            int x = least(*rootMain);
            (*rootMain) = delete (*rootMain, x);
            (*rootK) = insert(*rootK, x);
            *sum += x;
            (*total)++;
        }
    }
    else
    {
        (*rootMain) = delete (*rootMain, el);
    }
}

int main()
{
    int n, k;
    scanf("%d %d", &n, &k);
    struct node *rootMain = NULL;
    struct node *rootK = NULL;
    int rootKEls = 0;
    long long sumK = 0;

    for (int i = 0; i < n; i++)
    {
        int x;
        scanf("%d", &x);
        in(&rootK, &rootMain, x, &rootKEls, k, &sumK);
    }

    int u;
    scanf("%d", &u);

    while (u--)
    {
        int op;
        scanf("%d", &op);

        if (op == 1)
        {
            int x;
            scanf("%d", &x);
            in(&rootK, &rootMain, x, &rootKEls, k, &sumK);
        }
        else if (op == 2)
        {
            int x;
            scanf("%d", &x);
            del(&rootK, &rootMain, x, &rootKEls, k, &sumK);
        }
        else
        {
            int x, y;
            scanf("%d %d", &x, &y);
            del(&rootK, &rootMain, x, &rootKEls, k, &sumK);
            in(&rootK, &rootMain, y, &rootKEls, k, &sumK);
        }

        printf("%lld\n", sumK);
    }
}