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
        H_min->left->right = x;
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

//cut function used in decrease key
void cut(NODE* x, NODE* y)
{
    //removing node x from the parent y
    x->left->right=x->right;
    x->right->left=x->left;
    x->right=x->left=x;
    x->parent=NULL;
    y->degree=(y->degree)-1;
    //adding x to root list nodes
     x->right = H_min;
        x->left = H_min->left;
        H_min->left->right = x;
        H_min->left = x;

    x->mark=false;
}

//cascading cut function used in decrease key
void cascading_cut(NODE* y)
{
    NODE* z;
    z=y->parent;
   if(z!=NULL)
   {
       if(y->mark==false)
           y->mark=true;
       else
           cut(y,z);
           cascading_cut(z);
   }   
}

//decrease key function
void dec_key(int x,int k)
{
    NODE* t=NULL;
    t=search( H-min, x);
    if(t==NULL)
        cout<<"node doesn't exist"<<endl;

    if(k>x->data)
    {
        cout<<"new key greater than older one"<<endl;
        return ;
    }
    x->data=k;
    NODE* y=NULL;
    y=x->parent;

    if(y!=NULL && x->data < y->data)
    {
        cut(H_min,x,y);
        cascading_cut(H_min,y);
    }
    if (x->data < H_min->data)
            H_min = x;    
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
    cout << endl;
    Fib_heap_find_min();
    Fib_heap_extract_min();
    printTree(H_min);
    cout << endl;
    dec_key(34, 30);
    printTree(H_min);
    cout << endl;
    delete_key(6);
    printTree(H_min);
    cout << endl;
    Fib_heap_extract_min();

    NODE *val = search(H_min, 25);
    if (val == NULL)
    {
        cout << "Not found" << endl;
    }
    else
    {
        cout << val->data << endl;
    }

    return 0;
}
