#include <bits/stdc++.h>

using namespace std;

const int MIN = -1e9;

class Node
{
public:
    int key;
    bool color;
    Node *parent;
    list<Node *> children;
};

class FibonacciHeap
{
    list<Node *> rootlist;
    int total;

    FibonacciHeap(int key)
    {
        total = 1;
        rootlist.clear();
        Node *node = new Node();
        node->key = key;
        node->color = false;
        node->parent = NULL;
        node->children.clear();
        rootlist.push_back(node);
    }
    FibonacciHeap(Node *node)
    {
        total = node->children.size();
        rootlist.clear();
        rootlist.push_back(node);
        node->color = false;
        node->parent = NULL;
    }
    int minvalue()
    {
        return (this->rootlist).front()->key;
    }
    list<Node *> Rootlist()
    {
        return rootlist;
    }
    Node *merge(Node *a, Node *b)
    {
        if (a->key < b->key)
        {
            a->children.push_back(b);
            b->parent = a;
            return a;
        }
        b->children.push_back(a);
        a->parent = b;
        return b;
    }
    void swap(Node *a, Node *b)
    {
        Node *temp = a;
        a = b;
        b = temp;
    }
    void Print_Fibonacci_Tree(Node *node)
    {
        queue<Node *> q;
        vector<Node *> aux;
        q.push(node);
        int i = 0;
        cout << "Level " << i << " : ";
        while (!q.empty())
        {
            Node *node = q.front();
            cout << node->key;
            if (node->color)
                cout << "B ";
            else
                cout << "W ";
            for (auto it : node->children)
                aux.push_back(it);
            q.pop();
            if (q.empty())
            {
                i++;
                for (auto it : aux)
                    q.push(it);
                if (!q.empty())
                {
                    cout << endl
                         << "Level " << i << " : ";
                }
                aux.clear();
            }
        }
        cout << endl;
    }
    Node *traverseTree(Node *root, int val)
    {
        queue<Node *> q;
        vector<Node *> aux;
        q.push(root);
        while (!q.empty())
        {
            Node *node = q.front();
            if (node->key == val)
                return node;
            for (auto it : node->children)
                aux.push_back(it);
            q.pop();
            if (q.empty())
            {
                for (auto it : aux)
                    q.push(it);
                aux.clear();
            }
        }
        return NULL;
    }
    Node *find(int val)
    {
        for (auto it : rootlist)
        {
            Node *node = traverseTree(it, val);
            if (node != NULL)
                return node;
        }
        return NULL;
    }

public:
    FibonacciHeap()
    {
        total = 0;
        rootlist.clear();
    }
    void Union(FibonacciHeap fh)
    {
        /*if (this->rootlist.empty())
        {
            for (auto it : fh.rootlist)
            {
                this->rootlist.push_back(it);
            }
            return;
        }
        if (this->minvalue() > fh.minvalue())
        {
            for (auto it : this->rootlist)
            {
                fh.rootlist.push_back(it);
            }
            this->rootlist.clear();
        }
        for (auto it : fh.rootlist)
        {
            this->rootlist.push_back(it);
        }*/
        for (auto it : fh.rootlist)
        {
            if (this->rootlist.empty())
                this->rootlist.push_back(it);
            else if (it->key < this->rootlist.front()->key)
                this->rootlist.push_front(it);
            else
                this->rootlist.push_back(it);
        }

        this->total += fh.total;
    }

    void Insert(int val)
    {
        FibonacciHeap fh(val);
        this->Union(fh);
        //cout << "insert done\n";
    }

    void ExtractMin()
    {
        if (this->rootlist.empty())
            return;
        Node *minnode = this->rootlist.front();
        for (auto it : minnode->children)
        {
            this->rootlist.push_back(it);
        }
        this->rootlist.pop_front();
        vector<Node *> order(100, NULL);
        for (auto it : this->rootlist)
        {
            int idx = it->children.size();
            if (order[idx] == NULL)
                order[idx] = it;
            else
            {
                Node *temp = merge(it, order[idx]);
                order[idx] = NULL;
                ++idx;
                while (order[idx] != NULL)
                {
                    temp = merge(temp, order[idx]);
                    order[idx] = NULL;
                    ++idx;
                }
                order[idx] = temp;
            }
        }
        this->rootlist.clear();
        /* minnode = NULL;
        for (int i = 0; i < 100; i++)
        {
            if (order[i] != NULL)
                this->rootlist.push_back(order[i]);
        }
        minnode = this->rootlist.front();

        for (auto it : this->rootlist)
        {
            if (it != this->rootlist.front())
            {
                if (it->key < minnode->key)
                    minnode = it;
            }
        }
        swap(minnode, this->rootlist.front());
        */
        int mini = 1e9;
        for (int i = 0; i < 100; i++)
        {
            if (order[i] != NULL)
            {
                if (order[i]->key < mini)
                {
                    mini = order[i]->key;
                    this->rootlist.push_front(order[i]);
                }
                else
                    this->rootlist.push_back(order[i]);
            }
        }
    }
    void PrintHeap()
    {
        cout << "Printing Fibonacci Heap ... \n";
        for (auto it : rootlist)
        {
            cout << "Fibonacci Tree , F" << it->children.size() << endl;
            Print_Fibonacci_Tree(it);
        }
    }
    void FindMin()
    {
        if (rootlist.empty())
        {
            cout << "The Heap is Empty \n";
            return;
        }
        cout << "Minimum element is = " << rootlist.front()->key << endl;
    }
    void Delete(int val)
    {
        if (this->DecreaseKey(val, MIN))
            this->ExtractMin();
    }
    Node *cut(Node *node)
    {
        Node *par = node->parent;
        FibonacciHeap fh(node);
        for (auto it = par->children.begin(); it != par->children.end(); it++)
        {
            if (*it == node)
            {
                par->children.erase(it);
                break;
            }
        }
        this->Union(fh);
        return par;
    }
    bool DecreaseKey(int val1, int val2)
    {
        Node *node = find(val1);
        if (node == NULL)
        {
            cout << "Key does not exist !" << endl;
            return false;
        }
        node->key = val2;
        if (node->parent == NULL)
        {
            if(rootlist.front()->key > node->key)
            {
                for (auto it = rootlist.begin(); it != rootlist.end();it++)
                {
                    if(*it ==node)
                    {
                        rootlist.erase(it);
                        break;
                    }
                }
            }
            rootlist.push_front(node);
            return true; 
        }
          
        if (node->parent->key <= node->key)
            return true;
        //node->parent = NULL;
        Node *temp = cut(node);
        while (temp->parent != NULL)
        {
            if (temp->color == false)
            {
                temp->color = true;
                break;
            }
            else
            {
                temp = cut(temp);
            }
        }
        return true;
    }
};

int main()
{
    FibonacciHeap fh;
    fh.Insert(4);
    fh.Insert(3);
    fh.Insert(2);
    fh.Insert(7);
    fh.Insert(5);
    fh.Insert(6);
    //fh.DecreaseKey(4, 1);
    fh.Delete(5);
    fh.FindMin();
    fh.PrintHeap();
}