#ifndef QUEUE_H
#define QUEUE_H

class Queue
{
public:
    Queue();
    ~Queue(){
        delete [] queue;
    }

    void EnQueue(void* elemPtr);
    void* Extract();
    bool IsEmpty();
    int getLength() const;

private:
    void** queue; // Puntero a un arreglo de punteros a void
    int head; // Cabeza de la cola
    int tail; //Cola de la cola
    int size; //Tamagno fisico de la cola
    int length; // Número de elementos en la cola
    void SetSize (int newSize);
};

#endif // QUEUE_H
