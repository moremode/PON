#include "house.h"
#include <iostream>
#include <cstring>

namespace Sage4
{
    void House::setStreet(std::string street)
    {
        _street = street;
    }

    void House::setNumber(int number)
    {
        if (number <= 0)
            throw std::runtime_error("number isnt correct ( <= 0)");
        _number = number;
    }

    void House::setBuilding(int building)
    {
        if (building <= 0)
            throw std::runtime_error("building isnt correct ( <= 0)");
        _building = building;
    }

    void House::setValueMeter(int valueMeter)
    {
        if (valueMeter < 0)
            throw std::runtime_error("valueMeter isnt correct ( < 0)");
        _valueMeter = valueMeter;
    }

    void House::setValueConst(int valueConst)
    {
        if (valueConst < 0)
            throw std::runtime_error("valueConst isnt correct ( < 0)");
        _valueConst = valueConst;
    }

    House::House(std::string street, int number, int building, int valueMeter, int valueConst)
    {
        setStreet(street);
        setNumber(number);
        setBuilding(building);
        setValueMeter(valueMeter);
        setValueConst(valueConst);
        _flat = new Flat[_flatRealLen];
    }

    House::~House()
    {
        for (int i = 0; i < _flatLen; i++)
        {
            _flat[i].clearResident();
        }
        delete[] _flat;
    }

    void House::addFlat(Flat& flat)
    {
        if (_flatRealLen == _flatLen)
        {
            _flatRealLen *= 2;
            Flat* newFlat = new Flat[_flatRealLen];
            std::memcpy(newFlat, _flat, _flatRealLen * sizeof(Flat));
            delete[] _flat;
            _flat = newFlat;
        }
        int i = 0;
        for (; flat.getFlatNumber() > _flat[i].getFlatNumber() && i < _flatLen; i++) {}
        if (flat.getFlatNumber() == _flat[i].getFlatNumber())
        {
            throw std::runtime_error("contains with this number");
        }
        int part2c = _flatLen - i;
        Flat* newFlat = new Flat[_flatRealLen];
        if (i != 0)
            std::memcpy(newFlat, _flat, i * sizeof(Flat));
        if (part2c != 0)
            std::memcpy(newFlat + i + 1, _flat + i, part2c * sizeof(Flat));
        newFlat[i] = flat;
        delete[] _flat;
        _flat = newFlat;
        _flatLen++;
    }
    
    Flat& House::getFlat(int number) const
    {
        int i = 0;
        for (; number > _flat[i].getFlatNumber() && i < _flatLen; i++) {}
        if (number == _flat[i].getFlatNumber())
            return _flat[i];
        else
        {
            throw std::runtime_error("element isnt exists");
        }
    }

    Flat* House::getFlats() const
    {
        if (_flatLen)
        {
            return _flat;
        }
        else
        {
            return nullptr;
        }
        
    }

    void House::removeFlat(int number)
    {
        int i = 0;
        for (; number > _flat[i].getFlatNumber() && i < _flatLen; i++) {}
        int part2c = _flatLen - i - 1;
        if (i != _flatLen && number == _flat[i].getFlatNumber())
        {
            Flat* newFlat = new Flat[_flatRealLen];
            if (i != 0)
                std::memcpy(newFlat, _flat, i * sizeof(Flat));
            if (part2c != 0)
                std::memcpy(newFlat + i, _flat + i + 1, part2c * sizeof(Flat));
            delete[] _flat[i].getResidents();
            delete[] _flat;
            _flat = newFlat;
            _flatLen--;             
        }
        else
            throw std::runtime_error("element isnt exist");
    }

    void House::printFlats()
    {
        Flat* flats = getFlats();
        int len = getFlatsCount();
        for (int i = 0; i < len; i++)
        {
            Flat& flat = flats[i];
            flat.info();
        }
    }
}