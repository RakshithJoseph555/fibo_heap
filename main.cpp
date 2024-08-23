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

void Fib_heap_insert(NODE *x);
//to insert a new node to fibonacci heaps and x is pointer to new node

void Fib_heap_find_min();
//to find minimum element element in fib_heaps ie. H_min

NODE *Fib_heap_extract_min();
//to delete minimum element from fib_heaps ie. H_min and returns pointer of deleted element

void dec_key(int x, int k);
//to decrease old key to new key ie. 'x' is old key and 'k' is new key

void delete_key(int x);
//delete any element from fib_heaps 'x' is key to be deleted

void printTree(NODE *t);
//print all nodes present in fib_heaps 't' is pointer to minimum element ie.H_min

NODE *search(NODE *t, int x);
//search required element in fiib_heaps ie.'x','t' is pointer to min element ie.H_min and return pointer to 'x'

//dynamically allocates memory to NODE* and returns pointer to that node
NODE *get_list_node(int n)   
{
    NODE *p;

    p = (NODE *)malloc(sizeof(NODE));
    p->data = n;
    p->left = p->right = p;
    return p;
}

/*inserting a node into fibonacci heap*/
void Fib_heap_insert(NODE *x) // x is pointer to new node
{
    x->degree = 0;          //initialize all parameters
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
    H_no = H_no + 1;     //increment total no. of node count 
}
void printTree(NODE *t)
{
    if (t == NULL)
    {
        cout << "The tree is empty" << endl;
        return;
    }

    NODE *temp = t;
    do          //printing tree recursively
    {   

        cout << "-> " << temp->data;
        if (temp->child != NULL)
        {
            cout << "( ";              //ie. x->(->y) represents y is child of y
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

//link the nodes with same degree together ie. node y and node x have same degree
//make node 'y' child of node 'x'
void Fib_heap_link(NODE *y, NODE *x)
{
    (y->left)->right = y->right;
    (y->right)->left = y->left;
    
    y->left = y->right = y;
    y->parent = x;

    if (x->child == NULL)     //if x child list of x id empty then x->child=y
        x->child = y;

    y->right = x->child;
    y->left = (x->child)->left;
    ((x->child)->left)->right = y;
    (x->child)->left = y;
    if (y->data < ((x->child)->data))
        x->child = y;
    x->degree = x->degree + 1;     //increment degree of 'x'
    y->mark = false;
}

//no two nodes in root list should have same degree
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

NODE *search(NODE *t, int x)     //searching for element recursively
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

/*'x' is child node of parent node 'y' 
cut function cuts the link between 'x' and 'y' and adds 'x' to the root list*/
void cut(NODE *x, NODE *y)
{
    if (x == x->right)         //if parent has only one child than make parent->child=NULL
        y->child = NULL;
    x->left->right = x->right;
    x->right->left = x->left;
    if (x == y->child)        //if 'x' is not only in the child list of 'y' then make parent->child=x->right
        y->child = x->right;
    x->right = x->left = x;
    x->parent = NULL;          //cut link between 'x' AND 'y'
    y->degree = (y->degree) - 1;  //reduce degree of 'y' by 1
    x->right = H_min;            
    x->left = H_min->left;        //add 'x' to root list node
    H_min->left->right = x;
    H_min->left = x;            

    x->mark = false;          // clears x->mark and indicates that 'x' has been in the root list
}

// cascading cut function used in decrease key ie. 'y' is parent node of updated key ie. 'x'
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
            cut(y, z);    //if previously any node was cut from child list of parent 'y' then that parent is cut and added to root list
            cascading_cut(z);
        }
    }
}

// decrease key function
void dec_key(int x, int k)
{
    NODE *t = NULL;
    t = search(H_min, x); //search for the node whose key want to decrease
    if (t == NULL)
    {

        cout << "node doesn't exist" << endl;
        return;
    }

    if (k > t->data)    //if new key larger than old one then return
    {
        cout << "new key greater than older one" << endl;
        return;
    }
    t->data = k;  //update key to lesser
    NODE *y = NULL;
    y = t->parent;      //mark a pointer to parent of updated key

    if (y != NULL && t->data < y->data)  //check whether updated value is lesser than parent
    {
        cut(t, y);              //cut on updated node 
        cascading_cut(y);      //cascade cut on parent of updated node
    }
    if (t->data < H_min->data)     //if updated key is less than H_min then update H_min pointer
        H_min = t;
}
//delete key function
void delete_key(int x)
{
    NODE* t;
    dec_key(x, INT_MIN);        //calling decrease key function with very very small value ie. H_min=INT_MIN
    t=Fib_heap_extract_min();     //calling extract min() will actually delete desired element 
    free(t);
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
        cout << "Enter 7 to insert a node"  <<endl;
        cout << "Enter 8 to exit!!" << endl;
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
            NODE* f;
            f=Fib_heap_extract_min();
            free(f);
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
           { cout<<"value of node you want to insert:" <<endl;
            int val;
            cin>>val;
            Fib_heap_insert(get_list_node(val));}
            break;
        case 8:
            t=0;
            break;
        default:
            break;
        }
    }
    return 0;
}
