#include <iostream>
#include "DescFolium.h"

namespace Sage
{
    DescFolium::DescFolium(float n)
    {
        this->n = n;
    }

    DescFolium& DescFolium::setN(float n)
    {
        this->n = n;
        return *this;
    }

    float getFloat()
    {
        float number = 0;
        std::cin >> number;
        if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(2147483647, '\n');
        }
        return number;
    }

    int getInt()
    {
        int number = 0;
        std::cin >> number;
        if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(2147483647, '\n');
        }
        return number;
    }
}