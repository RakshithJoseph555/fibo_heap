#include <bits/stdc++.h>
#include <stddef.h>
using namespace std;

typedef struct node
{
    int data;
    int degree;
    struct node *parent;
    struct node *child;
    struct node *left;
    struct node *right;
    bool mark = false;
    bool seen = false;

} NODE;

NODE *H_min = NULL; // pointer to minimum element
int H_no = 0;       // no. of nodes in fibonacci heaps

NODE *get_list_node(int n)
{
    NODE *p;

    p = (NODE *)malloc(sizeof(NODE));
    p->data = n;
    p->left = p->right = p;
    return p;
}

void Fib_heap_print()
{
    NODE *temp = H_min;
    if (temp == NULL)
    {
        cout << "The heap is empty2!!!";
    }
    else
    {
        cout << "The root node list is: " << endl;
        do
        {
            cout << temp->data << " ";
            temp = temp->right;
        } while (temp != H_min && temp != NULL);
    }
    cout << endl
         << "Value of H_min is: " << H_min->data << endl;
    return;
}
// linking same degree trees to nodes . here removing y from root list and making child of x
void Fib_heap_link(NODE *y, NODE *x)
{
    (y->left)->right = y->right;
    (y->right)->left = y->left;
    if (x->right == y)
    {
        H_min = x;
    }
    y->left = y->right = y;
    y->parent = x;

    if (x->child == NULL)
        x->child = y;

    y->right = x->child;
    y->left = (x->child)->left;
    ((x->child)->left)->right = y;
    (x->child)->left = y;
    if (y->data < ((x->child)->data))
        x->child = y;
    x->degree = x->degree + 1;
}

/*inserting a node into fibonacci heap*/
void Fib_heap_insert(NODE *x) // x is pointer to new node
{
    x->degree = 0;
    x->parent = NULL;
    x->child = NULL;
    if (H_min == NULL)
        H_min = x;
    else
    {
        x->right = H_min;
        x->left = H_min->left;
        (H_min->left)->right = x;
        H_min->left = x;
        if (x->data < H_min->data)
            H_min = x;
    }
    H_no = H_no + 1;
}

// finding minimum element in fibonacci heaps
void Fib_heap_find_min()
{
    if (H_min != NULL)
        cout << "Minimum element present is:" << H_min->data << endl;
    else
        cout << "No element present" << endl;
}

void consolidate()
{
    int n = log(H_no) / log(2);
    NODE *a[n + 1];
    for (int i = 0; i <= n; i++)
    {
        a[i] = NULL;
    }
    NODE *temp = H_min;
    NODE *temp1 = temp;
    temp = temp->right;
    while (temp != H_min)
    {
        // cout << "hi" << endl;
        int deg = temp1->degree;
        while (a[deg] != NULL)
        {
            NODE *temp2 = a[deg];
            if (temp1->data > temp2->data)
            {
                NODE *temp3 = temp1;
                temp1 = temp2;
                temp2 = temp3;
            }
            if (temp2 == H_min || temp1->right == temp1)
                H_min = temp1;
            Fib_heap_link(temp2, temp1);
            a[deg] = NULL;
            deg++;
        }
        a[deg] = temp1;
        temp1 = temp;
        temp = temp->right;
    }
    for (int i = 0; i <= n; i++)
    {
        if (a[i] != NULL)
        {
            a[i]->left = a[i];
            a[i]->right = a[i];
            if (H_min == NULL)
            {
                H_min = a[i];
            }
            else
            {
                (H_min->left)->right = a[i];
                a[i]->right = H_min;
                a[i]->left = H_min->left;
                H_min->left = a[i];
                if (a[i]->data < H_min->data)
                    H_min = a[i];
            }
        }
    }
}
// Extracting the minimum element
NODE *Fib_heap_extract_min()
{
    NODE *temp = H_min;
    if (temp == NULL)
    {
        cout << "The heap is empty3!!" << endl;
        return NULL;
    }

    NODE *y = temp;

    if (temp->child != NULL)
    {
        NODE *x = temp->child;
        NODE *z = x;
        do
        {
            y = z->right;
            (H_min->left)->right = z;
            z->right = H_min;
            z->left = H_min->left;

            H_min->left = z;
            if (z->data < H_min->data)
            {
                H_min = z;
            }
            z->parent = NULL;
            z = y;
        } while (y != x);
    }

    (temp->left)->right = temp->right;
    (temp->right)->left = temp->left;
    if (temp == temp->right && temp->child == NULL)
        H_min = NULL;
    else
    {
        H_min = temp->right;
        consolidate();
    }
    H_no--;
    return temp;
}

// searching required element
NODE *search(NODE *t, int x)
{
    NODE *temp = t;
    if (temp == NULL)
    {
        cout << "The heap is empty1!!" << endl;
    }
    do
    {
        if (temp->data == x)
        {
            return temp;
        }

        if (temp->child != NULL)
        {
            NODE *te = search(temp->child, x);
            if (te != NULL)
            {
                return te;
            }
        }
        temp = temp->right;
    } while (temp != NULL && temp != t);

    return NULL;
}

// decrease key function
void dec_key(NODE *H_min, int x, int y)
{
    NODE *t = search(H_min, x);
}
void printTree(NODE *t)
{
    if (t == NULL)
    {
        return;
    }

    NODE *temp = t;
    do
    {

        cout << "-> " << temp->data;
        if (temp->child != NULL)
        {
            cout << "( ";
            printTree(temp->child);
            cout << " )";
        }

        temp = temp->right;

    } while (temp != NULL && temp != t);
}
void cut(NODE *x, NODE *y)
{
    // removing node x from the parent y
    x->left->right = x->right;
    x->right->left = x->left;
    x->right = x->left = x;
    x->parent = NULL;
    y->degree = (y->degree) - 1;
    // adding x to root list nodes
    x->right = H_min;
    x->left = H_min->left;
    H_min->left->right = x;
    H_min->left = x;

    x->mark = false;
}

// cascading cut function used in decrease key
void cascading_cut(NODE *y)
{
    NODE *z;
    z = y->parent;
    if (z != NULL)
    {
        if (y->mark == false)
            y->mark = true;
        else
            cut(y, z);
        cascading_cut(z);
    }
}

// decrease key function
void dec_key(int x, int k)
{
    NODE *t = NULL;
    t = search(H_min, x);
    if (t == NULL)
        cout << "node doesn't exist" << endl;

    if (k > t->data)
    {
        cout << "new key greater than older one" << endl;
        return;
    }
    t->data = k;
    NODE *y = NULL;
    y = t->parent;

    if (y != NULL && t->data < y->data)
    {
        cut(t, y);
        cascading_cut(y);
    }
    if (t->data < H_min->data)
        H_min = t;
}
void delete_key(int x)
{
    dec_key(x, -1);
    printTree(H_min);
    // Fib_heap_extract_min();
    return;
}
int main()
{
    fstream info("input.txt", ios_base::in);
    int n;

    while (info >> n)
    {
        Fib_heap_insert(get_list_node(n));
    }
    // Fib_heap_print();
    printTree(H_min);
    cout << H_no << endl;
    Fib_heap_find_min();
    Fib_heap_extract_min();
    printTree(H_min);
    cout << H_no << endl;
    NODE *val = search(H_min, 87);
    if (val == NULL)
    {
        cout << "Not found" << endl;
    }
    else
    {
        cout << val->data << endl;
    }
    Fib_heap_extract_min();
    printTree(H_min);
    cout << H_no << endl;
    // dec_key(34, 30);
    // printTree(H_min);
    // cout << endl;
    // delete_key(6);
    // printTree(H_min);
    // cout << endl;
    // Fib_heap_extract_min();

    // NODE *val = search(H_min, 25);
    // if (val == NULL)
    // {
    //     cout << "Not found" << endl;
    // }
    // else
    // {
    //     cout << val->data << endl;
    // }

    return 0;
}
