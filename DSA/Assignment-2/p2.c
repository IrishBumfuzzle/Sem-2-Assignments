#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node
{
    int attack;
    int defence;
    int count;
    struct node *parent;
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

node *insert(int attack, int defence)
{
    node *new_node = (node *)malloc(sizeof(node));
    new_node->attack = attack;
    new_node->defence = defence;
    new_node->count = 1;
    new_node->parent = NULL;
    new_node->left = NULL;
    new_node->right = NULL;

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
            current = current->left;
        else if (attack + defence == current->attack + current->defence)
        {
            if (attack < current->attack)
                current = current->left;
            else if (attack == current->attack)
            {
                prev->count++;
                return prev;
            }
            else
                current = current->right;
        }
        else
            current = current->right;
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
    new_node->parent = prev;
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

int compare(int a, int d)
{
    node *og = find_node(a, d);
    node *n = NULL;

    if (og == NULL)
        n = insert(a, d);
    else
        n = og;

    node *strongest_weaker = n != NULL ? find_right(n->left) : NULL;
    node *weakest_stronger = n != NULL ? find_left(n->right) : NULL;

    if (strongest_weaker == NULL)
    {
        if (n != NULL)
        {
            strongest_weaker = n;
            while (strongest_weaker != NULL)
            {
                if (strongest_weaker->parent != NULL && strongest_weaker->parent->right == strongest_weaker)
                {
                    strongest_weaker = strongest_weaker->parent;
                    break;
                }
                else
                    strongest_weaker = strongest_weaker->parent;
            }
        }
    }
    if (weakest_stronger == NULL)
    {
        weakest_stronger = n;
        while (weakest_stronger != NULL)
        {
            if (weakest_stronger->parent != NULL && weakest_stronger->parent->left == weakest_stronger)
            {
                weakest_stronger = weakest_stronger->parent;
                break;
            }
            else
                weakest_stronger = weakest_stronger->parent;
        }
    }

    printf("%d\n", og != NULL ? og->count : 0);

    strongest_weaker != NULL ? printf("%d %d %d\n", strongest_weaker->attack, strongest_weaker->defence, strongest_weaker->count) : printf("-1\n");
    weakest_stronger != NULL ? printf("%d %d %d\n", weakest_stronger->attack, weakest_stronger->defence, weakest_stronger->count) : printf("-1\n");

    if (og == NULL)
    {
        if (n->parent->right == n)
            n->parent->right = NULL;
        else
            n->parent->left = NULL;
        free(n);
    }

    return 0;
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
        else if (strcmp(temp, "COMPARE") == 0)
        {
            scanf("%d %d", &a1, &d1);
            compare(a1, d1);
        }
    }

    node *arr[n];
    int total = build_array(root, arr, 0);
    printf("%d\n", total);
    for (int i = 0; i < total; i++)
        printf("%d %d %d\n", arr[i]->attack, arr[i]->defence, arr[i]->count);
}