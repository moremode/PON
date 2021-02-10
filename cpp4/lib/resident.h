#include <iostream>

namespace Sage4
{
    enum Gender
    {
        Male, Female, CombatHelicopterX404
    };

    class Resident
    {
        protected:
            std::string _lastname;
            std::string _initials;
            int _year;
            Gender _gender;
            bool _status;
            bool _category;
            int _value = 0;
        public:
            Resident()
            {
                _year = 1900;
                _gender = Gender::CombatHelicopterX404;
            };
            Resident(std::string lastname, std::string initials, int year, Gender gender, bool status);
            ~Resident();
            bool setLastname(std::string);
            bool setInitials(std::string);
            bool setYear(int);
            bool setGender(Gender);
            bool setStatus(bool);
            //Resident setCategory(bool);
            std::string getLastname() const;
            std::string getInitials() const;
            int getYear() const;
            Gender getGender() const;
            bool getStatus() const;
            bool getCategory() const;
            virtual int getValue() const { return 0; };
            virtual bool setValue(int) { return false; };
    };

    class ConcessionaryResident : public Resident
    {
        public:
            ConcessionaryResident(std::string lastname, std::string initials, int year, Gender gender, bool status) : ConcessionaryResident(lastname, initials, year, gender, status, 25) {};
            ConcessionaryResident(std::string lastname, std::string initials, int year, Gender gender, bool status, int value);
            int getValue() const;
            bool setValue(int);
    };
}