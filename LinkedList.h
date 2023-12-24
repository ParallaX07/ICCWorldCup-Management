#include <bits/stdc++.h>

using namespace std;
template <class T>
class Node
{
public:
    T data;
    Node *next;
    Node *prev;

    Node(T data) : data(data), next(NULL), prev(NULL) {}
};


template <class T>
class LinkedList
{
private:
    int size;

public:
    Node<T> *head;
    Node<T> *tail;

    LinkedList()
    {
        head = NULL;
        tail = NULL;
    }

    // Adds node
    void insertNode(T data)
    {
        Node<T> *temp = new Node<T>(data);
        // check if list empty
        Node<T> *temp2 = head;
        if (head == NULL)
        {
            head = temp;
            tail = temp;
        }
        else
        { // Insert node at tail
            tail->next = temp;
            temp->prev = tail;
            tail = temp;
        }
        tail->next = NULL;
    }
};
