#include "queue.h"

#include <iostream>

Queue::Queue(){
    length = 0;
    head = 0;
    tail = 0;
    SetSize(5);
}

void Queue::SetSize(int newSize){
    void** temp = new void*[newSize];

    int tempL = length;
    if(length != 0){
        for (int i = 0; i < tempL; i++)
            temp[i] = Extract();

        delete[] queue;
    }

    queue = temp;
    length = tempL;
    if(length != 0)
        tail = length - 1;
    else
        tail = 0;
    size = newSize;
}

void Queue::EnQueue(void* elemPtr) {

    if(length == size)
        SetSize(size + 5);

    if(length == 0)
        queue[head] = elemPtr;
    else{
        if(tail + 1 == size)
            tail = 0;
        else
            tail++;
        queue[tail] = elemPtr;
    }
    length++;
}

void* Queue::Extract() {
    void* elemPtr = 0;
    if (length > 0) {
        --length;
        elemPtr = queue[head];
        queue[head] = 0;
        if(length == 0){
            head = 0;
            tail = 0;
        }
        else if(head + 1 == size)
            head = 0;
        else
            head++;
    }
    return elemPtr;
}

bool Queue::IsEmpty(){
    return length == 0;
}
int Queue::getLength() const
{
    return length;
}


