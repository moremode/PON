#include <iostream>

namespace Sage3
{
    struct QueueElement
    {
        int _value1;
        float _value2;

        QueueElement operator=(QueueElement q);

        friend std::istream& operator>>(std::istream& is, QueueElement& q);
        friend std::ostream& operator<<(std::ostream& os, QueueElement& q);
    };

    class Queue
    {
        private:
            QueueElement* qu;
            int now;
            int head;
            int len;
            bool empty;
        public:
            Queue();
            Queue(int len);
            Queue(int len, int elen, QueueElement* els);
            Queue(const Queue& queue);
            ~Queue();

            friend std::istream& operator>>(std::istream& is, Queue& q);
            friend std::ostream& operator<<(std::ostream& os, Queue& q);

            Queue operator=(const Queue& q);
            Queue& operator+=(QueueElement el);
            QueueElement operator()();
            void state();
    };
}