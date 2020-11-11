/*
Author :
    Name : Kazi Wasif Amin Shammya
    Institution : Bangladesh University of Engineering and Technology
    check the text file assigned to understand the how the function works 
*/

#include <bits/stdc++.h>
using namespace std;

const int MAX = 1e9;

class Node
{
public:
    int key;
    list<Node *> children;
};

class BinomialHeap
{
    vector<Node *> rootlist;
    int max_order;

    BinomialHeap(Node *node)
    {
        int order = node->children.size();
        max_order = order;
        rootlist = vector<Node *>(100, NULL);
        rootlist[order] = node;
    }
    // merge two nodes
    Node *merge(Node *a, Node *b)
    {
        if (a->key < b->key)
        {
            a->children.push_back(b);
            return a;
        }
        else
        {
            b->children.push_back(a);
            return b;
        }
    }
    //inserting a new node
    /*void insert_node(Node *node)
    {

        int i = 0;
        while (node != NULL)
        {

            if (rootlist[i] == NULL)
            {
                rootlist[i] = node;
                node = NULL;
            }
            else
            {
                node = merge(rootlist[i], node);
                rootlist[i] = NULL;
                i++;
            }

            max_order = max(i, max_order);
        }
    }*/

    int min_index()
    {
        int minkey = MAX, idx = -1;
        for (int i = 0; i <= max_order; i++)
        {
            if (rootlist[i] != NULL)
            {
                if (minkey > rootlist[i]->key)
                {
                    minkey = rootlist[i]->key;
                    idx = i;
                }
            }
        }
        return idx;
    }
    BinomialHeap create_binomial_heap(Node *node)
    {
        BinomialHeap bh(node);
        return bh;
    }
    Node *RootList(int idx)
    {
        return rootlist[idx];
    }
    int Max_Order()
    {
        return max_order;
    }
    void Print_Binomial_Tree(Node *node)
    {
        queue<Node *> q;
        vector<Node *> aux;
        q.push(node);
        int i = 0;
        cout << "Level " << i << " : ";
        while (!q.empty())
        {
            Node *node = q.front();
            cout << node->key << " ";
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
                    cout <<endl<< "Level " << i << " : ";
                }
                aux.clear();
            }
        }
        cout << endl;
    }

public:
    BinomialHeap()
    {
        rootlist = vector<Node *>(100, NULL);
        max_order = -1;
        //cout << "ok\n";
    }

    int Find_Min()
    {
        int idx = min_index();
        if (idx == -1)
        {
            cout << "Empty Heap\n";
            return MAX;
        }
        return rootlist[idx]->key;
    }

    void Insert(int val)
    {
        Node *node = new Node;
        node->key = val;
        BinomialHeap bh = create_binomial_heap(node);
        this->Union(bh);
        //insert_node(node);
        //cout << "ok\n";
    }

    void Union(BinomialHeap &bh)
    {
        Node *carry = NULL;
        int i, j;
        for (i = 0, j = 0; i <= max_order || j <= bh.Max_Order(); i++, j++)
        {
            max_order = max(i, max_order);
            if (this->rootlist[i] != NULL || bh.RootList(j) != NULL)
            {
                if (carry != NULL)
                {
                    if (this->rootlist[i] == NULL)
                        carry = merge(carry, bh.RootList(j));
                    else if (bh.rootlist[j] == NULL)
                    {
                        carry = merge(carry, this->rootlist[i]);
                        this->rootlist[i] = NULL;
                    }
                    else
                        carry = merge(carry, bh.RootList(j));
                }
                else
                {
                    if (this->rootlist[i] == NULL)
                        this->rootlist[i] = bh.RootList(j);
                    else if (bh.rootlist[j] == NULL)
                    {
                    }
                    else
                    {
                        carry = merge(this->rootlist[i], bh.RootList(j));
                        this->rootlist[i] = NULL;
                    }
                }
            }
            else
            {
                if (carry != NULL)
                {
                    this->rootlist[i] = carry;
                    carry = NULL;
                }
            }
        }
        if (carry != NULL)
        {
            max_order++;
            this->rootlist[i] = carry;
            carry = NULL;
        }
    }

    void Extract_Min()
    {
        int idx = min_index();
        if (idx == -1)
        {
            cout << "Empty Heap\n";
            return;
        }
        vector<Node *> aux;
        for (auto it : rootlist[idx]->children)
            aux.push_back(it);

        rootlist[idx] = NULL;

        for (auto it : aux)
        {
            BinomialHeap bh = create_binomial_heap(it);
            this->Union(bh);
        }
    }

    void PrintHeap()
    {
        cout << "Printing Binomial Heap ... \n";
        for (int i = 0; i <= max_order; i++)
        {
            if (rootlist[i] != NULL)
            {
                cout << "Binomial Tree , B" << i << endl;
                Print_Binomial_Tree(rootlist[i]);
            }
        }
    }
};

int main()
{
    BinomialHeap bh, bh1;
    bh.Insert(5);
    bh.Insert(2);
    bh.Insert(10);
    bh.Extract_Min();
    bh1.Insert(3);
    bh1.Insert(20);
    bh.Union(bh1);
    //bh.Extract_Min();

    bh.PrintHeap();
}
