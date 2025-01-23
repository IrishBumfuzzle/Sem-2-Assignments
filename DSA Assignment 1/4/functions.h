typedef struct Node *PtrNode;

typedef struct Node
{
    int Element;
    PtrNode NextNode;
    PtrNode PrevNode;
} Node;

PtrNode Insert(PtrNode Head, int num);
PtrNode Find(PtrNode Head, int num);
void Print(PtrNode Head);