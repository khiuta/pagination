#ifndef HELPERS_H
#define HELPERS_H
#define MAX_SIZE 100

#include <stdio.h>
#include <stdbool.h>

typedef struct
{
    int items[MAX_SIZE];
    int front;
    int rear;
} Queue;


void initializeQueue(Queue *q);
bool isEmpty(Queue *q);
bool isFull(Queue *q);
void enqueue(Queue *q, int value);
void dequeue(Queue *q);
int peek(Queue *q);
void printQueue(Queue *q);

#endif