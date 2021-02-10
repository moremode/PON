#include "lib/house.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

void hello(Sage4::House& house)
{
    std::cout << "PON house)" << "\n";
    std::cout << house.getStreet() << " " << house.getNumber() << "\n";
    std::cout << "Price on meter: " << house.getValueMeter() << "\n";
    std::cout << "Price on person: " << house.getValueConst() << "\n";
}

void printResident(Sage4::Resident& res)
{
    std::cout << res.getLastname() << " " 
                << res.getInitials() << " " 
                << res.getYear() << " " 
                << res.getGender()
                << (res.getStatus() ? " + " : " - ")
                << res.getValue() << "\n";
}

void changeResident(Sage4::Resident& resident)
{
    std::cout << "1. Set Lastname\n2. Set Initials\n3. Set year\n4. Set Gender\n5. Set Status\n" << (resident.getCategory() ? "6. Set Value" : "") << "\n>> ";
    int i;
    std::cin >> i;
    switch (i)
    {
        case 1:
            {
                std::cout << "Lastname: ";
                std::string lastname;
                std::cin >> lastname;
                resident.setLastname(lastname);
            }
            break;
        case 2:
            {
                std::cout << "Initials: ";
                std::string initials;
                std::cin >> initials;
                resident.setInitials(initials);
            }
            break;
        case 3:
            std::cout << "Year: ";
            int year;
            std::cin >> year;
            resident.setYear(year);
            break;
        case 4:
            {
                std::cout << "Gender: \n1. Male\n2. Female\n3. CombatHelicopterX404\n>> ";
                int gender;
                std::cin >> gender;
                Sage4::Gender g;
                switch (gender)
                {   
                    case 1:
                        g = Sage4::Male;
                        break;    
                    case 2:
                        g = Sage4::Female;
                        break;
                    default:
                        g = Sage4::CombatHelicopterX404;
                        break;
                }
                resident.setGender(g);
            }
            break;
        case 5:
            {
                std::cout << "Working?\n1. Yes\n2. No\n>> ";
                int work;
                std::cin >> work;
                resident.setStatus(work == 1 ? true : false);
            }
            break;
        case 6:
            {
                std::cout << "Value of concession(%): ";
                int val = 25;
                std::cin >> val;
                resident.setValue(val);
            }
            break;
        default:
            break;
    }
}

Sage4::Resident** getFlatResident(int resCount)
{
    if (resCount <= 0)
        return nullptr;
    Sage4::Resident** res = new Sage4::Resident*[resCount];
    for (int i = 0; i < resCount; i++)
    {
        std::cout << "Resident " << i + 1 << " Name: ";
        std::string name;
        std::cin >> name;
        std::cout << "Resident " << i + 1 << " Initials: ";
        std::string init;
        std::cin >> init;
        std::cout << "Resident " << i + 1 << " Birth Year: ";
        int year;
        std::cin >> year;
        std::cout << "Resident " << i + 1 << " Gender: \n1. Male\n2. Female\n3. CombatHelicopterX404\n>> ";
        int gender;
        std::cin >> gender;
        Sage4::Gender g;
        switch (gender)
        {   
            case 1:
                g = Sage4::Male;
                break;    
            case 2:
                g = Sage4::Female;
                break;
            default:
                g = Sage4::CombatHelicopterX404;
                break;
        }
        std::cout << "Is resident " << i + 1 << " working?\n1. Yes\n2. No\n>> ";
        int work;
        std::cin >> work;
        bool bWork = work == 1 ? true : false;
        std::cout << "Has concessions?\n1. Yes\n2. No\n>> ";
        int priv;
        std::cin >> priv;
        if (priv == 1)
        {
            std::cout << "Value of concession(%): ";
            int val = 25;
            std::cin >> val;
            res[i] = new Sage4::ConcessionaryResident(name, init, year, g, bWork, val);
        }
        else
        {
            res[i] = new Sage4::Resident(name, init, year, g, bWork);
        }
    }
    return res;
}

int getFlatCost(Sage4::House& house, Sage4::Flat& flat)
{
    int summ = 0;
    int count = flat.getResidentCount();
    for (size_t i = 0; i < count; i++)
    {
        Sage4::Resident& res = *(flat.getResidents()[i]);
        if (i == 0)
            summ += house.getValueMeter() * flat.getSquare() * (100 - res.getValue()) / 100;
        summ += house.getValueConst() * (100 - res.getValue()) / 100;
    }
    return summ;
}

void addFlat(Sage4::House& house)
{
    std::cout << "Flat number: ";
    int number;
    std::cin >> number;
    std::cout << "Flat square: ";
    int square;
    std::cin >> square;
    std::cout << "Resident count: ";
    int resCount;
    std::cin >> resCount;
    Sage4::Resident** res = getFlatResident(resCount);
    Sage4::Flat* flat = new Sage4::Flat(res, resCount, number, square);
    try
    {
        house.addFlat(*flat);
    }
    catch (std::exception e)
    {
        std::cout << "Error by creating flat\nTry again\n";
        flat->clearResident();
    }
    delete flat;
}

void changeFlat(Sage4::House& house)
{
    Sage4::Flat* flats = house.getFlats();
    int count = house.getFlatsCount();
    if (!count)
    {
        std::cout << "Clear\n";
        return;
    }
    std::cout << "Choose flat number: ";
    for (size_t i = 0; i < count; i++)
    {
        std::cout << flats[i].getFlatNumber() << " ";
    }
    std::cout << "\n";
    int number;
    std::cin >> number;
    int i = 0;
    while (flats[i].getFlatNumber() < i)
        i++;
    if (number != flats[i].getFlatNumber())
    {
        std::cout << "Not Found\n";
        return;
    }
    Sage4::Flat& flat = flats[i];
    flat.info();
    while (true)
    {
        std::cout << "\n1. Full Change\n2. Partial Change\n3. Clear flat\n4. Count Price\n5. Exit\n>> ";
        int x;
        std::cin >> x;
        if (x == 1)
        {
            std::cout << "Resident count: ";
            int resCount;
            std::cin >> resCount;
            Sage4::Resident** res = getFlatResident(resCount);
            flat.setResidents(res, resCount);
        }
        else if (x == 2)
        {
            if (flat.getResidentCount() > 0)
            {
                while (true)
                {
                    std::cout << "Choose resident [0-" << flat.getResidentCount() - 1 << "](smth else - exit): ";
                    int num;
                    std::cin >> num;
                    if (num >= 0 && num < flat.getResidentCount())
                    {
                        changeResident(*flat.getResidents()[num]);
                        printResident(*flat.getResidents()[num]);
                    }
                    else
                    {
                        break;
                    }
                }
            }
            else
            {
                std::cout << "Empty\n";
            }
            
        }
        else if (x == 3)
        {
            flat.setResidents(nullptr, 0);
        }
        else if (x == 4)
        {
            int summ = getFlatCost(house, flat);
            std::cout << summ << "\n";
        }
        else
        {
            break;
        }
    }
}

void menu(Sage4::House* house)
{
    while (true)
    {
        std::cout << "1. Add Flat\n2. Flat options\n3. Exit\n>> ";
        int opt;
        std::cin >> opt;
        if (opt == 1)
        {
            addFlat(*house);
        }
        else if (opt == 2)
        {
            changeFlat(*house);
        }
        else
        {
            delete house;
            std::exit(0);
        }
        std::cout << "\n";
    }
}

int main()
{
    std::srand(std::time(nullptr));
    int number = std::rand() % 100;
    int meter = std::rand() % 75;
    int one = std::rand() % 1000;
    Sage4::House* house = new Sage4::House("Sage Street", number, meter, one);
    menu(house);
}