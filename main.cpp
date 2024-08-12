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

NODE *get_list_node(void)
{
    NODE *p;

    p = (NODE *)malloc(sizeof(NODE));
    cout << "enter value node to be inserted:";
    cin >> p->data;
    p->left = p->right = p;
    return p;
}

/*inserting a node into fibonacci heap*/
void Fib_heap_insert(NODE *H_min, NODE *x) // x is pointer to new node
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
        H_min->left->right = x;
        H_min->left = x;
        if (x->data < H_min->data)
            H_min = x;
    }
    H_no = H_no + 1;
}

// finding minimum element in fibonacci heaps
void Fib_heap_find_min(NODE *H_min)
{
    if (H_min != NULL)
        cout << "Minimum element present is:" << H_min->data << endl;
    else
        cout << "No element present" << endl;
}

// Extracting the minimum element
NODE *Fib_heap_extract_min(NODE *H_min)
{
    NODE *temp = H_min;
    if (!temp)
    {
        NODE *x = temp->child;
        NODE *y = x;
        NODE *z = x;
        do
        {

            x->right = H_min;
            x->left = H_min->left;
            H_min->left->right = x;
            H_min->left = x;
            x->parent = NULL;
            x = y->right;
        } while (x != z);
    }
    temp->left->right = temp->right;
    temp->right->left = temp->left;
    if (temp = temp->right)
        H_min = NULL;
    else
    {
        H_min = temp->right;
        consolidate(H_min);
    }
    H_no--;
    return temp;
}

// linking same degree trees to nodes . here removing y from root list and making child of x
void Fib_heap_link(NODE *y, NODE *x)
{
    y->left->right = y->right;
    y->right->left = y->left;
    y->left = y->right = y;
    y->parent = x;

    if (x->child == NULL)
        x->child = y;
    else
    {
        y->right = x->child;
        y->left = x->child->left;
        x->child->left->right = y;
        x->child->left = y;
    }
    x->degree = x->degree + 1;
    y->mark = false;
}

// consolidate function
void consolidate(NODE *H_min)
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
        if (!a[i])
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

//searching required element
NODE* search(NODE* temp,int x)
{
     NODE* temp2=temp;
  //  NODE* temp3=NULL;
    temp2->seen=true;
    
    if(temp2->data==x)
        return temp2;
    else if(temp2->degree !=0)
    {
        /*temp3= */ search(temp2->child,x);
    }
 
    if(temp2->right->seen == false)
    {
       /* temp4=*/search(temp2->right,x);
    }
    else
    {
       
        return 0;
    }
        
}

//decrease key function
void dec_key(NODE* H_min, int x,int y)
{
    NODE* t=search( H-min, x);
    
}




int main()
{
    // We will create a heap and insert 3 nodes into it
    cout << "Creating an initial heap" << endl;
    NODE *x = get_list_node();
    // Fib_heap_insert(H_min,get_list_node());
    // Fib_heap_insert(H_min, get_list_node());
    // Fib_heap_insert(H_min, get_list_node());

    // cout << "Extracting min" << endl;
    // Extract_min();
    // display();

    // // Now we will decrease the value of node '8' to '7'
    // cout << "Decrease value of 8 to 7" << endl;
    // Find(H_min, 8, 7);
    // display();

    // // Now we will delete the node '7'
    // cout << "Delete the node 7" << endl;
    // Deletion(7);
    // display();

    return 0;
}
