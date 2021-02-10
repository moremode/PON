#include "flat.h"
#include <iostream>

namespace Sage4
{
    Flat::Flat(int number, int square) 
    {
        _number = number;
        _square = square;
    }

    Flat::Flat(Resident** resident, int count, int number, int squre) : Flat(number, squre)
    {
        _resident = count <= 0 ? nullptr : resident;
        _count = count;
    }

    Flat::~Flat()
    {
        
    }

    void Flat::setResidents(Sage4::Resident** res, int count)
    {
        clearResident();
        _resident = res;
        _count = count;
    }

    int Flat::commonResidents()
    {
        int common = 0;
        for (int i = 0; i < _count; i++)
        {
            Resident* res = _resident[i];
            if (!res->getCategory())
                common++;
        }
        return common;
    }

    int Flat::concessionaryResidents()
    {
        int concessionary = 0;
        for (int i = 0; i < _count; i++)
        {
            Resident* res = _resident[i];
            if (res->getCategory())
                concessionary++;
        }
        return concessionary;
    }

    bool Flat::typeOfFlatResident()
    {
        if (!_count)
            std::runtime_error("flat is empty");
        return _resident[0]->getCategory();
    }

    void Flat::info()
    {
        std::cout << "Number: " << _number << "\n";
        std::cout << "Residents: " << _count << "\n";
        std::cout << "Square: " << _square << "\n";
        if (_count > 0)
            std::cout << "Type: " << typeOfFlatResident() << "\n";
        for (int i = 0; i < _count; i++)
        {
            Resident* res = _resident[i];
            std::cout << res->getLastname() << " " 
                << res->getInitials() << " " 
                << res->getYear() << " " 
                << res->getGender()
                << (res->getStatus() ? " + " : " - ")
                << res->getValue() << "\n";
        }
    }

    void Flat::clearResident()
    {
        if (_count > 0)
        {
            for (size_t i = 0; i < _count; i++)
            {
                delete _resident[i];
            }
            delete _resident;
            _resident = nullptr;
            _count = 0;
        }
    }
}