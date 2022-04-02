#include <iostream>

template <typename T>
class PriorityQueue {
private:

    struct Node
    {
        T data;         //dana przechowywana w węźle struktury 
        int priority;   //priorytet elementu (im mniejszy, tym ważniejszy)
        Node *prev;     //wskaźnik na poprzedni węzeł  
        Node *next;     //wskaźnik na następny węzeł

        Node(const T & _data, const int & _priority, Node *_prev, Node *_next):
        data(_data), priority(_priority), prev(_prev), next(_next) {}
    };
    Node *head;         //wskaźnik na początek kolejki
    Node *tail;         //wskaźnik na koniec kolejki
    int Size;           //liczba elementów aktualnie przechowywanych w kolejce

public:

    PriorityQueue(): head(nullptr), tail(nullptr), Size(0) {};
    int size() const {return Size;};
    T min() const;
    T removeMin();
};