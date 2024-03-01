#ifndef DOUBLYLINKEDLIST_H
#define DOUBLYLINKEDLIST_H

#include <iostream>

template <typename T>
class DoublyLinkedList
{
public:
    struct Node
    {
        T data;
        Node *prev;
        Node *next;
        Node(T val) : data(val), prev(nullptr), next(nullptr) {}
    };

    DoublyLinkedList();
    ~DoublyLinkedList();

    void push_front(const T &data);
    void push_back(const T &data);
    T pop_front();
    T pop_back();
    bool isEmpty() const;
    void clear();

private:
    Node *head;
    Node *tail;
};

template <typename T>
DoublyLinkedList<T>::DoublyLinkedList() : head(nullptr), tail(nullptr) {}

template <typename T>
DoublyLinkedList<T>::~DoublyLinkedList()
{
    clear();
}

template <typename T>
void DoublyLinkedList<T>::push_front(const T &data)
{
    Node *newNode = new Node(data);
    if (isEmpty())
    {
        head = tail = newNode;
    }
    else
    {
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }
}

template <typename T>
void DoublyLinkedList<T>::push_back(const T &data)
{
    Node *newNode = new Node(data);
    if (isEmpty())
    {
        head = tail = newNode;
    }
    else
    {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
}

template <typename T>
T DoublyLinkedList<T>::pop_front()
{
    if (isEmpty())
        throw std::runtime_error("List is empty");
    Node *temp = head;
    T data = head->data;
    head = head->next;
    if (head == nullptr)
    {
        tail = nullptr;
    }
    else
    {
        head->prev = nullptr;
    }
    delete temp;
    return data;
}

template <typename T>
T DoublyLinkedList<T>::pop_back()
{
    if (isEmpty())
        throw std::runtime_error("List is empty");
    Node *temp = tail;
    T data = tail->data;
    tail = tail->prev;
    if (tail == nullptr)
    {
        head = nullptr;
    }
    else
    {
        tail->next = nullptr;
    }
    delete temp;
    return data;
}

template <typename T>
bool DoublyLinkedList<T>::isEmpty() const
{
    return head == nullptr;
}

template <typename T>
void DoublyLinkedList<T>::clear()
{
    while (!isEmpty())
    {
        pop_front();
    }
}

#endif
