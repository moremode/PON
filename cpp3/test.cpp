#include "lib/Queue.h"
#include <ctime>
#include <cstdlib>
#include <gtest/gtest.h>
#include <iostream>

TEST(QueueElement, create)
{
    Sage3::QueueElement el;
    el._value1 = 17;
    el._value2 = 0.73;
    float err = 0.0001;
    EXPECT_EQ(17, el._value1);
    EXPECT_NEAR(0.73, el._value2, err);
    Sage3::QueueElement el_copy;
    el_copy = el;
    EXPECT_EQ(17, el_copy._value1);
    EXPECT_NEAR(0.73, el_copy._value2, err);
}

TEST(Queue, create)
{
    Sage3::QueueElement el;
    el._value1 = 17;
    el._value2 = 0.73;
    Sage3::QueueElement el1;
    el1._value1 = 18;
    el1._value2 = 0.1;
    EXPECT_ANY_THROW({
        Sage3::Queue queue1(-1);
    });
    EXPECT_NO_THROW({
        Sage3::Queue queue1(1);
        queue1 += el;
        queue1();
    });
    EXPECT_NO_THROW({
        Sage3::Queue queue1;
        queue1 += el;
        queue1();
    });
    EXPECT_NO_THROW({
        Sage3::Queue queue1;
        queue1 += el;
        Sage3::Queue queue2(queue1);
        queue2 += el1;
        queue2();
        queue2();
    });
    EXPECT_NO_THROW({
        Sage3::QueueElement* qu = new Sage3::QueueElement[2];
        qu[0] = el;
        qu[1] = el1;
        Sage3::Queue queue1(2, 2, qu);
    });
    Sage3::Queue queue1;
    queue1 += el;
    Sage3::Queue queue2(queue1);
    queue2 += el1;
    EXPECT_EQ(17, queue2()._value1);
    EXPECT_EQ(18, queue2()._value1);
    Sage3::QueueElement* qu = new Sage3::QueueElement[2];
    qu[0] = el;
    qu[1] = el1;
    Sage3::Queue queue3(2, 2, qu);
    EXPECT_EQ(17, queue3()._value1);
    EXPECT_EQ(18, queue3()._value1);
}

TEST(Queue, add)
{
    std::srand(std::time(nullptr));
    Sage3::QueueElement el;
    el._value1 = 17;
    el._value2 = 0.73;
    Sage3::QueueElement el1;
    el1._value1 = 18;
    el1._value2 = 0.1;
    Sage3::QueueElement* qu = new Sage3::QueueElement[2];
    qu[0] = el;
    qu[1] = el1;
    Sage3::Queue queue1(2, 2, qu);
    int* pon = new int[100];
    EXPECT_EQ(17, queue1()._value1);
    EXPECT_EQ(18, queue1()._value1);
    for (size_t i = 0; i < 100; i++)
    {
        int x = std::rand() % 100;
        el1._value1 = x;
        pon[i] = x;
        el1._value2 = (float)(std::rand() % 10000) / 100;
        queue1 += el1;
    }
    for (size_t i = 0; i < 100; i++)
    {
        EXPECT_EQ(pon[i], queue1()._value1);
    }  
    EXPECT_ANY_THROW({
        queue1();
    });
}

TEST(Queue, assignment)
{
    std::srand(std::time(nullptr));
    Sage3::QueueElement el;
    el._value1 = -17;
    el._value2 = 0.73;
    Sage3::QueueElement el1;
    el1._value1 = 18;
    el1._value2 = 0.1;
    Sage3::QueueElement* qu = new Sage3::QueueElement[2];
    qu[0] = el;
    qu[1] = el1;
    Sage3::Queue queue1(2, 2, qu);
    int* pon = new int[100];
    EXPECT_EQ(-17, queue1()._value1);
    EXPECT_EQ(18, queue1()._value1);
    for (size_t i = 0; i < 100; i++)
    {
        int x = std::rand() % 100;
        el1._value1 = x;
        pon[i] = x;
        el1._value2 = (float)(std::rand() % 10000) / 100;
        queue1 += el1;
    }
    Sage3::Queue queue2;
    queue2 = queue1;
    for (size_t i = 0; i < 100; i++)
    {
        EXPECT_EQ(pon[i], queue2()._value1);
    }
}

int main()
{
    testing::InitGoogleTest();
    int x = RUN_ALL_TESTS();
    std::cout << "RESULT: " << x << "\n";
}