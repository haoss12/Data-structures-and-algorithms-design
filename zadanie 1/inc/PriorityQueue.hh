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
    bool is_empty() const {return (head == nullptr);};
    T min() const;
    T removeMin();
    void enqueue(const T & _data, const int & _priority);
};

template <typename T>
void PriorityQueue<T>::enqueue(const T & _data, const int & _priority)
{
    Node *new_node = new Node(_data, _priority, nullptr, nullptr);
    Node *temp = nullptr;   //wezel tymczasowy do poruszania sie po elementach

    if (head == nullptr)    //pierwszy element do pustej kolejki
    {
        head = new_node;   
        tail = new_node;
        Size++;
        return;
    }
    else                    //pozostale przypadki
    {
        temp = head;        //zaczynamy poszukiwania od pierwszego elementu

        while (temp != nullptr && _priority > temp->priority)
        {                       //poruszamy sie po strukturze w poszukiwaniu
            temp = temp->prev;  //miejsca do umieszczenia nowego węzła
        }                       //dopoki nie natrafimy na koniec kolejki
        
        if (temp == nullptr)    //przypadek gdy natrafimy na koniec i dodajemy
        {                       //nowy element na tyl kolejki
            tail->prev = new_node; 
            new_node->next = tail;
            new_node->prev = nullptr; //bo nie ma dalszych elementów
            tail = new_node;    //nowy element staje sie nowym "ogonem"
        }
        
    }
    Size++;
}

template <typename T>
T PriorityQueue<T>::min() const
{
    return head->data;
}