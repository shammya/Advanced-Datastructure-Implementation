#include <bits/stdc++.h>

using namespace std;

#define BLACK 0
#define RED 1

class Node
{
public:
    int key;
    Node *parent;
    Node *left;
    Node *right;
    int color;
};
typedef Node *NodeType;

class Red_Black_Tree
{
    NodeType root;
    NodeType NIL;

    NodeType Search(NodeType node, int val)
    {
        if (node->key == val || node == NIL)
            return node;
        else if (node->key > val)
            return Search(node->left, val);
        return Search(node->right, val);
    }
    void preorder(NodeType node)
    {
        if (node != NIL)
        {
            if (node != root)
                cout << "(";
            cout << node->key << ":";
            if (node->color == RED)
                cout << "r";
            else
                cout << "b";
            if (node->left == NIL && node->right != NIL)
                cout << "()";
            preorder(node->left);
            if (node->right == NIL && node->left != NIL)
                cout << "()";
            preorder(node->right);
            if (node != root)
                cout << ")";
        }
    }
    void leftRotate(NodeType x)
    {
        NodeType y = x->right;
        x->right = y->left;
        if (y->left != NIL)
        {
            y->left->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == NIL)
        {
            this->root = y;
        }
        else if (x == x->parent->left)
        {
            x->parent->left = y;
        }
        else
        {
            x->parent->right = y;
        }
        y->left = x;
        x->parent = y;
    }

    void rightRotate(NodeType x)
    {
        NodeType y = x->left;
        x->left = y->right;
        if (y->right != NIL)
        {
            y->right->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == NIL)
        {
            this->root = y;
        }
        else if (x == x->parent->right)
        {
            x->parent->right = y;
        }
        else
        {
            x->parent->left = y;
        }
        y->right = x;
        x->parent = y;
    }
    void fixInsert(NodeType k)
    {
        NodeType u;
        while (k->parent->color == RED)
        {
            if (k->parent == k->parent->parent->right)
            {
                u = k->parent->parent->left;
                if (u->color == RED)
                {

                    u->color = BLACK;
                    k->parent->color = BLACK;
                    k->parent->parent->color = RED;
                    k = k->parent->parent;
                }
                else
                {
                    if (k == k->parent->left)
                    {

                        k = k->parent;
                        rightRotate(k);
                    }

                    k->parent->color = BLACK;
                    k->parent->parent->color = RED;
                    leftRotate(k->parent->parent);
                }
            }
            else
            {
                u = k->parent->parent->right;

                if (u->color == RED)
                {

                    u->color = BLACK;
                    k->parent->color = BLACK;
                    k->parent->parent->color = RED;
                    k = k->parent->parent;
                }
                else
                {
                    if (k == k->parent->right)
                    {

                        k = k->parent;
                        leftRotate(k);
                    }

                    k->parent->color = BLACK;
                    k->parent->parent->color = RED;
                    rightRotate(k->parent->parent);
                }
            }
            if (k == root)
            {
                break;
            }
        }
        root->color = BLACK;
    }
    void fixDelete(NodeType x)
    {
        NodeType s;
        while (x != root && x->color == BLACK)
        {
            if (x == x->parent->left)
            {
                s = x->parent->right;
                if (s->color == RED)
                {
                    s->color = BLACK;
                    x->parent->color = RED;
                    leftRotate(x->parent);
                    s = x->parent->right;
                }
                if (s->left->color == BLACK && s->right->color == BLACK)
                {
                    s->color = RED;
                    x = x->parent;
                }
                else
                {
                    if (s->right->color == BLACK)
                    {
                        s->left->color = BLACK;
                        s->color = RED;
                        rightRotate(s);
                        s = x->parent->right;
                    }
                    s->color = x->parent->color;
                    x->parent->color = BLACK;
                    s->right->color = BLACK;
                    leftRotate(x->parent);
                    x = root;
                }
            }
            else
            {
                s = x->parent->left;
                if (s->color == RED)
                {
                    s->color = BLACK;
                    x->parent->color = RED;
                    rightRotate(x->parent);
                    s = x->parent->left;
                }

                if (s->right->color == BLACK && s->right->color == BLACK)
                {
                    s->color = RED;
                    x = x->parent;
                }
                else
                {
                    if (s->left->color == BLACK)
                    {
                        s->right->color = BLACK;
                        s->color = RED;
                        leftRotate(s);
                        s = x->parent->left;
                    }
                    s->color = x->parent->color;
                    x->parent->color = BLACK;
                    s->left->color = BLACK;
                    rightRotate(x->parent);
                    x = root;
                }
            }
        }
        x->color = BLACK;
    }
    void deleteNode(NodeType node, int key)
    {

        NodeType z = NIL;
        NodeType x, y;
        while (node != NIL)
        {
            if (node->key == key)
            {
                z = node;
            }

            if (node->key <= key)
            {
                node = node->right;
            }
            else
            {
                node = node->left;
            }
        }

        if (z == NIL)
        {
            cout << "Couldn't find key in the tree" << endl;
            return;
        }

        y = z;
        int y_original_color = y->color;
        if (z->left == NIL)
        {
            x = z->right;
            rbTransplant(z, z->right);
        }
        else if (z->right == NIL)
        {
            x = z->left;
            rbTransplant(z, z->left);
        }
        else
        {
            y = minimum(z->right);
            y_original_color = y->color;
            x = y->right;
            if (y->parent == z)
            {
                x->parent = y;
            }
            else
            {
                rbTransplant(y, y->right);
                y->right = z->right;
                y->right->parent = y;
            }

            rbTransplant(z, y);
            y->left = z->left;
            y->left->parent = y;
            y->color = z->color;
        }
        delete z;
        if (y_original_color == 0)
        {
            fixDelete(x);
        }
    }
    NodeType minimum(NodeType node)
    {
        if (node->left == NIL)
            return node;
        return minimum(node->left);
    }
    void rbTransplant(NodeType u, NodeType v)
    {
        if (u->parent == NIL)
        {
            root = v;
        }
        else if (u == u->parent->left)
        {
            u->parent->left = v;
        }
        else
        {
            u->parent->right = v;
        }
        v->parent = u->parent;
    }

public:
    Red_Black_Tree()
    {
        NIL = new Node;
        NIL->color = BLACK;
        NIL->left = NULL;
        NIL->right = NULL;
        root = NIL;
    }
    bool Find(int val)
    {
        if (Search(root, val) != NIL)
            return true;
        return false;
    }
    void Insert(int val)
    {
        NodeType x = root;
        NodeType y = NIL;
        while (x != NIL)
        {
            y = x;
            if (x->key > val)
                x = x->left;
            else
                x = x->right;
        }
        NodeType node = new Node;
        node->key = val;
        node->left = NIL;
        node->right = NIL;
        node->parent = y;
        node->color = RED;
        if (y == NIL)
        {
            node->color = BLACK, root = node;
            return;
        }

        if (node->key < y->key)
            y->left = node;
        else
            y->right = node;
        fixInsert(node);
    }

    void Delete(int x)
    {
        deleteNode(root, x);
    }
    void Preorder()
    {
        preorder(root);
    }
};

int main()
{
    freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
    Red_Black_Tree rb;

    while (!feof(stdin))
    {
        char ch;
        int n;
        cin >> ch >> n;
        if (ch == 'F')
        {
            if (rb.Find(n))
                cout << "True" ;
            else
                cout << "False" ;
        }
        if (ch == 'I')
        {
            rb.Insert(n);
            rb.Preorder();
        }
        if (ch == 'D')
        {
            rb.Delete(n);
            rb.Preorder();
        }
        cout << endl;
    }

    return 0;
}