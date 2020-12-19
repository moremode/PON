#include <iostream>
#include <cstring>
#include "Queue.h"

namespace Sage3
{
    std::istream& operator>>(std::istream& is, QueueElement& q)
    {
        std::cout << "Input int: ";
        std::cin >> q._value1;
        std::cout << "Input float: ";
        std::cin >> q._value2;
        return is;
    }

    std::ostream& operator<<(std::ostream& out, QueueElement& q)
    {
        std::cout << q._value1 << " " << q._value2;
        return out;
    }

    void isValidLen(int len, int elen = 0)
    {
        if (len < 0 || elen < 0)
            throw std::runtime_error("exception: array lengyh smaller than 0.");
        if (len < elen)
            throw std::runtime_error("exception: new array length smaller than last array length.");
    }

    void isNotNULL(QueueElement* q)
    {
        if (q == nullptr)
            throw std::runtime_error("exception: not enough memory");
    }

    QueueElement QueueElement::operator=(QueueElement q)
    {
        QueueElement ret;
        ret._value1 = q._value1;
        ret._value2 = q._value2;
        this->_value1 = q._value1;
        this->_value2 = q._value2;
        return ret;
    }

    Queue::Queue()
    {
        this->len = 0;
        this->now = 0;
        this->head = 0;
        this->empty = true;
        this->qu = nullptr;
    }

    Queue::Queue(int len)
    {
        isValidLen(len);
        this->len = len;
        this->now = 0;
        this->head = 0;
        this->empty = true;
        this->qu = new QueueElement[len];
    }

    Queue::Queue(int len, int elen, QueueElement* elms)
    {
        isValidLen(len, elen);
        this->empty = elen == 0;
        this->len = len;
        this->now = elen;
        if (elen == len)
            this->now = 0;
        this->head = 0;
        if (len)
        {
            this->qu = new QueueElement[len];
            std::memcpy(this->qu, elms, elen * sizeof(QueueElement));
        }
        else
        {
            this->qu = nullptr;
        }
    }

    Queue::Queue(const Queue& queue)
    {
        len = queue.len;
        empty = queue.empty;
        now = queue.now;
        head = queue.head;
        if (len)
        {
            qu = new QueueElement[len];
            std::memcpy(qu, queue.qu, len * sizeof(QueueElement));
        }
        else
        {
            qu = nullptr;
        } 
    }

    Queue::~Queue()
    {
        delete[] qu;
    }


    Queue Queue::operator=(Queue queue)
    {
        this->len = queue.len;
        this->empty = queue.empty;
        this->now = queue.now;
        this->head = queue.head;
        if (this->len)
        {
            this->qu = new QueueElement[this->len];
            std::memcpy(this->qu, queue.qu, this->len * sizeof(QueueElement));
        }
        else
        {
            this->qu = nullptr;
        }
        return *this;
    }

    Queue& Queue::operator+=(QueueElement el)
    {
        if (len == 0)
        {
            len = 15;
            qu = new QueueElement[len];
            isNotNULL(qu);
        }
        if (now == head && !empty)
        {
            int part2 = len - head; //start of second block
            len *= 2;
            QueueElement* ne = new QueueElement[len];
            isNotNULL(ne);
            std::memcpy(ne, qu, head * sizeof(QueueElement)); //first part of block
            std::memcpy(ne + (len - part2), qu + head, part2 * sizeof(QueueElement)); //second part of block
            head = len - part2;
            delete[] qu;
            qu = ne;
        }
        empty = false;
        qu[now] = el;
        now++;
        if (now == len)
            now = 0;
        return *this;
    }

    QueueElement Queue::operator()()
    {
        if (empty)
            throw std::runtime_error("exception: queue is empty");
        QueueElement el = qu[head];
        qu[head] = QueueElement();
        head++;
        if (head == len)
            head = 0;
        if (head == now)
            empty = true;
        return el;
    }

    std::istream& operator>>(std::istream& is, Queue& q)
    {
        QueueElement el;
        is >> el;
        q += el;
        return is;
    }

    std::ostream& operator<<(std::ostream& out, Queue& q)
    {
        QueueElement el = q();
        out << el;
        return out;
    }

    void Queue::state()
    {
        std::cout << "ARRAY LEN: " << this->len << "\nNEXT ELEMENT POSITION(FROM ZERO): " << this->now << "\nHEAD POSITION(FROM ZERO): " << this->head << "\nIS EMPTY?: " << this->empty << "\n\n";
        if (!empty)
        {
            for (int i = 0; i < len; i++)
            {
                if (head >= now)
                {
                    if (i >= head || i < now)
                    {
                        if (i == head)
                            std::cout << ">> ";
                        else
                            std::cout << "   ";
                        std::cout << i << ": " << this->qu->_value1 << " " << this->qu->_value2 << "\n";
                    }
                }
                else
                {
                    if (i >= head && i < now)
                    {
                        if (i == head)
                            std::cout << ">> ";
                        else
                            std::cout << "   ";
                        std::cout << i << ": " << this->qu->_value1 << " " << this->qu->_value2 << "\n";
                    }
                }       
            }
        }
        else
        {
            std::cout << "Empty!\n";
        }
    }
}