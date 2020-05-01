#ifndef STACK_H
#define STACK_H 

template <typename T> 
class Stack
{

    struct Item
    {
        T   value;
        Item* next;
        Item(T value, Item* next) {
            this->value = value;
            this->next = next;
        }
    };

    public:
        Stack();
        void push(T value);
        void pop();
        bool empty();
        T top();
        
    private:
        Item* head;
};

#endif