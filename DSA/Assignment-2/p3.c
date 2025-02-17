#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node
{
    int attack;
    int defence;
    int count;
    int children;
    struct node *left;
    struct node *right;
} node;

node *root = NULL;

int compare_cards(node *a, node *b)
{
    if (a->attack + a->defence < b->attack + b->defence)
        return -1;
    else if (a->attack + a->defence == b->attack + b->defence)
    {
        if (a->attack < b->attack)
            return -1;
        else if (a->attack == b->attack)
            return 0;
        else
            return 1;
    }
    else
        return 1;
}

int sideload = 1;
node *insert(int attack, int defence)
{
    node *new_node = (node *)malloc(sizeof(node));
    new_node->attack = attack;
    new_node->defence = defence;
    new_node->count = 1;
    new_node->left = NULL;
    new_node->right = NULL;
    new_node->children = 0;

    if (root == NULL)
    {
        root = new_node;
        return root;
    }

    node *current = root;
    node *prev = NULL;

    while (current != NULL)
    {
        prev = current;
        if (attack + defence < current->attack + current->defence)
        {
            current->children += sideload;
            current = current->left;
        }
        else if (attack + defence == current->attack + current->defence)
        {
            if (attack < current->attack)
            {
                current->children += sideload;
                current = current->left;
            }
            else if (attack == current->attack)
            {
                current->count += sideload;
                return current;
            }
            else
            {
                current->children += sideload;
                current = current->right;
            }
        }
        else
        {
            current->children += sideload;
            current = current->right;
        }
    }

    if (attack + defence < prev->attack + prev->defence)
        prev->left = new_node;
    else if (attack + defence == prev->attack + prev->defence)
    {
        if (attack < prev->attack)
            prev->left = new_node;
        else
            prev->right = new_node;
    }
    else
        prev->right = new_node;
    return new_node;
}

node *find_node(int a, int d)
{
    node *current = root;
    while (current != NULL)
    {
        if (a + d < current->attack + current->defence)
        {
            current = current->left;
        }
        else if (a + d == current->attack + current->defence)
        {
            if (a < current->attack)
            {
                current = current->left;
            }
            else if (a == current->attack)
            {
                return current;
            }
            else
            {
                current = current->right;
            }
        }
        else
        {
            current = current->right;
        }
    }
    return NULL;
}

int trade(int a1, int d1, int a2, int d2)
{
    if (a2 == -1 && d2 == -1)
    {
        insert(a1, d1);
        return 1;
    }

    node *requested = find_node(a2, d2);
    if (requested == NULL || requested->count < 2)
        return 0;

    node *receiving = find_node(a1, d1);

    if (receiving == NULL)
    {
        insert(a1, d1);
        sideload = -1;
        insert(a2, d2);
        sideload = 1;
        return 1;
    }

    int comp = compare_cards(receiving, requested);
    if (comp == -1)
        return 0;
    else
    {
        sideload = -1;
        insert(a2, d2);
        sideload = 1;
        insert(a1, d1);
        return 1;
    }
}

node *find_left(node *f)
{
    if (f == NULL)
        return NULL;
    if (f->left == NULL)
        return f;
    return find_left(f->left);
}

node *find_right(node *f)
{
    if (f == NULL)
        return NULL;
    if (f->right == NULL)
        return f;
    return find_right(f->right);
}

int build_array(node *current, node **arr, int index)
{
    if (current == NULL)
        return index;

    index = build_array(current->right, arr, index);
    if (current->count > 0)
        arr[index++] = current;
    index = build_array(current->left, arr, index);

    return index;
}

node *kth_strongest(int k, node *curr)
{
    // if (curr == NULL)
    //     return NULL;
    if (curr->children + curr->count < k)
        return NULL;

    int right_children = curr->right == NULL ? 0 : curr->right->children;
    int right_count = curr->right == NULL ? 0 : curr->right->count;

    if (k - right_children - right_count <= curr->count && k - right_children - right_count > 0)
        return curr;

    if (right_children + right_count >= k)
        return kth_strongest(k, curr->right);
    if (curr->left == NULL)
        return NULL;
    return kth_strongest(k - right_children - curr->count - right_count, curr->left);
}

int main()
{

    int n;
    scanf("%d", &n);

    int attack[n];
    int defence[n];
    for (int i = 0; i < n; i++)
    {
        scanf("%d %d", &attack[i], &defence[i]);
    }

    void in(int start, int end)
    {
        if (start > end)
            return;
        int mid = (start + end) / 2;
        insert(attack[mid], defence[mid]);
        in(start, mid - 1);
        in(mid + 1, end);
    }

    in(0, n - 1);

    int q;
    scanf("%d", &q);
    while (q--)
    {
        int a1, d1, a2, d2;
        char temp[20];
        scanf("%s", temp);
        if (strcmp(temp, "TRADE") == 0)
        {
            scanf("%d %d %d %d", &a1, &d1, &a2, &d2);
            printf("%d\n", trade(a1, d1, a2, d2));
        }
        else if (strcmp(temp, "KTH_STRONGEST") == 0)
        {
            scanf("%d", &a1);
            node *stronk = kth_strongest(a1, root);
            if (stronk == NULL)
                printf("-1\n");
            else
                printf("%d %d %d\n", stronk->attack, stronk->defence, stronk->count);
        }
    }

    node *arr[n];
    int total = build_array(root, arr, 0);
    printf("%d\n", total);
    for (int i = 0; i < total; i++)
        printf("%d %d %d\n", arr[i]->attack, arr[i]->defence, arr[i]->count);
}