#include <bits/stdc++.h>
#include <stdlib.h>
#include<fstream>
using namespace std;

#define ll long long

//**********************************************************************
// Node Structure
//**********************************************************************
struct node
{
    ll data;
    struct node *left;
    struct node *right;
};

//**********************************************************************
// Splay tree class contains all methods
//**********************************************************************
class splaytree
{
  public:
    struct node *base = NULL;  // work as root node of whole tree

    //**********************************************************************
    // Create New node and return it
    //**********************************************************************
    struct node *getnewnode(ll key)
    {
        struct node *newnode = (struct node *)malloc(sizeof(struct node));
        newnode->left = NULL;
        newnode->right = NULL;
        newnode->data = key;
        return newnode;
    }

    //**********************************************************************
    // Perform Left Rotation
    //**********************************************************************
    struct node *leftrotate(struct node *root)
    {
        struct node *rightchild = root->right;
        root->right = rightchild->left;
        rightchild->left = root;
        return rightchild;
    }

    //**********************************************************************
    // Perform Right Rotation
    //**********************************************************************
    struct node *rightrotate(struct node *root)
    {
        struct node *leftchild = root->left;
        root->left = leftchild->right;
        leftchild->right = root;
        return leftchild;
    }

    //**********************************************************************
    // 
    //**********************************************************************
    struct node *dosplay(struct node *root, ll key)
    {
        if (root == NULL)
            return root;
        //key found in tree
        else if (root->data == key)
            return root;
        else
        {
            if (root->data < key)
            {
                if (root->right == NULL)
                    return root;
                //RR(zag-zag) case --> required to perfrom Left - left rotation
                else if (root->right->data < key)
                {
                    root->right->right = dosplay(root->right->right, key);
                    root = leftrotate(root); //do left rotation from root
                }
                //RL (zag-zig) case --> required to perfrom right - left rotation
                else if (root->right->data > key)
                {
                    root->right->left = dosplay(root->right->left, key);
                    if (root->right->left != NULL)
                    {
                        root->right = rightrotate(root->right);
                    }
                }

                if (root->right == NULL)
                {
                    return root;
                }
                else
                {
                    root = leftrotate(root);
                    return root;
                }
            }
            else
            {
                if (root->left == NULL)
                    return root;
               //LL(zig-zig) case --> required to perfrom right - right rotation
                else if (root->left->data > key)
                {
                    root->left->left = dosplay(root->left->left, key);
                    root = rightrotate(root); //do right rotation from root
                }
                //LR (zig-zag) case --> required to perfrom left - right rotation
                else if (root->left->data < key)
                {
                    root->left->right = dosplay(root->left->right, key);
                    if (root->left->right != NULL)
                    {
                        root->left = leftrotate(root->left);
                    }
                }

                if (root->left == NULL)
                {
                    return root;
                }
                else
                {
                    root = rightrotate(root);
                    return root;
                }
            }
        }
    }

    //**********************************************************************
    // Function to insert key into splay tree
    //**********************************************************************
    void insertnode(ll key)
    {
        //when first node inserted into the tree (base is NULL)
        if (base == NULL)
        {
            base = getnewnode(key);
            return;
        }

        base = dosplay(base, key);

        //if key already present in tree
        if (base->data == key)
        {
            //cout << "Already exist key !!!" << endl;
            return;
        }
        else if (base->data < key)
        {
            struct node *newnode = getnewnode(key);
            newnode->left = base;
            newnode->right = base->right;
            base->right = NULL;
            base = newnode;
            return;
        }
        else
        {
            struct node *newnode = getnewnode(key);
            newnode->right = base;
            newnode->left = base->left;
            base->left = NULL;
            base = newnode;
            return;
        }
    }

    //**********************************************************************
    // return corrent position of node to be deleted
    //**********************************************************************
    struct node *deletehelper(struct node *root, ll key)
    {
        //when only single node in tree needs to deletes
        if (root->left == NULL && root->right == NULL)
        {
            return NULL;
        }
        //when node has right child only
        else if (root->left == NULL)
        {
            return root->right;
        }
        //when node has left child only
        else if (root->right == NULL)
        {
            return root->left;
        }
        //when node has both child present, 
        //find inorder successor of root node and make it as root and
        //make previous root's left child as current root's left child.
        else
        {
            struct node *tmp = dosplay(root->right, key);
            tmp->left = base->left;
            return tmp;
        }
    }

    //**********************************************************************
    // function to delete node from splay tree
    //**********************************************************************
    ll deletenode(ll key)
    {
        if (base == NULL)
            return false;
        base = dosplay(base, key);
        if (base->data == key)
        {
            struct node *temp = deletehelper(base, key);
            free(base);
            base=temp;
            return true;
        }
        return false;
    }

    //**********************************************************************
    // function to search key from splay tree.
    //**********************************************************************
    bool search(ll key)
    {
        if (base == NULL)
            return false;
        base = dosplay(base, key);
        if (base->data == key)
            return true;
        return false;
    }

    //**********************************************************************
    // print preorder traversal of splay tree.
    //**********************************************************************
    void preOrder(struct node *root)
    {
        if (root != NULL)
        {
            printf("%lld ", root->data);
            preOrder(root->left);
            preOrder(root->right);
        }
    }

    //**********************************************************************
    // print inorder traversal of splay tree.
    //**********************************************************************

    void inorder(struct node *root)
    {
        if (root != NULL)
        {
            inorder(root->left);
            //cout<<root->data<<endl;
		    ofstream fptr1;
		    fptr1.open("test_inorder_splay.txt",ios::app);
            fptr1<<root->data<<endl;
            fptr1.close();
            inorder(root->right);
        }
    }

    //**********************************************************************
    // print level-order traversal of splay tree.
    //**********************************************************************
    void levelOrder(node *root)
    {
        if(root==NULL)
            return;
        queue<node *> q;
        q.push(root);
        while (!q.empty())
        {
            node *x = q.front();
            q.pop();

            cout << x->data << " ";

            if ((x->left) != NULL)
                q.push(x->left);

            if ((x->right) != NULL)
                q.push(x->right);
        }
    }
};

int main()
{
    splaytree sp;
    ll choice, num;
    ll query;
    cin>>query;
    ofstream fptr11,fptr12;
    fptr11.open("test_search_splay.txt",ios::out);
    fptr12.open("test_delete_splay.txt",ios::out);
    clock_t start, end;
    double cpu_time_used;
    start = clock();
    while (query--)
    {
        // cout << "\n1.insert";
        // cout << "\n2.delete";
        // cout << "\n3.search";
        // cout << "\n4.Inorder";
        // cout << "\nEnter your choice : ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            //cout << "\nEnter number you want to insert : ";
            cin >> num;
            sp.insertnode(num);
            break;
        case 2:
            //cout << "\nEnter number you want to delete : ";
            cin >> num;
            fptr12<<sp.deletenode(num)<<endl;
            // if (sp.deletenode(num))
            //     cout << "\nElement deleted successfully :) ";
            // else
            //     cout << "\nElement not found :( ";
            break;
        case 3:
            //cout << "\nEnter number you want to search : ";
            cin>>num;
            fptr11<<to_string(sp.search(num))<<endl;

            // if (sp.search(num))
            //     cout << "\nElement found :) ";
            // else
            //     cout << "\nElement not found :( ";
            break;
        case 4:
            // cout << "\nLevel order : ";
            // sp.levelOrder(sp.base);
            // cout << "\nPreoder : ";
            // sp.preOrder(sp.base);
        	sp.inorder(sp.base);
            break;
        }
    }
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    cout<<cpu_time_used*1000;
    fptr11.close();
    fptr12.close();
    return 0;
}