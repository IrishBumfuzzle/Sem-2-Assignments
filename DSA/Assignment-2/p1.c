#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node
{
    int attack;
    int defence;
    int count;
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

void insert(int attack, int defence)
{
    node *new_node = (node *)malloc(sizeof(node));
    new_node->attack = attack;
    new_node->defence = defence;
    new_node->count = 1;
    new_node->left = NULL;
    new_node->right = NULL;

    if (root == NULL)
    {
        root = new_node;
        return;
    }

    node *current = root;
    node *prev = NULL;

    while (current != NULL)
    {
        prev = current;
        if (attack + defence < current->attack + current->defence)
        {
            current = current->left;
        }
        else if (attack + defence == current->attack + current->defence)
        {
            if (attack < current->attack)
            {
                current = current->left;
            }
            else if (attack == current->attack)
            {
                prev->count++;
                return;
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

    if (attack + defence < prev->attack + prev->defence)
    {
        prev->left = new_node;
    }
    else if (attack + defence == prev->attack + prev->defence)
    {
        if (attack < prev->attack)
        {
            prev->left = new_node;
        }
        else
        {
            prev->right = new_node;
        }
    }
    else
    {
        prev->right = new_node;
    }
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
        node *receiving = find_node(a1, d1);
        if (receiving == NULL)
            insert(a1, d1);
        else
            receiving->count++;
        return 1;
    }

    node *requested = find_node(a2, d2);
    if (requested == NULL || requested->count < 2)
        return 0;

    node *receiving = find_node(a1, d1);

    if (receiving == NULL)
    {
        insert(a1, d1);
        requested->count--;
        return 1;
    }

    int comp = compare_cards(receiving, requested);
    if (comp == -1)
        return 0;
    else
    {
        requested->count--;
        receiving->count++;
        return 1;
    }
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

int main()
{

    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
    {
        int a, d;
        scanf("%d %d", &a, &d);
        insert(a, d);
    }

    int q;
    scanf("%d", &q);
    while (q--)
    {
        int a1, d1, a2, d2;
        char temp[20];
        scanf("%s %d %d %d %d", temp, &a1, &d1, &a2, &d2);
        printf("%d\n", trade(a1, d1, a2, d2));
    }

    node *arr[n];
    int total = build_array(root, arr, 0);
    printf("%d\n", total);
    for (int i = 0; i < total; i++)
    {
        printf("%d %d %d\n", arr[i]->attack, arr[i]->defence, arr[i]->count);
    }
}