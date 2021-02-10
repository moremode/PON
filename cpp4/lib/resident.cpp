#include "resident.h"
#include <iostream>

namespace Sage4
{
    bool Resident::setLastname(std::string lastname)
    {
        _lastname = lastname;
        return true;
    }

    bool Resident::setInitials(std::string initials)
    {
        _initials = initials;
        return true;
    }

    bool Resident::setYear(int year)
    {
        this->_year = year;
        return true;
    }

    bool Resident::setGender(Gender gender)
    {
        this->_gender = gender;
        return true;
    }

    bool Resident::setStatus(bool status)
    {
        this->_status = status;
        return true;
    }

    std::string Resident::getLastname() const
    {
        return this->_lastname;
    }

    std::string Resident::getInitials() const
    {
        return this->_initials;
    }

    int Resident::getYear() const
    {
        return this->_year;
    }

    Gender Resident::getGender() const
    {
        return this->_gender;
    }

    bool Resident::getStatus() const
    {
        return this->_status;
    }

    bool Resident::getCategory() const
    {
        return _category;
    }

    Resident::Resident(std::string lastname, std::string initials, int year, Gender gender, bool status)
    {
        if (!(setLastname(lastname) && setInitials(initials) && setYear(year) && setGender(gender) && setStatus(status)))
        {
            throw std::runtime_error("Error by creating resident");
        }
        _category = false;
    }

    Resident::~Resident()
    {
        
    }

    bool ConcessionaryResident::setValue(int value)
    {
        if (value > 100)
            value = 100;
        if (value < 0)
            value = 0;
        _value = value;
        return true;
    }

    int ConcessionaryResident::getValue() const
    {
        return _value;
    }

    ConcessionaryResident::ConcessionaryResident(std::string lastname, std::string initials, int year, Gender gender, bool status, int value) : Resident(lastname, initials, year, gender, status)
    {
        _category = true;
        _value = value;
    }
}