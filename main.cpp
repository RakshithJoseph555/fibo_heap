#include<iostream>
#include <cmath>
using namespace std;

typedef struct node{
    int data;
    int degree;
    struct node* parent;
    struct node* child;
    struct node* left;
    struct node* right;
    bool mark;
    
}NODE;

NODE* H_min=NULL;       //pointer to minimum element
int H_no=0;             //no. of nodes in fibonacci heaps

NODE * get_list_node(void)
{
NODE *p;

p = (NODE *) malloc (sizeof(NODE));
cout<<"enter value node to be inserted:";
cin>>p->data;
p->left=p->right=p;
//p->data = get_value();
/* *p.next = NULL */

return p;
}

/*inserting a node into fibonacii heap*/
void Fib_heap_insert(NODE* H_min,NODE* x)  //x is pointer to new node
{
    x->degree=0;
    x->parent=NULL;
    x->child=NULL;
    x->mark=false;

    if(H_min==NULL)
    H_min=x;
    else
    {
        if(x->data < H_min->data)
        {
            x->right = H_min;
            x->left = H_min->left;
            H_min->left->right = x;
            H_min->left = x;
            H_min=x;
        }
        else
        {
            x->right = H_min;
            x->left = H_min->left;
            H_min->left->right = x;
            H_min->left = x;
        }
    }           
    H_no=H_no+1;
}

//finding minimum element in fibonacci heaps
void Fib_heap_find_min(NODE* H_min)
{
    if(H_min != NULL)
        cout<<"minimum element present is:"<<H_min->data<<endl;
    else
        cout<<"no element present"<<endl;
}

//Extracting the minimum element
void Fib_heap_extract_min(NODE* H_min)
{
    NODE* z=NULL;
    z=H_min;
}


//linking same degree trees to nodes
void Fib_heap_link(NODE* y,NODE* x)
{
    y->left->right=y->right;
    y->right->left=y->left;
    y->left=y->right=y;
    y->parent=x;

    if(x->child==NULL)
        x->child=y;
    else
    {
        y->right=x->child;
        y->left=x->child->left;
        x->child->left->right=y;
        x->child->left=y;
    }
    x->degree=x->degree+1;
    y->mark=false;
}


//consolidate function
void consolidate(NODE* H_min)
{
  /*/  int temp1; 
    float temp2 = (log(H_no)) / (log(2)); 
    int temp3 = temp2; 
    NODE* arr[temp3]; 
    for(int i=0; i<temp3; i++)
        arr[i]=NULL;
    
    NODE* ptr1 = H_min;
    NODE* ptr2;
    NODE* ptr3;
    NODE* ptr4 = ptr1;
   // for (NODE* curr=H_min ; )
   do {
        ptr4 = ptr4->right;
        temp1 = ptr1->degree;
        while (arr[temp1] != NULL) {
            ptr2 = arr[temp1];
            if (ptr1->data > ptr2->data) {
                ptr3 = ptr1;
                ptr1 = ptr2;
                ptr2 = ptr3;
            }
            if (ptr2 == H_min)
                H_min = ptr1;
            Fib_heap_link(ptr2, ptr1);
            if (ptr1->right == ptr1)
                H_min = ptr1;
            arr[temp1] = NULL;
            temp1++;
        }
        arr[temp1] = ptr1;
        ptr1 = ptr1->right;
    } while (ptr1 != H_min);
    H_min=NULL;
    for (int j = 0; j <= temp3; j++) {
        if (arr[j] != NULL) {
            arr[j]->left = arr[j];
            arr[j]->right = arr[j];
            if (H_min != NULL) {
                (H_min->left)->right = arr[j];
                arr[j]->right = H_min;
                arr[j]->left = H_min->left;
                H_min->left = arr[j];
                if (arr[j]->data < H_min->data)
                    H_min = arr[j];
            }
            else {
                H_min = arr[j];
            }
            if (H_min == NULL)
                H_min = arr[j];
            else if (arr[j]->data < H_min->data)
                H_min = arr[j];
        }
    }*/
}
//int main()
//{
  //  NODE* x;
//}