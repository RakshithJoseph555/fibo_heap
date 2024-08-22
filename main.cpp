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

void Fib_heap_link(NODE *y, NODE *x)
{
    (y->left)->right = y->right;
    (y->right)->left = y->left;
    // if (x->right == y)
    // {
    //     H_min = x;
    // }
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
    y->mark = false;
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
void printTree(NODE *t)
{
    if (t == NULL)
    {
        cout << "The tree is empty" << endl;
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
    do
    {
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
            if (temp2 == H_min)
            {
                H_min = temp2->right;
            }

            if (temp2 == temp)
                temp = temp->right;

            Fib_heap_link(temp2, temp1);
            a[deg] = NULL;
            deg++;
        }
        a[deg] = temp1;
        temp1 = temp;
        temp = temp->right;
    } while (temp1 != H_min);
    H_min = NULL;
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

    if (temp == temp->right && temp->child == NULL)
        H_min = NULL;
    else
    {
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
        H_min = temp->right;
        (temp->left)->right = temp->right;
        (temp->right)->left = temp->left;
        temp->child = NULL;
        consolidate();
    }
    H_no--;
    return temp;
}

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

void cut(NODE *x, NODE *y)
{
    x->left->right = x->right;
    x->right->left = x->left;
    x->right = x->left = x;
    x->parent = NULL;
    y->degree = (y->degree) - 1;
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
        {
            cut(y, z);
            cascading_cut(z);
        }
    }
}

// decrease key function
void dec_key(int x, int k)
{
    NODE *t = NULL;
    t = search(H_min, x);
    if (t == NULL)
    {

        cout << "node doesn't exist" << endl;
        return;
    }

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
    Fib_heap_extract_min();
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

    int t = -1;
    while (t != 0)
    {
        cout << "Enter 1 to print tree" << endl;
        cout << "Enter 2 to perform extract min" << endl;
        cout << "Enter 3 to delete a key" << endl;
        cout << "Enter 4 to decrease a key" << endl;
        cout << "Enter 5 to find the minimum" << endl;
        cout << "Enter 6 to search the tree" << endl;
        cout << "Enter 7 to exit!!" << endl;
        cin >> t;

        switch (t)
        {
        case 1:
        {
            printTree(H_min);
            cout << endl;
        }
        break;
        case 2:
            Fib_heap_extract_min();
            break;
        case 3:
        {
            cout << "Enter the value of the node to be deleted" << endl;
            int val;
            cin >> val;
            delete_key(val);
        }
        break;
        case 4:
        {
            cout << "Enter the value of the node to decrease, and the new value" << endl;
            int old_k, new_k;
            cin >> old_k >> new_k;
            dec_key(old_k, new_k);
        }
        break;
        case 5:
            Fib_heap_find_min();
            break;
        case 6:
        {
            int v;
            cout << "Enter the value to be searched" << endl;
            cin >> v;
            NODE *temp = search(H_min, v);
            if (temp == NULL)
                cout << "Element not found!!" << endl;
            else
                cout << "Element present in the tree!!" << endl;
        }
        break;
        case 7:
            t = 0;
            break;
        default:
            break;
        }
    }
    return 0;
}
