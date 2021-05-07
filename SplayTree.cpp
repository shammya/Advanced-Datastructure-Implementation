#include <bits/stdc++.h>
using namespace std;

#define MAX 1e9

class Node
{
public:
    int key;
    Node *left;
    Node *right;
    Node *parent;
};
typedef pair<Node *, Node *> PNN;

class SplayTree
{
    Node *root;
    Node *lastnode;
    int total, diam;

    void inorder_print(Node *node)
    {
        if (node == NULL)
            return;
        inorder_print(node->left);
        cout << node->key << " ";
        inorder_print(node->right);
    }
    void preorder_print(Node *node)
    {
        if (node == NULL)
            return;
        cout << node->key << " ";
        inorder_print(node->left);
        inorder_print(node->right);
    }
    void postorder_print(Node *node)
    {
        if (node == NULL)
            return;
        inorder_print(node->left);
        inorder_print(node->right);
        cout << node->key << " ";
    }

    Node *get_parent(int val)
    {
        Node *x = root;
        Node *y = NULL;
        while (x != NULL)
        {
            y = x;
            if (x->key > val)
                x = x->left;
            else
                x = x->right;
        }
        return y;
    }

    Node *search(Node *node, int val)
    {
        if (node->key == val || node == NULL)
            return node;
        else if (node->key > val)
            return search(node->left, val);
        return search(node->right, val);
    }
    int height(Node *node)
    {
        if (node == NULL)
            return -1;
        lastnode = node;
        return max(height(node->left), height(node->right)) + 1;
    }
    int diameter(Node *node)
    {
        if (node == NULL)
            return -1;
        int l = diameter(node->left) + 1;
        int r = diameter(node->right) + 1;
        diam = max(diam, l + r);
        return diam;
    }
    Node *successor(Node *node)
    {
        if (node->left == NULL)
            return node;
        return successor(node->left);
    }
    Node *predecessor(Node *node)
    {
        if (node->right == NULL)
            return node;
        return successor(node->right);
    }
    Node *right_rotate(Node *C)
    {
        if (C != NULL || C != root)
        {
            Node *P = C->parent;
            P->left = C->right;
            if (P->left != NULL)
                (P->left)->parent = P;
            C->parent = P->parent;
            P->parent = C;
            C->right = P;
            if (C->parent == NULL)
                root = C;
        }
        return C;
    }
    Node *left_rotate(Node *C)
    {
        if (C != NULL || C != root)
        {
            Node *P = C->parent;
            P->right = C->left;
            if (P->right != NULL)
                (P->right)->parent = P;
            C->parent = P->parent;
            P->parent = C;
            C->left = P;
            if (C->parent == NULL)
                root = C;
        }
        return C;
    }
    int pattern(Node *g, Node *p, Node *c)
    {
        if (p == g->left)
        {
            if (c == p->left)
                return 1;
            return 2;
        }
        else
        {
            if (c == p->right)
                return 3;
            return 4;
        }
    }
    void splay(Node *node)
    {
        while (node != root)
        {
            if (node->parent == root)
            {
                if (node == (node->parent)->left)
                    right_rotate(node);
                else
                    left_rotate(node);
            }
            else
            {
                int pat = pattern((node->parent)->parent, node->parent, node);
                if (pat == 1)
                {
                    node = right_rotate(node);
                    right_rotate(node);
                }
                else if(pat==2)
                {
                    node = left_rotate(node);
                    right_rotate(node);
                }
                else if(pat==3)
                {
                    node = left_rotate(node);
                    left_rotate(node);
                }
                else
                {
                    node = right_rotate(node);
                    left_rotate(node);
                }
                
            }
        }
    }

public:
    SplayTree()
    {
        total = 0;
        root = NULL;
        diam = -1;
    }

    bool Find(int key)
    {
        if (search(root, key) == NULL)
            return false;
        return true;
    }

    void Insert(int val)
    {
        Node *y = get_parent(val);

        Node *node = new Node();
        node->key = val;
        node->left = NULL;
        node->right = NULL;
        node->parent = y;

        if (y == NULL)
        {
            root = node;
            return;
        }

        if (node->key < y->key)
            y->left = node;
        else
            y->right = node;
        total++;
        splay(node);
    }

    void Delete(int val)
    {
        Node *node = search(root, val);
        if (node == NULL)
            return;
        if (node->right == NULL && node->left == NULL)
        {
            if ((node->parent)->left == node)
                (node->parent)->left = NULL;
            else
                (node->parent)->right = NULL;
            return;
        }
        if (node->left == NULL)
        {
            (node->parent)->right = node->right;
            (node->right)->parent = node->parent;
            return;
        }
        if (node->right == NULL)
        {
            (node->parent)->left = node->left;
            (node->left)->parent = node->parent;
            return;
        }
        Node *sucsr = successor(node->right);

        Node *par = get_parent(sucsr->key);
        node->key = sucsr->key;
        par->left = sucsr->right;
        if ((par->left) != NULL)
            (par->left)->parent = par;
    }

    void PreorderTraversal()
    {
        cout << endl;
        preorder_print(root);
        cout << endl;
    }

    void InorderTraversal()
    {
        cout << endl;
        inorder_print(root);
        cout << endl;
    }

    void PostorderTraversal()
    {
        cout << endl;
        postorder_print(root);
        cout << endl;
    }
    void Height()
    {
        int h = height(root);
        if (h == -1)
            cout << "Tree is empty\n";
        else
            cout << "Height is = " << h << endl;
    }
    void Diameter()
    {
        int x = diameter(root);
        if (diam == -1)
            cout << "Tree is empty\n";
        else
            cout << "Diameter of the Tree is = " << diam << endl;
    }
    void TotalNodes()
    {
        cout << "Total nodes are = " << total << endl;
    }
    int Root_Value()
    {
        if(root==NULL)
            return MAX;
        return root->key;
    }
};

int main()
{
    SplayTree spt;
    spt.Insert(4);
    cout<<spt.Root_Value()<<endl;
    spt.Insert(5);
    cout<<spt.Root_Value()<<endl;
    spt.Insert(8);
    cout<<spt.Root_Value()<<endl;
    spt.Insert(6);

    cout<<spt.Root_Value()<<endl;
}
