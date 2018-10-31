#include <bits/stdc++.h>
#include <stdlib.h>
#include <fstream>
using namespace std;

#define ll long long
bool found = false;
//**********************************************************************
// Node Structure
//**********************************************************************
struct node
{

    ll data;
    struct node *left;
    struct node *right;
    ll bf;
    ll height;
    ll tcount;
};

//**********************************************************************
// Height =Max Distance from leaf node OR Max height of its subtree
// Bf = balance factor
// tcount =  Maintain total count of node including itself
//**********************************************************************

//**********************************************************************
// create empty node with given Data
//**********************************************************************
struct node *getnode(ll x)
{
    struct node *temp = (struct node *)malloc(sizeof(struct node));
    temp->data = x;
    temp->left = NULL;
    temp->right = NULL;
    temp->height = -1;
    temp->bf = 0;
    temp->tcount = 1;
    return temp;
}

//**********************************************************************
// return height of Perticular node
//**********************************************************************
ll getheight(node *root)
{
    if (root == NULL)
        return -1;
    else
        return root->height;
}

//**********************************************************************
// Set Height of perticular node from its child
//**********************************************************************
ll setHeight(node *root)
{
    if (root == NULL)
    {
        return -1;
    }
    else
    {
        return (1 + max(getheight(root->left), getheight(root->right)));
    }
}

//**********************************************************************
// return tcount of Perticular node
//**********************************************************************
ll getCount(node *root)
{
    if (root == NULL)
        return 0;
    else
        return root->tcount;
}

//**********************************************************************
// Set tcount of perticular node from its child's tcount
//**********************************************************************
ll setCount(node *root)
{

    if (root == NULL)
    {
        return 0;
    }
    else
    {
        return (1 + getCount(root->left) + getCount(root->right));
    }
}

//**********************************************************************
// Calculate balance factor of perticular Node
//**********************************************************************
ll setbalancefactor(node *root)
{
    return (getheight(root->left) - getheight(root->right));
}

//**********************************************************************
// Search perticular element from tree == Log(n)
//**********************************************************************
bool searchElement(node *root, ll x)
{
    if (root == NULL)
        return false;
    else
    {
        if (root->data == x)
        {
            return true;
        }
        else if (root->data > x)
        {
            return searchElement(root->left, x);
        }
        else if (root->data < x)
        {
            return searchElement(root->right, x);
        }
    }
    return false;
}

//**********************************************************************
// Update/Recalculate height , Bf and tcount of tree after rotation
//**********************************************************************
void updateHeightAndBf(node *root)
{
    root->height = setHeight(root);
    root->bf = setbalancefactor(root);
    root->tcount = setCount(root);
}

//**********************************************************************
// Rotate sub-tree to left side OR move wighter right part to left
//**********************************************************************
node *leftRotation(node *root)
{
    node *rightchild = root->right;
    root->right = rightchild->left;
    rightchild->left = root;
    updateHeightAndBf(root);
    updateHeightAndBf(rightchild);
    return rightchild;
}

//**********************************************************************
// Rotate sub-tree to right side OR move wighter left part to right
//**********************************************************************
node *rightRotation(node *root)
{
    node *leftchild = root->left;
    root->left = leftchild->right;
    leftchild->right = root;
    updateHeightAndBf(root);
    updateHeightAndBf(leftchild);
    return leftchild;
}

//**********************************************************************
// Find Which Rotation required for balancing
//**********************************************************************
node *balancetree(node *root)
{
    //cout<<"balancetree called for  : "<<root->data;
    ll rootbf = root->bf;
    if (rootbf == 2)
    {
        ll rootleftbf = (root->left)->bf;
        if (rootleftbf >= 0)
        {
            //cout<<"LL rotation"<<endl;
            return rightRotation(root);
        }
        else
        {

            //cout<<"LR rotaion";
            root->left = leftRotation(root->left);
            return rightRotation(root);
        }
    }
    else if (rootbf == -2)
    {
        ll rootrightbf = (root->right)->bf;
        if (rootrightbf <= 0)
        {
            //cout<<"RR rotation"<<endl;
            return leftRotation(root);
        }
        else
        {

            //cout<<"RL rotation"<<endl;
            root->right = rightRotation(root->right);
            return leftRotation(root);
        }
    }

    return root;
}

//**********************************************************************
// Return inorder successor of node
//**********************************************************************
struct node *getInordersuccessor(struct node *root)
{
    struct node *temp1 = root;
    while (temp1->left != NULL)
        temp1 = temp1->left;

    return temp1;
}

//**********************************************************************
// Delete specific Node from tree
//**********************************************************************
struct node *deleteSpecificNode(struct node *root, ll data)
{
    node *cur;
    if (root == NULL)
    {
        return root;
    }
    if (data < root->data)
    {
        cur = deleteSpecificNode(root->left, data);
        root->left = cur;
    }
    else if (data > root->data)
    {
        cur = deleteSpecificNode(root->right, data);
        root->right = cur;
    }
    // Element found in tree
    else
    {
        found = true;
        //leaf node to be deleted
        if (root->left == NULL && root->right == NULL)
        {
            root = NULL;
            //return root;
        }
        // if it has only one side tree
        else if (root->left == NULL || root->right == NULL)
        {
            if (root->left != NULL)
                root = root->left;
            else
                root = root->right;
        }
        //node have both side tree
        else
        {
            struct node *node1 = getInordersuccessor(root->right);
            root->data = node1->data;
            root->right = deleteSpecificNode(root->right, node1->data);
        }
    }
    if (root == NULL)
        return root;
    root->height = setHeight(root);
    root->bf = setbalancefactor(root);
    root->tcount = setCount(root);
    return balancetree(root);
}

//**********************************************************************
// Insert node into tree
//**********************************************************************
struct node *insert(struct node *root, ll data)
{
    //cout<<"Node to be inserted : "<<data<<endl;
    if (root == NULL)
    {
        node *temp = getnode(data);
        temp->height = setHeight(temp);
        temp->tcount = setCount(temp);
        temp->bf = setbalancefactor(temp);
        //printf("\nfirst insertion data : %lld, height : %lld , bf : %lld ",temp->data,temp->height,temp->bf);
        return temp;
    }
    else
    {

        node *cur;
        if (data < root->data)
        {
            cur = insert(root->left, data);
            root->left = cur;
        }
        else if (data > root->data)
        {
            cur = insert(root->right, data);
            root->right = cur;
        }
        else
        {
            return root;
        }
        root->height = setHeight(root);
        root->bf = setbalancefactor(root);
        root->tcount = setCount(root);
        //printf("\n*****Node : %lld  height : %lld  Bf : %lld ",root->data,root->height,root->bf);
        return balancetree(root);

        //return root;
    }
}

//**********************************************************************
// Print inorder of tree along with its data, height, bf and tcount
//**********************************************************************
void inorder(node *root)
{
    if (root != NULL)
    {
        inorder(root->left);
        //cout<<root->data<<endl;
        ofstream fptr1;
        fptr1.open("test_inorder_avl.txt", ios::app);
        fptr1 << root->data << endl;
        fptr1.close();
        inorder(root->right);
    }
}

//**********************************************************************
// Find Nth smallest Element from tree === O(Height of tree)
//**********************************************************************
ll getNSmallestElement(node *root, ll k)
{

    ll totalleftchild = getCount(root->left);

    if (totalleftchild + 1 == k)
    { // +1 for rootNode itself
        return root->data;
    }
    else if (totalleftchild + 1 >= k)
    {
        return getNSmallestElement(root->left, k);
    }
    else
    {
        return getNSmallestElement(root->right, k - (totalleftchild + 1));
    }

    // NOT EFFICIENT METHOD, TAKES TIME O(n)
    // if(root!=NULL)
    // {
    //     getNSmallestElement(root->left);

    //     nsmallest--;
    //     //printf("\nNode : %lld  height : %lld  Bf : %lld ",root->data,root->height,root->bf);
    //     if(nsmallest==0)
    //     {
    //         //cout<<"\nRoot->data"<<root->data;
    //         smallestAns = (root->data);
    //     }

    //     getNSmallestElement(root->right);
    // }
}

//**********************************************************************
// Main Method , Program starts from Here...!!!
//**********************************************************************
int main()
{
    ll total, query, choice, num;
    struct node *root = NULL;
    cin >> query;
    ofstream fptr11, fptr12;
    fptr11.open("test_search_avl.txt", ios::out);
    fptr12.open("test_delete_avl.txt", ios::out);
    while (query--)
    {
        cin >> choice;
        switch (choice)
        {
        case 1:
            cin >> num;
            root = insert(root, num);
            break;
        case 2:
            cin >> num;
            found = false;
            root = deleteSpecificNode(root, num);
            fptr12 << to_string(found) << endl;
            break;
        case 3:
            cin >> num;
            fptr11 << to_string(searchElement(root, num)) << endl;
            break;
        case 4:
            inorder(root);
            break;
        }
    }
    fptr11.close();
    fptr12.close();
    return 0;
}