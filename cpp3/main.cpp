#include "lib/Queue.h"
#include <typeinfo>
#include <iostream>

void printMenu()
{
    std::cout << "" << "\n";
    std::cout << "Choose action(just send me number):" << "\n";
    std::cout << "1. Add element to queue" << "\n";
    std::cout << "2. Print element from queue" << "\n";
    std::cout << "3. Print queue stats" << "\n";
    std::cout << "4. Exit" << "\n\n";
    std::cout << ">>> ";
}

void addElement(Sage3::Queue* queue)
{
    Sage3::QueueElement q; 
    std::cin >> q;
    *queue += q;
    std::cout << "Successfull!\n";
}

void printElement(Sage3::Queue* queue)
{
    std::cout << (*queue);
    std::cout << "\n";
}

void stat(Sage3::Queue* queue)
{
    queue->state();
}

void actions(Sage3::Queue* queue)
{
    int pon = 0;
    std::cin >> pon;
    switch (pon)
    {
    case 1:
        addElement(queue);
        break;
    case 2:
        printElement(queue);
        break;
    case 3:
        stat(queue);
        break;
    case 4:
        delete queue;
        std::exit(0);
        break;
    default:
        std::cout << "NEPON\n";
        break;
    }
}

int main()
{
    Sage3::Queue* q = new Sage3::Queue();
    Sage3::Queue q1 = 1;
    while (1)
    {
        printMenu();
        actions(q);
    }
}